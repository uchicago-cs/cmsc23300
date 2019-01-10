/* 
 *
 *  CMSC 23300 - Networks and Distributed Systems
 *  
 *  A simple multi-threaded server that requires a mutex lock to avoid a race condition.
 *
 *  The code is nearly identical to server-pthreads.c. Look for comments with the test
 *  "ADDED" to see what has been changed exactly.
 *
 *  To actually use the lock, you must compile with -DMUTEX
 *  
 *  Written by: Borja Sotomayor
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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

#define NLOOPS (1000000)

/* ADDED: A "server context" struct that contains information that needs to be shared
 * amongst all the worker threads. It contains a number of connections, along with
 * a mutex to protect access to the number of connections.
 */
struct server_ctx
{
    unsigned int num_connections;
    pthread_mutex_t lock;
};

struct worker_args
{
    int socket;
    /* ADDED: We need to pass the server context to the worker thread */
    struct server_ctx *ctx;
};

void *service_single_client(void *args);

int main(int argc, char *argv[])
{
    /* ADDED: Malloc the server context and initialize its values,
     * which includes initializing the mutex.*/
    struct server_ctx *ctx = calloc(1, sizeof(struct server_ctx));
    ctx->num_connections = 0;
    pthread_mutex_init(&ctx->lock, NULL);

    sigset_t new;
    sigemptyset (&new);
    sigaddset(&new, SIGPIPE);
    if (pthread_sigmask(SIG_BLOCK, &new, NULL) != 0) 
    {
        perror("Unable to mask SIGPIPE");
        exit(-1);
    }

    int server_socket;
    int client_socket;
    pthread_t worker_thread;
    struct addrinfo hints, *res, *p;
    struct sockaddr_storage *client_addr;
    socklen_t sin_size = sizeof(struct sockaddr_storage);
    struct worker_args *wa;
    int yes = 1;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if (getaddrinfo(NULL, "23300", &hints, &res) != 0)
    {
        perror("getaddrinfo() failed");
        pthread_exit(NULL);
    }

    for(p = res;p != NULL; p = p->ai_next)
    {
        if ((server_socket = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
        {
            perror("Could not open socket");
            continue;
        }

        if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
        {
            perror("Socket setsockopt() failed");
            close(server_socket);
            continue;
        }

        if (bind(server_socket, p->ai_addr, p->ai_addrlen) == -1)
        {
            perror("Socket bind() failed");
            close(server_socket);
            continue;
        }

        if (listen(server_socket, 5) == -1)
        {
            perror("Socket listen() failed");
            close(server_socket);
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
        client_addr = calloc(1, sin_size);
        if ((client_socket = accept(server_socket, (struct sockaddr *) client_addr, &sin_size)) == -1)
        {
            free(client_addr);
            perror("Could not accept() connection");
            continue;
        }

        wa = calloc(1, sizeof(struct worker_args));
        wa->socket = client_socket;
        wa->ctx = ctx;

        if (pthread_create(&worker_thread, NULL, service_single_client, wa) != 0)
        {
            perror("Could not create a worker thread");
            free(client_addr);
            free(wa);
            close(client_socket);
            close(server_socket);
            return EXIT_FAILURE;
        }
    }

    /* ADDED: Destroy the lock */
    pthread_mutex_destroy(&ctx->lock);
    free(ctx);

    return EXIT_SUCCESS;
}


void *service_single_client(void *args) {
    struct worker_args *wa;
    struct server_ctx *ctx;
    int socket, nbytes, i;
    char buffer[100];

    wa = (struct worker_args*) args;
    socket = wa->socket;
    ctx = wa->ctx;

    pthread_detach(pthread_self());

    /* ADDED: Protect access to num_connections with the lock */
    #ifdef MUTEX
    pthread_mutex_lock (&ctx->lock);
    #endif

    /* The following two loops will result in num_connections
       being ultimately incremented by just one, but we do
       this with these loops to increase the chances of a
       race condition happening */
    for(i=0; i< NLOOPS; i++)
        ctx->num_connections++;
    for(i=0; i< NLOOPS-1; i++)
        ctx->num_connections--;
    fprintf(stderr, "+ Number of connections is %d\n", ctx->num_connections);

    /* ADDED: Unlock the lock when we're done with it. */
    #ifdef MUTEX
    pthread_mutex_unlock (&ctx->lock);
    #endif

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

    /* ADDED: Same as the above loops, but decrementing num_connections by one */
    #ifdef MUTEX
    pthread_mutex_lock (&ctx->lock);
    #endif
    for(i=0; i< NLOOPS; i++)
        ctx->num_connections--;
    for(i=0; i< NLOOPS-1; i++)
        ctx->num_connections++;
    fprintf(stderr, "- Number of connections is %d\n", ctx->num_connections);
    #ifdef MUTEX
    pthread_mutex_unlock (&ctx->lock);
    #endif

    close(socket);
    pthread_exit(NULL);
}

