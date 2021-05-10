#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <sys/socket.h> // defines socket operations
#include <netinet/in.h> // defines internet constants
#include <netdb.h> // manage tables for IP conversions
#include <arpa/inet.h> // defines internet operations
#include <errno.h> // used for error messages
#include <unistd.h>

int main(int argc, char *argv[]){
	int sock, bytes_recv;
	char send_data[1024],recv_data[1024];
	struct hostent *host;
	struct sockaddr_in server_addr;
	
	// Reads command line (IP) do servidor
	host = gethostbyname(argv[1]);
	
	// Creates a socket
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Error in the socket creation");
		exit(1);
	}
	fflush(stdout);
	
	// data about server’s socket
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(5000);
	server_addr.sin_addr = *((struct in_addr *)host->h_addr);
	bzero(&(server_addr.sin_zero),8);
	
	// Connects with the named server
	if (connect(sock, (struct sockaddr *) & server_addr, sizeof(struct sockaddr)) == -1){ 
		perror("Connection error");
		exit(1);
	}

	// Repeat while connection remains active
	while(1) { // Reads user’s input
		printf ("\n GIVE THE TEXT (q or Q to quit) : ");
		fgets(send_data, sizeof(send_data), stdin);
		  // Sends text or disconnection request to the server
		send(sock, send_data, strlen(send_data), 0);
		
		// Receives server’s response
		bytes_recv=recv(sock,recv_data,1024,0);
		recv_data[bytes_recv] = '\0';
		
		// Prints response or closes the socket if requested
		if (strcmp(recv_data,"Closing the connection\n")!=0)
			printf("\n Received data = %s ", recv_data);
		else{ 
			printf("\n %s ", recv_data);
			close(sock);
			break;
		}	
	} // End of while(1)
	return 0;
}
