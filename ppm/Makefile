CC=gcc
CFLAGS=-g -Wall
STANDARD_LIBS=-lpthread
PPM_OBJ=ppm.o ppm_main.o
LIBS_OBJ=libs/LinkedListApi.o libs/threadApi.o libs/WheelTimer.o
PPM_LIBS=../libs/libs.a
PPM_CLIENT_LIBS=../ppm_client/ppm_client.a
INCLUDES=-I . -I ../libs -I ../ppm_client
TARGET:exe ${PPM_LIBS} ${PPM_CLIENT_LIBS}

ppm.o:ppm.c
	gcc -g -c ${INCLUDES} ppm.c -o ppm.o
ppm_main.o:ppm_main.c
	gcc -g -c ${INCLUDES} ppm_main.c -o ppm_main.o

${PPM_LIBS}:
	(cd ../libs; make)
${PPM_CLIENT_LIBS}:
	(cd ../ppm_client; make)
exe:${PPM_LIBS} ${PPM_OBJ} ${STANDARD_LIBS} ${PPM_CLIENT_LIBS} 
	${CC} ${CFLAGS} ${PPM_OBJ} -o exe -L . ${PPM_LIBS} ${PPM_CLIENT_LIBS} ${STANDARD_LIBS}
clean:
	rm *.o
	(cd ../libs; make clean)
	(cd ../ppm_client; make clean)	
	rm exe
