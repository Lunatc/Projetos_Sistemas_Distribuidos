/*/
============================================================================
Trabalho 1 de Sistemas Distribuidos - Código Cliente
Nomes: Cintia Bras Mesquita, Igor Yoshimitsu Ide e Tiago Pinheiro Camargo
============================================================================
/*/
#include <stdio.h>	
#include <string.h>	
#include <stdlib.h>
#include <arpa/inet.h>	
#include <unistd.h>
#include <time.h>

int main(int argc , char *argv[]){
	
	int sock;
	
	struct sockaddr_in server;
	
	char message[2000];
	srand(time(NULL));
    	
    	double pi, count = 0; 
    	long int i, N;
    	long double x, y, d;
    	
    	//Cria o socket
	sock = socket(AF_INET , SOCK_STREAM , 0);
	if (sock == -1){
		printf("Erro em criar o socket");
		exit(1);
	}
	
	puts("Socket created");
	
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons( 8080 );

	//Connect to remote server
	if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		perror("connect failed. Error");
		return 1;
	}
	
	puts("Conectado\n");
	
	
	//Receive message
	while(recv(sock , message , 2000 , 0) < 0){
		
	}
	puts(message);
	printf("Trabalho recebido");
	N = strtold(message, NULL);
	
	for(i=0;i<N;i++){
        
        	x = ((double) rand() / (RAND_MAX));
        	y = ((double) rand() / (RAND_MAX));
        
        	x = x*x;
        	y = y*y;
        
        	d = x+y;
        
        	if(d<1){
            		count++;
        	}
    	}
    		
    
	pi = 4*(count/N);
	sprintf (message, "%f", pi);
	
	//Send Pi
	if( send(sock , message , strlen(message) , 0) < 0){
		puts("Send failed");
		return 1;
	}
	 close(sock);
	
	close(sock);
	return 0;
}
