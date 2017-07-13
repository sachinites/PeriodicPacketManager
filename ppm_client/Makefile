CC=gcc
CFLAGS=-Wall -g
INCLUDES=-I . -I ../libs -I ../ppm
OBJ=ppm_pkt_enums.o
TARGET=ppm_client.a
${TARGET}:$(OBJ)
	ar rs ${TARGET} ${OBJ}
ppm_pkt_enums.o:ppm_pkt_enums.c
	gcc -g -c ${INCLUDES} ppm_pkt_enums.c -o ppm_pkt_enums.o
clean:
	rm *.o
	rm ${TARGET}

