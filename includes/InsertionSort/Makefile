# CFLAGS?= -pedantic -O2 -Wall -DNEBUG -W
# CFLAGS?= -pedantic -O0 -W -DDEBUG -g
CC = g++

SOURCE=src/
VPATH = ${SOURCE}

APP=InsertionSort
APPOBJS=InsertionSort.o

all: $(APP)

$(APP): $(APPOBJS)
	$(CC) -o $(APP) $(APPOBJS)

redisTest.o: InsertionSort.cpp InsertionSort.h

.PHONY: test check clean dep
test: $(APP)
	@./{APP}
check: test
clean:
	rm -rf *.o $(APP)
dep:
	$(CC) -MM ${SOURCE}*.c ${SOURCE}*.cpp
