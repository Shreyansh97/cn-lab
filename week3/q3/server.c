#include "../../my_includes.h"

int main() {
	int server_sockfd, client_sockfd;
	int server_len, client_len;
	struct sockaddr_in server_address, client_address;
	int result;
	fd_set readfds,testfds;
	server_sockfd = socket(AF_INET,SOCK_STREAM,0);
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(5600);
	server_len = sizeof(server_address);
	bind(server_sockfd,(struct sockaddr*)&server_address,server_len);
	listen(server_sockfd,5);
	FD_ZERO(&readfds);
	FD_SET(server_sockfd,&readfds);
	time_t tick;
	while(1) {
		char ch;
		int fd,nread;
		testfds = readfds;
		printf("server waiting\n");
		result = select(FD_SETSIZE,&testfds,(fd_set*)0,(fd_set*)0,(struct timeval *)0);
		if(result < 1) {
			perror("server error");
			exit(1);
		}
		for(fd=0;fd<FD_SETSIZE;fd++) {
			if(FD_ISSET(fd,&testfds)) {
				if(fd == server_sockfd) {
					client_len = sizeof(client_address);
					client_sockfd = accept(server_sockfd, (struct sockaddr*)&client_address,&client_len);
					FD_SET(client_sockfd,&readfds);
					printf("adding client on fd %d\n", client_sockfd);
				}
				else {
					ioctl(fd,FIONREAD, &nread);
					if(nread == 0) {
						close(fd);
						FD_CLR(fd, &readfds);
						printf("removing client on fd %d\n", fd);
					}
					else {
						char str[256];
						read(fd,str,sizeof(str));
						tick = time(NULL);
						snprintf(str,sizeof(str),"%s",ctime(&tick));
						write(fd,str,sizeof(str));
					}
				}
			}
		}
	}
}