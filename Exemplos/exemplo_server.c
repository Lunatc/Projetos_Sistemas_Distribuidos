//Slide 1
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <sys/socket.h> // defines socket operations
#include <netinet/in.h> // defines internet constants
#include <netdb.h> // manage tables for IP conversions
#include <arpa/inet.h> // defines internet operations
#include <errno.h> // used for error messages

int main(int argc, char *argv[]){
	int sock, connected, bytes_recv, true = 1, i, j;
	char send_data[1024] , recv_data[1024];
	struct sockaddr_in server_addr, client_addr;
	int sin_size;

	//Slide 2
	// Creates the socket, checking for its success
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Error creating the Socket");
		exit(1);
	}
	// Adjusts socket’s options
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &true,sizeof(int))== -1){ 
		perror("Error in Setsockopt");
		exit(1);
	}
	// Initializes socket’s parameters. Note port address (set to 5000)
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(5000); // host-endian to network-endian
	server_addr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(server_addr.sin_zero),8);

	//Slide 3
	// Links the created socket to its physical socket
	if (bind(sock, (struct sockaddr *)&server_addr, sizeof(structsockaddr)) == -1) {
		perror("It was not possible to bind");
		exit(1);
	}

	// Define o tamanho da fila de entrada (5)
	if (listen(sock, 5) == -1) {
		perror("Error defining input queue size");
		exit(1);
	}

	printf("\nTCP Server wait for clients at port 5000\n");
	fflush(stdout);

	//Slide 4
	// Infinite loop for the server’s life
	while(true){ 
		sin_size = sizeof(struct sockaddr_in);
		connected = accept(sock, (struct sockaddr *)&client_addr,&sin_size);
		printf("\nReceiving connection (Client: %s , Port: %d)\n",
		inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
		fflush(stdout);

		//Slide 5
		// This loop is executed for all connections. The server returns
		// a text to the client until she/he decides to leave
		while(true){ // Receives the request
			if ((bytes_recv = recv(connected, recv_data,1024,0)) <= 0) {
				printf("Lost connection\n");
				break;
			}
			recv_data[bytes_recv] = '\0';
			// Copy the input text backwards as the server’s response
			j = strlen(recv_data)-2;
			for (i=0; i<=j; i++)
				send_data[i] = recv_data[j-i];
				send_data[i] = '\0';

		//Slide 6
		// Checks the text to see if it was a request to leave (q/Q)
		if (strcmp(recv_data,"q")==0 || strcmp(recv_data,"Q")==0){ 
			strcpy(send_data,"Connection will be closed\n");
			send(connected, send_data, strlen(send_data), 0);
			printf("Connection closed by the client\n");
			close(connected);
			break;
		}
		else // If not leaving, then send the response text
			send(connected, send_data, strlen(send_data), 0);
			fflush(stdout);
		} // End of connection
	} // End of server’s li
	close(sock);
	return 0;
}