//reverse a string

#include <stdio.h>

#define MAXLEN 1000

void reverses(char s[], int len);
int get_line(char line[], int maxlen);
void copycopy(char from[], char to[]);

int main(){
    int len = 0;
    char myline[MAXLEN];
    char reversed[MAXLEN];
    len = get_line(myline,MAXLEN);
    reverses(myline, len);
    printf("%s",myline);

}

int get_line(char line[], int maxlen){
    char c;
    int i = 0;
    while(i < maxlen-1 && (c = getchar())!= '\n' && c != EOF){
        line[i] = c;
        ++i;
    }
    if (c == '\n'){
        line[i]=c;
        ++i;
    }
    line[i] = '\0';
    return i;
}

void reverses(char s[], int len){
    char revHelper[MAXLEN];
    copycopy(s,revHelper);
    int j = 0;
    for(int i = len-1; i >=0; --i){
        s[j]=revHelper[i];
        ++j;
    }
    s[j]='\n';
    s[j+1]='\0';

}

void copycopy(char from[], char to[]){
    int i = 0;
    while((to[i]=from[i])!='\0'){
        ++i;
    }
}