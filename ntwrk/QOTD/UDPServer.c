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

    srand(time(0)); //this lets the seed of randomness be defined through clock: offering a better randomization 

    //quotes list
    const char * quotes[QUOTESNUMBER] ={
        "Laugh hard, run fast, be kind --Twelfth Doctor",
    "The lieutenant remains silent, but his expression couldn't say I told you so any louder. --Kim Kitsuragi",
    "I AM A FRAGMENT OF THE WORLD SPIRIT, THE GENIUS LOCI OF REVACHOL. --Shivers",
    "Dear reader, if you are tired by this tedious procedure, take pity on me, for i carried it out at least 70 times. --Kepler"
    };


    
    struct sockaddr_in server_addr, client_addr;
    char client_request[2048];

    socklen_t addr_len = sizeof(client_addr);
    
    //clearing up memory before using it
    memset(&server_addr, 0, addr_len);
    memset(&client_addr, 0, sizeof(client_addr));
    memset(client_request, 0, sizeof(client_request));

    //structuing the socket
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(20300); //arbitrary hardcoded port
    server_addr.sin_addr.s_addr = INADDR_ANY; //accetta da qualsiasi indirizzo
    
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    printf("OK Socket\n");

    //binding the socket
    bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    printf("OK Bind\n");
    
    //this defines the length of the client address in socklen_t format 
    socklen_t cl_addr_len = sizeof(client_addr);

    //the receive from: the client is listening
    recvfrom(sockfd, client_request,sizeof(client_request), 0, (struct sockaddr *)&client_addr, &cl_addr_len);

    //acknowledges connection
    printf("Received connection from %s", inet_ntoa(client_addr.sin_addr));

    //picks a random number from 0 to number-of-quotes 
    int quotenumb = (rand()%QUOTESNUMBER);

    //sends the quote
    sendto(sockfd, quotes[quotenumb], sizeof(quotes[quotenumb]), 0, (struct sockaddr *)&client_addr,cl_addr_len);
    
    //closes the socket immediately after
    close(sockfd);
    return 0;
    
    

}

