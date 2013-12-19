#include <unistd.h>
#include "SocketPack.h"

#include <iostream>
using namespace std;

#define SERVER_PORT 6666
//#define MAXLINE 1024

void str_echo(int);

int main(int argc, char *argv[])
{
    int listenfd, connfd;
    pid_t pid;
    socklen_t clilen;
    struct sockaddr_in servaddr, cliaddr;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERVER_PORT);
    Bind(listenfd, &servaddr, sizeof(servaddr));

    Listen(listenfd, LISTENQ);
    Signal(SIGCHLD,sig_chld);

    cout<<"============ start to accept ============"<<endl;

    for(;;)
    {
        clilen = sizeof(cliaddr);
        connfd = Accept(listenfd, &cliaddr, &clilen);
        if( (pid = fork()) == 0)
        {
            Close(listenfd);
            str_echo(connfd);
            exit(0);
        }else{
            Close(connfd);
        }
    }
    return 0;
}

void str_echo(int sockfd)
{
    ssize_t n;
    char line[MAXLINE];
    for(;;)
    {
        if( (n = Read(sockfd, line, MAXLINE)) == 0)
            return;
        Write(sockfd, line, n);
    }
}
