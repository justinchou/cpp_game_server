#include <iostream>
#include <stdlib.h>
#include <string>

#include <errno.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <memory.h>

#include <pthread.h>

#define MAXLINE 4096

using std::cout;
using std::endl;

void *handleMessage(void *);

typedef struct message
{
    int connfd;
    char buff[MAXLINE];
} message;

int main()
{

    int listenfd, connfd;
    struct sockaddr_in servaddr;
    char buff[MAXLINE];
    
    if( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        cout<<"create socket error"<<strerror(errno)<<"(errno: "<<errno<<")"<<endl;
        exit(1);
    }
    
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(6666);
    
    if( bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1)
    {
        cout<<"bind socket error"<<strerror(errno)<<"(errno: "<<errno<<")"<<endl;
        exit(2);
    }
    
    if( listen(listenfd, 10) == -1)
    {
        cout<<"listen socket error"<<strerror(errno)<<"(errno: "<<errno<<")"<<endl;
        exit(2);
    }
    
    cout<<"==============  waiting for clients  =============="<<endl;
    
    while(1)
    {
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
        if( connfd == -1)
        {
            cout<<"listen socket error"<<strerror(errno)<<"(errno: "<<errno<<")"<<endl;
            exit(3);
        }

	pthread_t t1;
	message *msg = new message();
	msg->connfd = connfd;
	strcpy(msg->buff, buff);

	pthread_create(&t1,NULL,handleMessage,msg);
    }
    
    close(listenfd);
}

void *handleMessage(void *msg)
{
    message *pointer = (message *)msg;
    int n;
    while( (n = recv(pointer->connfd, pointer->buff, MAXLINE, 0)) < 0
                && (errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN)
    ){
        cout<<"receive n is:"<<n<<endl;
        cout<<"fd is:"<<pointer->connfd<<"; err code is:"<<errno<<" != "<<EINTR<<" or "<<EWOULDBLOCK<<" or "<<EAGAIN<<endl;
    }

    {
        pointer->buff[n] = '\0';
        cout<<"receive from client: "<<pointer->buff<<"\tlength: "<<n<<endl;
    }

    close(pointer->connfd);
}
