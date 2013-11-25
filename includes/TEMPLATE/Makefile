# CFLAGS?= -pedantic -O2 -Wall -DNEBUG -W
# CFLAGS?= -pedantic -O0 -W -DDEBUG -g
CC = g++

SOURCE=src/
REDIS=${SOURCE}redis/
VPATH = ${SOURCE} ${REDIS}

CLIENTOBJS=anet.o
LIBNAME=libredisclient.a

APP=redisTest
APPOBJS=redisTest.o
APPLIBS=$(LIBNAME) -lstdc++ -lpthread -lboost_thread-mt

all: $(LIBNAME) $(APP)

$(LIBNAME): $(CLIENTOBJS)
	ar rcs $(LIBNAME) $(CLIENTOBJS)

$(APP): $(LIBNAME) $(APPOBJS)
	$(CC) -o $(APP) $(APPOBJS) $(APPLIBS)

anet.o: anet.c fmacros.h anet.h
redisTest.o: redisclient.h redisTest.cpp


.PHONY: test check clean dep
test: $(APP)
	@./redisTest
check: test
clean:
	rm -rf $(LIBNAME) *.o $(APP)
dep:
	$(CC) -MM ${SOURCE}*.c ${SOURCE}*.cpp
