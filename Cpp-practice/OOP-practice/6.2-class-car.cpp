#include <iostream>

class Car{
    private:
        int year;
        std::string model;
        int hp;
    public:
        Car(int y, std::string m, int h){
            year = y;
            model = m;
            hp = h;
        }
        
        void showCar(){
            std::cout << "Year: " << year << " Model: "
            << model << " Horsepower: " << hp << "\n";
        }
};

int main()
{
    Car Ford(1992,"Escort",67);
    
    Ford.showCar();

    return 0;
}