#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

struct prog
{
	char prog[10000];
	int pid;
	int size;
};

int main()
{
	int client_sockfd,server_sockfd,len;
	struct sockaddr_in client_address;
	struct sockaddr_in server_address;
	server_sockfd = socket(AF_INET,SOCK_STREAM,0);
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_address.sin_port = 1902;
	len = sizeof(server_address);
	bind(server_sockfd,(struct sockaddr*)&server_address,len);
	listen(server_sockfd,5);
	while(1)
	{
		char buffer[1000];
		struct prog a;
		printf("server waiting...\n");
		client_sockfd = accept(server_sockfd,(struct sockaddr*)&client_address,&len);
		read(client_sockfd,&a,sizeof(a));
		int openid = open("recieve.out",O_WRONLY,777);
		chmod("recieve.out",S_IXOTH|S_IXGRP|S_IXUSR);
		write(openid,a.prog,a.size);
		FILE *in;
		FILE *popen();
		if(!(in = popen("./recieve.out","r")))
			exit(1);
		while(fgets(buffer,sizeof(buffer),in)!=NULL)
			printf("%s\n",buffer);
		pclose(in);
		printf("Server read....\n");
		write(client_sockfd,&buffer,1000);
		printf("Written to client...\n");
		close(client_sockfd);
	}
	close(server_sockfd);
}