CC=gcc
CFLAGS=-Wall -g
INCLUDES=-I . -I ../libs -I ../ppm
OBJ=ppm_pkt_enums.o ppm_client.o ppm_client_sock.o
TARGET=libppm_client.a
${TARGET}:$(OBJ)
	ar rs ${TARGET} ${OBJ}
ppm_pkt_enums.o:ppm_pkt_enums.c
	gcc -g -c ${INCLUDES} ppm_pkt_enums.c -o ppm_pkt_enums.o
ppm_client.o:ppm_client.c
	gcc -g -c ${INCLUDES} ppm_client.c -o ppm_client.o
ppm_client_sock.o:ppm_client_sock.c
	gcc -g -c ${INCLUDES} ppm_client_sock.c -o ppm_client_sock.o
clean:
	rm *.o
	rm ${TARGET}

