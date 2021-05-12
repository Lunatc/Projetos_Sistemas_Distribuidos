#include <stdio.h>
#include <stdlib.h>

int N = 100000;

int main(){
    
    int i, count=0;
    float d, x, y, pi;
    
    for(i=0;i<N;i++){
        
        x = ((double) rand() / (RAND_MAX));
        y = ((double) rand() / (RAND_MAX));
        
        x = x*x;
        y = y*y;
        
        d = x+y;
        
        if(d<=1){
            count++;
        }
    }
    
    pi = 4*(count/N);
    
    printf("%f = 4 * (%d / %d)", pi, count, N);
    
    return 0;
}
