#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>

#define MAX_CLIENTS 4

int main(){
	int socketServer;
	struct sockaddr_in sa;
    struct sockaddr_in saClientConnesso;

	socketServer = socket(PF_INET, SOCK_STREAM,0);
	sa.sin_family = AF_INET; //l'ip
	sa.sin_port = htons(8000); //la porta
	sa.sin_addr.s_addr = INADDR_ANY; //accetto da tutti gli ip

    //la bind permette alla socketserver di mettersi in ascolto su una porta
    ///la bind: si deve fare casting perche' la bind si aspetta una struttura 
    // sockaddr che e' una struttura generica di sockaddr 
    socklen_t sockLen = sizeof(saClientConnesso);
	bind(socketServer, (struct sockaddr *)&sa, &sockLen); 

    //per mettersi in ascolto effettivamente sulla porta definita sopra:
    //il primo parametro e' il file descriptor della socket, il secondo 
    // "al massimo a quante connessioni/chiamate il server possa rispondere"
    printf("Socket in ascolto sulla porta %d\n", ntohs(sa.sin_port));
    int listen(socketServer, MAX_CLIENTS);
    
	//la porta di ascolto viene scelta a random dal sistema operativo.
    //Inoltre ho bisogno di una reference al client, per poter inviargli dati
    // in risposta: la accept ritorna proprio una referenza al client. 
    //E' bloccante, e attende connessioni. 
    printf("In attesa di connessione...\n");
    int socketClient = accept(socketServer, (struct sockaddr*)&saClientConnesso,
        &sockLen);
    printf("Qualcuno si e' collegato\n");

    //messaggio da inviare
    char msg[256] = "Ciao melo\0";

    //scrivo sul file descriptor della socket, che equivale a mandare 
    //il messaggio 
    write(socketClient, msg, 256);
    printf("Messaggio inviato, chiusura del client e del server.\n");

    //chiudo la connessione: 
    close(socketClient);
    close(socketServer);
    printf("exiting...\n");
    exit(0);

}