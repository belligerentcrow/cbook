#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <pthread.h>
#include <netinet/in.h>
#include <unistd.h>

#define MAX_BUF 1024
int socketfd;

//funzione del thread
void gestore_ricezione(){
    char buffer[MAX_BUF];
    while(true){
        ssize_t bytes = recv(socketfd, buffer, MAX_BUF-1, 0);
        if(bytes == 0){
            //il server ha chiuso la connessione
            break;
        }
        printf("\n Receive %s\n", buffer);
        fflush(stdout); //flusho dopo che scrivo

    }

}

void gestione_send(){
    char buffer[MAX_BUF];
    while(true){
        fflush(stdout); //flusho quando devo inviare
        scanf("%s", buffer);
        buffer[strcspn(buffer, "\n")] == '\0';
        if(strcmp(buffer, "exit")==0){
            break;
        }
        send(socketfd, buffer, strlen(buffer),0);
    }

}

int main(int argCount char * argValues[]){
    if (argCount<3 ){
        printf("Usage: %s <IP> <Port>", argValues[0]);
        perror("Wrong arguments");
        exit(EXIT_FAILURE);
    }
    //int socketfd;
    struct sockaddr_in serverAddressPort;
    char buffer[MAX_BUF];

    //creo socket
    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    //definisco porta e indirizzo di connessione al server
    serverAddressPort.sin_family = AF_INET;
    serverAddressPort.sin_port = htons(atoi(argv[2]));    

    //convert IP address from text to binary 
    inet_pton(AF_INET, argValues[1], &serverAddressPort.sin_addr);

    //connessione al server
    //sizof forse non funziona vedi altro server.c
    connect(socketfd, (struct sockaddr *)&serverAddressPort, 
        sizeof(serverAddressPort));

    printf("Connessione riuscita al server %s:%s\n", 
        argValues[1], argValues[2]);
    printf("Print exit to quit\n");
    while(true){
        
        //"flusho" lo standard output
        fflush(stdout);
        //gestire logica del software client
        
        //prendo in input
        //fgets(buffer, MAX_BUF, stdin);
        
        //send
        scanf("%s",buffer);
        printf("%s\n", buffer);
        buffer[strcspn(buffer, "\n")] = \0;
        if(strcmp(buffer, "exit")==0){
            break;
        }
        send(socketfd, buffer, strlen(buffer),0);

        
        //ricezione
        int bytesReceived = recv(socketfd, buffer, MAX_BUF-1, 0);
        if(bytesReceived == 0){
            //il server vuole chiudere la trasmissione
            break;
        }
    }

}