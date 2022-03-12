#include <iostream>
#include <thread>

void hola(){
    std::cout << "Hola Mundo" << std::endl;
}
int main(){
    std::thread h1(hola);
    h1.join();

    return 0;
}