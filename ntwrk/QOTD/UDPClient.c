#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int sockfd;
    struct sockaddr_in server_addr;
    char server_message[2048], client_request[2048];
    socklen_t ser_struct_len = sizeof(server_addr);

    memset(&server_addr, 0, ser_struct_len);
    memset(client_request, 0, sizeof(client_request));
    memset(server_message, 0, sizeof(server_message));

    sockfd=socket(AF_INET, SOCK_DGRAM, 0);
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("192.168.1.210"); // Hardcoded the server address here
    server_addr.sin_port = htons(20300);
    printf("Socket Created\n");
    sendto(sockfd, client_request, strlen(client_request), 0, (struct sockaddr *)&server_addr, ser_struct_len);

    recvfrom(sockfd, server_message, sizeof(server_message), 0, (struct sockaddr *)&server_addr, &ser_struct_len);
    printf("Quote received: %s", server_message);
    for(int i = 0; i < 2000; ++i){

    }
}