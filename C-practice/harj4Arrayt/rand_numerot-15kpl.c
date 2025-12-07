#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 15   
#define MIN_RAND (-40)  
#define MAX_RAND 40   

int main(void)
{
	printf("An array of size 15 filled with random numbers (between -40 ... 40) is:\n");
	srand(time(NULL));

	int array[ARRAY_SIZE];

	// Random numbers in loop to fill array
	for (int i = 0; i < ARRAY_SIZE; i++) {

		array[i] = rand() % (MAX_RAND + 1 - MIN_RAND) + MIN_RAND;

		// Add space and ,
		if (i < ARRAY_SIZE-1) printf("%d, ",array[i]);
		// Last row
		else printf("%d",array[i]);
	}

}