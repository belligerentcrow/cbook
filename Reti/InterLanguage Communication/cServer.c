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

#define MAX_CONNECTIONS 5
#define BUFFER_SIZE 8192

typedef struct{
    int sockfd;
    struct sockaddr_in address;
} clientData;

typedef struct{
    clientData * clients[MAX_CONNECTIONS];
    int count;
    pthread_mutex_t mutex;
} clientsList;

int init_server(uint16_t port){
    int sockfd;
    struct sockaddr_in addr;
    socklen_t addressLen = sizeof(addr);
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0))<0){
        exit_with_sys_err("creating server socket");
    }
    memset(&addr,0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if((bind(sockfd, (struct sockaddr *)&addr, addressLen))<0){
        exit_with_sys_err("Bind error");
    }
    if((listen(sockfd, MAX_CONNECTIONS))<0){
        exit_with_sys_err("Listen Error");
    }
    return sockfd;
}

clientsList mainClientsList = {.count =0};

void broadcast(const char * message, int senderfd){
    pthread_mutex_lock(&mainClientsList.mutex);
    for(int i = 0; i<mainClientsList.count; i++){
        if(mainClientsList.clients[i]->sockfd != senderfd){
            send(mainClientsList.clients[i]->sockfd, message, strlen(message), 0);
        }
    }
    pthread_mutex_unlock(&mainClientsList.mutex);
}



void * clientManagement(void * args){
    clientData * data = (clientData *)args;

    int clientSock = data->sockfd;
    char buffer[BUFFER_SIZE];
    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &data->address.sin_addr, client_ip, INET_ADDRSTRLEN);
    int client_port = ntohs(data->address.sin_port);

    printf("[CLIENT_MANAGEMENT] New connection from ... %s:%d", client_ip, client_port);
    pthread_mutex_lock(&mainClientsList.mutex);
    mainClientsList.clients[mainClientsList.count++] = data;
    pthread_mutex_unlock(&mainClientsList.mutex);

    while(true){
        ssize_t bytes_received = recv(clientSock, buffer, BUFFER_SIZE-1, 0);
        if(bytes_received<=0){
            if(bytes_received == 0){
                printf("Client %s:%d disconnected...\n", client_ip, client_port);
            }else{
            perror("recv failed");
            break;
        }
        }
        buffer[bytes_received] = '\0';
        char messageIncoming[BUFFER_SIZE+INET_ADDRSTRLEN];
        snprintf(messageIncoming, sizeof(messageIncoming) + sizeof(client_port) + sizeof(client_ip), "[CLIENT %s:%d] %s", client_ip, client_port, buffer);
        printf("%s", messageIncoming);
        broadcast(messageIncoming, clientSock);
        if(strcmp(buffer, "exit\n")==0){
            break;
        }
    }
}

int main(int argc, char * argv[]){
    if(argc!=2){
        printf("[MAIN] Usage: %s <port>\n", argv[0]);
        exit_with_err("Wrong usage", 1);
    }
    if(atoi(argv[1])<1024){
        printf("[MAIN] Do not use reserved ports! >1024 only please\n");
        exit_with_err("Reserved ports", 2);
    }
    int portnumber = atoi(argv[1]);
    int serverSock, clientSock;
    struct sockaddr_in addr;
    socklen_t socketlength=sizeof(addr);
    if((serverSock = init_server((uint16_t) portnumber))<0){
        exit_with_sys_err("Server Init");
    }
    printf("[MAIN] C server running on port %d...\n", portnumber);

    
    pthread_mutex_init(&mainClientsList.mutex, NULL);

    while(true){
        clientData * clientConn = malloc(sizeof(clientData));
        socklen_t addresslength = sizeof(clientConn->address);
        if((clientConn->sockfd = accept(serverSock, (struct sockaddr *)&clientConn->address, &addresslength))<0){
            free(clientConn);
            perror("accept");
            continue;
        }
        pthread_t threadManagement;
        if((pthread_create(&threadManagement, NULL, clientManagement, (void *)clientConn))!=0){
            perror("pthread_create");
            close(clientConn->sockfd);
            free(clientConn);
        }else{
            pthread_detach(threadManagement);
        }
    }
   
    close(serverSock);
    pthread_mutex_destroy(&mainClientsList.mutex);
    exit(EXIT_SUCCESS);

}