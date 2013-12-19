#include <iostream>
#include <stdlib.h>
#include <string>

#include <errno.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <memory.h>

using namespace std;;

#define MAXLINE 4096

int main(int argc, char** argv)
{
    int sockfd, n;
    int len;
    char recvline[4096], sendline[4096];
    struct sockaddr_in servaddr;

    if( argc != 2){
        cout<<"usage: ./client <ipaddress>"<<endl;
        exit(1);
    }

    cout<<"argc: "<<argc<<", argv0"<<argv[0]<<", argv1"<<argv[1]<<endl;

    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        cout<<"create socket error: "<<strerror(errno)<<"(errno: "<<errno<<")"<<endl;
        exit(2);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(6666);
    if( inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0){
        cout<<"inet_pton error for "<<argv[1]<<endl;
        exit(3);
    }

    if( connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
        cout<<"connect socket error: "<<strerror(errno)<<"(errno: "<<errno<<")"<<endl;
        exit(0);
    }

    while(1)
    {
        cout<<"send msg to server: ";
        fgets(sendline, 4096, stdin);
        if( send(sockfd, sendline, strlen(sendline), 0) < 0)
        {
            cout<<"send message error: "<<strerror(errno)<<"(errno: "<<errno<<")"<<endl;
            exit(0);
        }
    
        len = recv(sockfd,recvline,n,0);
        if(len < 0)
        {
            cout<<"length: "<<len<<endl;
            break;
        }
        cout<<"receive data: "<<recvline<<", len: "<<len<<endl;
    }
    close(sockfd);
    exit(0);
}
