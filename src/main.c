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

	// initiate HTTP_Server
	HTTP_Server http_server;
	init_HTTPServer(&http_server,6969);

    // client_socket
	int client_socket;
	
	// registering Routes
	struct RoutesHashTable* table = create_HashTable(CAPACITY);
	insert_HashTable(table, "/", "index.html");
	insert_HashTable(table, "/about", "about.html");

    // print Routes
    DebugLog();
	print_HashTable(table);

	while (1) {
        // read client_msg
		char client_msg[4096] = "";

		// accept client_socket
		client_socket = accept(http_server.socket, NULL, NULL);

        // print client_msg
        read(client_socket, client_msg, 4095);
		printf("%s\n",client_msg);

		// parsing client socket header to get HTTP method, route
		// Example: GET /index.html HTTP/1.1
		char* method = "";
		char* urlRoute = "";

		char* client_message_header = strtok(client_msg, "\n");
		printf("\n\n%s\n\n", client_message_header);
		
		char *token;
		int header_parse_counter = 0;
		// Get the first token
		token = strtok(client_message_header, " ");

		// Walk through other tokens
		while (token != NULL) {
			
			if (header_parse_counter == 0)
			{
				method = token;
			}
			else if (header_parse_counter == 1)
			{
				urlRoute = token;
				break;
			}
			token = strtok(NULL, " ");
			header_parse_counter += 1;
		}
		
		// get template
		char template[100] = "";
		
		if(strstr(urlRoute, "/static/") != NULL){
			strcat(template, "static/index.css");
		}else{
			char* destination = search_HashTable(table, urlRoute);
			strcat(template,"templates/");
			if(destination){
				strcat(template, destination);
			}else{
				strcat(template, "404.html");
			}
		}

		// render template
		char* response_data = render_template(template);


		// header OK
		char http_header[4096] = "HTTP/1.1 200 OK\r\n\r\n";
		
		// concat header and reponse
		strcat(http_header, response_data);
		strcat(http_header, "\r\n\r\n");

		// send response message
		send(client_socket, http_header,sizeof(http_header),0);

		// close socket
		close(client_socket);
		// free data after used
		free(response_data);
	}
	return 0;
}
