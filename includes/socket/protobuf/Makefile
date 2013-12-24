## THIS IS A CPP COMPILE TEMPLATE Makefile ##

CCFLAGS  = -lprotobuf 
# CFLAGS = -pedantic -O2 -Wall -DNEBUG -W $(CCFLAGS)
CFLAGS   = -pedantic -O0 -W -DDEBUG -g $(CCFLAGS)

# CC = gcc
CC = g++

CCVPATH	    = include/addressbook 
VPATH	    = include:src:tests:$(CCVPATH)

SOURCE      = src/
TESTPATH    = tests/
TMPPATH     = tmp/
INSTALLPATH = /usr/bin/

TARGET      = write
TESTS       = read
TARGETOBJS  = write.o
TESTSOBJS   = read.o
ALLOBJS     = $(TARGET) $(TESTS)

ALL: $(ALLOBJS)
	make tidy
$(TARGET): ${TARGETOBJS} addressbook.pb.cc
	$(CC) $(CFLAGS) -o $@ $^
$(TESTS): $(TESTSOBJS) addressbook.pb.cc
	$(CC) $(CFLAGS) -o $@ $^

tidy:
	mv ${TARGET} ${TESTS} ${TARGETOBJS} ${TESTSOBJS} ${TMPPATH}
install:
	cp -rf ${TARGET} ${INSTALLPATH}
uninstall:
	cd ${INSTALLPATH} && rm -rf ${TARGET}

test:	$(TARGET)
		@./${TARGET}
check:	test
exec:	test
e:	test

clean:
	rm -rf ${TARGET} ${TESTS} ${TARGETOBJS} ${TESTSOBJS} *.o
	cd ${TEMP_PATH} && rm -rf ${TARGET} ${TESTS} ${TARGETOBJS} ${TESTSOBJS} *.o
clear: clean

dep:
	$(CC) -MM ${SOURCE}*.c ${SOURCE}*.cpp
.PHONY: tidy install uninstall test check exec e clean clear dep
