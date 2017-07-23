#ifndef __PPM_SCHED__H
#define __PPM_SCHED__H

#include "../libs/WheelTimer.h"
#include "ppm.h"

#define PPM_SCHEDULER_SIZE	60
#define PPM_SCHED_CLOCK_TICK_INTERVAL	1	

void
ppm_setup_scheduler();

ppm_scheduler_t* ppm_get_scheduler();

void
ppm_scheduler_start();

void
ppm_dump_scheduler();

#define PPM_SCHEDULE_OUTBOUND_PKT(wt_elem)	\
	register_app_event(ppm_get_scheduler(), \
	wt_elem_temp.app_callback,		\
	wt_elem_temp.arg,			\
	wt_elem_temp.arg_size,			\
	wt_elem_temp.time_interval,		\
	wt_elem_temp.is_recurrence)


#endif
