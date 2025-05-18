#include <fcntl.h>  //file-control methods and options (open, O_RDONLY, O_WRONLY)
#include <libgen.h>  //contains the method 'basename()', to extract the filename from a path
#include <limits.h> //PATH_MAX, which defines the maximum length of a file path
#include <stdio.h> // IO operations (perror(), printf(), and i suppose sprintf()) 
#include <stdlib.h> //methods such as exit(), malloc(), calloc()
#include <unistd.h> //POSIX API (the read(), write(), close() methods)
#define MODE 0600   //this is a file-permission code: owner can RW, others cannot
#define BUFFER_SIZE 2048 // buffersize for Reading data during copy. the chunk

char *create_dest_path(char *source, char *dest){
  char *path = calloc(PATH_MAX, sizeof(char)); //malloc(sizeof(char)*PATH_MAX), allocates memory for the dest path
  sprintf(path, "%s/%s", dest, basename(source)); //creates the full path by concat dest and the filename of source, through basename()
  return path;
}

void copy(char *source, char *dest){
  int sd, dd, size;
  char buffer[BUFFER_SIZE]; //creating a buffer

  //source is opened in a readonly mode
  if((sd = open(source, O_RDONLY))== -1){ //sd = the open source
      perror(source); //error handling if opening source fails
      exit(EXIT_FAILURE);
  }
  char *path = create_dest_path(source, dest); // creating destination path with the method above, by allocating memory and creatingpath

  //destination is opened in a write-only mode, creates it if it doesnt exist. dd = the open-destination
  if((dd=open(path, O_WRONLY | O_CREAT | O_TRUNC, MODE)) == -1){
    perror(path); //error handling if opening destination fails
    exit(EXIT_FAILURE);
  }

  //actual copying is done here, reading from source, putting in buffer, writing in destination
  do{
    if((size = read(sd,buffer,BUFFER_SIZE)) = -1){ //creates the chunk. sd=source
      perror("read"); //if error on read 
      exit(EXIT_FAILURE);
    }
    //writes the chunk in destination. dd = destination
    if(write(dd,buffer,size)==-1){
      perror("write"); //if error on write
      exit(EXIT_FAILURE);
    }
  } while (size == BUFFER_SIZE); //continue until the entire file has been read
  free(path); //free the allocated memory for the dest path string, which was on the heap. the memory allocated to path is just a pointer. 
}

int main(int argc, char **argv){
  if(argc <3){
    printf("Usage: %s <file-1> [file-2] ... [file-n] <dest-dir>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  //copy each file in arguments except the last one which will be destination
  for(int i = 1; i <argc -1; i++){
    copy(argv[i], argv[argc-1]);
  }
  exit(EXIT_SUCCESS);
}
