#include <iostream>
#include <thread>
#include <chrono>

class Aleatorio{
    public:
        void operator () () {
             srand(time(NULL));
             
             for (int i = 0; i < 10; i++)
             {
                 std::cout <<  rand() << " ";
             }
             std::cout << "\n";

        }
};

int main(){
    Aleatorio a1, a2;
    std::thread hilo1 (a1);
    std::thread hilo2 (a2);

    hilo1.join();
    hilo2.join();
}