#include <stdio.h>

// counts digits, white space, chars
int main(){
    int c, i, nwhite, nother;
    int ndigit[10];
    nwhite = nother = 0;
    for(i = 0; i< 10; i++){
        ndigit[i] = 0;
    }

    while((c = getchar())!= EOF){
        if(c >= '0' && c<='9'){
            ++ndigit[c-'0'];
        }else if(c == ' '|| c == '\t' || c == '\n'){
            ++nwhite;
        }else{
            ++nother;
        }
    }
    printf("digits: ");
    for(i = 0; i < 10; i++){
        printf(" %d", ndigit[i]);
    }
    printf(", whitespace: %d, other chars: %d", nwhite, nother);
}