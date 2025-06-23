#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

#define BUFFSIZE 1024
#define LINE_SEPARATOR " "

typedef enum{
    REGISTRAZIONE = 'r';
    SUCCESS = '1',
    FAIL = '0',
    LOGIN = 'l',
    SEND = 's',
    RECEIVE = 'R',
    EXIT = 'q',
} Operation;

typedef struct{
    Operation op;
    char username[16];
    char password[16];
    int port;
    int token; //32bit
    char message[1000];
} Message;

bool search_username(Message * msg){
    char line[1000]; 
    char * username;
    FILE * database = fopen("database.txt", "r");
    
    while(fgets(line, 1000, database)!=NULL){ //TODO: error checking later on
        username = strtok(line, "");
        printf("[INFO] Controllo se l'username esiste\n")
        if(strcmp(username, msg->username)==0){
            printf("[ERRORE] Username esistente\n");
            return true;
        }
    }
    fclose(database);
    return false;
}

void register_user(Message * msg, char ip[]){
    if(search_username(msg)){
        printf("Utente gia' presente all'interno del file \n");
        msg->op = FAIL;
        return;
    }else{
        printf("Inizio registrazione client\n");
        msg->op = SUCCESS;
        msg->token = rand();
        FILE * database  = fopen("database.txt", "a");
        fprintf(database, "%s %s %s %d %d", msg->username, msg->password, ip, msg->port, msg->token);
        fclose(database);
    }
}

void send_message(Message * msg, int sockfd){
    if(!get_username_by_token(msg)){
        msg->op FAIL;
        return;
    }

    msg->op = RECEIVE;
    msg->token = 0;

    char line[1000];
    char * username;
    char * ip;
    char * port;
    FILE * database = fopen("database.txt", "r");
    struct sockaddr_in client_addr;
    memset(&client_addr, 0, sizeof(struct sockaddr_in));
    client_addr.sin_family = AF_INET;
    
    while(fgets(line, 10000, database)!=NULL){
        username = strtok(line, LINE_SEPARATOR);
        strtok(NULL, LINE_SEPARATOR);
        ip = strtok(NULL, LINE_SEPARATOR);
        port = strtok(NULL, LINE_SEPARATOR);
        if (strcmp(username, msg->username)){
            printf("Invio all'utente %s con ip %s e porta %s", username, ip, port);
            client_addr.sin_port = htons(atoi(port));
            inet_pton(AF_INET, ip, &client_addr.sin_addr);
            sendto(sockfd, msg, sizeof(Message), 0, (struct sockaddr *)&client_addr, sizeof(struct sockaddr_in));
        }
    }
}

bool get_username_by_token(Message * msg){
    char line[1000];
    char * token;
    char * username;
    FILE * database = fopen("database.txt",  //???????????????????????????????????????????????????????????????????????????????????????
}


int main (int argc, char argv[]){
    if(argc<2 || atoi(argv[1])){
        fprintf(stderr, "Usage: %s <PORT>\n", argv[0]);
        exit(1);
    }
    int sockfd;
    struct sockaddr_in serv_addr, client_addr;
    socklen_t client_struct_length = sizeof(struct sockaddr_in);
    Message msg; 
    char buffer[BUFFSIZE];
    char ip[INET_ADDRSTRLEN];
    
    FILE * database = fopen("database.txt", "rw");

    memset(&serv_addr, 0, sizeof(serv_addr));
    memset(&client_addr, 0, sizeof(client_addr));
    memset(&msg, 0, sizeof(msg));

    sockfd = open(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[1]));
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    while(true){
        //ricezione del messaggio
        recvfrom(sockfd, &msg, sizeof(Message), 0, (struct sockaddr *)&client_addr, &client_struct_length);

        //decidere quale operazione effettuare in base alla richiesta dell'utente
        switch(msg.op){
            case REGISTRAZIONE:
                inet_ntop(AF_INET, &client_addr.sin_addr, ip, client_struct_length);
                register_user(&msg, ip);
                break;
            case SEND:
                send_message(&msg, sockfd);
                break;
            case EXIT:
                printf("Interruzione di comunicazione\n");
                break;
            default:
                printf("L'operazione non e' stata riconosciuta\n");
                continue;
        }
        sendto(sockfd, &msg, sizeof(Message), 0, (struct sockaddr *)&client_addr, &client_struct_length);

    }


    



    return 0;
}