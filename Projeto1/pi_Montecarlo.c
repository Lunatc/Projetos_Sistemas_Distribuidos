#include <stdio.h>
#include <stdlib.h>

int main(){
    
    int i, count=0, N;
    float d, x, y, pi;
    
    N = 100000; 
    
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
    
    pi = count/N;
    pi = pi*4;
    printf("%f = 4 * (%d / %d)", pi, count, N);
    
    return 0;
}
