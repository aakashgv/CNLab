#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>  // defines hostent structure

int main(int argc,char *argv[]){
    
       int sockfd,newsockfd,portno,n;
       struct sockaddr_in serv_addr,cli_addr;
       
       struct hostent *server;  // hostent : use store info about host such as hostname ,ipv
       
       char buffer[1000];  // size same as in server 
       
         if(argc<3){
               fprintf(stderr,"error : less no. of argument\n");
                exit(1);
         }
         
         portno=atoi(argv[2]);
         
         sockfd=socket(AF_INET,SOCK_STREAM,0);
         
            if(sockfd<0){
                printf("error : opening in socket\n");
               } 
            server=gethostbyname(argv[1]);
                  if(server==NULL)
                         fprintf(stderr,"error,no such host");
                         
                          bzero( (char *) &serv_addr,sizeof(serv_addr) );
                          serv_addr.sin_family=AF_INET;
                          bcopy( (char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr,server->h_length);
                          serv_addr.sin_port=htons(portno);
                          
                          if(connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr) )<0){
                                printf("connection failed");
                          }
                  //}
         //}
         
             while(1){
                            bzero(buffer,1000);
                            fgets(buffer,1000,stdin);
                            n=write(sockfd,buffer,strlen(buffer));
                              if(n<0){
                                   printf("error :on writing");
                              }
                              bzero(buffer,1000);
                              n=read(sockfd,buffer,1000);
                              
                              if(n<0){
                                      printf("error : on reading");
                              }
                              printf("server %s\n",buffer);
                              
                              int i=strncmp("bye",buffer,3);
                              if(i==0)
                                  break;
                }
            //    close(newsockfd);
                close(sockfd);          
      return 0;
}
