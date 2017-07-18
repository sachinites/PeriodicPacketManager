CC=gcc
CFLAGS=-g -Wall
STANDARD_LIBS=-lpthread
PPM_OBJ=ppm.o ppm_main.o ppm_sock.o ppm_recv.o ppm_sched.o
LIBS_OBJ=libs/LinkedListApi.o libs/threadApi.o libs/WheelTimer.o
PPM_LIBS=../libs/libsulibs.a
PPM_CLIENT_LIBS=../ppm_client/libppm_client.a
INCLUDES=-I . -I ../libs -I ../ppm_client
TARGET:exe ${PPM_LIBS} ${PPM_CLIENT_LIBS}

ppm.o:ppm.c
	gcc -g -c ${INCLUDES} ppm.c -o ppm.o
ppm_main.o:ppm_main.c
	gcc -g -c ${INCLUDES} ppm_main.c -o ppm_main.o
ppm_sock.o:ppm_sock.c
	gcc -g -c ${INCLUDES} ppm_sock.c -o ppm_sock.o
ppm_recv.o:ppm_recv.c
	gcc -g -c ${INCLUDES} ppm_recv.c -o ppm_recv.o
ppm_sched.o:ppm_sched.c
	gcc -g -c ${INCLUDES} ppm_sched.c -o ppm_sched.o

${PPM_LIBS}:
	(cd ../libs; make)
${PPM_CLIENT_LIBS}:
	(cd ../ppm_client; make)
exe:${PPM_LIBS} ${PPM_OBJ} ${STANDARD_LIBS} ${PPM_CLIENT_LIBS} 
	${CC} ${CFLAGS} ${PPM_OBJ} -o exe -L ../ppm_client -lppm_client -L ../libs -lsulibs ${STANDARD_LIBS}
clean:
	rm *.o
	(cd ../libs; make clean)
	(cd ../ppm_client; make clean)	
	rm exe
