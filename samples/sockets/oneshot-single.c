/* 
 *
 *  CMSC 23300 / 33300 - Networks and Distributed Systems
 *  
 *  This is the simplest possible one-shot server
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

int main(int argc, char *argv[])
{
    /* A socket is just a file descriptor, i.e., an int */
    int serverSocket;    // Used to listen for connections
    int clientSocket;    // Used to communicate with one specific client

    /* A sockaddr struct holds socket address information for lots of different types of sockets.

    struct sockaddr {
        unsigned short    sa_family;    // address family, AF_xxx
        char              sa_data[14];  // 14 bytes of protocol address <- Actually an arbitrary amount
    }; 

    We could modify the 14 bytes of data manually, but there are more specific structs we can use. 

    [Note: 14 is essentially an arbitrary size. Although historically all socket addresses could fit in
     those bytes, that is no longer true (e.g., IPv6). The sa_data field simply provides byte-level access
     to the data, which can be more than 14 bytes]

    For IPv4 we use struct sockaddr_in:

    struct sockaddr_in {
        short int          sin_family;  // Address family, AF_INET
        unsigned short int sin_port;    // Port number
        struct in_addr     sin_addr;    // Internet address
        unsigned char      sin_zero[8]; // Same size as struct sockaddr
    };
    */
    struct sockaddr_in serverAddr, clientAddr;

    /* We need this to call setsockopt(), which expects a *pointer* to the socket option */
    int yes = 1;

    /* We will need this to call accept(), which expects a *pointer* to the sockaddr size */
    socklen_t sinSize = sizeof(struct sockaddr_in);

    /* Message we're going to send out */
    char *msg = "Hello, socket!\n";

    /* Make sure serverAddr is all zeroes */
    memset(&serverAddr, 0, sizeof(serverAddr));
 
    /* Set other fields. Note we need to convert the port to network order. */
    serverAddr.sin_family = AF_INET;          // IPv4
    serverAddr.sin_port = htons(23300);       // TCP port number
    serverAddr.sin_addr.s_addr = INADDR_ANY;  // Bind to any address
    
    /* Create the socket*/    
    serverSocket = socket(PF_INET,       // Family: IPv4
                          SOCK_STREAM,   // Type: Full-duplex stream (reliable)
                          IPPROTO_TCP);  // Protocol: TCP

    /* Note: We could set the protocol to zero since PF_INET and SOCK_STREAM implies that TCP is
       going to be used. */

    /* Note 2: We've created the sockaddr_in struct manually to better show its contents,
       and to provide the simplest possible implementation. However, it would be better to use
       getaddrinfo (as shown in client.c) to support IPv4 and IPv6. Note that this would involve
       using sockaddr_storage, since we don't know a priori if we'll be using IPv4 or IPv6. */

    /* Make sure socket was created correctly */
    if(serverSocket == -1)
    {
        perror("Could not open socket");
        exit(-1);
    }

    /* Make the address reusable. This prevents "Address already in use" errors if we
       try to reuse that port "too quickly" (more specifically, when the server closes the socket,
       the connection must stay in the TIME_WAIT state to make sure the client received the
       acknowledgement that the connection has been terminated. During this time, this port
       is unavailable to other processes, unless we specify this option) */
    if(setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
    {
        perror("Socket setsockopt() failed");
        close(serverSocket);
        exit(-1);
    }

    /* Bind the socket to the address */
    if(bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) == -1)
    {
        perror("Socket bind() failed");
        close(serverSocket);
        exit(-1);
    }

    /* Start listening. The second parameter is the "backlog", or the maximum number of
       connections that we'll allow to queue up.
       Note that listen() doesn't block until incoming connections arrive. It just makes
       the OS aware that this process is willing to accept connections on this socket
       (which is bound to a specific IP and port) */
    if(listen(serverSocket, 5) == -1)
    {
        perror("Socket listen() failed");
        close(serverSocket);
        exit(-1);
    }
    
    fprintf(stderr, "Waiting for a connection... ");

    /* When an incoming connection arrives, accept it. The call to accept() blocks until
       the incoming connection arrives */
    if( (clientSocket = accept(serverSocket, (struct sockaddr *) &clientAddr, &sinSize)) == -1)
    {
        perror("Socket accept() failed");
        close(serverSocket);
        exit(-1);
    }

    /* accept() returns a new socket that we can use to communicate with the client. 
       clientAddr is also used to return the sockaddr for the client (with the client's
       IP address and port).

       So, in this case, we send the message to the client. Note that we can get away with
       using a single call to send() because it's a small message, and it's very likely
       send() can send all of it in a single go. For larger messages, we would need to
       check if the number of bytes we send matches the number of bytes *actually* sent
       (and make more calls to send with the remainder of the message, if necessary)*/
    if (send(clientSocket, msg, strlen(msg), 0) <= 0)
    {
        perror("Socket send() failed");
        close(serverSocket);
        close(clientSocket);
        exit(-1);
    }

    close(clientSocket);
    fprintf(stderr, "message sent!\n");
    
    /* Note that the above is a one-shot server. The program not only closes the connection
       after sending a single message, it also exits altogether after sending that message. 
       If we want to support many consecutive connections, we would just need to place
       everything between the fprintf's in a while(1) { } loop */

    close(serverSocket);

    return 0;
}
