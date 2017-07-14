#ifndef __PPM_PKT_ENUMS_H__
#define __PPM_PKT_ENUMS_H__

/*Identifiers of outbound packet known to PPM*/

/*Protocol Pkt enums should be strictly in increasing order 
 and is independant of protocol version of enums. Please re-define enums of 
your protocol packets here. These enums are used only by PPM. Please maintain a mapping in
your protocol from this enum to your protocol version of packet enums*/

#define PPM_MAX_PROTO_NAME_SIZE 64
#define PPM_IF_NAME_SIZE        32


typedef enum{
	PPM_PERIODICITY_DISABLE,
	PPM_PERIODICITY_ENABLE
} PIM_PKT_PERIODICITY;

typedef enum {
        ISIS_LAN_L1_HELLO = 0,
        ISIS_LAN_L2_HELLO,
        ISIS_PTP_L1_HELLO,
        ISIS_PTP_L2_HELLO,
        ISIS_L1_LSP,
        ISIS_L2_LSP,
	ISIS_PPM_PKT_MAX,
	PPM_MAX_PKT_ID

	/*Write pkt IDs of next protocol packets*/
} ppm_outbound_pkt_id_t;

const char*
ppm_get_str_enum(ppm_outbound_pkt_id_t pkt_id);

#endif
