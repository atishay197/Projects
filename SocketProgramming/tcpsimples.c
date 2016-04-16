#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

struct sqid
{
	int sq;
	int pid;
};

int main()
{
	int server_sockfd, client_sockfd, len;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;
	server_sockfd = socket(AF_INET,SOCK_STREAM,0);
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_address.sin_port = 1907;
	len = sizeof(server_address);
	bind(server_sockfd,(struct sockaddr*)&server_address,len);
	listen(server_sockfd,5);
	while(1)
	{
		struct sqid a;
		int n;
		printf("server waiting\n");
		client_sockfd = accept(server_sockfd,(struct sockaddr*)&client_address,&len);
		if(!fork())
		{
			read(client_sockfd,&n,8);
			printf("Server read : %d\n",n);
			a.sq = n*n;
			a.pid = getpid();
			printf("Server writing %d :: %d ....\n",a.sq,a.pid);
			write(client_sockfd,&a,sizeof(a));
			close(client_sockfd);
		}
	}
}