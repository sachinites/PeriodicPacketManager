CC=gcc
CFLAGS=-g -Wall
STANDARD_LIBS=-lpthread
ISIS_OBJ=isis_main.o
PPM_LIBS=../libs/libsulibs.a
PPM_CLIENT_LIBS=../ppm_client/libppm_client.a
INCLUDES=-I . -I ../libs -I ../ppm_client
TARGET:isis.exe
isis_main.o:isis_main.c
	${CC} ${CFLAGS} -c ${INCLUDES} isis_main.c -o isis_main.o
isis.exe:${PPM_LIBS} ${ISIS_OBJ} ${STANDARD_LIBS} ${PPM_CLIENT_LIBS} 
	${CC} ${CFLAGS} ${ISIS_OBJ} -o isis.exe -L ../ppm_client -lppm_client -L ../libs -lsulibs ${STANDARD_LIBS}
clean:
	rm *.o
	rm isis.exe
