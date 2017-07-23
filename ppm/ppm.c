#include "ppm.h"
#include <assert.h>
#include <stdlib.h>
#include "../libs/LinkedListApi.h"
#include <stdio.h>
#include <string.h>
#include "ppm_sched.h"
#include "ppm_emitter.h"

ppm_outbound_gl_db_t* ppm_outb_gl_db;
extern void ppm_client_init_lc_ppm_reachability_info();
extern void ppm_client_init_socket();

#define PPM_THREAD_POOL_SIZE	10

ppm_outbound_rule_t*
ppm_get_new_outbound_rule(const ppm_input_struct_t *ppm_input_struct_info){
	
	unsigned int egress_intf_cnt = 0;
	oif_info_t *oif = NULL;

	if(ppm_input_struct_info->pkt_size >= MTU_SIZE){
		printf("%s() : Warning : Exceeding MTU size, pkt size = %u\n", 
				__FUNCTION__, ppm_input_struct_info->pkt_size);
		return;
	}

	ppm_outbound_rule_t *new_out_rule = calloc(1, sizeof(ppm_outbound_rule_t));
	
	new_out_rule->is_active = FALSE;
	new_out_rule->pkt_id = ppm_input_struct_info->pkt_id;
	new_out_rule->pkt = calloc(1, ppm_input_struct_info->pkt_size);
	memcpy(new_out_rule->pkt, ppm_input_struct_info->pkt, ppm_input_struct_info->pkt_size);
	new_out_rule->pkt_size = ppm_input_struct_info->pkt_size;
	new_out_rule->pkt_display_fn = NULL; /*TBD*/
	new_out_rule->time_interval = ppm_input_struct_info->time_interval;
	new_out_rule->is_periodic = ppm_input_struct_info->is_periodic;
	
	new_out_rule->emit_fn = NULL;
	new_out_rule->oif_list = PPM_INIT_NEW_OIF_LIST;
	for(; egress_intf_cnt < ppm_input_struct_info->egress_intf_cnt; 
		egress_intf_cnt++){
		
		oif = calloc(1, sizeof(oif_info_t));	
		oif->ifindex = ppm_input_struct_info->ifindex_array[egress_intf_cnt];
		oif->wt_elem = NULL; /*Will be created on instllation of Rule into Scheduler*/
		PPM_ADD_IFINDEX_TO_OIF_LIST(new_out_rule, (void *)oif);
	}
	
	return new_out_rule;
}

extern void
ppm_setup_sockets(const char LC_NO);


extern blocked_pool_t gl_blocked_th_pool;

static void
ppm_init_thread_lib(){
	init_blocked_pool(&gl_blocked_th_pool, PPM_THREAD_POOL_SIZE);	

}

void
ppm_init(const char LC_NO){
	static char only_once = 0;
	assert(!only_once);
	only_once = 1;
	ppm_outb_gl_db = calloc(1,sizeof(ppm_outbound_gl_db_t));
	ppm_outb_gl_db->ppm_outbound_protocol_db_list = init_singly_ll();	
	ppm_client_init_lc_ppm_reachability_info();
	ppm_init_thread_lib();
	ppm_setup_sockets(LC_NO);
	ppm_setup_scheduler();
	ppm_scheduler_start();
}

ppm_outbound_protocol_db_t *
ppm_is_proto_registered(const char * proto_name){
	
	assert(ppm_outb_gl_db);
	return (ppm_outbound_protocol_db_t *)singly_ll_lookup_by_key(GET_PPM_OUTBOUND_DB_LIST,
				       proto_name, strlen(proto_name), 
				       (unsigned int)&((ppm_outbound_protocol_db_t *)0)->proto);
}

ppm_outbound_rule_t *
ppm_is_outbound_pkt_registered(const char * proto_name, 
		      const ppm_outbound_pkt_id_t pkt_id, 
		      ppm_outbound_protocol_db_t **proto_db){

	assert(ppm_outb_gl_db);
	ppm_outbound_rule_t *pkt_out_rule = NULL;
	ppm_outbound_protocol_db_t *_proto_db = NULL;

	if(!(_proto_db = ppm_is_proto_registered(proto_name)))
		return NULL;
	
	*proto_db = _proto_db;
	if(pkt_id >= (_proto_db)->protocol_max_pkt_id)
		return NULL;
	
	pkt_out_rule = &((_proto_db)->ppm_proto_outbound_rule_list[pkt_id]);	

	if(IS_RULE_ACTIVE(pkt_out_rule))
		return pkt_out_rule;

	return NULL;
}

