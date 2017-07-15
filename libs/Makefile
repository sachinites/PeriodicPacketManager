LIBS=-lpthread
CC=gcc
CFLAGS=-Wall -g
INCLUDES=-I .
OBJ=WheelTimer.o threadApi.o LinkedListApi.o
TARGET=libsulibs.a
${TARGET}:$(OBJ)
	ar rs ${TARGET} $(OBJ)
%.o:%.c
	 ${CC} ${CFLAGS} -c ${INCLUDES} $<
clean:
	rm *.o
	rm ${TARGET}

