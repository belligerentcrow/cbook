#include <fcntl.h>
#include "lib-misc.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#define BUFSIZE 8192
#define PATH_MAX 4086


void checksize(int filedesc, char * sourcename){
	// mi sposto velocemente alla fine del file per capire di quanti byte sia
	// stampo grandezza file 
	// poi torno all'inizio
	int pos = lseek(filedesc, 0, SEEK_END);
	printf("[MAIN] lettura '%s', di %d byte\n",sourcename,pos); 
	pos = lseek(filedesc, 0, SEEK_SET);

}


int copy(char * source, char * dest){
	int sd, dd, size, total=0, pos;
	char buffer[BUFSIZE];
	char path_destination[PATH_MAX];
	//sprintf(path_destination, "%s/%s", "dest", dest);
	printf("%s\n",path_destination);

	//apro source
	if((sd = open(source, O_RDONLY, S_IRUSR | S_IRGRP))<0){
		exit_with_sys_err("open source error");
	}
	
	checksize(sd, source);

	//apro destinazione
	if((dd=open(dest, O_WRONLY | O_CREAT))<0){
		exit_with_sys_err("open or create destination");
	}
	
	//effettiva copia qui 
	do{	
		//read
		if((size=read(sd, buffer, BUFSIZE))<0){
			exit_with_sys_err("read from source copy");
		}
		total+=size;
		printf("Ho letto %d byte\n", size);
		//write
		if((write(dd, buffer, size))<0){
			exit_with_sys_err("write on destination");
		}
	} while(size==BUFSIZE);

	//closing up everything
	close(sd);
	close(dd);
	//ritorno totale bytes copiati 
	return total;
}


int main(int argc,  char * argv[]){

	if(argc!=3){
		printf("usage: copy <source> <dest>");
		exit_with_sys_err("wrong args");
	}

	printf("[MAIN] provando duplicazione di %d file\n",argc-2);
	for(int i = 1; i < argc-1; ++i){
		int total = copy(argv[i], argv[argc-1]);
		printf("Totale: %d byte copiati\n", total);
	}
	printf("All went well\n");
	exit(EXIT_SUCCESS);
}
