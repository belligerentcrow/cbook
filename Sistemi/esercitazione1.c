#include <fcntl.h>
#include "lib-misc.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#define BUFSIZ 8192

/*
* scrivere un programma in c che permetta di copiare un numero arbitrario di 
*/

int main(int argv, char * argc[]){
    int sd, dd, err, size;
    char * buf[BUFSIZE];

    if(argv<3){
        exit_with_sys_err("Not enough argumnets");
    }
    for(int i = 1; i<argv-1;++i ){
        if((sd = open(argc[i], O_RDONLY)<0)){
            exit_with_sys_err("open file");
        }
        if((dd = open(argc[i], O_WRONLY))){
            exit_with_sys_err("open")
        }

        do{
        if((size = read(sd, buf, sizeof(buf)))<0){
            exit_with_sys_err("read file");
        }
        if((write(fd, buf, size)<0)){
            exit_with_sys_err("write file");
        }
        }while(size==sizeof(buf));
    }


}