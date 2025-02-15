#include <stdio.h>

main (){
    int fahr, celsius; //variables for the temperatures
    int lower, step, upper; 

    lower = 0; //starting point
    upper = 300; //ending point
    step = 20; //how much is added each step

    fahr = lower; //we start the fahr counting with 0
    while(fahr<=upper){   //while the fahr temperature is not yet 300;
        celsius = 5* (fahr - 32) / 9;  //cels to fahr conversion formula
        printf("%3d %6d\n", fahr, celsius); // print fahr then cels
        fahr = fahr + step; //add the step to fahr temperature
    }
}