void
ppm_add_new_outbound_protocol_db(const char *proto_name, ppm_outbound_pkt_id_t pkt_max_id){

	assert(ppm_outb_gl_db);

	if(ppm_is_proto_registered(proto_name)){
		printf("Error : %s() db for protocol : %s already instantiated\n", __FUNCTION__, proto_name);
		return;
	}	
	ppm_outbound_protocol_db_t *proto_db = calloc(1,sizeof(ppm_outbound_protocol_db_t));
	strncpy(proto_db->proto, proto_name, PPM_MAX_PROTO_NAME_SIZE -1);
	proto_db->proto[PPM_MAX_PROTO_NAME_SIZE -1] = '\0';
	proto_db->protocol_max_pkt_id = pkt_max_id;
	proto_db->ppm_proto_outbound_rule_list = calloc(pkt_max_id, sizeof(ppm_outbound_rule_t));
	PPM_ADD_NEW_OUTBOUND_PROTOCOL_DB(proto_db);
}

bool_t
ppm_add_outbound_rule(const char *proto_name, ppm_outbound_rule_t *outbound_rule){

	assert(ppm_outb_gl_db);
	ppm_outbound_protocol_db_t *proto_db = NULL;

	if(ppm_is_outbound_pkt_registered(proto_name, outbound_rule->pkt_id, &proto_db)){
		printf("%s() : Error : Attempt to add a duplicate rule for protocol : %s, pkt_id : %s\n",
			 __FUNCTION__, proto_name, ppm_get_str_enum(outbound_rule->pkt_id));
		return FALSE;
	}

	memcpy(GET_PROTO_RULE(proto_db, outbound_rule->pkt_id), outbound_rule, sizeof(ppm_outbound_rule_t));
	return TRUE;
}



void
ppm_free_outbound_rule(ppm_outbound_rule_t *rule){
	/*Need to be re-written*/
#if 0
	free(rule->pkt);
	delete_singly_ll(rule->oif_list);
	free(rule->oif_list);
	memset(rule, 0 , sizeof(ppm_outbound_rule_t));
#endif
}

#if 0
static void
ppm_free_outbound_rule(ppm_outbound_rule_t *rule){

	free(rule->pkt);
	ll_t *oif_list = rule->oif_list;

	unsigned int i = 0, node_count = 0;
	singly_ll_node_t *head = NULL, *next = NULL;
	ppm_in_out_if_t *intf = NULL;

	head =  GET_HEAD_SINGLY_LL(oif_list);
	node_count = GET_NODE_COUNT_SINGLY_LL(oif_list);

	for(; i < node_count; i++){
		next = GET_NEXT_NODE_SINGLY_LL(head);
		intf = (ppm_in_out_if_t *)head->data;
		if(intf->ref_count > 1){
			intf->ref_count--;
			head = next;
			continue;
		}

		free(intf);
		singly_ll_remove_node(oif_list, head);
		free(head);
		head = next;		
	}

	delete_singly_ll(rule->oif_list);
	free(rule->oif_list);
	memset(rule, 0 , sizeof(ppm_outbound_rule_t));
}
#endif

bool_t
ppm_remove_outbound_rule(const char *proto_name, ppm_outbound_pkt_id_t pkt_id){

	assert(ppm_outb_gl_db);
	ppm_outbound_protocol_db_t *proto_db = NULL;
	ppm_outbound_rule_t *pkt_out_rule = NULL;

	if(!(pkt_out_rule = ppm_is_outbound_pkt_registered(proto_name, pkt_id, &proto_db))){
		printf("%s() : Warning :  Attempt to remove non existing rule for protocol : %s, pkt_id : %s",
			 __FUNCTION__, proto_name, ppm_get_str_enum(pkt_id));
		return TRUE;
	}
	
	ppm_free_outbound_rule(pkt_out_rule);
	return TRUE;
}

