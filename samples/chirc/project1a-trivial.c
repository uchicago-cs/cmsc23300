#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(int argc, char *argv[])
{
	int serverSocket;
	int clientSocket;
	struct sockaddr_in serverAddr, clientAddr;
	int yes = 1;
	socklen_t sinSize = sizeof(struct sockaddr_in);

	int opt;
	char *port = "6667";

	while ((opt = getopt(argc, argv, "p:o:h")) != -1)
		switch (opt)
		{
			case 'p':
				port = strdup(optarg);
				break;
			case 'o':
				break;
			default:
				printf("ERROR: Unknown option -%c\n", opt);
				exit(-1);
		}

	char *msg = ":bar.example.com 001 user1 :Welcome to the Internet Relay Network user1!user1@foo.example.com\r\n";

	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(atoi(port));
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	
	serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
	bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
	listen(serverSocket, 5);

	while(1)
	{
		clientSocket = accept(serverSocket, (struct sockaddr *) &clientAddr, &sinSize);
		send(clientSocket, msg, strlen(msg), 0);
	}

	close(serverSocket);

	return 0;
}

