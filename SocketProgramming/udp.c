#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	int sockfd,len,n;
	struct sockaddr_in address;
	sockfd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = 1807;
	len = sizeof(address);
	while(1)
	{
		printf("Enter number : ");
		scanf("%d",&n);
		sendto(sockfd,&n,8,0,(struct sockaddr *)&address,len);
		recvfrom(sockfd,&n,8,0,(struct sockaddr *)&address,&len);
		printf("Value from server : %d\n",n);
	}
	return 0;
}