bool_t
ppm_update_outbound_rule(const char *proto_name, ppm_outbound_rule_t *outbound_new_rule){

	assert(ppm_outb_gl_db);
	ppm_outbound_protocol_db_t *proto_db = NULL;
	ppm_outbound_rule_t *pkt_out_rule = NULL;


	if(!(pkt_out_rule = ppm_is_outbound_pkt_registered(proto_name, outbound_new_rule->pkt_id, &proto_db))){
		printf("%s() : Warning :  Attempt to update non-existing rule for protocol : %s, pkt_id : %s",
			 __FUNCTION__, proto_name, ppm_get_str_enum(outbound_new_rule->pkt_id));
		return FALSE;
	}


	ppm_remove_outbound_rule(proto_name, outbound_new_rule->pkt_id);
	ppm_add_outbound_rule(proto_name, outbound_new_rule);
	return TRUE;
}

void
ppm_dump_in_out_intf(const ppm_in_out_if_t *intf){
	printf("intf->ifname : %s\n", intf->ifname);
	/*Expand later ....*/
}



void
ppm_dump_outbound_rule(const ppm_outbound_rule_t *rule){

	singly_ll_node_t *head = NULL;
	oif_info_t *intf = NULL;
	unsigned int i = 0;

	printf("is_active : %s\n", rule->is_active ? "TRUE" : "FALSE");
	printf("pkt_id	: %s\n", ppm_get_str_enum(rule->pkt_id));
	printf("pkt_size : %u\n", rule->pkt_size);
	printf("Periodic time interval : %u\n", rule->time_interval);
	printf("is_periodic : %s\n", rule->is_periodic ? "TRUE" : "FALSE" );
	printf("ppm_cumulative_out_sent_stats : %u\n", rule->ppm_cumulative_out_sent_stats);
	if(rule->oif_list){
		printf("OIF list : #oifs : %u\n", GET_OIF_COUNT(rule));
		head = GET_HEAD_SINGLY_LL(rule->oif_list);
		for(; i < GET_NODE_COUNT_SINGLY_LL(rule->oif_list); i++){
			intf = (oif_info_t *)head->data;
			//ppm_dump_in_out_intf(intf);
			printf("	OIF #%u, ifindex = %u\n", i, (unsigned int)intf->ifindex);
			head = GET_NEXT_NODE_SINGLY_LL(head);
		}	
	}
	else
		printf("OIF list : NULL\n");

	printf("Now Printing the packet content :\n");
	if(rule->pkt_display_fn)
		rule->pkt_display_fn(rule->pkt, rule->pkt_size);
	else
		printf("pkt display fn not registered with PPM\n");

}

void
ppm_dump_outbound_db(){
	
	assert(ppm_outb_gl_db);
	ppm_outbound_protocol_db_t *proto_db = NULL;
	ppm_outbound_rule_t *pkt_out_rule = NULL;

	ll_t *ppm_db_list = GET_PPM_OUTBOUND_DB_LIST;
	singly_ll_node_t *head = GET_HEAD_SINGLY_LL(ppm_db_list);

	unsigned int i = 0, j = 0;


	for(; i < GET_NODE_COUNT_SINGLY_LL(ppm_db_list); i++){
		proto_db = (ppm_outbound_protocol_db_t *)head->data;
		printf("Protocol Name : %s\n", proto_db->proto);
		printf("	max_pkt_id : %s\n", ppm_get_str_enum(proto_db->protocol_max_pkt_id));

		for(j = 0; j < proto_db->protocol_max_pkt_id; j++){
			pkt_out_rule = GET_PROTO_RULE(proto_db, j);
			if(IS_RULE_ACTIVE(pkt_out_rule)){
				ppm_dump_outbound_rule(pkt_out_rule);
				printf(" ============ \n\n");
			}
		}
		head = GET_NEXT_NODE_SINGLY_LL(head);
	}

	printf("PPM dumping the PPM scheduler : \n\n");

	ppm_dump_scheduler();
}
