//1.Write a udp client server program,client writing messages to server program and server
//return back the same toggled msg to client
//Abhishek sahu

#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>

#define PORT 8000

int main()
{
	int sockfd1;

	struct sockaddr_in servaddr;

	sockfd1 = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd1 < 0)
	{
		perror("socket: ");
		exit(1);
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	connect(sockfd1, (struct sockaddr *) &servaddr, sizeof(servaddr));
	printf("Client connecting to server.............\n");

	while(1)
	{
		char buff[100];
		int n;

		printf("Enter message to send to server: \n");
		gets(buff);
	
		send(sockfd1, buff, strlen(buff), 0);
		printf("Data sended to server\n");

		n = recv(sockfd1, buff, sizeof(buff), 0);
		if(n < 0)
		{
			perror("recv: ");
			exit(4);
		}
		printf("Rev'd data from server : %s\n", buff);		
	}	

	close(sockfd1);
	return 0;
}