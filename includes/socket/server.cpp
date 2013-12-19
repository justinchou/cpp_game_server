#include <iostream>
#include <stdlib.h>
#include <string>

#include <errno.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <memory.h>

#define MAXLINE 4096

using std::cout;
using std::endl;

int main()
{

    int listenfd, connfd;
    struct sockaddr_in servaddr;
    char buff[MAXLINE];
    int n;
    
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

        if( connfd == -1 )
//        if ( (connfd = accept(listenfd, (struct sockaddr*)NULL, NULL)) == -1)
        {
            cout<<"listen socket error"<<strerror(errno)<<"(errno: "<<errno<<")"<<endl;
            exit(3);
        }

        while( (n = recv(connfd, buff, MAXLINE, 0)) < 0
		&& (errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN)
	){
            cout<<"receive n is:"<<n<<endl;
            cout<<"fd is:"<<connfd<<"; err code is:"<<errno<<" != "<<EINTR<<" or "<<EWOULDBLOCK<<" or "<<EAGAIN<<endl;
        }

        {
       	    buff[n] = '\0';
            cout<<"receive from client: "<<buff<<"\tlength: "<<n<<endl;

            send(connfd, buff, strlen(buff), 0);

        }

        close(connfd);
        sleep(1);
    }
    
    close(listenfd);
}
