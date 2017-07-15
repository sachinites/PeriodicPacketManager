#ifndef __PPM__CLIENT_H__
#define __PPM__CLIENT_H__

#include "ppm_pkt_enums.h"
#include "../common_str.h"

typedef void (*pkt_display_fn_t)(char *, unsigned int);

/*PPM Input Structure*/
typedef enum{
	PPM_INSTALL_NEW_RULE,
	PPM_REMOVE_PROTOCOL,
	PPM_DISABLE_PROTOCOL,
	PPM_ADD_NEW_EGREE_INTF,
	PPM_REMOVE_EDRESS_INTF,
	PPM_UPDATE_TIME_INTERVAL,
	PPM_UPDATE_PERIODICITY,
	PPM_UPDATE_PKT_BUFFER	
} PPM_INPUT_MSG_TYPE;/*Msgs from PPM client to PPM daemon*/

typedef struct ppm_msg_hdr{
	PPM_INPUT_MSG_TYPE ppm_msg_type;
} ppm_msg_hdr_t;

typedef struct _ppm_input_struct{
	ppm_outbound_pkt_id_t pkt_id;
	char proto_name[PPM_MAX_PROTO_NAME_SIZE];
	unsigned short pkt_size;	/*Size of the pkt*/
	char pkt[MTU_SIZE];			/*Pkt buffer*/
	unsigned int time_interval;
	char is_periodic;
	unsigned int egress_intf_cnt;
	unsigned int ifindex_array[0];
} ppm_input_struct_t;


ppm_input_struct_t *
ppm_get_new_ppm_input_structure(const ppm_outbound_pkt_id_t pkt_id,
			    const char *proto_name,
			    const unsigned short pkt_size,
			    const char *pkt,
			    const unsigned int time_interval,
			    const char is_periodic,
			    const unsigned int egress_intf_cnt,
			    const unsigned int *ifindex_array);

typedef struct _ppm_update_egress_intf{
	char proto_name[PPM_MAX_PROTO_NAME_SIZE];
	ppm_outbound_pkt_id_t pkt_id;
	char add_or_delete;
	unsigned int egress_intf_cnt;
	unsigned int ifindex_array[0];
} ppm_update_egress_intf_t;

ppm_update_egress_intf_t *
ppm_get_new_ppm_update_egress_intf_structure(const ppm_outbound_pkt_id_t pkt_id,
					     const char *proto_name,
					     const unsigned int egress_intf_cnt,
					     const unsigned int *ifindex_array
					     );

void
ppm_update_egress_interface(ppm_update_egress_intf_t *ppm_update_egress_intf_info);

void
ppm_update_time_interval(const ppm_outbound_pkt_id_t pkt_id,
			 const char *proto_name, const unsigned int new_time_interval);

void
ppm_disable_periodicity(const ppm_outbound_pkt_id_t pkt_id,
			const char *proto_name, PIM_PKT_PERIODICITY periodicity);

void
ppm_update_packet_buffer(const ppm_outbound_pkt_id_t pkt_id, const char *proto_name, 
			  char *pkt_buffer, unsigned int pkt_size);

void
ppm_install_new_outbound_rule(ppm_input_struct_t *ppm_input_struct_info);

void
ppm_uninstall_outbound_rule(const ppm_outbound_pkt_id_t pkt_id, const char *proto_name);

#endif
