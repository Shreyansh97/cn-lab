#include "../../my_includes.h"

int main(){
	int sd;
	int buf[50][50];
	int rows,columns;
	struct sockaddr_in sadd,cadd;
	sd=socket(AF_INET,SOCK_DGRAM,0);
	sadd.sin_addr.s_addr=htonl(INADDR_ANY);
	sadd.sin_family=AF_INET;
	sadd.sin_port=htons(10600);
	int result = bind(sd,(struct sockaddr*)&sadd,sizeof(sadd));
	while(1) {
		int len=sizeof(cadd);
		recvfrom(sd,&rows,sizeof(int),0,(struct sockaddr*)&cadd,&len);
		recvfrom(sd,&columns,sizeof(int),0,(struct sockaddr*)&cadd,&len);
		for(int i=0;i<rows;i++)
			recvfrom(sd,buf[i],columns*sizeof(int),0,(struct sockaddr*)&cadd,&len);
		printf("%d rows and %d columns\n", rows, columns);
		printf("Received matrix\n");
		for(int i=0;i<rows;i++) {
			for(int j=0;j<columns;j++)
				printf("%d ", buf[i][j]);
			printf("\n");
		}	
	}
	return 0;
}