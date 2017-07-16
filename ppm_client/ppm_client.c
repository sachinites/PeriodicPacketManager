#include "ppm_client.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

extern unsigned int 
ppm_client_send_msg_to_ppm(const char *msg, unsigned int msg_size);

void
ppm_init_client_lib(){
	ppm_client_init_lc_ppm_reachability_info();
	ppm_client_init_socket();
}


void
ppm_create_outbound_protocol_db(const char *proto_name,
		ppm_outbound_pkt_id_t pkt_max_id){

	ppm_input_struct_t *ppm_input_struct_info = NULL;

	ppm_msg_hdr_t *ppm_msg_hdr = calloc(1, sizeof(ppm_msg_hdr_t) + 
					sizeof(ppm_input_struct_t));

	ppm_input_struct_info = (ppm_input_struct_t *)(ppm_msg_hdr + 1);

	ppm_msg_hdr->ppm_msg_type = PPM_ADD_PROTOCOL;
	ppm_input_struct_info->pkt_id = pkt_max_id;
	strncpy(ppm_input_struct_info->proto_name, proto_name, PPM_MAX_PROTO_NAME_SIZE -1);
	ppm_input_struct_info->proto_name[PPM_MAX_PROTO_NAME_SIZE -1] = '\0';

	ppm_client_send_msg_to_ppm((char *)ppm_msg_hdr, sizeof(ppm_msg_hdr_t) + sizeof(ppm_input_struct_t));	
	free(ppm_msg_hdr);
}

ppm_input_struct_t *
ppm_get_new_ppm_input_structure(const ppm_outbound_pkt_id_t pkt_id,
                            const char *proto_name,
                            const unsigned short pkt_size,
                            const char *pkt,
                            const unsigned int time_interval,
                            const char is_periodic,
                            const unsigned int egress_intf_cnt,
                            const unsigned int *ifindex_array){

	unsigned int i = 0;

	if(pkt_size > MTU_SIZE){
		printf("%s() : Error : Attempt to send pkt larger than MTU size. Proto : %s, pkt_id : %s\n", 
				__FUNCTION__, proto_name, ppm_get_str_enum(pkt_id));
		assert(0);
	}

	ppm_input_struct_t *ppm_input_struct_info = calloc(1, sizeof(ppm_input_struct_t) + pkt_size + 
							      (egress_intf_cnt * sizeof(unsigned int)));

	ppm_input_struct_info->pkt_id = pkt_id;
	strncpy(ppm_input_struct_info->proto_name, proto_name, strlen(proto_name));
	ppm_input_struct_info->proto_name[strlen(proto_name)] = '\0';

	ppm_input_struct_info->pkt_size = pkt_size;

	memcpy(ppm_input_struct_info->pkt, pkt, pkt_size);
	ppm_input_struct_info->time_interval = time_interval;
	ppm_input_struct_info->is_periodic = is_periodic;
	
	ppm_input_struct_info->egress_intf_cnt = egress_intf_cnt;

	for(; i < egress_intf_cnt; i++){
		ppm_input_struct_info->ifindex_array[i] = *(ifindex_array + i);
	}
	return ppm_input_struct_info;
}


ppm_update_egress_intf_t *
ppm_get_new_ppm_update_egress_intf_structure(const ppm_outbound_pkt_id_t pkt_id,
                                             const char *proto_name,
                                             const unsigned int egress_intf_cnt,
					     const unsigned int *ifindex_array
					     ){

        unsigned int i = 0;
	ppm_update_egress_intf_t *ppm_update_egress_intf_info = calloc(1, sizeof(ppm_update_egress_intf_t) + 
									  (egress_intf_cnt * sizeof(unsigned int)));

	ppm_update_egress_intf_info->pkt_id = pkt_id;
	strncpy(ppm_update_egress_intf_info->proto_name, proto_name, strlen(proto_name));
	ppm_update_egress_intf_info->proto_name[strlen(proto_name)] = '\0';

	ppm_update_egress_intf_info->egress_intf_cnt = egress_intf_cnt;

	
	for(; i < egress_intf_cnt; i++){
		ppm_update_egress_intf_info->ifindex_array[i] = *(ifindex_array + i);
	}

	return ppm_update_egress_intf_info;
}


void
ppm_update_egress_interface(ppm_update_egress_intf_t *ppm_update_egress_intf_info){


}


void
ppm_update_time_interval(const ppm_outbound_pkt_id_t pkt_id,
                         const char *proto_name, const unsigned int new_time_interval){

}

void
ppm_disable_periodicity(const ppm_outbound_pkt_id_t pkt_id, const char *proto_name, 
						PIM_PKT_PERIODICITY periodicity){

}

void
ppm_update_packet_buffer(const ppm_outbound_pkt_id_t pkt_id, const char *proto_name,
			 char *pkt_buffer, unsigned int pkt_size){

}

void
ppm_install_new_outbound_rule(ppm_input_struct_t *ppm_input_struct_info){
	
	if(!ppm_input_struct_info) return;
	unsigned int rc = 0;

	unsigned int msg_size = sizeof(ppm_msg_hdr_t) + sizeof(ppm_input_struct_t) +
				(ppm_input_struct_info->egress_intf_cnt*sizeof(ppm_input_struct_info->ifindex_array[0]));

	ppm_msg_hdr_t *ppm_install_msg = 
			calloc(1, msg_size);

	if(!ppm_install_msg) {
		printf("%s() : Memory allocation failed\n", __FUNCTION__);
		return;
	}

	ppm_install_msg->ppm_msg_type = PPM_INSTALL_NEW_RULE;
	memcpy(ppm_install_msg + 1, ppm_input_struct_info, msg_size - sizeof(ppm_msg_hdr_t));
	
	rc = ppm_client_send_msg_to_ppm((char *)ppm_install_msg, msg_size);	
	printf("%s() : %u bytes sent to ppm\n", __FUNCTION__, msg_size);
	free(ppm_install_msg); 
}

void
ppm_uninstall_outbound_rule(const ppm_outbound_pkt_id_t pkt_id, const char *proto_name){

}
