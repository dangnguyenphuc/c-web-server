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


int main() {
	// DEBUG
	// RoutesHashTable *ht = create_HashTable(CAPACITY);
    // insert_HashTable(ht, (char *)"1", (char *)"First address");
    // insert_HashTable(ht, (char *)"2", (char *)"Second address");
    // insert_HashTable(ht, (char *)"Hel", (char *)"Third address");
    // insert_HashTable(ht, (char *)"Cau", (char *)"Fourth address");
    // print_search(ht, (char *)"1");
    // print_search(ht, (char *)"2");
    // print_search(ht, (char *)"3");
    // print_search(ht, (char *)"Hel");
    // print_search(ht, (char *)"Cau"); // Collision!
    // print_HashTable(ht);
    // deleteElement_HashTable(ht, (char *)"1");
    // deleteElement_HashTable(ht, (char *)"Cau");
    // print_HashTable(ht);
    // free_HashTable(ht);
    // print_HashTable(ht);
    // return 0;


	// initiate HTTP_Server
	

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
