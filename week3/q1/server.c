#include "../../my_includes.h"

void sort(int *a,int n) {
	for(int i=0;i<n;i++) {
		for(int j=0;j<n-i-1;j++) {
			if(a[j] > a[j+1]) {
				int t = a[j];
				a[j] = a[j+1];
				a[j+1] = t;
			}
		}
	}
}

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
			int buf[256];
			int n;
			read(newsockfd,&n,sizeof(int));
			read(newsockfd,buf,sizeof(buf));
			sort(buf,n);
			int p = getpid();
			write(newsockfd,&p,sizeof(int));
			write(newsockfd,buf,sizeof(buf));
			char s[256];
			printf("Process id %d\n",getpid() );
		}
		else
			close(newsockfd);
	}
}