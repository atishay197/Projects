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
	int sockfd,len;
	struct sockaddr_in address;
	int result,n;
	while(1)
	{
		printf("Square : ");
		scanf("%d",&n);
		sockfd = socket(AF_INET,SOCK_STREAM,0);
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = inet_addr("127.0.0.1");
		address.sin_port = 1907;
		len = sizeof(address);
		result = connect(sockfd,(struct sockaddr*)&address,len);
		if(result == -1)
		{
			perror("Client Error\n");
			exit(0);
		}
		struct sqid a;
		write(sockfd,&n,8);
		read(sockfd,&a,sizeof(a));
		printf("Square from server : %d from process %d\n",a.sq,a.pid);
		close(sockfd);
	}
}