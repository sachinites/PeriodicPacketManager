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


#endif
