TARGET=lru
OBJS=main.o hash_table.o
$(TARGET): $(OBJS)
	g++ -o ${TARGET} $(OBJS)

main.o: main.cpp
	g++ -c main.cpp
hash_table.o: hash_table.cpp hash_table.h
	g++ -c hash_table.cpp
#stl.o: stl.cpp stl.h
#	g++ -c stl.cpp
#String.o: String.cpp String.h
#	g++ -o String.o -c String.cpp


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
