#include "lib-misc.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define THREAD_NUMBER 2
#define BUFSIZE 8192
#define NUM_CYCLES 50

struct shared{
    pthread_mutex_t lock;
};

struct thread_data{
    pthread_t tid;
    FILE * filelog;
    struct shared * shy;
};

void * firstFunc(void *arg){
    int err;
    struct thread_data *dataptr=(struct thread_data*) arg;
    dataptr->tid = pthread_self();
    printf("[%lu] Thread, inizio operazioni", dataptr->tid);
    char buf[BUFSIZE];
    strcpy(buf, "[1] - MIMIMIMIMIMIMIMIMIMI\n");
    size_t nbytes = strlen(buf);
    //entro sezione critica
    for(int i = 0; i < NUM_CYCLES; ++i){
        if((err = pthread_mutex_lock(&dataptr->shy->lock))!=0){ 
            exit_with_err("first takes lock\n", err);
        }
        //scrivo in file
        if(((err = fwrite(buf, nbytes,nbytes,dataptr->filelog)))!=0){
            exit_with_err("first write\n", err);
        }
        //esco sezione critica
        if((err = pthread_mutex_unlock(&dataptr->shy->lock))!=0){
            exit_with_err("first yields lock\n", err);
        }
    }
    return (NULL);
}

void * secondFunc(void * arg){
    int err;
    struct thread_data *dataptr = (struct thread_data*)arg;
    dataptr->tid = pthread_self();
    printf("[%lu] Thread, inizio operazioni\n", dataptr->tid);
}



int main(int argc, char * argv[]){
    
    if(argc<2){
        exit_with_err_msg("Errore! Inserire nome file di log\n");
    }
    FILE * doc; //creo puntatore a file che sara' da condividere 
    if((doc = fopen(argv[1], "a"))<0){
        exit_with_sys_err("fopen file\n"); //cerco di aprire il file (dato per argomento)
    }
    int err=0;
    struct shared shard = {PTHREAD_MUTEX_INITIALIZER};
    struct thread_data dats[THREAD_NUMBER];

    for(int i = 0; i <THREAD_NUMBER; ++i){ //inizializzo le strutture dei threads
        dats[i].filelog = doc;
        dats[i].shy = &shard;
    }
    //processo si presenta (educato)
    printf("[%d] sono il processo che contiene i thread!, il mio padre è %d\n", getpid(), getppid());

    pthread_t firstThread, secondThread; //per ora due

    if((err=pthread_create(firstThread, NULL, firstFunc, (void*)(&dats[0])))!=0){
        exit_with_err("errore creazione primo thread\n", err);
    }

    if((err=pthread_create(secondThread, NULL, secondFunc, (void*)(&dats[1])))!=0){
        exit_with_err("errore creazione secondo thread\n", err);
    }
    
    printf("[%d] aspetto che i thread finiscano... tocca a '%lu'\n", getpid(), dats[0].tid);
    if((err=pthread_join(firstThread, NULL))!=0){
        exit_with_err("pthread_join first\n",err);
    }
    printf("[%d] '%lu' terminato!\n", getpid(), dats[0].tid);

    printf("[%d] aspetto che i thread finiscano... tocca a '%lu'\n", getpid(), dats[1].tid);
    if((err=pthread_join(secondThread,NULL))!=0){
        exit_with_err("uscita secondo thread\n",err);
    }
    printf("[%d] '%lu' terminato!\n", getpid(), dats[1].tid);

    printf("[%d] chiudendo tutto...\n", getpid());
    fclose(doc);

}