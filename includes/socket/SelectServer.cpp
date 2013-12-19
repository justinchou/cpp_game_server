#include <iostream>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>

#include <errno.h>

#include <memory.h>

using namespace std;

#define LISTENQ 10
#define MAXLINE 1024
#define SERVER_PORT 6666

int handle_data(int,int,fd_set&);

int main()
{
    int listenfd, connfd;
    struct sockaddr_in cliaddr, servaddr;
    
    if( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        cout<<"create socket error"<<strerror(errno)<<"(errno: "<<errno<<")"<<endl;
        return 1;
    }
    
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERVER_PORT);

    if( bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1)
    {
        cout<<"bind socket error"<<strerror(errno)<<"(errno: "<<errno<<")"<<endl;
        return 2;
    }
    
    if( listen(listenfd, LISTENQ) == -1)
    {
        cout<<"listen socket error"<<strerror(errno)<<"(errno: "<<errno<<")"<<endl;
        return 3;
    }
    
    cout<<"==============  waiting for clients  =============="<<endl;

    int maxfd, sln;
    fd_set readfds, writefds, exceptfds;
    struct timeval timeout;

    FD_ZERO(&readfds);
    FD_ZERO(&writefds);
    FD_ZERO(&exceptfds);

    do{
        timeout.tv_sec = 10;
        timeout.tv_usec = 0;

        FD_SET(listenfd,&readfds);
        FD_SET(listenfd,&writefds);
        FD_SET(listenfd,&exceptfds);
        maxfd = listenfd + 1;

        fcntl(listenfd,F_SETFL,O_NONBLOCK);
//        sln = select(maxfd+1, &readfds, &writefds, &exceptfds, &timeout);
        sln = select(maxfd+1, &readfds, NULL, NULL, NULL);
        if (sln == -1)
        {
            cout<<"select failed: "<<strerror(errno)<<"(errno: "<<errno<<")"<<endl;
            return 4;
        } else if(sln == 0) {
            cout<<"select time out! sln:"<<sln<<" maxfd:"<<maxfd<<endl;
        } else if(sln > 0) {
            cout<<"in here, select find socket data have changed! sln:"<<sln<<" maxfd:"<<maxfd<<endl;
        }

cout<<"sln:"<<sln<<" maxfd:"<<maxfd<<endl;
        
        for(int i = 0; i <= maxfd && sln > 0; i++)
        {
            if(FD_ISSET(i,&readfds))
            {

cout<<"in if: i:"<<i<<" listenfd:"<<listenfd<<endl;
                --sln;
                if(i == listenfd)
                {
cout<<"new connect i:"<<i<<endl;
                    socklen_t clilen = sizeof(cliaddr);
                    connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &clilen);
                    if(connfd == -1)
                    {
                        if ((errno != EAGAIN) && (errno != EWOULDBLOCK))
                        {
                            cout<<"accept new client failed: "<<strerror(errno)<<"(errno: "<<errno<<")"<<endl;
                            continue;
                        }
                    }
                    cout<<"New Client Connected, Ip: ("<<inet_ntoa(cliaddr.sin_addr)<<")."<<endl;
                    FD_SET(connfd, &readfds);
cout<<"set connection fd:"<<connfd<<endl;
                    maxfd = ( connfd > maxfd ? connfd+1 : maxfd+1 );
                } else {
cout<<"old connect i:"<<i<<endl;
                    handle_data(i,connfd,readfds);
                }

            } // end if
        } // end for

    } while(true);

    return 0;
}

int handle_data(int clientfd, int connfd, fd_set &readfds)
{
    int readbits;
    char line[MAXLINE];
    char szHtmlBuf[] = "HTTP/1.1 200 OK\r\n" \
"Date: Sat, 05 Jan 2013 03:13:29 GMT\r\n" \
"Vary: Accept-Encoding\r\n" \
"Content-Type: text/html; charset=gb2312\r\n" \
"Accept-Ranges: bytes\r\n" \
"Content-Length: 57\r\n" \
"\r\n" \
"<html> <head>欢迎光临</head> <body>屌丝逆袭季</body></html>";

    cout<<"receive data now !"<<endl;

    while( (readbits = recv(connfd, line, MAXLINE, 0)) < 0
    	&& (errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN)
    ){
        cout<<"receive bits length:"<<readbits<<endl;
        cout<<"fd is:"<<connfd<<"; err code is:"<<errno<<" != "<<EINTR<<" or "<<EWOULDBLOCK<<" or "<<EAGAIN<<endl;
        if(errno == ECONNRESET)
        {
            close(clientfd);
            FD_CLR(clientfd, &readfds);
            cout<<"exit in exception:"<<strerror(errno)<<"(errno: "<<errno<<")"<<endl;
            return 1;
        } else {
            cout<<"connection reset by peer."<<strerror(errno)<<"(errno: "<<errno<<")"<<endl;
            return 2;
        }
    }

    if(readbits == 0)
    {
        close(clientfd);
        FD_CLR(clientfd,&readfds);
        cout<<"connection exit"<<endl;
    } else {
        line[readbits] = 0;
        cout<<"receive data: "<<line<<endl;

        write(clientfd, szHtmlBuf, sizeof(szHtmlBuf));
    }

    return 0;
}
