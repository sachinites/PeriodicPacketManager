#include <stdio.h>
#include "ppm_sched.h"

extern ppm_outbound_gl_db_t* ppm_outb_gl_db;

void 
ppm_setup_scheduler(){
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
ppm_schedule_outbound_rule(ppm_outbound_rule_t *ppm_outbound_rule){
	if(!IS_RULE_ACTIVE(ppm_outbound_rule)){
		printf("%s() : Error : Attempt to Schedule the Inactive Rule\n", __FUNCTION__);
		return;
	}
}
