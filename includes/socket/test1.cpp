#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <errno.h>
#include <memory.h>
#include <stdlib.h>

using namespace std;

#define SERVER_PORT 6666
#define LISTENQ 10

void doit(int connfd);

int Listen(int sockfd, int backlog)
{
     char *ptr;
     if( (ptr = getenv("LISTENQ")) != NULL)
     {
          backlog = atol(ptr);
     }

cout<<ptr<<endl<<backlog<<endl;

     int ret = listen(sockfd, backlog);
     if( ret < 0)
     {
          cout<<"Listen error! "<<strerror(errno)<<" (errno: "<<errno<<")"<<endl;
     }

     return ret;
}


int 
main()
{
    pid_t pid;
    int listenfd, connfd;
    struct sockaddr_in cliaddr, servaddr;

    listenfd = socket(AF_INET,SOCK_STREAM,0);
    if(listenfd == -1) 
    {
        cout<<"create socket error: "<<strerror(errno)<<" - (errno:"<<errno<<")"<<endl;
        return 1;
    }

    memset(&servaddr,0,sizeof(struct sockaddr_in*));
    servaddr.sin_family = AF_INET;

    char ip[] = "127.0.0.1";
    int ret = inet_pton(AF_INET,ip,&servaddr.sin_addr);
//    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    servaddr.sin_port = htons(SERVER_PORT);

    int bindRet = bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    if (bindRet == -1)
    {
        cout<<"bind socket error: "<<strerror(errno)<<" - (errno:"<<errno<<")"<<endl;
        return 1;
    }

    Listen(listenfd,3);

//    int listenRet = listen(listenfd, LISTENQ);
//    if (listenRet == -1)
//    {
//        cout<<"listen port "<<servaddr.sin_port<<" error: "<<strerror(errno)<<" - (errno:"<<errno<<")"<<endl;
//        return 1;
//    }

    while(1)
    {
        socklen_t clilen = sizeof(cliaddr);
        connfd = accept(listenfd,(struct sockaddr*)&cliaddr,&clilen);
        if( (pid = fork()) == 0)
        {
            doit(connfd);
//            close(connfd);
//            return 0;
        } else {
//            close(connfd);
        }
    }

    close(listenfd);

    return 0;
}

void doit(int connfd)
{
    char buff[1024];
    int len = read(connfd,buff,sizeof(buff));
    buff[len] = 0;
    cout<<connfd<<", len:"<<len<<", value:"<<buff<<endl;
    write(connfd,buff,len);
}
