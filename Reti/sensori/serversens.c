#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include "sensorprotocol.h"

#define ever (;;)
#define MAX_sensors 4 //max sensors in queue
#define PORT 8080
#define MAX_BUFF 1024


typedef struct {
   int sockfd;
   struct sockaddr_in address;
   char last_msg[MAX_BUFF];
} sensor_info;


typedef struct{
    int socket;
    struct sockaddr_in address;
    uint8_t id_sensor;
    time_t timestamp;
    bool riccobnene;
    float temperature
    uint8_t humidity;
}sensor_info;

typedef stuct{
    sensor_info * sensor[MAX_sensors];
    int count;
    pthread_mutex_t mutex;
}sensor_list;

// shared data structure with mutex
typedef struct {
   sensor_info *sensors[MAX_sensors];
   int count;
   pthread_mutex_t mutex;
} sensor_list;

sensor_list sensors = { .count = 0 };


void gestionesensor(void * argv){

    sensor_info *info = (sensor_info *)argv;

    //int sensor_sock = sensor->socket;

    int sensor_sock = info->sockfd;
    char buffer[MAX_BUFF];
    char sensor_ip[INET_ADDRSTRLEN];
  
    inet_ntop(AF_INET, &info->address.sin_addr, sensor_ip, INET_ADDRSTRLEN);
    int sensor_port = ntohs(sensor->address.sin_port);

    //voglio aggiungere 
    

    pthread_mutex_lock(&sensors.mutex);
    sensors.sensors[sensors.count++] = info;
    pthread_mutex_unlock(&sensors.mutex);

    for (;;){
        ssize_t bytes_received = recv(sensor_sock, buffer, MAX_BUFF, 0);


        //disconnessione del sensore
        if(bytes_received == 0){
            printf("sensor %s:%d disconnected\n", sensor_ip, sensor_port);
            pthread_mutex_lock(&sensors.mutex);
            for(int i = 0; i < sensors.count; i++) {
                if(sensors.sensors[i]->sockfd == sensor->socket) {
                    free(sensors.sensors[i]);
                    for(int j = i; j < sensors.count - 1; j++) {
                        sensors.sensors[j] = sensors.sensors[j + 1];
                    }
                    sensors.count--;
                    break;
                }
            }
            pthread_mutex_unlock(&sensors.mutex);

            break;
        }

        sscanf(buffer, MSG_PROTOCOL, &(sensor->id_sensor),
                &(sensor->timestamp),
                &(sensor->riccobene),
                &(sensor->temperature),
                &(sensor->humidity),
                &(sensor->quality));
        //buffer[bytes_received] = '\0';
        if(firstMessage){
            printf("New connection from sensor %s:%d\n", sensor_ip, sensor_port);
        }
       
        printf("[SENSOR %hhu][%ld][Riccobene? %d] Dati : %f C, %d hum, %d Qual \n",
            sensor->id_sensor, sensor->timestamp,
            sensor->riccobene, sensor->temperature,
            sensor->humidity, sensor->quality);
        if(sensor->temperature >40){
            send(sensor->socket, "AAAAAAAAAAAAAa");
        }
        //broadcast_message(buffer, sensor_sock);

    }

    close(sensor_sock);
}

void broadcast_message(const char *message, int sender_fd) {

   pthread_mutex_lock(&sensors.mutex);
  
   for(int i = 0; i < sensors.count; i++) {
       if(sensors.sensors[i]->sockfd != sender_fd) {
           send(sensors.sensors[i]->sockfd, message, strlen(message), 0);
       } else {
        strcpy(sensors.sensors[i]->last_msg, message);
       }
   }
  
   pthread_mutex_unlock(&sensors.mutex);
}





int create_server(uint16_t port){

   int socketServerFD;
   struct sockaddr_in addr;
   socklen_t addr_len = sizeof(addr);

   if ((socketServerFD = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
       perror("socket failed");
       return -1;
   }

   memset(&addr, 0, sizeof(addr));
   addr.sin_family = AF_INET;
   addr.sin_port = htons(port);
   addr.sin_addr.s_addr = htonl(INADDR_ANY);

   // Bind and listen
   if (bind(socketServerFD, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
       perror("bind failed");
       return -2;
   }

   if (listen(socketServerFD, MAX_sensors) < 0) {
       perror("listen failed");
       return -3;
   }

   return socketServerFD;
}


int main(int argc, char * argv[]){

    if(argc < 2){
        printf("Allora sei scemo, mi devi usare come %s <PORT>\n", argv[0]);
        exit(1);
    }

    int serverSocketFD = create_server(atoi(argv[1]));

    if(serverSocketFD<0){
        exit(1);
    }

    printf("Server in ascolto sulla porta %s\n", argv[1]);

    for(;;){

        sensor_info *sensor = malloc(sizeof(sensor_info));
        socklen_t addrlen = sizeof(sensor->address);

        sensor->socket = accept(serverSocketFD, (struct sockaddr*)&sensor->address, &addrlen);

        //devo separare logicamente il codice in due processi

        pthread_t threadsensor;
        pthread_create(&threadsensor, NULL, (void *)gestionesensor, (void*)sensor);
        pthread_detach(threadsensor);
        
    }
    

    // devo poter gestire il sensor in separata sede e continuare ad accettare altre connessioni
    printf("Chiusura del server\n");
    pthread_mutex_destroy(&sensors.mutex);
    close(serverSocketFD);
    exit(0);

}

