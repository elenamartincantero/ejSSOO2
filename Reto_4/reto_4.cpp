#include <iostream>
#include <thread>

void loop(){
    for (int i = 0; i < 1000000000; i++)
    {
    }
    std::cout << "Fin del bucle\n";
}

int main(){
    std::thread hilo(loop);

    //hilo.join();
    hilo.detach();
    std::cout << "Fin del main\n";
}