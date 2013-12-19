#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER_PORT 8888
#define MAX_BUF_SIZE 1024

void udpc_requ(int sockfd,const struct sockaddr_in*addr,int len)
{
   char buffer[MAX_BUF_SIZE];
   int n;
   while(1)
   {
      printf("please input char:\n");
      fgets(buffer,MAX_BUF_SIZE+1,stdin);
      sendto(sockfd,buffer,strlen(buffer),0,(struct sockaddr *)addr,len);
      bzero(buffer,MAX_BUF_SIZE);
   }
}


int main(int argc,char**argv)
{
   int sockfd;
   struct sockaddr_in addr;
   struct hostent*host;

   if(argc!=2)
   {
      fprintf(stderr,"Usage:%s server_ip\n",argv[0]);
      exit(1);
   }

   if((host=gethostbyname(argv[1]))==NULL)
   {
      fprintf(stderr,"Gethostname error\n");
      exit(1);
   }

//socket

   sockfd=socket(AF_INET,SOCK_DGRAM,0);
   if(sockfd<0)
   {  
      fprintf(stderr,"Socket Error:%s\n",strerror(errno));
      exit(1);
   }

//ip port

   bzero(&addr,sizeof(struct sockaddr_in));
   addr.sin_family=AF_INET;
   addr.sin_port=htons(SERVER_PORT);
   /* if(inet_aton(argv[1],&addr.sin_addr)<0)
   {
   fprintf(stderr,"IP error:%s\n",strerror(errno));
   exit(1);
   } */
   addr.sin_addr=*((struct in_addr *)host->h_addr);


   udpc_requ(sockfd,&addr,sizeof(struct sockaddr_in));

//   close(sockfd);
}
