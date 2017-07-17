#ifndef __COMMON__H
#define __COMMON__H

typedef struct _mac_addr_t{
	char mac[6];
} mac_addr_t;

typedef enum{
        FALSE,
        TRUE
} bool_t;

typedef unsigned int ipv4_addr;

#define MTU_SIZE	1526
#define VLAN_MAX	512
#endif
