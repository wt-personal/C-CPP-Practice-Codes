#include <stdio.h>

#define a 30 

int main() {
    char array[a] = "This is a string\n";
    char arr2[a] = {0};

    printf("%s", array);

    int size = sizeof(array) / sizeof(array[0]);

    for (int i = 0; i < size; i++) {

        char c = array[i];

        if (c >= 'A' && c <= 'Z') {
            arr2[i] = ((c - 'A' + 13) % 26) + 'A';
        }
        else if (c >= 'a' && c <= 'z') {
            arr2[i] = ((c - 'a' + 13) % 26) + 'a';
        }
        else {
            arr2[i] = c;  // copy unchanged (space, punctuation, newline)
        }
    }

    printf("%s\n", arr2);
}
