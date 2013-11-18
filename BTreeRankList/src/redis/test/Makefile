#CFLAGS?= -pedantic -O2 -Wall -DNEBUG -W
CFLAGS?= -pedantic -O0 -W -DDEBUG -g
CC = g++

VPATH= ../

CLIENTOBJS = anet.o
LIBNAME = libredisclient.a

TESTAPP = client
TESTAPPOBJS = client.o
TESTAPPLIBS = $(LIBNAME) -lstdc++ -lpthread -lboost_thread-mt

all: $(LIBNAME) $(TESTAPP)

$(LIBNAME): $(CLIENTOBJS)
	ar rcs $(LIBNAME) $(CLIENTOBJS)

$(TESTAPP): $(LIBNAME) $(TESTAPPOBJS)
	$(CC) -o $(TESTAPP) $(TESTAPPOBJS) $(TESTAPPLIBS)

test: $(TESTAPP)
	@./client
check: test
clean:
	rm -rf $(LIBNAME) *.o $(TESTAPP)
dep:
	$(CC) -MM *.c *.cpp

anet.o: anet.c fmacros.h anet.h
client.o: redisclient.h client.cpp
