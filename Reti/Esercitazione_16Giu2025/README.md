# Esercitazione di programmazione: Chat UDP con Registrazione e Token

## Scopo dell'esercitazione
Progettare e completare una piccola applicazione client-server bassata su UDP che consenta:
* La **registrazione** di un utente tramite *username*, *password* e porta locale di ascolto 
* L'assegnazione di un **token segreto a 32bit** che identifichi un modo univoco l'utente
* L'invio di **messaggi broadcast** dal client al server e la redistribuzione a tutti gli altri client registrati
* Il mantenimento di un **file di database** lato server con le quadruple *username*, *password*, *ip*, *porta*, *token*.

## Requisiti funzionali  
* **RF1** - Un client appena registrato riceve il proprio token in risposta dal server
* **RF2** - Un client che prova a registrarsi con un username gia' esistente ottiene FAIL (se e' gia' registrato otterra' lo stesso token che aveva precedentemente ricevuto, altrimenti 0)
* **RF3** - Un client puo' inviare un messaggio solo se in possesso di un token valido
* **RF4** - Tutti i client attivi ricevono i messaggi broadcast in tempo reale
* **RF5** - Il token rimane segreto: non compare nei messaggi inoltrati