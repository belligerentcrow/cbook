#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <stdbool.h>
#include "lib-misc.h"

#define BUFFER_SIZE 8192
int clientsock;

void * sendingThread(void * args){
    char buffer[BUFFER_SIZE];
    while(true){
        printf("> ");
        fflush(stdout);
        if(!fgets(buffer, BUFFER_SIZE, stdin)) break;
        strcat(buffer, " [C CLIENT]");
        buffer[strcspn(buffer, "\n")] = '\0';
        if((strcmp(buffer, "exit"))==0){
            send(clientsock, buffer, strlen(buffer), 0);
            close(clientsock);
            exit(0);
        } 

        if((send(clientsock, buffer, sizeof(buffer), 0))<0){
            close(clientsock);
            exit_with_sys_err("send error");
        }
    }
    return NULL;
}

void * receiveThread(void * args){
    char buffer[BUFFER_SIZE];
    while(true){
        ssize_t bytesReceived = recv(clientsock, buffer, sizeof(buffer), 0);
        if(bytesReceived <=0){
            if(bytesReceived == 0){
                printf("[REC_THREAD] Connection with the server has been closed!\n");
            }else{
                printf("[REC_THREAD] Receive Error\n");
            }
            close(clientsock);
            exit(1);
        }
        buffer[bytesReceived] = '\0';
        printf("\n>%s\n", buffer);
        fflush(stdout);
    }
    return 0;
}

int main(int argc, char * argv[]){
    if(argc!=3){
        printf("[MAIN] Usage: %s <ip> <port>\n", argv[0]);
        exit_with_err("Wrong usage", 1);
    }
    
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE];
    if((clientsock = socket(AF_INET, SOCK_STREAM, 0))<0){
        exit_with_sys_err("socket()");
    }
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = atoi(argv[2]);
    inet_pton(AF_INET, argv[1],&serv_addr.sin_addr);
    if((connect(clientsock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)))<0){
        close(clientsock);
        exit_with_sys_err("connect");
    }

    pthread_t recThread, sendThread;
    int thrError;
    if((thrError = pthread_create(&recThread, NULL, (void *) receiveThread, NULL))<0){
        close(clientsock);
        exit_with_err("threadcreate receive", thrError);
    }
    if((thrError = pthread_create(&sendThread, NULL, (void *) sendingThread, NULL))<0){
        close(clientsock);
        exit_with_err("threadcreate send", thrError);
    }

    if((thrError = pthread_join(recThread, NULL))<0){
        exit_with_err("threadJoin rec", thrError);
    }
    if((thrError = pthread_join(sendThread, NULL))<0){
        exit_with_err("threadJoin send", thrError);
    }
}