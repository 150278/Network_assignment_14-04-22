#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>


void handleClient(int connfd);


int main()
{
	int sock_fd, connfd, retval;
	pid_t childpid;

	socklen_t clilen;
	struct sockaddr_in clientaddr, servaddr;

	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(sock_fd < 0)
	{
		perror("sock: ");
		exit(1);
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); //htonl(INADDR_ANY);
	servaddr.sin_port = htons(8000); // 16 bit short 	TCP protocol HTTP---port

	retval = bind(sock_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	if(retval < 0)
	{
		perror("bind: ");
		exit(2);
	}

	listen(sock_fd, 5);

	while(1)
	{
		char s_buf[200];
		char r_buf[200];
		pid_t p;

		int n;

		clilen = sizeof(clientaddr);
		connfd = accept(sock_fd, (struct sockaddr *) &clientaddr, &clilen);
		printf("client connected\n");
		
		p = fork();
		if(p == 0)
		{
			close(sock_fd);
			handleClient(connfd);
		}
		close(connfd);
	}

	return 0;
}


void handleClient(int connfd)
{
	int n;
	char buff[200];

	n = read(connfd, buff, 200);
	buff[n] = '\0';

	printf("Data rec'd from client : %s\n",buff);
	printf("\nrequested handled by server: %d\n",getpid());
	write(connfd, "Good bye", 8);

	printf("\nData sended to client\n");
        exit(0);	//terminate child
}
