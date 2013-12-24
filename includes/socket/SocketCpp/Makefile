# Makefile for the socket programming example

simple_server_objects = ServerSocket.o Socket.o simple_server_main.o
simple_client_objects = ClientSocket.o Socket.o simple_client_main.o

all : simple_server simple_client

simple_server: $(simple_server_objects)
	g++ -o simple_server $(simple_server_objects)
simple_client: $(simple_client_objects)
	g++ -o simple_client $(simple_client_objects)

Socket: Socket.cpp Socket.h
ServerSocket: ServerSocket.cpp ServerSocket.h
ClientSocket: ClientSocket.cpp ClientSocket.h
simple_server_main: simple_server_main.cpp
simple_client_main: simple_client_main.cpp

clean:
	rm -f *.o simple_server simple_client
s:
	./simple_server &
	sleep 2
	wait 
	./simple_client
e:
	-ps -ef | grep simple_server | grep -v grep | cut -d ' ' -f 4 | xargs kill -9

