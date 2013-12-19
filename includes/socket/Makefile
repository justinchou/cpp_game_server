CFLAGS=-g

SERVER=server
CLIENT=client
Pthread=pthread
PthreadServer=PthreadServer
ForkServer=ForkServer
stack=stack
ALLFILES=$(SERVER) $(CLIENT) $(Pthread) $(PthreadServer) $(ForkServer) $(stack)
ALL: $(ALLFILES)
	chmod +x $(ALLFILES)

$(CLIENT): client.cpp
	g++ $(CFLAGS) -o $(CLIENT) client.cpp
$(SERVER): server.cpp
	g++ $(CFLAGS) -o $(SERVER) server.cpp
$(PthreadServer): PthreadServer.cpp
	g++ $(CFLAGS) -o $(PthreadServer) PthreadServer.cpp -lpthread
$(Pthread): pthread.cpp
	g++ $(CFLAGS) -o $(Pthread) pthread.cpp -lpthread
$(ForkServer): ForkServer.cpp
	g++ $(CFLAGS) -o $(ForkServer) ForkServer.cpp -lpthread
$(stack): stack.cpp
	g++ -g -rdynamic -o $(stack) stack.cpp

clean:
	rm -rf $(ALLFILES)

