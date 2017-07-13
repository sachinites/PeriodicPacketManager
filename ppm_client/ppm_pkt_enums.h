#ifndef __PPM_PKT_ENUMS_H__
#define __PPM_PKT_ENUMS_H__

/*Identifiers of outbound packet known to PPM*/

typedef enum {
        ISIS_LAN_L1_HELLO,
        ISIS_LAN_L2_HELLO,
        ISIS_PTP_L1_HELLO,
        ISIS_PTP_L2_HELLO,
        ISIS_L1_LSP,
        ISIS_L2_LSP,
	ISIS_PPM_PKT_MAX,



	PPM_MAX_PKT_ID
} ppm_outbound_pkt_id_t;

const char*
ppm_get_str_enum(ppm_outbound_pkt_id_t pkt_id);

#endif
