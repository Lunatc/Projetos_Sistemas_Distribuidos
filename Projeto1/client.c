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

	int i;
    	float count=0;
    	double d, x, y, pi;
    	long N;
    	
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
	printf("Trabalho recebido");
	N = strtol(message, NULL, 10);
	
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
	
	//Receive message
	if( recv(sock , message , 2000 , 0) < 0){
		puts("recv failed");
		return 1;
	}
	puts(message);
	
	
	close(sock);
	return 0;
}
