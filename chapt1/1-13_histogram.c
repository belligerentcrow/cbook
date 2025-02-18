#include <stdio.h>

#define IN 1
#define OUT 0
#define MAXLENGHT 30

main(){
    int wlenghts[MAXLENGHT]; //array with 'all' possible lenghts
    int state, lenghtword, c, prevstate; 
    prevstate = OUT;
    state = lenghtword = 0; //state notes if we're in a word, while lenghtword counts the lenght
    c = 0;
    for(int i = 0; i<MAXLENGHT; ++i){
        wlenghts[i] = 0;
    }
    while((c = getchar()) != '0') { // 0 as stop key
        ++lenghtword;       //every char it increases
        if(c == ' ' || c == '\n' || c == '\t'){
            state = OUT;
            if(prevstate ==OUT){
            ++wlenghts[lenghtword-1]; //increases the corresponding place in the array
            } 
            lenghtword = 0; //then sets the current word lenght to 0
        }else if (state == OUT){
            state = IN;
        }
    }
    int count = 0;
    for(int i = 0; i<=MAXLENGHT; ++i){
        count = wlenghts[i];
        printf("%d : ",i);
        while(count >0){
            printf("x");
            --count;
        }
        printf("\n");
    }
}