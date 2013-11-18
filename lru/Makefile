# path defination
VPATH=src/
TEMP_PATH=tmp/
INSTALL_PATH=/usr/bin/

# target defination
TARGET=lru
OBJS=main.o lru.o

CC=g++
GDB=-g -Wall

# compile dependencies
$(TARGET): $(OBJS)
	g++ ${GDB} -o ${TARGET} $(OBJS)
	make tidy
main.o: main.cpp
#	g++ -c main.cpp
lru.o: lru.cpp lru.h
#	g++ -c src/lru.cpp -o lru.o


# other commonds help
tidy:
	-mv ${OBJS} ${TEMP_PATH}
install:
	cp -r ${TARGET} ${INSTALL_PATH}
uninstall:
	cd ${INSTALL_PATH} && rm -rf ${TARGET}
clean:
	-rm -f ${TARGET} $(OBJS)
	cd ${TEMP_PATH} && rm -f ${TARGET} $(OBJS)
clear:
	-rm -f ${TARGET} $(OBJS)
	cd ${TEMP_PATH} && rm -f ${TARGET} $(OBJS)
exec:
	chmod +x ./${TARGET}
	./${TARGET}
e:
	chmod +x ./${TARGET}
	./${TARGET}
.PHONY: clean clear install exec e
