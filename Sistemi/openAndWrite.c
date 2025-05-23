#include "lib-misc.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define FILENAME "test.txt"

int main(void) {
    int fd;
    char buffer1[] = "nel mezzo del cammin di nostra vita mi ritrovai per una selva oscura che la diritta via era smarrita ahi quant'a dir cos'era e' cosa dura esta selva selvaggia et aspra e forte";
    char buffer2[] = "AAAAAAAAAAAAAAAAAAAAAAAAAAAA";
    
    if((fd=open(FILENAME, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH))<0){
        exit_with_sys_err("open");
    }
    
    if(write(fd, buffer1, sizeof(buffer1)-1)!=sizeof(buffer1)-1){
        exit_with_sys_err("first write");
    }

    if(lseek(fd,10,SEEK_SET)==-1){
        exit_with_sys_err("lseek");
    }
    
    if(write(fd, buffer2,sizeof(buffer2)-1)!=sizeof(buffer2)-1){
        exit_with_sys_err("second write");
    }

    for(int i =0; i<51; ++i){
        char buffer3[sizeof("xx - hey!\n")] = "";
        if(i<10){
            sprintf(buffer3,"%d - hey! \n",i);
        }else{
            sprintf(buffer3, "%d - hey!\n",i);
        }

        if(write(fd, buffer3,sizeof(buffer3)-1)!=sizeof(buffer3)-1){
            exit_with_sys_err("second write");
        }
    }
    close(fd);
    printf("all's right with the world\n"); 
    exit(EXIT_SUCCESS);
}
