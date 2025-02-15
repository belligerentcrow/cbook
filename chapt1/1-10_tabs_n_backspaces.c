#include <stdio.h>

main(){
    int c;
    c = 0;
    while((c=getchar())!=EOF){
        if(c == '\t'){
            putchar('\\');
            putchar('t');
        }else if(c == '\b'){
            putchar('\\');
            putchar('b');
        }else if(c == '\\'){
            putchar('\\');
            putchar('\\');
        }else{
            putchar(c);
        }
    }
}