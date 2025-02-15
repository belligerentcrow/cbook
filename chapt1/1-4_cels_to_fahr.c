#include <stdio.h>

main (){
    float fahr, celsius;
    int lower, upper;
    float step;

    lower = 0;
    upper = 50;
    step = 0.5;

    celsius = lower;
    printf("Celsius \t Fahrenheit\n");
    while(celsius <= upper){
        fahr = celsius * (9.0/5.0) +32;
        printf("%3.1f %6.1f\n", celsius, fahr);
        celsius = celsius + step;
    }
}