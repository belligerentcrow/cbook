#include <stdio.h>

//copy input to output 

int main(){
    int c;
    printf("EOF%d\n", EOF);
    while((c = getchar())!= EOF){
	printf("\nbool = %b\n",getchar()!=EOF);
        putchar(c);
    }
}
