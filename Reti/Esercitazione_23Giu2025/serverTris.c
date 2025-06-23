#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_CLIENTS 20
#define BUFFER_SIZE 1024
#define MAX_NAME_LEN 256

typedef struct {
    char nameClient[MAX_NAME_LEN];
    int sockfd;
    struct sockaddr_in address;
} client_info;

// shared data structure with mutex
typedef struct {
   client_info *clients[MAX_CLIENTS];
   int count;
   pthread_mutex_t mutex;
} client_list;

client_list clients = { .count = 0 };

void *handle_client(void *arg) {
   client_info *info = (client_info *)arg;
   int client_sock = info->sockfd;
   char buffer[BUFFER_SIZE];
   char client_ip[INET_ADDRSTRLEN];
  
   inet_ntop(AF_INET, &info->address.sin_addr, client_ip, INET_ADDRSTRLEN);
   int client_port = ntohs(info->address.sin_port);

   printf("New connection from %s:%d\n", client_ip, client_port);

   // Add client to list
   pthread_mutex_lock(&clients.mutex);
   clients.clients[clients.count++] = info;
   pthread_mutex_unlock(&clients.mutex);
     for(;;) {
       ssize_t bytes_received = recv(client_sock, buffer, BUFFER_SIZE - 1, 0);
       if(bytes_received <= 0) {
           if(bytes_received == 0)
               printf("Client %s:%d disconnected\n", client_ip, client_port);
           else perror("recv failed");
           break;
       }

       buffer[bytes_received] = '\0';
      
       char formatted_message[BUFFER_SIZE + INET_ADDRSTRLEN];

       //snprintf(formatted_message, sizeof(formatted_message),"[%s:%d] %s", client_ip, client_port, buffer);
       //printf("%s", formatted_message);
       /// ------------------------ 

       if(strcmp(buffer, "exit\n") == 0) {
           break;
       }
    }
}

int main(int argc, char argv[]){
    int server_fd;
    struct sockaddr_in address;
    pthread_mutex_init(&clients.mutex, NULL);

    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
       perror("socket failed");
       exit(1);
   }
    
   address.sin_family = AF_INET;
   address.sin_addr.s_addr = INADDR_ANY;
   address.sin_port = htons(PORT);

   if(bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0){
    perror("bind failed");
    exit(1)
   }
   if ((listen(server_fd, MAX_CLIENTS))<0){
    perror("listen");
    exit(1);
   }
   printf("Server listening on port %d\n",PORT);

   for(;;) {
       client_info *client = malloc(sizeof(client_info));
       socklen_t addrlen = sizeof(client->address);
      
       // accept new connection
       if((client->sockfd = accept(server_fd, (struct sockaddr *)&client->address, &addrlen)) < 0) {
           perror("accept");
           free(client);
           continue;
       }

       // Create thread for new client
       pthread_t thread_id;
       if(pthread_create(&thread_id, NULL, handle_client, (void *)client) != 0) {
           perror("pthread_create");
           close(client->sockfd);
           free(client);
       } else {
           pthread_detach(thread_id);
       }
   }


}