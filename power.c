#include <stdio.h>

int power(int, int);

int main(){
    int first, second;
    first = 10;
    second = 3;
    int powpow = power(first, second);
    printf("%d to the %d = %d\n", first, second, powpow);
}

int power(int x, int y){
    int poweringup = 1;
    for(int i = 0; i <y; ++i){
        poweringup = poweringup*x;
    }
    return poweringup;
}
