#ifndef _SOCKET_PACKAGE_H_
#define _SOCKET_PACKAGE_H_	1

#ifndef __DEBUG__
#define __DEBUG__ 0
#endif

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <iostream>
using std::cout;
using std::endl;

#define ERROR_SOCKET	1
#define ERROR_BIND	2
#define ERROR_LISTEN	3
#define ERROR_ACCEPT	4
#define ERROR_CONNECT	5

#define LISTENQ		10
#define MAXSIZE		1024
#define MAXLINE		1024

#ifndef S_IFSOCK
#error S_IFSOCK not defined
#endif



int Socket(int family = AF_INET, int type=SOCK_STREAM, int protocol=0)
{
    int listenfd;
    listenfd = socket(family, type, protocol);
    if( listenfd == -1)
    {
        cout<<"create socket error"<<strerror(errno)<<"(errno: "<<errno<<")"<<endl;
        exit(ERROR_SOCKET);
    }
    return listenfd;
}

int Bind(int listenfd, struct sockaddr *servaddr, int servaddr_size)
{
    int b = bind(listenfd, servaddr, servaddr_size);
    if( b == -1 )
    {
        cout<<"bind socket error"<<strerror(errno)<<"(errno: "<<errno<<")"<<endl;
        exit(ERROR_BIND);
    }
    return b;
}

int Bind(int listenfd, struct sockaddr_in *servaddr, int servaddr_size)
{
    int b = bind(listenfd, (struct sockaddr*)servaddr, servaddr_size);
    if( b == -1 )
    {
        cout<<"bind socket error"<<strerror(errno)<<"(errno: "<<errno<<")"<<endl;
        exit(ERROR_BIND);
    }
    return b;
}

int Listen(int listenfd, int backlog)
{
    char *ptr;
    int l;

    if( (ptr = getenv("LISTENQ")) != NULL)
    {
         backlog = atol(ptr);
    }

    l = listen(listenfd, backlog);
    if( l < 0)
    {
         cout<<"Listen error! "<<strerror(errno)<<" (errno: "<<errno<<")"<<endl;
         exit(ERROR_LISTEN);
    }

    return l;
}

int Listen(int listenfd)
{
    int l = listen(listenfd, LISTENQ);
    if( l == -1 )
    {
        cout<<"listen socket error"<<strerror(errno)<<"(errno: "<<errno<<")"<<endl;
        exit(ERROR_LISTEN);
    }
    return l;
}

int Accept(int listenfd, struct sockaddr *cliaddr, socklen_t *clilen)
{
    int connfd = accept(listenfd, cliaddr, clilen);
    if(connfd == -1)
    {
        if(errno == EINTR)
        {
            return  Accept(listenfd, cliaddr, clilen);
        }
        cout<<"accept client error"<<strerror(errno)<<"(errno: "<<errno<<")"<<endl;
        exit(ERROR_ACCEPT);
    }
    return connfd;
}

int Accept(int listenfd, struct sockaddr_in *cliaddr, socklen_t *clilen)
{
    int connfd = accept(listenfd, (struct sockaddr*)cliaddr, clilen);
    if(connfd == -1)
    {
        if(errno == EINTR)
        {
            return  Accept(listenfd, cliaddr, clilen);
        }
        cout<<"accept client error"<<strerror(errno)<<"(errno: "<<errno<<")"<<endl;
        exit(ERROR_ACCEPT);
    }
    return connfd;
}

int Close(int sockfd)
{
    return close(sockfd);
}

int Connect(int listenfd, struct sockaddr *servaddr, int servaddr_size)
{
    int c = connect(listenfd,servaddr,servaddr_size);
    if(c == -1)
    {
        cout<<"bind socket error"<<strerror(errno)<<"(errno: "<<errno<<")"<<endl;
        exit(ERROR_CONNECT);
    }
    return c;
}




