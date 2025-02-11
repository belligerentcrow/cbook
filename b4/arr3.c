#include <stdio.h>

#define MAXLEN 1000

int get_line(char s[], int lenlenght);
void copycopy(char from[], char to[]);

int main(){
    int len, max;
    char line[MAXLEN];
    char longest[MAXLEN];

    max = 0;
    while((len = get_line(line, MAXLEN)>0)){
        if (len>max){
            max=len;
            copycopy (line,longest);
        }
    }
    if (max >0){
        printf("%s",longest);
    }
    return 0;

}

int get_line(char s[], int maxlen){
    int c, i;
    for (i = 0; i<maxlen-1 && (c = getchar())!='\n' && c!= EOF; ++i){
        s[i] = c;
    }
    if (c == '\n'){
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;

}

void copycopy(char from[], char to[]){
    int i = 0;
    while((to[i]=from[i])!='\0'){
        ++i;
    }
}