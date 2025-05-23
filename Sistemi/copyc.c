#include <fcntl.h>
#include "lib-misc.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#define BUFSIZE 8192

int main(int argc,  char * argv[]){
	int sd, dd, size, total=0, pos;
	char buffer[BUFSIZE];
	if(argc!=3){
		printf("usage: copy <source> <dest>");
		exit_with_sys_err("wrong args");
	}
	if((sd = open(argv[1], O_RDONLY, S_IRUSR | S_IRGRP))<0){
		exit_with_sys_err("open source");
	}else{
		pos = lseek(sd, 0, SEEK_END);
		printf("[MAIN] lettura di '%s', di %d byte\n", argv[1], pos);
		pos = lseek(sd, 0, SEEK_SET);
	}
	if((dd=open(argv[2], O_WRONLY | O_CREAT, S_IWUSR | S_IWGRP))<0){
		exit_with_sys_err("open or create destination");
	}
	printf("[MAIN] duplicazione di %d file\n",argc-2);
	do{
		if((size=read(sd, buffer, BUFSIZ))<0){
			exit_with_sys_err("open from source copy");	
		}
		total+=size;
		printf("Ho letto %d byte\n", size);
		if((write(dd, buffer, size))<0){
			exit_with_sys_err("write on destination");
		}
	}while(size==BUFSIZ);
	printf("La dimensione totale è di %d byte\n",total);
	close(sd);
	close(dd);
	exit(EXIT_SUCCESS);
}
