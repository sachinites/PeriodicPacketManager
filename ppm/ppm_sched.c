#include <stdio.h>
#include "ppm_sched.h"
#include "ppm_emitter.h"
#include "../libs/LinkedListApi.h"
#include <stdlib.h>
#include <assert.h>

extern ppm_outbound_gl_db_t* ppm_outb_gl_db;


void 
ppm_setup_scheduler(){
	static char is_setup = 0;
	assert(!is_setup);
	is_setup = 1;
	ppm_scheduler_t *sched = init_wheel_timer(PPM_SCHEDULER_SIZE,
			PPM_SCHED_CLOCK_TICK_INTERVAL);

	ppm_outb_gl_db->scheduler = sched;
}

ppm_scheduler_t *
ppm_get_scheduler(){
	return ppm_outb_gl_db->scheduler;
}


void
ppm_scheduler_start(){
	start_wheel_timer(ppm_get_scheduler());
}


void
ppm_schedule_outbound_rule(const char *proto_name, ppm_outbound_rule_t *ppm_outbound_rule){
	if(!IS_RULE_ACTIVE(ppm_outbound_rule)){
		printf("%s() : Error : Attempt to Schedule the Inactive Rule\n", __FUNCTION__);
		return;
	}

	wheel_timer_elem_t *wt_elem = NULL, wt_elem_temp;
	unsigned int i = 0;
	singly_ll_node_t *head = NULL;
	oif_info_t *oif = NULL;

	head = GET_HEAD_SINGLY_LL(ppm_outbound_rule->oif_list);
	for(; i < GET_OIF_COUNT(ppm_outbound_rule); i++){

		wt_elem_temp.time_interval = ppm_outbound_rule->time_interval;
		wt_elem_temp.is_recurrence = ppm_outbound_rule->is_periodic;
		wt_elem_temp.app_callback  = wrapper_ppm_emit_pkt_one_interface;

		pkt_emit_per_interface_info_t *emit_info_per_intf = 
			calloc(1, sizeof(pkt_emit_per_interface_info_t));
		
		emit_info_per_intf->pkt      = ppm_outbound_rule->pkt;
		emit_info_per_intf->pkt_size = ppm_outbound_rule->pkt_size;
		oif = (oif_info_t *)head->data;	
		emit_info_per_intf->ifindex  = oif->ifindex;

		wt_elem_temp.arg = emit_info_per_intf;

		wt_elem_temp.arg_size = sizeof(pkt_emit_per_interface_info_t);

		/*Schedule the outbound rule*/
		wt_elem = PPM_SCHEDULE_OUTBOUND_PKT(wt_elem_temp);

		oif->wt_elem = wt_elem;
		head = GET_NEXT_NODE_SINGLY_LL(head);
	}
}



void
ppm_dump_scheduler(){
	
	print_wheel_timer(ppm_get_scheduler());

}
