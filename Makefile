CC=gcc
CFLAGS=-g -Wall
LIBS=-lpthread 
OBJ=threadApi.o WheelTimer.o
LL=LinkedListApi.o
TREE=
Q=
STACK=
DS_OBJ=${STACK} ${LL} ${Q} ${TREE}
TARGET:rp_exe ppm_exe 
%.o:%.c
	${CC} ${CFLAGS} -c -I . $<

#${STACK}:DS/Stack/stack.c
#	(cd DS/Stack; make)
#${LL}:DS/LinkedList/HALinkedListApi.c DS/LinkedList/LinkedListApi.c
#	(cd DS/LinkedList; make)
#${TREE}:DS/Trees/tree.c
#	(cd DS/Trees; make)
#${Q}:DS/Queue/Queue.c
#	(cd DS/Queue; make)
rp_exe: rp_main.o
	${CC} ${CFLAGS} rp_main.o -o rp_exe ${LIBS}
rp_main.o:rp_main.c
	${CC} ${CFLAGS} -c rp_main.c -o rp_main.o
ppm_exe: ppm_main.o ${OBJ} ${LL}
	${CC} ${CFLAGS} ppm_main.o ${OBJ} ${LL} -o ppm_exe ${LIBS}
ppm_main.o:ppm_main.c
	${CC} ${CFLAGS} -c ppm_main.c -o ppm_main.o
clean:
	rm *.o
	rm ppm_exe rp_exe
