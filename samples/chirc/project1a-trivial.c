/*
 *
 *  CMSC 23300 / 33300 - Networks and Distributed Systems
 *
 *  main() code for chirc project
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

#include "log.h"

int main(int argc, char *argv[])
{
    int opt;
    char *port = "6667", *passwd = NULL;
    int verbosity = 0;

    while ((opt = getopt(argc, argv, "p:o:vqh")) != -1)
        switch (opt)
        {
        case 'p':
            port = strdup(optarg);
            break;
        case 'o':
            passwd = strdup(optarg);
            break;
        case 'v':
            verbosity++;
            break;
        case 'q':
            verbosity = -1;
            break;
        case 'h':
            fprintf(stderr, "Usage: chirc -o PASSWD [-p PORT] [(-q|-v|-vv)]\n");
            exit(0);
            break;
        default:
            fprintf(stderr, "ERROR: Unknown option -%c\n", opt);
            exit(-1);
        }

    if (!passwd)
    {
        fprintf(stderr, "ERROR: You must specify an operator password\n");
        exit(-1);
    }

    /* Set logging level based on verbosity */
    switch(verbosity)
    {
    case -1:
        chirc_setloglevel(QUIET);
        break;
    case 0:
        chirc_setloglevel(INFO);
        break;
    case 1:
        chirc_setloglevel(DEBUG);
        break;
    case 2:
        chirc_setloglevel(TRACE);
        break;
    default:
        chirc_setloglevel(INFO);
        break;
    }

    int server_socket;
    int client_socket;
    struct sockaddr_in server_addr, client_addr;
    int yes = 1;
    socklen_t sin_size = sizeof(struct sockaddr_in);

    char *msg = ":bar.example.com 001 user1 :Welcome to the Internet Relay Network user1!user1@foo.example.com\r\n";

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(port));
    server_addr.sin_addr.s_addr = INADDR_ANY;

    server_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    bind(server_socket, (struct sockaddr *) &server_addr, sizeof(server_addr));
    listen(server_socket, 5);

    while(1)
    {
        client_socket = accept(server_socket, (struct sockaddr *) &client_addr, &sin_size);
        send(client_socket, msg, strlen(msg), 0);
    }

    close(server_socket);

    return 0;
}

