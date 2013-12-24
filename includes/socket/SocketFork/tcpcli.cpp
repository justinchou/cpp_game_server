#include <stdio.h>
#include "SocketPack.h"

#include <iostream>
using namespace std;

#define SERV_PORT 6666
//#define MAXLINE 1024

void str_cli(FILE *, int);

int main(int argc, char *argv[])
{
    int listenfd;
    struct sockaddr_in servaddr;
    CheckArgc(argc,2);

    listenfd = Socket(AF_INET,SOCK_STREAM,0);

    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET,argv[1],&servaddr.sin_addr);
    Connect(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    str_cli(stdin, listenfd);

    return 0;
}

void str_cli(FILE *fp, int listenfd)
{
    ssize_t n;
    char *ret;
    char sendline[MAXLINE], recvline[MAXLINE];

    cout<<"input message:";
    while( (ret = Fgets(sendline,MAXLINE,fp)) != NULL)
    {
        Write(listenfd, sendline, strlen(sendline));
        if( (n = Read(listenfd,recvline,MAXLINE)) == 0)
        {
            cout<<"serv error!"<<endl;
        }
        Fputs(recvline,stdout);
        cout<<"input message:";
    }
}
