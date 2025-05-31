#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    int sockfd;
    struct sockaddr_in server_addr;
    //creating char arrays of the messages
    char server_message[2048], client_request[2048];
    socklen_t ser_struct_len = sizeof(server_addr);

    //clearing structures
    memset(&server_addr, 0, ser_struct_len);
    memset(client_request, 0, sizeof(client_request));
    memset(server_message, 0, sizeof(server_message));

    //creating socket
    sockfd=socket(AF_INET, SOCK_DGRAM, 0);
    
    //defining the socket parameters (hardcoded now)
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("YOUR ADDRESS HERE"); // Hardcoded the server address here
    server_addr.sin_port = htons(20300); //hardcoded an arbitrary port here

    printf("Socket Created\n");

    //sendto the server any kind of packet (irrelevant in this particular protocol)
    sendto(sockfd, client_request, strlen(client_request), 0, (struct sockaddr *)&server_addr, ser_struct_len);

    //receiving the quote
    recvfrom(sockfd, server_message, sizeof(server_message), 0, (struct sockaddr *)&server_addr, &ser_struct_len);
    //printing the quote
    printf("Quote received: %s", server_message);
    
}