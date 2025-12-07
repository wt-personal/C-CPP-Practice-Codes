#include <stdio.h>
#include <stdlib.h>

#define EHDOISSA (vastukset <= 0 || ohm <= 0 || vastukset > 1000)

float paralres(int count, int res, char yes) {

    float sum = 0.0f;

    if (yes == 'y') {
        // same resistor value for all
        for (int i = 0; i < count; i++) {
            sum += 1.0f / res;
        }
    } else {
        // ask each resistor separately
        for (int i = 0; i < count; i++) {
            float r;
            printf("Give resistance for resistor %d: ", i + 1);
            scanf("%f", &r);
            sum += 1.0f / r;
        }
    }

    return 1.0f / sum;
}

int main() {

    int vastukset = 1, ohm = 1;
    printf("Parallel resistors counter v0:\n");

    char samavastus[4] = {0};
    printf("Do we use the same resistance values for all resistors? (y/n): ");
    scanf(" %3s", samavastus);

    do {
        printf("How many resistors are in parallel? Max 1000:\n");
        scanf("%d", &vastukset);

        if (samavastus[0] == 'y') {
            printf("All resistors same value. Enter the resistance in ohms: ");
            scanf("%d", &ohm);
        }

        if (EHDOISSA)
            printf("Values zero or below are not allowed!\n");

    } while (EHDOISSA);

    float kokonaisres = paralres(vastukset, ohm, samavastus[0]);

    if (kokonaisres > 1)
        printf("Whole resistance is %.2f Ohms\n", kokonaisres);
    else
        printf("Whole resistance is %f Ohms\n", kokonaisres);

    // Fix: clear leftover newline from scanf
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}

    printf("Press Enter to exit...");
    getchar();

    return 0;
}