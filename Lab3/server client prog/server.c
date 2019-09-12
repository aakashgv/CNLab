#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>


int main(int argc,char *argv[]){

      if(argc<2){
               fprintf(stderr,"error : port no. not provided\n");
               exit(1);
      }
          int sockfd,newsockfd,portno,n;
          socklen_t clilen; // datatype in socket.h  32 bit datatype
          
          char buffer[1000];
          
          struct sockaddr_in serv_addr,cli_addr;  // it give address and included in netinet/in.h
          
          sockfd=socket(AF_INET,SOCK_STREAM,0);
          
          if(sockfd<0){
                // faliure
                   printf("error in opening socket\n");
          }
              bzero((char *)&serv_addr,sizeof(serv_addr));// alternative of memset
              
              portno=atoi(argv[1]);
 
            serv_addr.sin_family=AF_INET;
            serv_addr.sin_addr.s_addr=INADDR_ANY;
            serv_addr.sin_port=htons(portno);  // htons : host to network 
                           
                if( bind(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr))<0){
                             printf("error : binding fail");
                }           
                
               listen(sockfd,10);  // 10 clients connect to server at a time
                         
               clilen=sizeof(cli_addr);
               
               newsockfd=accept(sockfd,(struct sockaddr *) &cli_addr,&clilen );               
               if(newsockfd<0){
                            printf("error :"); 
               }               
               
                 while(1){
                            bzero(buffer,1000);
                             n=read(newsockfd,buffer,1000);
                           if(n<0){
                                   printf("error : on reading");
                           }                          
                           printf("client :%s\n",buffer);
                           bzero(buffer,1000);
                           
                           fgets(buffer,1000,stdin);
                            
                           n=write(newsockfd,buffer,strlen(buffer)); 
                            if(n<0){
                                   printf("error : on writing");
                            }
                            int i=strncmp("bye",buffer,3);
                            if(i==0){
                                     break;
                             }
                 }              
                 
                 close(newsockfd);
                 close(sockfd);
     return 0;
}
