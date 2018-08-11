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
	printf("Enter number of elements : ");
	int numelements;
	scanf("%d",&numelements);
	printf("Enter elements\n");
	int* arr = (int*) malloc(sizeof(int)*numelements);
	for(int i=0;i<numelements;i++)
		scanf("%d",arr+i);
	write(sockfd,&numelements,sizeof(int));
	write(sockfd,arr,sizeof(int)*numelements);
	int p;
	read(sockfd,&p,sizeof(int));
	read(sockfd,arr,sizeof(int)*numelements);
	printf("Sorted array from server : \n");
	for(int i=0;i<numelements;i++)
		printf("%d ", arr[i]);
	printf("\nServer process id : %d\n", p);
}