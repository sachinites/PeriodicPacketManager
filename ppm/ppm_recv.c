#include "ppm.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

extern char LC_NO;
ppm_outbound_rule_t*
ppm_get_new_outbound_rule(const ppm_input_struct_t *ppm_input_struct_info);


void
ppm_process_aplication_msg(char *msg, unsigned int msg_size){

	if(!msg || !msg_size)
		return;

	ppm_msg_hdr_t *ppm_client_msg = (ppm_msg_hdr_t *)msg;
	
	switch(ppm_client_msg->ppm_msg_type){
		case PPM_ADD_PROTOCOL:
		{
			ppm_input_struct_t *ppm_input_struct_info = 
						(ppm_input_struct_t *)(ppm_client_msg + 1);

			ppm_add_new_outbound_protocol_db(ppm_input_struct_info->proto_name, 
							 ppm_input_struct_info->pkt_id);
		}
		break;
		case PPM_INSTALL_NEW_RULE:
		{
			ppm_outbound_rule_t *ppm_new_rule = NULL;

			ppm_input_struct_t *ppm_input_struct_info =
					(ppm_input_struct_t *)(ppm_client_msg + 1);
			
			ppm_outbound_protocol_db_t *_proto_db = NULL, 
						   *ppm_outbound_protocol_db = NULL;

			ppm_outbound_protocol_db = 
					ppm_is_proto_registered(ppm_input_struct_info->proto_name);

			if(!ppm_outbound_protocol_db){
				printf("%s() : FATAL : protocol %s Not instantiated in PPM\n", 
						__FUNCTION__, ppm_input_struct_info->proto_name);
				return;
			}

			ppm_new_rule = ppm_is_outbound_pkt_registered(ppm_input_struct_info->proto_name,
								      ppm_input_struct_info->pkt_id, 
								      &_proto_db);

			assert(_proto_db == ppm_outbound_protocol_db);

			if(ppm_new_rule){
				printf("%s() : Error : Rule already registered in protocol : %s, for pkt_id : %s\n",
						__FUNCTION__, ppm_input_struct_info->proto_name, 
						ppm_get_str_enum(ppm_input_struct_info->pkt_id));
				return;
			}	
		
			/*Sanity checks has been passed, now install the rule in PPM*/

			ppm_new_rule = ppm_get_new_outbound_rule(ppm_input_struct_info);

			/*Let us Activate the rule, if not required, it has to deactivated explicitely*/
			ACTIVATE_RULE(ppm_new_rule);

			if(!ppm_new_rule){
				printf("%s() : New Outbound Rule memory allocation failed\n", __FUNCTION__);
				return;
				
			}

			if(!ppm_add_outbound_rule(ppm_input_struct_info->proto_name, ppm_new_rule)){
				printf("%s() : PPM failed to install new rule, proto  = %s, pkt_id = %s\n",
						__FUNCTION__, ppm_input_struct_info->proto_name,
						ppm_get_str_enum(ppm_input_struct_info->pkt_id));
				ppm_free_outbound_rule(ppm_new_rule);
				ppm_new_rule = NULL;
				return;
			}
			
			printf("%s() : New outbound rule for proto  = %s, pkt_id = %s Installed\n",
					__FUNCTION__, ppm_input_struct_info->proto_name,
					ppm_get_str_enum(ppm_input_struct_info->pkt_id));
		}
		break;
		case PPM_REMOVE_PROTOCOL:
		case PPM_DISABLE_PROTOCOL:
		case PPM_ADD_NEW_EGREE_INTF:
		case PPM_REMOVE_EDRESS_INTF:
		case PPM_UPDATE_TIME_INTERVAL:
		case PPM_UPDATE_PERIODICITY:
		case PPM_UPDATE_PKT_BUFFER:
		default:
			printf("%s() : Error : Unknown msg recieved by PPM on LC# %d", __FUNCTION__, LC_NO);
			break;
	}
}
