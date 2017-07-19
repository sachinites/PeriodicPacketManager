#ifndef __PPM__H__
#define __PPM__H__

#include "../ppm_client/ppm_pkt_enums.h"
#include "../common_str.h"
#include "../ppm_client/ppm_client.h"
#include "../libs/WheelTimer.h"


typedef void (*emit_fn_t)(char *, unsigned int, unsigned int *, unsigned int);


typedef struct LL ll_t;

typedef struct oif_sent_stats_per_proto{
	ppm_outbound_pkt_id_t pkt_id;
	unsigned int sent_stats;
} if_sent_stats_per_proto_t;

typedef struct oif_recv_stats_per_proto{
	ppm_outbound_pkt_id_t pkt_id;
	unsigned int recv_stats;
} if_recv_stats_per_proto_t;

typedef struct ppm_in_out_if{
	mac_addr_t src_mac;
	mac_addr_t dst_mac;
	ipv4_addr src_ip;
	char ifname[PPM_IF_NAME_SIZE];
	unsigned int ifindex;
	if_sent_stats_per_proto_t sent_stats[PPM_MAX_PKT_ID];
	if_recv_stats_per_proto_t recv_stats[PPM_MAX_PKT_ID];
	unsigned int ref_count;
} ppm_in_out_if_t;

typedef struct oif_info_t_{
	unsigned int ifindex;
	wheel_timer_elem_t *wt_elem;
} oif_info_t;

typedef struct ppm_outbound_rule{
	bool_t is_active;	/*Disable Or enable this rule*/
	ppm_outbound_pkt_id_t pkt_id;
	char *pkt;		/*Pointer to pkt buffer*/
	unsigned int pkt_size;  /* Size of the packet*/
	pkt_display_fn_t pkt_display_fn;
	unsigned int time_interval;	/*Time interval in seconds*/
	bool_t is_periodic;
	emit_fn_t emit_fn;
	unsigned int ppm_cumulative_out_sent_stats;
	ll_t *oif_list;	/*list of oif_info_t structures*/
} ppm_outbound_rule_t;

#define GET_OIF_COUNT(rule_ptr)(GET_NODE_COUNT_SINGLY_LL(rule_ptr->oif_list))

#define ACTIVATE_RULE(rule_ptr)	(rule_ptr->is_active = 1)

#define DE_ACTIVATE_RULE(rule_ptr)	(rule_ptr->is_active = 0)
#define IS_RULE_ACTIVE(rule_ptr)	(rule_ptr->is_active == 1)

#define GET_PROTO_RULE(proto_db_ptr, pkt_id)	\
		(&proto_db_ptr->ppm_proto_outbound_rule_list[pkt_id])

#define GET_PPM_OUTBOUND_DB_LIST	(ppm_outb_gl_db->ppm_outbound_protocol_db_list)

#define PPM_ADD_NEW_OUTBOUND_PROTOCOL_DB(proto_db)	\
		singly_ll_add_node_by_val(ppm_outb_gl_db->ppm_outbound_protocol_db_list, proto_db);

#define PPM_INIT_NEW_OIF_LIST	(init_singly_ll())

/*This macro assumes that ifindex is unsigned int size only*/
#define PPM_ADD_IFINDEX_TO_OIF_LIST(rule_ptr, data_ptr)	\
		(singly_ll_add_node_by_val(rule_ptr->oif_list, data_ptr))	

/*ppm per protocol databse*/
typedef struct ppm_outbound_protocol_db{
	char proto[PPM_MAX_PROTO_NAME_SIZE];
	ppm_outbound_pkt_id_t protocol_max_pkt_id;
	ppm_outbound_rule_t *ppm_proto_outbound_rule_list; /*key is pkt id*/
} ppm_outbound_protocol_db_t;


/*ppm global database*/

typedef wheel_timer_t	ppm_scheduler_t;

typedef struct ppm_outbound_gl_db{
	ll_t *ppm_outbound_protocol_db_list; /*key is protocol name*/
	ppm_scheduler_t *scheduler;
} ppm_outbound_gl_db_t;

void
ppm_init(const char LCNO);


void
ppm_add_new_outbound_protocol_db(const char *proto_name, ppm_outbound_pkt_id_t pkt_max_id);

/*return 0 on success, 1 on failure*/
bool_t
ppm_add_outbound_rule(const char *proto_name, ppm_outbound_rule_t *outbound_rule);

/*return 0 on success, 1 on failure*/
bool_t
ppm_remove_outbound_rule(const char *proto_name, ppm_outbound_pkt_id_t pkt_id);

/*return 0 on success, 1 on failure*/
bool_t
ppm_update_outbound_rule(const char *proto_name, ppm_outbound_rule_t *outbound_new_rule);

ppm_outbound_protocol_db_t *
ppm_is_proto_registered(const char * proto_name);

ppm_outbound_rule_t *
ppm_is_outbound_pkt_registered(const char * proto_name, 
		      const ppm_outbound_pkt_id_t pkt_id, 
		      ppm_outbound_protocol_db_t **proto_db);

void
ppm_free_outbound_rule(ppm_outbound_rule_t *rule);

void
ppm_dump_outbound_db();

void
ppm_dump_outbound_rule(const ppm_outbound_rule_t *rule);

void
ppm_dump_in_out_intf(const ppm_in_out_if_t *intf);

#endif
