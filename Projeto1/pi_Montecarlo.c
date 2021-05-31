#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    
    srand(time(NULL));
    
    double pi, tempo, count = 0; 
    long int i, N;
    long double x, y;
    clock_t t;
    
    N=1000000000;
    
    t = clock();
     
    for(i=0;i<N;i++){
            
        x = ((double) rand() / (RAND_MAX));
        y = ((double) rand() / (RAND_MAX));
        
        if(((x*x)+(y*y))<1){
            count++;
        }
           
    }

        
    pi = 4*(count/N);
		 
    t = clock() - t;
    tempo = ((double) t)/CLOCKS_PER_SEC;
        
    printf("tempo = %lf \n", tempo);
    printf("\n%lf = 4 * (%f / %f)\n", pi, count, N);
        
    return 0;
}
