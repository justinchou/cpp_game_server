TARGET=mysqlTest
OBJS=mysqlTest.o

cflags=$$(mysql_config --cflags)
libs=$$(mysql_config --libs)

$(TARGET): $(OBJS)
	g++ -o ${TARGET} $(OBJS) $(libs)

mysqlTest.o: mysqlTest.cpp
	g++ -o mysqlTest.o $(cflags) -c mysqlTest.cpp $(libs)

clean:
	-rm -f ${TARGET} $(OBJS)
clear:
	-rm -f ${TARGET} $(OBJS)
install:
	chmod +x ./${TARGET}
	./${TARGET}
exec:
	chmod +x ./${TARGET}
	./${TARGET}
e:
	chmod +x ./${TARGET}
	./${TARGET}
.PHONY: clean clear install exec e
