#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

struct prog
{
	char prog[10000];
	int pid;
	int size;
};

int main()
{
	int sockfd,len;
	struct sockaddr_in address;
	char c;
	struct prog a;
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = 1902;
	len = sizeof(address);
	int result = connect(sockfd,(struct sockaddr*)&address,len);
	if(result == -1)
	{
		perror("Error in client\n");
		exit(0);
	}
	char buffer[1000];
	int openid = open("runner",O_RDONLY,777);
	a.size = read(openid,a.prog,10000);
	printf("Writing to server....\n");
	write(sockfd,&a,sizeof(a));
	printf("Waiting for server....\n");
	read(sockfd,&buffer,1000);
	printf("Value from server : %s\n",buffer);
	close(sockfd);
	return 0;
}