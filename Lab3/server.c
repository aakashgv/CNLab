#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
 #include <sys/socket.h> 
 #include <netinet/in.h>
#define SERVER_PORT 9898
#define BUFFER_SIZE 100
int main() {
	char buf[100];
	struct sockaddr_in cliaddr,servaddr;
	int sockfd,confd,clilen;
	sockfd = socket(AF_INET , SOCK_STREAM , 0) ;

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERVER_PORT);
	servaddr.sin_addr.s_addr =htonl( INADDR_ANY) ;
	bind(sockfd, (struct sockaddr *)&servaddr,sizeof(servaddr));
	listen(sockfd,10);
	while(1) {
		clilen=sizeof(cliaddr);
		confd= accept(sockfd,(struct sockaddr *)&cliaddr,&clilen);
		/* printf("Client IP: %s\n", inet_ntoa(cliaddr.sin_addr)); */
		/* printf("Client Port: %hu\n", ntohs(cliaddr.sin_port)); */
		read(confd, buf, BUFFER_SIZE); printf("Received:%s\n",buf);
		write(confd, buf, BUFFER_SIZE);
		close(confd);
	}
	return 0;
}
