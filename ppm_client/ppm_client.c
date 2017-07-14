#include "ppm_client.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

}

void
ppm_uninstall_outbound_rule(const ppm_outbound_pkt_id_t pkt_id, const char *proto_name){

}