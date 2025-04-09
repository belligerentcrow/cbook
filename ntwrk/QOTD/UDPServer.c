//#include <winsock2.h>
#include <stdlib.h>
#include <string.h>
//#include <ws2tcpip.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>

#define QUOTESNUMBER 4



int main(int argc, char * argv[]){
    srand(time(0));
    const char * quotes[QUOTESNUMBER] ={
        "Laugh hard, run fast, be kind --Twelfth Doctor",
    "The lieutenant remains silent, but his expression couldn't say I told you so any louder. --Kim Kitsuragi",
    "I AM A FRAGMENT OF THE WORLD SPIRIT, THE GENIUS LOCI OF REVACHOL. --Shivers",
    "Dear reader, if you are tired by this tedious procedure, take pity on me, for i carried it out at least 70 times. --Kepler"
    };


    
    struct sockaddr_in server_addr, client_addr;
    char client_request[2048];

    socklen_t addr_len = sizeof(client_addr);
    
    memset(&server_addr, 0, addr_len);
    memset(&client_addr, 0, sizeof(client_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(20300);
    server_addr.sin_addr.s_addr = INADDR_ANY; //accetta da qualsiasi indirizzo
    
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    printf("OK Socket\n");

    bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    printf("OK Bind\n");
    socklen_t cl_addr_len = sizeof(client_addr);
    recvfrom(sockfd, client_request,sizeof(client_request), 0, (struct sockaddr *)&client_addr, &cl_addr_len);
    printf("Received connection from %s", inet_ntoa(client_addr.sin_addr));

    
    int quotenumb = (rand()%QUOTESNUMBER);

    
    sendto(sockfd, quotes[quotenumb], sizeof(quotes[quotenumb]), 0, (struct sockaddr *)&client_addr,cl_addr_len);
    for(int i = 0; i < 2000; ++i){

    }
    close(sockfd);
    return 0;
    
    

}

