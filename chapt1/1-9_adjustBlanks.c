#include <stdio.h>

main(){
    int c, prevc, nblanks;
    nblanks=0;
    prevc = 0;
    while((c = getchar())!=EOF){
        if(prevc == ' ' && c == ' '){
            putchar('\b');
        }
        putchar(c);
        prevc= c;
    }
}