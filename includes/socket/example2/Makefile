OBJS=client server

ALL: $(OBJS)
	chmod -R +x $(OBJS)

client: tcpcli.cpp SocketPack.h
	g++ tcpcli.cpp -o client
server: tcpserv.cpp SocketPack.h
	g++ tcpserv.cpp -o server

clean:
	rm -rf $(OBJS) *.o
clear: clean

