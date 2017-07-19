#ifndef __PPM_EMITTER_H__
#define __PPM_EMITTER_H__

#include "../ppm_client/ppm_client.h"

void
wrapper_ppm_emit_pkt_one_interface (void *arg, int arg_size);

typedef struct _pkt_emit_per_interface_info{
	const char *pkt;
	unsigned int pkt_size;
	unsigned int ifindex;
} pkt_emit_per_interface_info_t;

void 
free_pkt_emit_per_interface_info(pkt_emit_per_interface_info_t *pkt_emit_per_interface_info);


#endif 
