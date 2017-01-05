/* 
 *
 *  CMSC 23300 / 33300 - Networks and Distributed Systems
 *  
 *  A client that bombs a server with N connections
 *
 *  Usage:
 *
 *      ./client-bomb -h <host> -p <port> -n <number of connections>
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

int main(int argc, char *argv[])
{
    int *sockets, nsockets;
    struct addrinfo hints, *res, *p;
    char *host, *port;
    int nbytes, opt, i;

    while ((opt = getopt(argc, argv, "h:p:n:")) != -1)
        switch (opt)
        {
            case 'h':
                host = strdup(optarg);
                break;
            case 'p':
                port = strdup(optarg);
                break;
            case 'n':
                nsockets = atoi(optarg);
                break;
            default:
                printf("Unknown option\n"); exit(1);
        }

    sockets = malloc(nsockets * sizeof(int));

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(host, port, &hints, &res) != 0)
    {
        perror("getaddrinfo() failed");
        exit(-1);
    }

    for(p = res;p != NULL; p = p->ai_next) 
    {
        if ((sockets[0] = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) 
        {
            perror("Could not open socket");
            continue;
        }

        if (connect(sockets[0], p->ai_addr, p->ai_addrlen) == -1) 
        {
            close(sockets[0]);
            perror("Could not connect to socket");
            continue;
        }

        break;
    }
    
    if (p == NULL)
    {
            fprintf(stderr, "Could not find a socket to connect to.\n");
        exit(-1);
    }

    /* Bomb! */
    printf("Bombing with %d\n", nsockets);
    for(i=1; i<nsockets; i++)
    {
        sockets[i] = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        connect(sockets[i], p->ai_addr, p->ai_addrlen);
    }
    sleep(2);

    for(i=0; i<nsockets; i++)
    {
        close(sockets[i]);
    }
    printf("Done\n");

    freeaddrinfo(res);
    return 0;
}
