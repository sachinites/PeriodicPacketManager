#include <stdio.h>

static void
ppm_emit_pkt_one_interface(char *pkt, unsigned int pkt_size, unsigned int ifindex){
	static unsigned int i = 0;
	printf("%s() : is called...%u  \n", __FUNCTION__, i++);
}

void
wrapper_ppm_emit_pkt_one_interface (void *arg, int arg_size){
	ppm_emit_pkt_one_interface(NULL, 0, 0);	

}

static void
ppm_flood_pkt_on_vlan(char *pkt, unsigned int pkt_size, unsigned int vlan_id){
	printf("%s() : is called...\n", __FUNCTION__);
}

