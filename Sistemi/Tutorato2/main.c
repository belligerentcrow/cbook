#include <fcntl.h>
#include "lib-misc.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

#define MODE 0600 
#define BUFSIZE 2048
#define PATH_MAX 4086

void copy(char * source, char * dest){
    char path_destination[PATH_MAX];
    sprintf(path_destination, "%s/%s", "dest", dest);

    int fin, fout, size;
    char buffer[BUFSIZE];
    if((fin = open(source, O_RDONLY | O_CREAT))<0){
        exit_with_sys_err("Errore open fin");
    }

    do {
        size = read(fin, buffer, BUFSIZE);
        if(size<0){
            exit_with_sys_err("size error");
        }elseif(size>0){
            if((write(fout, buffer, size))<0){
                
            }
        }
    } while(true);
    
}

#define exit_with_err_msg(...)                                                 \
    do {                                                                       \
        fprintf(stderr, __VA_ARGS__);                                          \
        exit(EXIT_FAILURE);                                                    \
    } while (0)


int main(int argc, char * argv []){
    if (argc < 3){
        exit_with_err_msg("Usage: %s <source> <dest>", argv[0]);
    }

    for(int i = 1; i < argc-1; ++i){
        
    }

}   