#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024
#define MAX_NAME_LEN 256

int sockClientfd;
struct sockaddr_in sa;
char buffer[BUFFER_SIZE];

void * receivingMoves(void * args){
    while(true){
        ssize_t bytes_received = recv(sockClientfd, buffer, BUFFER_SIZE-1, 0);
        if(bytes_received <0){
            perror("recv failed");
            break;
        }else if(bytes_received==0){
            printf("server closed connection\n");
            break;
        }
        printf("Received: %s", buffer);
        sendingMoves();
    }
   
}

void sendingMoves(){
    if(!fgets(buffer, BUFFER_SIZE, stdin)){
        break;
    }
    buffer[strcspn(buffer, "\n")]='\0';
    if(strcmp(buffer, "exit")==0){
        break;
    }
    if(send(sockClientfd, buffer, strlen(buffer), 0)<0){
        perror("send failed");
        break;
    }
    printf("> ");
    fflush(stdout);
    
}


int main(int argc, char* argv[]) {
   if(argc !=4){
       //remember, argv[0] is the same program!
       fprintf(stderr, "Usage: %s <IP> <Port> <Name>\n", argv[0]);
       exit(1);
   }

    // save the socket file descriptor
   


   // create socket (ip, using TCP)
   if ((sockClientfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
       perror("socket creation failed");
       exit(1);
    }

    memset(&sa, '\0', sizeof(sa));

    sa.sin_family = AF_INET;
    sa.sin_port = htons(atoi(argv[2]));

    if((inet_pton(AF_INET, argv[1], &sa.sin_addr))<=0){
        perror("invalid address");
        exit(1);
    }

    if (connect(sockClientfd, (struct sockaddr *)&sa, sizeof sa) < 0) {
        perror("connect");
        close(socketClientfd);
        return 2;
    }
    
    char name[MAX_NAME_LEN];
    strcpy(name, argv[3]);
    if(send(sockClientfd, name, strlen(name), 0)<0){
        perror("send failed");
        break;
    }

    pthread_t receiveMoves;
    pthread_create(&receiveMoves, NULL, (void *)receivingMoves, NULL);
    pthread_join(receiveMoves, NULL);


}
