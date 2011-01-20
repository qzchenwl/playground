#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"

#define ECHO_PORT   (2002)
#define MAX_LINE    (1000)

int main(int argc, const char *argv[])
{
    int                 list_s;             /* listening socket */
    int                 conn_s;             /* connection socket */
    int                 optval = 1;         /* socket option */
    short int           port;               /* port number */
    struct sockaddr_in  servaddr;           /* socket address structure */
    char                buffer[MAX_LINE];    /* character buffer */
    char                *endptr;            /* for strtol() */

    /* Get port number from the command line, and 
     * set to default port if no arguments were supplied */

    if (argc == 2) {
        port = strtol(argv[1], &endptr, 0);
        if (*endptr) {
            fprintf(stderr, "ECHOSERV: Invalid port number.\n");
            exit(EXIT_FAILURE);
        }
    }
    else if (argc < 2) {
        port = ECHO_PORT;
    }
    else {
        fprintf(stderr, "ECHOSERV: Invalid arguments.\n");
        exit(EXIT_FAILURE);
    }

    /* create the listening socket */
    if ((list_s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket()");
        exit(EXIT_FAILURE);
    }

    /* set socket option */
    if (setsockopt(list_s, SOL_SOCKET, SO_REUSEADDR, \
                (const void *)&optval, sizeof(optval)) < 0) {
        perror("setsockopt()");
        exit(EXIT_FAILURE);
    }

    /* Set all bytes in socket address structure to
     * zero, and fill in the relevant data members */
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(port);

    /* Bind our socket address to the listening socket,
     * and call listen() */
    if (bind(list_s, (struct sockaddr *)&servaddr, sizeof(servaddr))) {
        perror("bind()");
        exit(EXIT_FAILURE);
    }
    if (listen(list_s, LISTENQ) < 0) {
        perror("listen()");
        exit(EXIT_FAILURE);
    }

    /* Enter an infinite loop to respond
     * to client requests and echo input */
    while (1) {
        /* Wait for a connection, the accept() it */
        if ((conn_s = accept(list_s, NULL, NULL)) < 0) {
            perror("accept()");
            exit(EXIT_FAILURE);
        }
        printf("pid %d accept\n", getpid());
        /* Retrieve an input line from the connected socket
         * then simply write it back to the same socket. */
        //Readline(conn_s, buffer, MAX_LINE-1);
        //Writeline(conn_s, buffer, strlen(buffer));
        /* Close the connected socket */
        if (close(conn_s) < 0) {
            perror("close()");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
