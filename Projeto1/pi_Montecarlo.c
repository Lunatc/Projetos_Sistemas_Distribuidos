#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    
    srand(time(NULL));
    
    int i;
    double  count=0; 
	long double N = 3100000000;
    double d, x, y, pi, tempo;
    clock_t t;
	    
    t = clock();
    
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
		 
    t = clock() - t;
    tempo = ((double) t)/CLOCKS_PER_SEC;
        
    printf("tempo = %lf \n", tempo);
    printf("\n%lf = 4 * (%f / %f)\n", pi, count, N);
        
    return 0;
}
