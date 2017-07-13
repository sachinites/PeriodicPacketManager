#ifndef __ISIS__H_
#define __ISIS__H_

#include "common_str.h"
#include "LinkedListApi.h"
/* Adjacency Data structure*/

typedef struct _isis_level1_lan_adj_oif_t{
	ll_t *adj_list;
} isis_level1_adj_oif_t;


typedef struct _isis_level2_lan_adj_oif_t{
	ll_t *adj_list;
} isis_leve2_adj_oif_t;


typedef struct _isis_level1_p2p_adj_oif_t{
	ll_t *adj_list;
} isis_leve1_p2p_adj_oif_t;

typedef struct _isis_level2_p2p_adj_oif_t{
	ll_t *adj_list;
} isis_leve2_p2p_adj_oif_t;


typedef enum{
	ISIS_LAN_LEVEL1_ADJ,
	ISIS_LAN_LEVEL2_ADJ,
	ISIS_P2P_LEVEL1_ADJ,
	ISIS_P2P_LEVEL2_ADJ
} ISIS_ADJ_TYPE;

#define ISIS_MAX_PDU_SIZE	MTU_SIZE


/* ISIS Structures to hold the formatted packet*/

typedef struct  _isis_outbound_pkt_t{
	char isis_pkt_buffer[ISIS_MAX_PDU_SIZE];
	unsigned int time_interval;
	ISIS_ADJ_TYPE adj_type;
	char is_valid;
} isis_outbound_pkt_t;

/* ISIS outBound */

#endif
