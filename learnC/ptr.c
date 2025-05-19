#include <stdio.h>

int main(){
    int numero;
    int * numPtr;
    numero = 19;
    numPtr = &numero;
    printf("Numero: %u, Puntatore: %u\n",numero, numPtr);
    int ** numPtrPtr = &numPtr;
    printf("Numero: %u, Puntatore: %X, Puntatore a Puntatore: %X\n",numero, numPtr, numPtrPtr);
    int *** numPtrPtrPtr = &numPtrPtr;
    printf("Numero: %u, Puntatore: %X, Puntatore a Puntatore: %X, Puntatore a Puntatore a Puntatore: %X\n",numero, numPtr, numPtrPtr, numPtrPtrPtr);
    printf("Numero: %u, Numero *: %u, Numero **: %u, Numero***: %u\n",numero, *numPtr, **numPtrPtr, ***numPtrPtrPtr);
    
    printf("Indirizzo di numero: %X, indirizzo di numPtr: %X\n", &numero,&numPtr);
    printf("Indirizzo di numPtrPtr: %X, indirizzo di numPtrPtrPtr: %X\n", &numPtrPtr,&numPtrPtrPtr);
    *numPtr = 18;
    printf("Numero dopo modifica *: %u\n", numero);
    **numPtrPtr = 22;
    printf("Numero dopo modifica **: %u\n", numero);
    ***numPtrPtrPtr = 12;
    printf("Numero dopo modifica ***: %u\n", numero);

    //printf("Provo a stampare *&numPtr: %X\n", *&numPtr);
    //printf("Provo a stampare &*numPtr: %X\n", &*numPtr);
    printf("Stampo *&numPtr: %X, stampo &*numPtr: %X, stampo numPtr: %X, stampo &numero: %X\n",*&numPtr, &*numPtr, numPtr, &numero);
    return 0;
}