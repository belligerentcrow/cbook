#include "lib-misc.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define STARTVALUE 0
#define INCREMENT_FIRST 1
#define INCREMENT_SECOND 2
#define INCREMENT_THIRD 3
#define CYCLES 50

struct shared{
    unsigned long c;
    pthread_mutex_t lock;
};

struct thread_data{
    pthread_t tid;
    unsigned long incr;
    struct shared *shy;
};

void * firstFunc(void *arg){
    int err;
    struct thread_data *dataptr = (struct thread_data *)arg;
    printf("[%lu] sono il primo thread! pid: %d\n", dataptr->tid,getpid());
    printf("[%lu] figlio conta...\n",dataptr->tid);
    for(int i =0; i<CYCLES; ++i){
        //entro sezione critica
        if((err = pthread_mutex_lock(&dataptr->shy->lock))!=0){
            exit_with_err("pthread_mutex_lock_first", err);
        }
        dataptr->shy->c+=INCREMENT_FIRST; //sezione critica

        //lascio sezione critica
        if((err=pthread_mutex_unlock(&dataptr->shy->lock))!=0){
            exit_with_err("pthread_mutex_unlock_first", err);
        }
    }
    printf("[%lu] incrementi applicati. Siamo a %lu\n", dataptr->tid, dataptr->shy->c);
    return (NULL);
}

void * secondFunc(void *arg){
    int err;
    struct thread_data *dataptr = (struct thread_data *)arg;
    printf("[%lu] sono il secondo thread! pid: %d\n", dataptr->tid,getpid());
    printf("[%lu] figlio conta...\n",dataptr->tid);
    for(int i =0; i<CYCLES; ++i){
        //entro sezione critica
        if((err = pthread_mutex_lock(&dataptr->shy->lock))!=0){
            exit_with_err("pthread_mutex_lock_second", err);
        }
        dataptr->shy->c+=INCREMENT_SECOND; //sezione critica //sezione critica

        //lascio sezione critica
        if((err=pthread_mutex_unlock(&dataptr->shy->lock))!=0){
            exit_with_err("pthread_mutex_unlock_second", err);
        }
    }
    printf("[%lu] incrementi applicati. Siamo a %lu\n", dataptr->tid, dataptr->shy->c);
    return (NULL);
}

void * thirdFunc(void *arg){
    int err;
    struct thread_data *dataptr = (struct thread_data *)arg;
    printf("[%lu] sono il terzo thread! pid: %d\n", dataptr->tid,getpid());
    printf("[%lu] figlio conta...\n",dataptr->tid);
    for(int i =0; i<CYCLES; ++i){
        //entro sezione critica
        if((err = pthread_mutex_lock(&dataptr->shy->lock))!=0){
            exit_with_err("pthread_mutex_lock_third", err);
        }
        dataptr->shy->c+=INCREMENT_THIRD; //sezione critica //sezione critica

        //lascio sezione critica
        if((err=pthread_mutex_unlock(&dataptr->shy->lock))!=0){
            exit_with_err("pthread_mutex_unlock_third", err);
        }
    }
    printf("[%lu] incrementi applicati. Siamo a %lu\n", dataptr->tid, dataptr->shy->c);
    return (NULL);
}

int main(void){
    pid_t currentPID = getpid();
    int err=0;
    struct shared sh = {0,PTHREAD_MUTEX_INITIALIZER};
    //pthread_mutex_t mutex = pthread_mutex_init(PTHREAD_MUTEX_INITIALIZER, c);
    struct thread_data dats[3];
    unsigned long expectedTot = STARTVALUE+((INCREMENT_FIRST*CYCLES) + (INCREMENT_SECOND*CYCLES)+(INCREMENT_THIRD*CYCLES));
    
    dats[0].incr = INCREMENT_FIRST;
    dats[0].shy = &sh;
    dats[1].incr = INCREMENT_SECOND;
    dats[1].shy = &sh;
    dats[2].incr = INCREMENT_THIRD;
    dats[2].shy = &sh;

    
    printf("%d\n",currentPID);
    printf("[%d] padre creato.\n", getpid());
    printf("[%d] sono il padre!, il mio padre è %d\n", getpid(), getppid());
    
    pthread_t firstThread, secondThread, thirdThread;

    printf("[%d] creo primo thread\n",getpid());
    if((err=pthread_create(&firstThread, NULL, firstFunc, (void *)(&dats[0])))!=0){
        exit_with_err("pthread_create first thread", err);
    }

    printf("[%d] creo secondo thread\n",getpid());
    if((err=pthread_create(&secondThread, NULL, secondFunc,(void *)(&dats[1])))!=0){
        exit_with_err("pthread_create second thread", err);
    }

    printf("[%d] creo terzo thread\n",getpid());
    if((err=pthread_create(&thirdThread, NULL, thirdFunc, (void *)(&dats[2])))!=0){
        exit_with_err("pthread_create third thread", err);
    }


    printf("[%d] aspetto che i thread finiscano... tocca a '%lu'\n", getpid(), dats[0].tid);
    if((err=pthread_join(firstThread, NULL))!=0){
        exit_with_err("pthread_join first\n",err);
    }
    printf("[%d] '%lu' terminato!\n", getpid(), dats[0].tid);

    printf("[%d] aspetto che i thread finiscano... tocca a '%lu'\n", getpid(), dats[1].tid);
    if((err=pthread_join(secondThread, NULL))!=0){
        exit_with_err("pthread_join second",err);
    }
    printf("[%d] '%lu' terminato!\n", getpid(), dats[1].tid);

    printf("[%d] aspetto che i thread finiscano... tocca a '%lu'\n", getpid(), dats[2].tid);
    if((err=pthread_join(thirdThread, NULL))!=0){
        exit_with_err("pthread_join third",err);
    }
    printf("[%d] '%lu' terminato!\n", getpid(), dats[2].tid);

    printf("[%d] controllo finale: dovrebbe essere %lu, e ho %lu\n", getpid(), expectedTot, sh.c);

   if(expectedTot==sh.c){
        printf("[%d] risultato corretto!", getpid());
        exit(EXIT_SUCCESS);
   }else{
        printf("[%d] risultato errato!", getpid());
        exit(EXIT_FAILURE);
   }
}