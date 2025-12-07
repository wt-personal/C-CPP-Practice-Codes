#include <iostream>

using namespace std;

int main()
{
    string moi[4] = {"Pekka","Erkki","Helga",""};
    
    cout << "Anna nimi: \n";
    
    cin >> moi[3];
    
    for (int i = 0; i < 4; i++)
    {
        cout << (i?"":"nimet ovat:\n") << moi[i] << endl;
    }
    
    return 0;
}