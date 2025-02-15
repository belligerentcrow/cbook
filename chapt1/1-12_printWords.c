#include <stdio.h>

main (){
    int nl,c;
    c = 0;
    while((c=getchar())!=EOF){
        if(c == ' '){
            putchar('\n');
        }else{
            putchar(c);
        }
    }
}