#include <fcntl.h>
#include "lib-misc.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#define BUFSIZE 8192

int main(int argc,  char * argv[]){
	int sd, dd, size;
	char buffer[BUFSIZE];
	if(argc!=3){
		printf("usage: copy <source> <dest>");
		exit_with_sys_err("wrong args");
	}
	
	if((sd = open(argv[1], O_RDONLY))<0){
		exit_with_sys_err("open source");
	}
	if((dd=open(argv[2], O_WRONLY | O_CREAT))<0){
		exit_with_sys_err("open or create destination");
	}
	
	do{
		if((size=read(sd, buffer, BUFSIZ))<0){
			exit_with_sys_err("open from source copy");	
		}
		if((write(dd, buffer, size))<0){
			exit_with_sys_err("write on destination");
		}

	}while(size==BUFSIZ);

	close(sd);
	close(dd);
	exit(EXIT_SUCCESS);
}
