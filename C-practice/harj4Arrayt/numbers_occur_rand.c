#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 1000 // Arrayn koko = kuinka monta
#define MIN_RAND 0      // pienin raja-arvo
#define MAX_RAND 10     // suurin raja-arvo

int main(void)
{
	printf("Number occurrence:\n");
	srand(time(NULL));

	// Arrayden koot
	int array[ARRAY_SIZE];
	int timescount[ARRAY_SIZE]= {0};

	// Arvotaan numerot
	for (int i = 0; i < ARRAY_SIZE; i++) {
		array[i] = rand() % (MAX_RAND + 1 - MIN_RAND) + MIN_RAND;

	}

	// tarkistetaan numerot 0-10 (eli 11 eri numeroa)
	for (int x = 0; x <= MAX_RAND; x++) {

		// Tarkistetaan arrayn koon mukaan jokainen numero
		for (int i = 0; i < ARRAY_SIZE; i++) {

			// arrayn indeksi = x niin  +1 laskuri-arrayhyn
			if(x == array[i]) timescount[x]++;

		}
		printf("number %2d occurred %3d times\n",x,timescount[x]);
	}

}
