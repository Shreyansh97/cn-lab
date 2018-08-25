#include "../../my_includes.h"

int main(){
	int sd;
	struct sockaddr_in address;
	sd=socket(AF_INET,SOCK_DGRAM,0);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(10600);
	int rows = 5;
	int columns = 4;
	int arr[5][4] = {
		{5,6,7,8},
		{9,10,11,12},
		{13,14,15,16},
		{1,2,3,4},
		{17,18,19,20}
	};
	int len=sizeof(address);
	sendto(sd,&rows,sizeof(int),0,(struct sockaddr*)&address,len);
	sendto(sd,&columns,sizeof(int),0,(struct sockaddr*)&address,len);
	for(int i=0;i<rows;i++)
		sendto(sd,arr[i],sizeof(int)*columns,0,(struct sockaddr*)&address,len);
	return 0;
}