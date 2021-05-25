#include<stdio.h>
#include<string.h>	
#include<stdlib.h>	
#include<sys/socket.h>
#include<arpa/inet.h>	
#include<unistd.h>	
#include<time.h>
#include<pthread.h> 
#include<math.h>
#include <limits.h>
#include <float.h>


long N;

void *connection_handler(void *);

int main(int argc , char *argv[]){
	int socket_desc , new_socket , c , *new_sock;
	char message[1000];
	int atoi (const char *str);
	int n; 
	
	struct sockaddr_in server , client;
	
	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1){
		printf("Could not create socket");
	}
	
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( 8888 );
	
	//Bind
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0){
		puts("bind failed");
		return 1;
	}
	puts("Bind done");
	
	//Listen
	listen(socket_desc , 3);
	
	printf("Escreva o número de sorteios (entre 3 e 10):\n");
	scanf("%d",&n);
			
	N = pow(10,n);
	
	//Accept and incoming connection
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);
	while( (new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) ){
		
		printf("Cliente conectado\n");
		
		pthread_t sniffer_thread;
		new_sock = malloc(1);
		*new_sock = new_socket;
		
		if( pthread_create( &sniffer_thread , NULL ,  connection_handler , (void*) new_sock) < 0)
		{
			perror("could not create thread");
			return 1;
		}
	
		
		//Now join the thread , so that we dont terminate before the thread
		//pthread_join( sniffer_thread , NULL);
		puts("Handler assigned\n");
	}
	
	if (new_socket<0)
	{
		perror("accept failed");
		return 1;
	}
	
	return 0;
}

/*
 * This will handle connection for each client
 * */
void *connection_handler(void *socket_desc)
{
	//Get the socket descriptor
	int sock = *(int*)socket_desc;
	int read_size, count=0;
	char message[1000] , client_message[2000];
	double tempo;
	
    	clock_t t;
	
	//Send some messages to the client
	
	sprintf(message, "%ld", N);
	
	//Receive a message from client
	while( (read_size = recv(sock , client_message , 2000 , 0)) > 0 ){
		
		puts(client_message);	
		
		write(sock , message , strlen(message));
		
	}	
		
		
		if(count==1){
			t = clock();
			printf("\n O valor de pi é:%s", client_message);
			t = clock() - t;
		}
		//break;
		count++;
	
	strcpy(message,"Obrigada pela sua ajuda\n");
	write(sock , message , strlen(message));
	
	if((read_size = recv(sock , client_message , 2000 , 0)) < 0){
		puts("recv failed");
	}
		
	tempo = ((double) t)/CLOCKS_PER_SEC;
	printf("%lf \n", tempo);
	
	if(read_size == 0)
	{
		puts("Client disconnected");
		fflush(stdout);
	}
	else if(read_size == -1)
	{
		perror("recv failed");
	}
		
	//Free the socket pointer
	free(socket_desc);
	
	return 0;
}
