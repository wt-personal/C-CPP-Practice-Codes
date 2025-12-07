#include <iostream>

#define MAX 5

void sorttaa(int array[]) {
    
    for (int i = 0; i < MAX - 1; i++) {
        for (int j = 0; j < MAX - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int array[MAX] = {0};
    
    for (int i = 0; i < MAX; i++){
        std::cout << "Anna luku " << (i+1) << " :";
        
        std::cin >> array[i];
    }

    // printti
    std::cout << "Luvut olivat reversed:\n";
    for (int i = MAX; 0 < i; i--){
        std::cout << array[i-1];
    }
    
    sorttaa(array);
    
    std::cout << "\nJärjestetty:\n";
    for (int i = 0; i < MAX; i++){
        std::cout << array[i];
    }

    return 0;
}