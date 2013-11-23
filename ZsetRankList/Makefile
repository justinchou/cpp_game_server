# CFLAGS?= -pedantic -O2 -Wall -DNEBUG -W
CFLAGS?= -pedantic -O0 -W -DDEBUG -g
CC = g++

TEMP_PATH=tmp/
INSTALL_PATH=/usr/bin/
SOURCE=src/
REDIS=${SOURCE}redis/
VPATH = ${SOURCE} ${REDIS}

LIBNAME=libredisclient.a
CLIENTOBJS=anet.o

APP=ZsetRankList
APPOBJS=ZsetRankList.o apposition.o redisclient.o
APPLIBS=$(LIBNAME) -lstdc++ -lpthread -lboost_thread-mt

all: $(LIBNAME) $(APP)
#	make tidy
$(LIBNAME): $(CLIENTOBJS)
	ar rcs $(LIBNAME) $(CLIENTOBJS)
$(APP): $(LIBNAME) $(APPOBJS)
	$(CC) ${CFLAGS} -o $(APP) $(APPOBJS) $(APPLIBS)


anet.o: anet.c fmacros.h anet.h
redisclient.o: redisclient.h redisclient.cpp
ZsetRankList.o: redisclient.h ZsetRankList.cpp
apposition.o: redisclient.h apposition.cpp apposition.h

tidy:
	mv ${LIBNAME} ${CLIENTOBJS} ${APPOBJS} ${TEMP_PATH}
install:
	cp -rf ${APP} ${INSTALL_PATH}
uninstall:
	cd ${INSTALL_PATH} && rm -rf ${APP}

test: $(APP)
	@./${APP}
check: test
exec: test
e: test

clean:
	rm -rf ${LIBNAME} ${CLIENTOBJS} ${APPOBJS} ${APP} *.o
	cd ${TEMP_PATH} && rm -rf ${LIBNAME} ${CLIENTOBJS} ${APPOBJS} ${APP} *.o
clear: clean

dep:
	$(CC) -MM ${SOURCE}*.c ${SOURCE}*.cpp
.PHONY: tidy install uninstall test check exec e clean clear dep
