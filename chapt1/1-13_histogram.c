#include <stdio.h>

#define IN 1
#define OUT 0

main(){
    int wlenghts[30]; //array with 'all' possible lenghts
    int state, lenghtword, c, prevstate; 
    prevstate = OUT;
    state = lenghtword = OUT; //state notes if we're in a word, while lenghtword counts the lenght

    while((c = getchar()) != '0') { // 0 as stop key
        ++lenghtword;       //every char it increases
        if(c == ' ' || c == '\n' || c == '\t'){
            state = OUT;
            if(prevstate ==OUT){
            ++wlenghts[lenghtword+1]; //increases the corresponding place in the array
            } 
            lenghtword = 0; //then sets the current word lenght to 0
        }else if (state == OUT){
            state = IN;
        }
    }
}