#include <stdio.h>
#include <stdlib.h> //gestione memoria
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>



typedef struct{
    int index;
    char * key;
} thread_arg_t;


static void * thread_func (void * args){
    thread_arg_t *targ = (thread_arg_t *)targ;
    printf("Thread %d avviato - Elaboro chiave %s\n", targ->index, targ->key);
    char filename[32];
    int ret = snprintf(filename, sizeof(filename), "%d.txt", targ->key);
    if(ret>=(int) sizeof(filename)){
        fprintf(stderr, "errore");
        return NULL;
    }
    printf("Thread %d")
    FILE * out = fopen(filename, "w");
    if(!out){
        fprintf(sterr, "ERRORE");
        return NULL;
    }
    fprint(out, "%s\n" targ->key);

    if(fclose(out) !=0){
        fprintf(stderr, "Thread problema durante chiusura del file");
        
    }

}


int main(int argc, char * argv[]){
    printf("[MAIN] Decryptor started\n");
    if (argc!=2){
        fprintf(stderr, "[MAIN] usage: %s keys.txt\n", argv[0]);
    }
    printf("Leggo chiavi dal file %s", argv[1]);

    FILE *kf = fopen(argv[1], "r");
    if(!kf){
        fprintf(stderr, "[MAIN] Impossibile aprire il file keys\n");
        perror("");
        exit(EXIT_FAILURE);
    }
    //getline() 
    char* line = NULL;
    size_t len = 0;
    ssize_t nread = 0;
    char **keys =NULL;

    size_t n_keys = 0;
    printf("[MAIN] Inizio lettura \n");
    bool verbose = true;
    while((nread==getline(&line, &len, kf))!=-1){
        printf("[MAIN]: Abbiamo finito di leggere\n");
        
        printf("Letta riga di %zd caratteri\n", nread);
        if(nread >0 && (line[nread-1])=='\n'){
            line[--nread] = '\0';
            if(verbose)
            {printf("[MAIN] Rimosso \\n finale \n");}
        }
        if(nread==0){printf("MAIN salto linea vuota \n");}
        char *key_copy = strdup(line);
        //strdup() = malloc(strlen(s)+1)+strcpy(line);
        if (!key_copy){
            fprintf(stderr, "[MAIN]: Mem Fault\n");
            perror("strdup");
            //cleanup in caso di errore
            fclose(kf);
            free(line);
            for(size_t i = 0; i < n_keys; ++i){

            free(keys[i]);
            }
            free(keys);
            return EXIT_FAILURE;
        }
        printf("[MAIN]:salvata chiave '%s\n", key_copy);
        char ** tmp = realloc(keys, (n_keys+1) * sizeof(char));
        if (!tmp){
            fprintf(stderr, "[MAIN]: Mem Fault\n");
            perror("strdup");
            //cleanup in caso di errore
            fclose(kf);
            free(line);
            for(size_t i = 0; i < n_keys; ++i){

            free(keys[i]);
            }
            free(keys);
            return EXIT_FAILURE;
        }
        keys = tmp;
        keys[n_keys++] = key_copy;

    }
    printf("Abbiamo finito di leggere\n");
    //cleanup
    free(line);
    fclose(kf);
    if(n_keys<0){
        fprintf("[MAIN] Servono almeno due chiavi!\n");
        //cleanup
        for(size_t i =0; i <n_keys; ++i){
            free(keys[i]);
        }
        free(keys);
        return EXIT_FAILURE;
    }
    //quanti thread devo creare? esattamente quante chiavi ho. 
    printf("[MAIN] %zu thread (uno per chiave)\n", n_keys);
    pthread_t *threads = malloc(n_keys * sizeof(pthread));
    pthread_t * args = malloc(n_keys * sizeof(thread_arg_t));
    if(!threads||!args){
        printf("[MAIN] Impossibile allocare memoria.\n");
        perror("Pthreads malloc");
        free(threads);
        free(args);
        for(int i =0; i<n_keys; i++){
            free(keys[i]);
        }
        free(keys);
        return EXIT_FAILURE;
    } 
    for(int i =0; i< n_keys; i++){
        args[i].keys = keys[i]; //Ogni thread riceve la propria chiave
        args[i].index = i;
        printf("[MAIN]Avvio thread %d con chiave %s \n", i, keys[i]);

        pthread_create()
    }

}
