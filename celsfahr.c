#include <stdio.h>

/* print fahrenheit celsius table 
 * for fahr = 0, 20, ..., 300  */

int main(){
	int fahrenheit, cels;
	int lower, upper, step;
	
	lower = 0;
	upper = 300;
	step = 20;

	fahrenheit = lower;
	while ( fahrenheit <= upper ){
		cels = 5 * (fahrenheit-32) / 9;
		printf("%d\t%d\n", fahrenheit, cels);
		fahrenheit = fahrenheit + step;
	}
}
