/*This file defines the behavior how the particular outbound ISIS pkt type should be treated by PPM*/

#include "ppm.h"

/*If ISIS pkt type is L1 LAN hellos*/
static void
isis_ppm_outbound_level1_lan_hello(char *pkt_buf, 
				   unsigned int size, 
				   unsigned int *ifindex_array, 
				   unsigned int n_interfaces){
	
	unsigned int i = 0;

	printf("%s() ....\n");
	for(; i < n_interfaces; i++){
		printf("ISIS LvL1 LAN Hello pkt of size %u sent on interface %u\n", size, ifindex_array[i]);
	}
}
