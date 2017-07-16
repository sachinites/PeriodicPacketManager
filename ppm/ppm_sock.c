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
#include "../ppm_client/ppm_client.h"

#define PPM_MAX_RECV_BUFFER     (1024*1024)

extern
ppm_lc_reachability_info_t ppm_lc_reachability_info;

extern void 
ppm_process_aplication_msg(char *msg, unsigned int msg_size);

static int ppm_sock_fd;



static void
ppm_process_sock_msg(char *ppm_rec_buff, unsigned int msg_size){

        printf("%s() : called ...\n", __FUNCTION__);
	ppm_process_aplication_msg(ppm_rec_buff, msg_size);
}


static void*
ppm_recv_sock_msg(void *arg){

        int addr_len = 0,
            len = 0;

        char ppm_rec_buff[PPM_MAX_RECV_BUFFER];
        struct sockaddr_in ppm_recv_lc_addr;
        addr_len = sizeof(struct sockaddr);

READ:
        len = recvfrom(ppm_sock_fd, ppm_rec_buff, PPM_MAX_RECV_BUFFER, 0, 
			(struct sockaddr *)&ppm_recv_lc_addr, (socklen_t *)&addr_len);

        ppm_process_sock_msg(ppm_rec_buff, (unsigned int)len);

        goto READ;

        return NULL;
}


void
ppm_setup_sockets(char LC_NO){

     	int sock_fd = 0;

        _pthread_t ppm_comm_thread;
        int DETACHED =0;

        sock_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if(sock_fd == -1){
                printf("%s() : THA  socket creation failed\n", __FUNCTION__);
                return;
        }

        ppm_sock_fd = sock_fd;

        if (bind(ppm_sock_fd, (struct sockaddr *)&ppm_lc_reachability_info.dest_addr[(unsigned int)LC_NO], sizeof(struct sockaddr)) == -1){
                printf("%s() : Error : socket bind failed, errno = %d\n", __FUNCTION__, errno);
                exit(1);
        }

        pthread_initialize(&ppm_comm_thread, 0 , DETACHED);
        pthread_create(&ppm_comm_thread.pthread_handle,
                        &ppm_comm_thread.attr, ppm_recv_sock_msg, NULL);
}
