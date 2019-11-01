#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
void error(const char *msg)
{
	perror(msg);
	exit(0);
}

int main(int argc, char *argv[])
{
	int sockfd, portno, n;
	char buffer[256];
	hostent *server;
	sockaddr_in serv_addr;
	if (argc < 3)
	{
		fprintf(stderr, "usage %s hostname port \n", argv[0]);
		exit(0);
	}
	portno = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		error("Error opening socket");
	}
	server = gethostbyname(argv[1]);
	if (server == NULL)
	{
		fprintf(stderr, "Error,no such host\n");
		exit(1);
	}
	printf("direccion de serv_addr \n : %s \n", (char *)&serv_addr);

	bzero((char *)&serv_addr, sizeof(serv_addr));

	printf("direccion de serv_addr (postBorrado)\n :  %s \n", (char *)&serv_addr);

	serv_addr.sin_family = AF_INET;

	bcopy(server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length); //no se que hace
	serv_addr.sin_port = htons(portno);

	if (connect(sockfd, (sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) // por que (sockaddr*)&serv_addr no me da error de parseo?

		while (1)
		{
			bzero(buffer, sizeof(buffer));

			n = read(sockfd, buffer, 255);
			printf("%lo", strlen(buffer));

			if (n < 0)
			{
				error("Error reading socket");
				bzero(buffer, 255); //para que lo limpio?
			}
			printf("Server:%s \n", buffer);

			fgets(buffer, sizeof(buffer), stdin);

			write(sockfd, buffer, strlen(buffer));
			if (n < 0)
				error("Error writting socket");

			printf("Server: %s \n", buffer);

			if (n < 0)
				error("Error writting socket");

			int i = strcmp("bye", buffer);
			if (i == 0)
				break;
		}

	close(sockfd);
	return 0;
}
