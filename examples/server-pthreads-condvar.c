/* 
 *
 *  CMSC 23300 / 33300 - Networks and Distributed Systems
 *  
 *  A simple multi-threaded server that uses a condition
 *  variable to signal an event from one thread to another.
 *  
 *  Written by: Borja Sotomayor
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>
#include <signal.h>
#include <errno.h>
#include <time.h>

#define NLOOPS 1000000

const char *port = "23300";

pthread_mutex_t lock;
pthread_cond_t cv_setup_done;

struct workerArgs
{
	int socket;
	int setup_done;
};

void *accept_clients(void *args);
void *service_single_client(void *args);

int main(int argc, char *argv[])
{
	pthread_t server_thread, printer_thread;

	sigset_t new;
	sigemptyset (&new);
	sigaddset(&new, SIGPIPE);
	if (pthread_sigmask(SIG_BLOCK, &new, NULL) != 0) 
	{
		perror("Unable to mask SIGPIPE");
		exit(-1);
	}

	pthread_mutex_init(&lock, NULL);
	pthread_cond_init(&cv_setup_done, NULL);

	if (pthread_create(&server_thread, NULL, accept_clients, NULL) < 0)
	{
		perror("Could not create server thread");
		exit(-1);
	}

	pthread_join(server_thread, NULL);

	pthread_mutex_destroy(&lock);
	pthread_cond_destroy(&cv_setup_done);

	pthread_exit(NULL);
}

void *accept_clients(void *args)
{
	int serverSocket;
	int clientSocket;
	pthread_t worker_thread;
	struct addrinfo hints, *res, *p;
	struct sockaddr_storage *clientAddr;
	socklen_t sinSize = sizeof(struct sockaddr_storage);
	struct workerArgs *wa;
	int yes = 1;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if (getaddrinfo(NULL, port, &hints, &res) != 0)
	{
		perror("getaddrinfo() failed");
		pthread_exit(NULL);
	}

	for(p = res;p != NULL; p = p->ai_next) 
	{
		if ((serverSocket = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) 
		{
			perror("Could not open socket");
			continue;
		}

		if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
		{
			perror("Socket setsockopt() failed");
			close(serverSocket);
			continue;
		}

		if (bind(serverSocket, p->ai_addr, p->ai_addrlen) == -1)
		{
			perror("Socket bind() failed");
			close(serverSocket);
			continue;
		}

		if (listen(serverSocket, 5) == -1)
		{
			perror("Socket listen() failed");
			close(serverSocket);
			continue;
		}

		break;
	}
	
	freeaddrinfo(res);

	if (p == NULL)
	{
    		fprintf(stderr, "Could not find a socket to bind to.\n");
		pthread_exit(NULL);
	}

	while (1)
	{
		clientAddr = malloc(sinSize);
		if ((clientSocket = accept(serverSocket, (struct sockaddr *) clientAddr, &sinSize)) == -1) 
		{
			free(clientAddr);
			perror("Could not accept() connection");
			continue;
		}

		wa = malloc(sizeof(struct workerArgs));
		wa->socket = clientSocket;
		wa->setup_done = 0;

		pthread_mutex_lock(&lock);
		if (pthread_create(&worker_thread, NULL, service_single_client, wa) != 0) 
		{
			perror("Could not create a worker thread");
			free(clientAddr);
			free(wa);
			close(clientSocket);
			close(serverSocket);
			pthread_exit(NULL);
		}

		printf("\n(%d) accept_clients(): Waiting for thread setup to complete.\n", clientSocket);
		while(!wa->setup_done)
			pthread_cond_wait(&cv_setup_done, &lock);
		printf("(%d) accept_clients(): Woke up (setup complete).\n", clientSocket);
		pthread_mutex_unlock(&lock);
	}

	pthread_exit(NULL);
}

void *service_single_client(void *args) {
	struct workerArgs *wa;
	int socket, nbytes, i;
	char buffer[100];

	wa = (struct workerArgs*) args;
	socket = wa->socket;

	printf("(%d) service_single_client(): Starting setup.\n", socket);

	pthread_detach(pthread_self());

	sleep(2); // Pretent like we're doing some work.

	wa->setup_done = 1;
	printf("(%d) service_single_client(): Setup complete.\n", socket);
	pthread_mutex_lock(&lock);
	pthread_cond_signal(&cv_setup_done);
	pthread_mutex_unlock(&lock);


	while(1)
	{
		nbytes = recv(socket, buffer, sizeof(buffer), 0);
		if (nbytes == 0)
			break;
		else if (nbytes == -1)
		{
			perror("Socket recv() failed");
			close(socket);
			pthread_exit(NULL);
		}
		/* Ignore anything that's actually recv'd. We just want
		   to keep the connection open until the client disconnects */
	}

	printf("(%d) service_single_client(): Disconnected.\n", socket);
	close(socket);
	pthread_exit(NULL);
}

