#include "../../my_includes.h"

int main() {
	int sockfd, newsockfd, portno, clilen;
	struct sockaddr_in seraddr,cliaddr;
	int i,value;
	sockfd = socket(AF_INET, SOCK_STREAM,0);
	seraddr.sin_family = AF_INET;
	seraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	seraddr.sin_port = htons(5600);
	bind(sockfd,(struct sockaddr*)&seraddr,sizeof(seraddr));
	listen(sockfd,5);
	while(1) {
		clilen = sizeof(clilen);
		newsockfd = accept(sockfd,(struct sockaddr*)&cliaddr,&clilen);
		if(fork()==0) {
			printf("ACCEPTED NEW CONNECTION\n");
			int a,b;
			char op;
			read(newsockfd,&a,sizeof(int));
			read(newsockfd,&b,sizeof(int));
			read(newsockfd,&op,sizeof(char));
			switch(op) {
				case '*' : a*=b;
				break;
				case '/' : a/=b;
				break;
				case '-' : a-=b;
				break;
				case '+' : a+=b;
				break;
				default : a=-1;
			}
			write(newsockfd,&a,sizeof(int));
		}
		else
			close(newsockfd);
	}
}