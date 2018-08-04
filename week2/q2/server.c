#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <ctype.h>

int main() {
	struct sockaddr_in sa , cli;
	int sockfd , conntfd;
	int len,ch;
	bzero(&sa,sizeof(sa));
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if (sockfd < 0) {
		printf("Error in socket\n");
		exit(0);
	} else
		printf("socket opened\n");
	sa.sin_port = htons(5600);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(sockfd,(struct sockaddr*)&sa,sizeof(sa)) < 0)
		printf("Error in binding\n");
	else
		printf("Binded successfully\n");
	listen(sockfd,50);
	while(1) {
		len = sizeof(ch);
		conntfd = accept(sockfd,(struct sockaddr*)&cli,&len);
		printf("Accepted\n");
		while(1) {
			char buf[256];
			read(conntfd,buf,sizeof(buf));
			printf("MESSAGE: %s\n",buf);
			printf("CLIENT IP: %d\nPORT NO: %d\n",cli.sin_addr.s_addr,cli.sin_port);
			for(int i=0;i<strlen(buf);i++)
				buf[i] = toupper(buf[i]);
			write(conntfd,buf,sizeof(buf));
		}
	}
}