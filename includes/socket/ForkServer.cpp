#include <iostream>
#include <stdlib.h>
#include <string>

#include <errno.h>
#include <semaphore.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <memory.h>

#define MAXLINE 4096

using std::cout;
using std::endl;

sem_t sem;
int fpid[10];

int main()
{

    int listenfd, connfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t clilen;
    char buff[MAXLINE];
    int n;

    sem_init(&sem,0,0);

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

    sem_post(&sem);
//    sem_wait(&sem);

    while(1)
    {
        clilen = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &clilen);
        pid_t pid;
        if( (pid = fork()) == 0)
        {
            close(listenfd);

            if( connfd == -1 )
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
    
            exit(0);
        } else {
            cout<<"pid is: "<<pid<<endl;
            close(connfd);
        }
    }
    
}
