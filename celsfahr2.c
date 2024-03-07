#include <stdio.h>
/* print Fahrenheit-Celsius table 
 * for fahr = 0, 20, ... 300;
 * floating-point version */

int main(){
    float fahrenheit, cels;
    int low, up, stepp;
    
    low = 0;
    up = 300;
    stepp = 20;

    fahrenheit = low;
    printf("Fahrenheit:\tCelsius:\n");
    printf("-------------------------\n");
    while (fahrenheit <= up) {
	cels = (5.0 / 9.0) * (fahrenheit - 32.0);
	printf("%3.2f\t\t %6.3f \n", fahrenheit, cels);
	fahrenheit = fahrenheit + stepp;
    }
    return 0;
}
