#include <stdio.h>
#include <string.h>

#define MAX_PATH 4096

void copy(char *src, char* dest){
    char path_destination[PATH_MAX];
    sprintf(path_destination, "%s/%s", dest, basename(src));
    printf("Copying...")

}


int main(int argc, char * argv[]){
    // ./main <file> ... <file> <dest> 
    if(argc <3){
        printf("Usage: %s, ./main file1 [file2] ... [filen] dest\n", argv[0])
        exit(EXIT_FAILURE);
    }

    //copy() files from argv[1] to argv[n-2] to argv[n-1]
    
    for(int i =1; i <argc-1; ++i){
        copy(argv[i], argv[argc-1]);
    }
    
    exit(EXIT_SUCCESS);

}