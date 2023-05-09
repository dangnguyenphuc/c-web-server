#include "HTTP_Server.h"
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>

void init_HTTPServer(HTTP_Server* http_server, int port){
    // port assignment
    http_server->port = port;

    // create server socket
        // protocol family: AF_INET for IPv4 and AF_INET6 for IPv6.
        // type parameter: connection-oriented stream of data (e.g., SOCK_STREAM) or an unreliable, datagram-oriented packet service (e.g., SOCK_DGRAM).
        // protocol parameter: IPPROTO_TCP specifies the TCP protocol, while IPPROTO_UDP specifies the UDP protocol.
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = INADDR_ANY;
    

    // bind server_socket
    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

    // listen for incoming connections
    listen(server_socket, 4);

    http_server->socket = server_socket;
    printf("HTTP Server Initialized\nPort: %d\n", http_server->port);
}