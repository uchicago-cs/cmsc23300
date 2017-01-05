/* 
 *
 *  CMSC 23300 / 33300 - Networks and Distributed Systems
 *  
 *  A simple multi-threaded server
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

const char *port = "23300";

/* We will use this struct to pass parameters to one of the threads */
struct workerArgs
{
    int socket;
};

void *accept_clients(void *args);
void *service_single_client(void *args);

int main(int argc, char *argv[])
{
    /* The pthread_t type is a struct representing a single thread. */
    pthread_t server_thread;

    /* If a client closes a connection, this will generally produce a SIGPIPE
       signal that will kill the process. We want to ignore this signal, so
       send() just returns -1 when this happens. */
    sigset_t new;
    sigemptyset (&new);
    sigaddset(&new, SIGPIPE);
    if (pthread_sigmask(SIG_BLOCK, &new, NULL) != 0) 
    {
        perror("Unable to mask SIGPIPE");
        exit(-1);
    }

    /* The pthread_create function creates a new thread.
       The first parameter is a pointer to a pthread_t variable, which we can use
       in the remainder of the program to manage this thread.
       The second parameter is used to specify the attributes of this new thread
       (e.g., its stack size). We can leave it NULL here.
       The third parameter is the function this thread will run. This function *must*
       have the following prototype:

           void *f(void *args);

       Note how the function expects a single parameter of type void*. The fourth
       parameter to pthread_create is used to specify this parameter. In this case,
       we have no parameters to pass to the thread function, so we leave it NULL.
       If we _do_ need to pass parameters, we will typically malloc a struct
       with the necessary args. The thread function is typically responsible
       for freeing this struct.

       The thread we are creating here is the "server thread", which will be
       responsible for listening on port 23300 for incoming connections. This thread,
       in turn, will spawn threads to service each incoming connection, allowing
       multiple clients to connect simultaneously.

       Note that, in this particular example, creating a "server thread" is redundant,
       since there will only be one server thread, and the program's main thread (the 
           one running main()) could fulfill this purpose. */
    if (pthread_create(&server_thread, NULL, accept_clients, NULL) < 0)
    {
        perror("Could not create server thread");
        exit(-1);
    }

    pthread_join(server_thread, NULL);

    pthread_exit(NULL);
}


/* This is the function that is run by the "server thread".
   The socket code is similar to oneshot-single.c, except that we will
   use getaddrinfo() to get the sockaddr (instead of creating it manually)
   and we will use sockaddr_storage when accepting a client connection
   (instead of using sockaddr_in, which assumes that the incoming connection
   is coming from an IPv4 host).
   Additionally, this function will spawn a new thread for each new client
   connection.

   See oneshot-single.c and client.c for more documentation on how the socket
   code works.
 */
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
    hints.ai_flags = AI_PASSIVE; // Return my address, so I can bind() to it

    /* Note how we call getaddrinfo with the host parameter set to NULL */
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

    /* Loop and wait for connections */
    while (1)
    {
        /* Call accept(). The thread will block until a client establishes a connection. */
        clientAddr = malloc(sinSize);
        if ((clientSocket = accept(serverSocket, (struct sockaddr *) clientAddr, &sinSize)) == -1) 
        {
            /* If this particular connection fails, no need to kill the entire thread. */
            free(clientAddr);
            perror("Could not accept() connection");
            continue;
        }

        /* We're now connected to a client. We're going to spawn a "worker thread" to handle
           that connection. That way, the server thread can continue running, accept more connections,
            and spawn more threads to handle them. 

           The worker thread needs to know what socket it must use to communicate with the client,
           so we'll pass the clientSocket as a parameter to the thread. Although we could arguably
           just pass a pointer to clientSocket, it is good practice to use a struct that encapsulates
           the parameters to the thread (even if there is only one parameter). In this case, this is
           sone with the workerArgs struct. */
        wa = malloc(sizeof(struct workerArgs));
        wa->socket = clientSocket;

        if (pthread_create(&worker_thread, NULL, service_single_client, wa) != 0) 
        {
            perror("Could not create a worker thread");
            free(clientAddr);
            free(wa);
            close(clientSocket);
            close(serverSocket);
            pthread_exit(NULL);
        }
    }

    pthread_exit(NULL);
}


/* This is the function that is run by the "worker thread".
   It is in charge of "handling" an individual connection and, in this case
   all it will do is send a message every five seconds until the connection
   is closed.

   See oneshot-single.c and client.c for more documentation on how the socket
   code works.
 */
void *service_single_client(void *args) {
    struct workerArgs *wa;
    int socket, nbytes;
    char tosend[100];

    /* Unpack the arguments */
    wa = (struct workerArgs*) args;
    socket = wa->socket;

    /* This tells the pthreads library that no other thread is going to
       join() this thread. This means that, once this thread terminates,
       its resources can be safely freed (instead of keeping them around
       so they can be collected by another thread join()-ing this thread) */
    pthread_detach(pthread_self());

    fprintf(stderr, "Socket %d connected\n", socket);

    while(1)
    {
        sprintf(tosend,"%d -- Hello, socket!\n", (int) time(NULL));

        nbytes = send(socket, tosend, strlen(tosend), 0);

        if (nbytes == -1 && (errno == ECONNRESET || errno == EPIPE))
        {
            fprintf(stderr, "Socket %d disconnected\n", socket);
            close(socket);
            free(wa);
            pthread_exit(NULL);
        }
        else if (nbytes == -1)
        {
            perror("Unexpected error in send()");
            free(wa);
            pthread_exit(NULL);
        }
        sleep(5);
    }

    pthread_exit(NULL);
}

