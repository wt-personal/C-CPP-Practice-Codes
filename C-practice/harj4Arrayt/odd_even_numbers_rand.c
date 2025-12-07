#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 15   // Arrayn koko = kuinka monta
#define MIN_RAND (-50)  // pienin raja-arvo
#define MAX_RAND 120    // suurin raja-arvo

int main(void)
{
	printf("All numbers are:\n");
	srand(time(NULL));

	// randon numerot
	int array[ARRAY_SIZE];

	// parilliset ja parittomat
	int even[ARRAY_SIZE];
	int uneven[ARRAY_SIZE];

	// kuinka monta kpl
	int even_size = 0;
	int uneven_size = 0;

	// Arvotaan numerot
	for (int i = 0; i < ARRAY_SIZE; i++) {
		array[i] = rand() % (MAX_RAND +1 - MIN_RAND) + MIN_RAND;
		// Jos pariton sijotetaan uneven array
		if (array[i] % 2) {
			uneven[uneven_size] = array[i];
			uneven_size++;

		}
		// Muuten sijotetaan parillisiin
		else  {
			even[even_size] = array[i];
			even_size++;
		}
		printf("%3d ",array[i]);
	}

	// printataan numeroiden verran numeroita
	printf("\nOdd numbers are:\n");
	for (int i = 0; i < uneven_size; i++) {
		printf("%3d ",uneven[i]);
	}

	printf("\nEven numbers are:\n");
	for (int i = 0; i < even_size; i++) {
		printf("%3d ",even[i]);
	}

}
