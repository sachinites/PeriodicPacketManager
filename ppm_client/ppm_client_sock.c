#include <sys/types.h>
#include <sys/socket.h>
#include <memory.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include "../libs/threadApi.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define MAX_LINE_CARDS	8
#define PPM_MAX_RECV_BUFFER	(1024*1024)

typedef struct _ppm_lc_reachability_info{
        struct sockaddr_in dest_addr[MAX_LINE_CARDS + 1];
} ppm_lc_reachability_info_t;

static ppm_lc_reachability_info_t ppm_lc_reachability_info;


void
ppm_client_init_lc_ppm_reachability_info(){

	ppm_lc_reachability_info.dest_addr[0].sin_family      = AF_INET;
	ppm_lc_reachability_info.dest_addr[0].sin_port	      = 200;
	inet_pton(AF_INET, "127.0.0.1", &ppm_lc_reachability_info.dest_addr[0].sin_addr);

	
	ppm_lc_reachability_info.dest_addr[1].sin_family      = AF_INET;
	ppm_lc_reachability_info.dest_addr[1].sin_port	      = 201;
	inet_pton(AF_INET, "127.0.0.1", &ppm_lc_reachability_info.dest_addr[1].sin_addr);


	ppm_lc_reachability_info.dest_addr[2].sin_family      = AF_INET;
	ppm_lc_reachability_info.dest_addr[2].sin_port	      = 202;
	inet_pton(AF_INET, "127.0.0.1", &ppm_lc_reachability_info.dest_addr[2].sin_addr);
	
	ppm_lc_reachability_info.dest_addr[3].sin_family      = AF_INET;
	ppm_lc_reachability_info.dest_addr[3].sin_port	      = 203;
	inet_pton(AF_INET, "127.0.0.1", &ppm_lc_reachability_info.dest_addr[3].sin_addr);

	ppm_lc_reachability_info.dest_addr[4].sin_family      = AF_INET;
	ppm_lc_reachability_info.dest_addr[4].sin_port	      = 204;
	inet_pton(AF_INET, "127.0.0.1", &ppm_lc_reachability_info.dest_addr[4].sin_addr);


	ppm_lc_reachability_info.dest_addr[5].sin_family      = AF_INET;
	ppm_lc_reachability_info.dest_addr[5].sin_port	      = 205;
	inet_pton(AF_INET, "127.0.0.1", &ppm_lc_reachability_info.dest_addr[5].sin_addr);


	ppm_lc_reachability_info.dest_addr[6].sin_family      = AF_INET;
	ppm_lc_reachability_info.dest_addr[6].sin_port	      = 206;
	inet_pton(AF_INET, "127.0.0.1", &ppm_lc_reachability_info.dest_addr[6].sin_addr);


	ppm_lc_reachability_info.dest_addr[7].sin_family      = AF_INET;
	ppm_lc_reachability_info.dest_addr[7].sin_port	      = 207;
	inet_pton(AF_INET, "127.0.0.1", &ppm_lc_reachability_info.dest_addr[7].sin_addr);
	
	ppm_lc_reachability_info.dest_addr[8].sin_family      = AF_INET;
	ppm_lc_reachability_info.dest_addr[8].sin_port	      = 208;
	inet_pton(AF_INET, "127.0.0.1", &ppm_lc_reachability_info.dest_addr[8].sin_addr);
	
}

static int ppm_client_sock_fd;

static int
get_current_no_lc(){
	return 2;
}


static void
ppm_client_process_sock_msg(char *ppm_rec_buff, int len){

	printf("%s() : called ...\n", __FUNCTION__);

}

static void*
ppm_recv_sock_msg(void *arg){

        int tha_sock_fd = 0, 
	    addr_len = 0, 
	    len = 0;

        char ppm_rec_buff[PPM_MAX_RECV_BUFFER];
        struct sockaddr_in ppm_recv_lc_addr;
	addr_len = sizeof(struct sockaddr);

READ:
        len = recvfrom(ppm_client_sock_fd, ppm_rec_buff, PPM_MAX_RECV_BUFFER, 0, (struct sockaddr *)&ppm_recv_lc_addr, (socklen_t *)&addr_len);

        ppm_client_process_sock_msg(ppm_rec_buff, len);

        goto READ;

        return NULL;
}

unsigned int
ppm_client_send_msg_to_ppm(const char *msg, unsigned int msg_size){

	int n_lcs = get_current_no_lc(), i = 1;
	unsigned int rc = 0;

	for(; i <= n_lcs; i++ ){
		rc = sendto(ppm_client_sock_fd, msg, msg_size, 0, 
			(struct sockaddr *)&ppm_lc_reachability_info.dest_addr[i],
			sizeof(struct sockaddr));

		printf("%s() : %u bytes sent to LC%d\n", __FUNCTION__, rc, i);		
	}

	return 0;
}



int
ppm_client_init_socket(){

	int current_no_lc = 0, 
	    sock_fd = 0, i = 0, 
	    opt=1;

	_pthread_t ppm_recv_thread;
	int DETACHED =0;

	sock_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(sock_fd == -1){
		printf("%s() : THA  socket creation failed\n", __FUNCTION__);
		return -1;
	}
	ppm_client_sock_fd = sock_fd;

	if (bind(ppm_client_sock_fd, (struct sockaddr *)&ppm_lc_reachability_info.dest_addr[0], sizeof(struct sockaddr)) == -1){
		printf("%s() : Error : socket bind failed, errno = %d\n", __FUNCTION__, errno);
		exit(1);
	}

	pthread_initialize(&ppm_recv_thread, 0 , DETACHED);
	pthread_create(&ppm_recv_thread.pthread_handle,
			&ppm_recv_thread.attr, ppm_recv_sock_msg, NULL);

}

