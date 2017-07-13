#ifndef __PPM__CLIENT_H__
#define __PPM__CLIENT_H__

typedef void (*pkt_display_fn_t)(char *, unsigned int);

/*PPM Input Structure*/

typedef struct _ppm_input_struct{
	unsigned short pkt_size;	/*Size of the pkt*/
	char *pkt[MTU_SIZE];		/*Pkt buffer*/
	unsigned int time_interval;
	char is_periodic;
	unsigned int n_interfaces;
	unsigned int ifindex_array[0];
} ppm_input_struct_t;





#endif
