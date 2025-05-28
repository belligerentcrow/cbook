#include <stdio.h>
#include <stdlib.h>

int main(void){
    int a = 903;
    float b = 291.12;
    char c = 'a';
    int * pa = &a;
    float *pb = &b;
    char * pc = &c;
    printf("int: %d\t\t float:%d\t\t char:%d\n",sizeof(int), sizeof(float), sizeof(char));
    printf("int pointer: %d\t float pointer:%d\t char pointer:%d\n",sizeof(int *), sizeof(float *), sizeof(char *));
}