ssize_t Read(int sockfd, void *buff, size_t nbytes)
{
    int nread;
    char *tmpbuff = (char *)buff;

    nread = read(sockfd, tmpbuff, nbytes);
    if(nread < 0)
    {
        if(errno == EINTR)
        {
            return Read(sockfd, buff, nbytes);
        }
        else
        {
            return -1;
        }
    }
    tmpbuff[nread] = '\0';
    return nread;
}

ssize_t Readn(int sockfd, void *buff, size_t nbytes)
{
    ssize_t nleft = nbytes;
    ssize_t nread = 0;
    char *tmpbuff = (char *)buff;

    while(nleft > 0)
    {

        nread = read(sockfd, tmpbuff, nleft);
        if (nread < 0)
        {
            if (errno == EINTR)
            {
                nread = 0;
            }
            else
            {
                return -1;
            }
        }
        else if (nread == 0)
        {
            break;
        }
        else
        {
            nleft -= nread;
            tmpbuff += nread;
        }

    }
    return nbytes - nleft;
}

ssize_t Write(int sockfd, const void *buff, size_t nbytes)
{
    int nwrite;
    char *tmpbuff = (char *)buff;

    nwrite = write(sockfd, tmpbuff, nbytes);
    if(nwrite < 0)
    {
        if(errno == EINTR)
        {
            Write(sockfd, buff, nbytes);
        }
        else
        {
            return -1;
        }
    }
    tmpbuff[nwrite] = '\0';
    return nwrite;
}

ssize_t Writen(int sockfd, const void *buff, size_t nbytes)
{
    size_t nleft = nbytes;
    ssize_t nwriten = 0;
    const char *tmpbuff = (const char *)buff;

    while(nleft > 0)
    {
        nwriten = write(sockfd, tmpbuff, nleft);
        if(nwriten <= 0)
        {
            if(errno == EINTR)
            {
                nwriten = 0;
            }
            else
            {
                return -1;
            }
        }
        else
        {
            nleft -= nwriten;
            tmpbuff += nwriten;
        }
    }
    return nwriten;
}

ssize_t Readline(int sockfd, void *buff, size_t maxlen)
{
//    ssize_t n     = 0,
//            rc    = 0;
//    char c        = 0,
//         *tmpbuff = buff;
//
//    for (n = 1; n<maxlen;)
//    {
//        rc = read(sockfd, &c, 1);
//        if(rc != 1)
//        {
//            if(errno == EINTR)
//            {
//                continue;
//            }
//            return -1;
//        }
//        else
//        {
//            *tmp++ = c;
//            if(c == '\n')
//            {
//
//            } else if (rc == 0)
//        }
//    }
}

char *Fgets(char *s, int size, FILE *stream)
{
    return fgets(s, size, stream);
}

int Fputs(const char *s, FILE *stream)
{
    return fputs(s, stream);
}



void sig_chld(int signo)
{
    pid_t pid;
    int stat;
    while( (pid = waitpid(-1,&stat,WNOHANG)) > 0)
    {
        cout<<"child "<<pid<<" terminated"<<endl;
    }
    return;
}

typedef void Sigfunc(int);
Sigfunc *Signal(int signo, Sigfunc *func)
{
    struct sigaction act, oact;

    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    if(signo == SIGALRM) {
#ifdef SA_INTERRUPT
        act.sa_flags |= SA_INTERRUPT;
#endif
    } else {
#ifdef SA_RESTART
        act.sa_flags |= SA_RESTART;
#endif
    }

    if(sigaction(signo,&act,&oact)<0)
    {
        return SIG_ERR;
    }
    return oact.sa_handler;
}


int Isfdtype(int fd, int fdtype)
{
    struct stat buf;
    if(fstat(fd,&buf) < 0)
    {
        return -1;
    }
    
    if( (buf.st_mode & S_IFMT) == fdtype)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int CheckArgc(int argc, int except)
{
    int dert = argc - except;
    if( dert < 0 )
    {
        cout<<"argv num "<<argc<<" less than except "<<except<<endl;
        exit(dert);
    }
    return argc;
}

#endif
