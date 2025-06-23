# TRIS 

## Client
* Si deve registrare al Server con nick 
* Deve mandare le mosse al server quando e' il suo turno
* Posizioni della griglia:
    1 | 2 | 3
    ---------
    4 | 5 | 6
    ---------
    7 | 8 | 9
* Mando una send iniziale per registrarmi con il server, poi ho un thread che aspetta risposte dal server. 
    * Quando riceve una risposta, (clear-to-send) il client chiama una funzione per mandare una risposta al server 
## Server
* Deve poter aprire molte connessioni TCP
* Deve controllare se il nick esiste
* Mette in attesa i client fin quando non ce ne sono due disponibili
* Quando ce ne sono due liberi metterli in una partita 
    * Gestire le mosse e il risultato
* Loggare quello che succede in un file
