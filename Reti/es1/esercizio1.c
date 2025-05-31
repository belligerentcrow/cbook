/*1. Si scriva su file di testo ```testo.txt``` quello che l'utente inserisce da tastiera 
parola per parola, finche' non inserisce la parola ```"FINE"``` (usando la ```fprintf()```)
2. Stampare a video il contenuto di un file di testo ```prova.txt``` usando ```fscanf()```
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


void scrivi(char testo[50], bool isWriting){
    do{
        printf("write...\n");
        scanf("%s", testo);
        if(!(strcmp(testo, "FINE"))){
            isWriting = 0;
            printf("FINED!!!");
        }
    }while(isWriting == true && strlen(testo)>50);
}

int selectMenu(){
    int x = 0;
    do{
    printf("Please select:\n1) print\n2) write\n3) exit\n");
    scanf("%d",&x);
    } while (x<=0 || x>=4);

    return x;
}

int main(){
    char fname[] = "./testo.txt";
    FILE * myfile;

    printf("Select Menu: \n");
    int menuchoose = selectMenu();
    while(menuchoose != 3){
        if(menuchoose == 1){
        //print
            myfile = fopen(fname, "r+");
            if (myfile==NULL){
                printf("file %s non trovato!",fname);
                exit(-1);
            }
            fseek(myfile,0,SEEK_SET);
            while(!feof(myfile)){
            char t[20];
            fscanf(myfile,"%s",t);
            printf("%s\n",t);
            }
            fclose(myfile);
        }else if(menuchoose == 2){
        //write
            myfile = fopen(fname,"a+");
            if (myfile==NULL){
                printf("file %s non trovato!",fname);
                exit(-1);
            }
            //fseek(myfile,0,SEEK_END);
            char mytesto[50];
            
            while(strcmp(mytesto,"FINE")){
                fprintf(myfile,"%s\n",mytesto);
                scrivi(mytesto,1);
            }
            fclose(myfile);
        }else{
            printf("Very well! Exiting...\n");
        }
    }
    printf("Procedure completed!\n");
    return 0;
}

