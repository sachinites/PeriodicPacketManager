#include "ppm_pkt_enums.h"

const char*
ppm_get_str_enum(ppm_outbound_pkt_id_t pkt_id){
	switch(pkt_id){
		case ISIS_LAN_L1_HELLO:
			return "ISIS_LAN_L1_HELLO";
		case ISIS_LAN_L2_HELLO:
			return "ISIS_LAN_L2_HELLO";
		case ISIS_PTP_L1_HELLO:
			return "ISIS_PTP_L1_HELLO";
		case ISIS_PTP_L2_HELLO:	
			return "ISIS_PTP_L2_HELLO";
		case ISIS_L1_LSP:
			return "ISIS_L1_LSP";
		case ISIS_L2_LSP:
			return "ISIS_L2_LSP";
		case ISIS_PPM_PKT_MAX:
			return "ISIS_PPM_PKT_MAX";
		default:
			return "UNKNOWN_PKT";
	}
}
