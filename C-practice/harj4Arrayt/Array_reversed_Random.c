#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 20   // Arrayn koko = kuinka monta
#define MIN_RAND 10     // pienin raja-arvo
#define MAX_RAND 140    // suurin raja-arvo

int main(void)
{
	printf("Array of numbers is:     ");
	srand(time(NULL));

	// arrayden koko
	int array[ARRAY_SIZE];
	int array_reversed[ARRAY_SIZE];

	// Arvotaan numerot
	for (int i = 0; i < ARRAY_SIZE; i++) {
		array[i] = rand() % (MAX_RAND + 1 - MIN_RAND) + MIN_RAND;
		/* sijoitetaan numerot kC$C$nteisessC$ jC$rjestyksessC$
		// esim ARRAY_SIZE-i-1 = 20-0-1 = 19 ekalla kierroksella
		// sijoitetaan viimeiseen indeksiin array[]:n eka numero jne */
		array_reversed[ARRAY_SIZE-i-1] = array[i];
		printf("%d ",array[i]);
	}

	printf("\nSame array in reverse order is: ");

	for (int i = 0; i < ARRAY_SIZE; i++) {
		printf("%d ",array_reversed[i]);
	}

	return 0;
}
