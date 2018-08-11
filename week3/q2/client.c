#include "../../my_includes.h"

int main() {
	int len,result,sockfd;
	struct sockaddr_in address;
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(5600);
	len = sizeof(address);
	result = connect(sockfd,(struct sockaddr*)& address, len);
	if(result == -1) {
		perror("\nCLIENT ERROR");
		exit(1);
	}
	int a,b;
	int ans = 0;
	char c;
	printf("Enter 2 numbers\n");
	scanf("%d",&a);
	scanf("%d",&b);
	printf("Enter operator (*,+,-,/)\n");
	while(c!='+' && c!='-' && c!='/' && c!='*')
		scanf("%c",&c);
	write(sockfd,&a,sizeof(int));
	write(sockfd,&b,sizeof(int));
	write(sockfd,&c,sizeof(char));
	read(sockfd,&ans,sizeof(int));
	printf("%d %c %d = %d\n",a,c,b,ans);
}