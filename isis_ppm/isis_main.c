#include "../ppm_client/ppm_client.h"
#include "../ppm_client/ppm_pkt_enums.h"
#include <string.h>
#include <stdlib.h>

int
main(int argc, char **argv){
	
	const char *proto_name = "ISIS";
	const char *pkt = "This is LAN L1 LSP PACKET";
	unsigned int ifindex[4] = {1,2,3,4};

	/*Intialize client librray*/
	ppm_init_client_lib();

	ppm_create_outbound_protocol_db(proto_name, ISIS_PPM_PKT_MAX);
#if 1
	ppm_input_struct_t *isis_lan_l1_lsp = 
		ppm_get_new_ppm_input_structure(ISIS_L1_LSP, 
						proto_name, 
						strlen(pkt), 
						pkt,
						10,
						1,
						4,
						&ifindex);

	ppm_install_new_outbound_rule(isis_lan_l1_lsp);
	free(isis_lan_l1_lsp);	
	
	ppm_input_struct_t *isis_lan_l2_lsp = 
		ppm_get_new_ppm_input_structure(ISIS_L2_LSP, 
						proto_name, 
						strlen(pkt), 
						pkt,
						3,
						1,
						4,
						&ifindex);

	ppm_install_new_outbound_rule(isis_lan_l2_lsp);	
	free(isis_lan_l2_lsp);	
	
	ppm_input_struct_t *isis_lan_l1_hello = 
		ppm_get_new_ppm_input_structure(ISIS_LAN_L1_HELLO, 
						proto_name, 
						strlen(pkt), 
						pkt,
						4,
						1,
						4,
						&ifindex);

	ppm_install_new_outbound_rule(isis_lan_l1_hello);
	free(isis_lan_l1_hello);
#endif		
	return 0;
}
