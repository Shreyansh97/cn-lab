#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <unistd.h>

int main() {
	struct sockaddr_in sa , cli;
	int sockfd , conntfd;
	int len,ch;
	char str[200];
	time_t tick;
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
		tick = time(NULL);
		snprintf(str,sizeof(str),"time : %sserver pid : %d \n",ctime(&tick),getpid());
		printf("%s",str);
		write(conntfd,str,sizeof(str));
	}
}