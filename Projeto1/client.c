#include <stdio.h>	
#include <string.h>	
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>	
#include <unistd.h>
#include <time.h>

int main(int argc , char *argv[]){

	int sock;
	struct sockaddr_in server;
	char message[1000] , server_reply[2000];  //char *message, server_reply[2000];
	int  atoi (const char *str);      // string to integer, ascii to int 
	int i, N;
    	float  count=0;
    	double d, x, y, pi;
    	
	srand(time(NULL));
	
	//Cria o socket
	sock = socket(AF_INET , SOCK_STREAM , 0);
	
	if (sock == -1){
		printf("Erro em criar o socket");
		exit(1);
	}
	printf("Socket criado\n");
	
	
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons( 8888 );

	//Conectar ao server local
	if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		perror("A conexão falhou. Erro!");
		return 1;
	}
	
	printf("Conectado\n");
	
	//keep communicating with server
	while(1){
			
		strcpy(message,"Connected");
			
		//Send some data
		if( send(sock , message , strlen(message) , 0) < 0){
			puts("Send failed");
			return 1;
		}
		
		//Receive a reply from the server
		if( recv(sock , server_reply , 2000 , 0) < 0){
			puts("recv failed");
			break;
		}
		
		printf("Server Responde:%s",server_reply);
		
		N = atoi(server_reply);
		//printf("é: %d",N);
    
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
    		
    		//printf("BAtata");
    
		pi = 4*(count/N);
		//printf("\n%lf = 4 * (%f / %f)", pi, count, N);
		sprintf (message, "%lf", pi);
		//printf("%s",message);
		
		//Send some data
		if( send(sock , message , strlen(message) , 0) < 0){
			puts("Send failed");
			return 1;
		}
		
		//Receive a reply from the server
		if( recv(sock , server_reply , 2000 , 0) < 0){
			puts("recv failed");
			break;
		}
		
	}
	
	close(sock);
	return 0;
}
