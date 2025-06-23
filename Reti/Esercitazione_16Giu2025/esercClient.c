#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

#define BUFFSIZE 1024
#define LINE_SEPARATOR " "

typedef enum{
    REGISTRAZIONE = 'r';
    SUCCESS = '1',
    FAIL = '0',
    LOGIN = 'l',
    SEND = 's',
    RECEIVE = 'R',
    EXIT = 'q',
} Operation;

typedef struct{
    Operation op;
    char username[16];
    char password[16];
    int port;
    int token; //32bit
    char message[1000];
} Message;

int main(int argc, char argv[]){
    
}