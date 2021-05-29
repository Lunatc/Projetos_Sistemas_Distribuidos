#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include<math.h>


int main(int argc , char *argv[]){
	
	int socket_d , new_socket[16] , c;
	
	struct sockaddr_in server , client;
	
	char message[2000], client_message[2000];
	int n,num_clientes, i=0; 
	long N;
	double resultado, tempo;
    	clock_t t;
	
	//int atoi (const char *str);
	
	//Create socket
	socket_d = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_d == -1){
		printf("Could not create socket");
	}
	
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( 8080 );
	
	//Bind
	if( bind(socket_d,(struct sockaddr *)&server , sizeof(server)) < 0){
		puts("bind failed");
		return 1;
	}
	puts("Bind done");
	
	//Listen
	listen(socket_d , 16);
	
	puts("Escreva o número de clientes esperados:(2, 4, 8 ou 16)\n");
	scanf("%d",&num_clientes);
	
	printf("Escreva o número de sorteios (entre 3 e 10):\n");
	scanf("%d",&n);
		
	N = pow(10,n);
	printf("N:%ld\n",N); //teste
	
	//Accept and incoming connection
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);
	
	N = N/num_clientes;
	sprintf(message, "%ld", N);
	
	for(i=0;i<num_clientes;i++){
		
		if((new_socket[i] = accept(socket_d, (struct sockaddr *)&client, (socklen_t*)&c)) < 0){
			perror("Could not accept client");
			return 1;
		}
		
		printf("Cliente conectado\n");
		
		if (new_socket[i]<0){
			perror("accept failed");
			return 1;
		}
	}
	
	printf("All clients connected!");
	
	t = clock();
	for(i=0;i<num_clientes;i++){	
		
		send(new_socket[i], message, strlen(message), 0);
		
		
            if ((recv(new_socket[i], client_message, strlen(message), 0)) > 0){
                resultado += atof(client_message);
            }
            
	}
	
	resultado = resultado/num_clientes;
	
	t = clock() - t;
	tempo = ((double) t)/CLOCKS_PER_SEC;
	printf("Tempo de execucao: %lf \n", tempo);
	
	
	printf("Pi:%f",resultado);

}
