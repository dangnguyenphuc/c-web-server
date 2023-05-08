#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "../include/Notification.h"
#include "../include/HTTP_Server.h"
#include "../include/Routes.h"
#include "../include/Response.h"

int hash(char* key) {
    int hash_val = 0;
    while (*key) {
        hash_val = (hash_val << 5) + *key++;
		printf("%d", hash_val);
    }
	
    return hash_val % 100;
}

int main() {
	// initiate HTTP_Server
	int i = hash("dang");
	printf("%d", i);
	return 0;
    // client_socket
	
	
	// registering Routes
	

    // print Routes
    DebugLog();

	// display all available routes


	while (1) {
        // read client_msg
		

        // print client_msg
        

		// parsing client socket header to get HTTP method, route
		

		// get template
		
		// render template

		// header OK
		char http_header[4096] = "HTTP/1.1 200 OK\r\n\r\n";

		// concat header and reponse
		

		// send response message
		

		// close socket
		
		// free data after used
		
	}
	return 0;
}
