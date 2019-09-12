#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
 #include <sys/socket.h> 
 #include <netinet/in.h>
 #include <stdlib.h>
#define SERVER_PORT 9898
#define BUFFER_SIZE 100

int main (int argc,char *argv[]) {
char buf[100];
struct sockaddr_in cliaddr,servaddr;
int sockfd,confd,clilen;
sockfd = socket(AF_INET , SOCK_STREAM , 0) ;
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(SERVER_PORT);
servaddr.sin_addr.s_addr =inet_addr(argv[1]) ; // or inet_pton()
connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) ;
clilen = sizeof(cliaddr);

printf("Enter data:\n");
 scanf("%s",buf) ;
write(sockfd, buf, BUFFER_SIZE);
read(sockfd, buf, BUFFER_SIZE); printf("Received Data :%s\n",buf);
close(sockfd);
exit(0);
}
