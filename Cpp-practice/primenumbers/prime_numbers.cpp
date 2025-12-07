#include <iostream>

using namespace std;

int prime(int a){
    for(int i = 2; i < a; i++){

        if (a % i == 0) return -1;
    }
    return a;
}

int main(){

    int nro = 2;
    
    cout << "Mihin lukuun asti tulostetaan alkulukuja?:\n";
    do{
        cin >> nro;
        if (nro < 2) cout << "Ei ole sopiva luku! Anna luku 2 tai isompi. \n";
    } while (nro < 2);

    cout << "Alkuluvut numeroon " << nro << " asti:\n";
    
    for(int i = 2; i <= nro; i++){
        if (prime(i) > 0) cout << prime(i) << endl;
    }
}