#ifndef _SOCKET_PACKAGE_H_
#define _SOCKET_PACKAGE_H_	1

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>

#include <iostream>
using std::cout;
using std::end;

#define ERROR_SOCKET	1
#define ERROR_BIND	2
#define ERROR_LISTEN	3
#define LISTENQ		10
#define MAXSIZE		1024

#ifndef S_IFSOCK
#error S_IFSOCK not defined
#endif

int Socket(int family = AF_INET, int type, int protocol)
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

void Bind(int listenfd, struct sockaddr_in *servaddr, int servaddr_size)
{
    if( bind(listenfd, (struct sockaddr*)servaddr, servaddr_size) == -1)
    {
        cout<<"bind socket error"<<strerror(errno)<<"(errno: "<<errno<<")"<<endl;
        exit(ERROR_BIND);
    }
}

void Listen(int listenfd)
{
    if( listen(listenfd, LISTENQ) == -1)
    {
        cout<<"listen socket error"<<strerror(errno)<<"(errno: "<<errno<<")"<<endl;
        exit(ERROR_LISTEN);
    }
}

ssize_t Readn(int sockfd, void *buff, size_t nbytes)
{
    ssize_t nleft = nbytes;
    ssize_t nread = 0;
    char *tmpbuff = buff;

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
    return n - nleft;
}

/**
 * 
 */
ssize_t Writen(int sockfd, const void *buff, size_t len)
{
    size_t nleft = len;
    ssize_t nwriten = 0;
    const char *tempbuff = buff;

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
    return len;
}

/**
 * read the max of maxlen length data from sockfd \
 * and store the data into position which the pointer buff points
 *
 */
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

/**
 * Judge that if an fd is typeof fdtype
 */
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

#endif
