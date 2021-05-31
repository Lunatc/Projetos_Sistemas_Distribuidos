#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <math.h>

int main(int argc , char *argv[]){
	
	int socket_d , new_socket[20] , c;
	//time_t inicio, fim;
	struct timeval start, end;
    
	struct sockaddr_in server , client;
	
	char message[2000], client_message[2000];
	int n,num_clientes, i=0; 
	long long N;
	double resultado, tempo;
	
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
	listen(socket_d , 25);
	
	puts("Escreva o numero de clientes esperados:(2, 4, 8 ou 16)\n");
	scanf("%d",&num_clientes);
	
	printf("Escreva o numero de sorteios (entre 3 e 10):\n");
	scanf("%d",&n);
		
	N = pow(10,n);
	printf("N:%lld\n",N); //teste
	
	//Accept and incoming connection
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);
	
	N = N/num_clientes;
	sprintf(message, "%lld", N);
	
	for(i=0;i<num_clientes;i++){
		
		if((new_socket[i] = accept(socket_d, (struct sockaddr *)&client, (socklen_t*)&c)) < 0){
			perror("Could not accept client");
			return 1;
		}
		
		printf("%d:Cliente conectado\n",i+1);
		
		if (new_socket[i]<0){
			perror("accept failed");
			return 1;
		}
	}
	
	printf("All clients connected!");
	gettimeofday(&start, NULL);
	//inicio = time(NULL);
	for(i=0;i<num_clientes;i++){	
		
		send(new_socket[i], message, strlen(message), 0);
	
            
	}
	
	for(i=0;i<num_clientes;i++){	
		
            if ((recv(new_socket[i], client_message, strlen(message), 0)) > 0){
                resultado += atof(client_message);
            }
            
	}
	
	
	resultado = resultado/num_clientes;
	gettimeofday(&end, NULL);
	tempo = ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));
	printf("Time taken : %f seconds\n", tempo/1000000);
	///fim = time(NULL);
	//fprintf(stdout, "O tempo de execucao em segundos e %f\n", difftime(fim, inicio));
	
	for(i=0;i<num_clientes;i++){	
		
		send(new_socket[i], "Concluido", strlen(message), 0);
            
	}
	
	printf("Pi:%f",resultado);
	
	
	return 0;
	
}
