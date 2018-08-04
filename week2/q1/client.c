#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

int main() {
	int len,result,sockfd,n=1;
	struct sockaddr_in address;
	char ch[256],buf[256];

	sockfd = socket(AF_INET,SOCK_STREAM,0);
	address.sin_family=AF_INET;
	address.sin_addr.s_addr=htonl(INADDR_ANY);
	address.sin_port=htons(5600);
	len=sizeof(address);
	result = connect(sockfd,(struct sockaddr*)&address,len);
	if(result == -1) {
		perror("\nCLIENT ERROR");
		exit(1);
	}
	write(sockfd,ch,0);
	printf("RESPONSE : \n");
	read(sockfd,buf,sizeof(buf));
	puts(buf);
}