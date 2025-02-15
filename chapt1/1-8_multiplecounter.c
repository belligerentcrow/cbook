#include <stdio.h>

main(){
    int c, nl, ntabs, nblanks;
    nl=0;
    ntabs=0;
    nblanks=0;
    printf("h");
    while((c=getchar())!=EOF){
        if(c == '\n'){
            ++nl;
        }
        if(c == ' '){
            ++nblanks;
        }
        if(c == '\t'){
            ++ntabs;
        }
        if(c == 'p'){
            break;
        }
    }
    printf("lines: %d, tabs: %d, blanks: %d\n",nl,ntabs,nblanks);
}