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
	int server_sockfd, n, len;
	struct sockaddr_in server_address,client_address;
	server_sockfd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_address.sin_port = 1807;
	len = sizeof(server_address);
	while(1)
	{
		printf("Server waiting...\n");
		bind(server_sockfd,(struct sockaddr *)&server_address,len);
		int recvlen = recvfrom(server_sockfd,&n,sizeof(int),0,(struct sockaddr*)&client_address,&len);
		n = n*n;
		printf("Writing : %d\n",n);
		sendto(server_sockfd,&n,sizeof(int),0,(struct sockaddr*)&client_address,len);
	}
	close(server_sockfd);
}