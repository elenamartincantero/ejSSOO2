#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <algorithm>
#include <functional>

#define FILOSOFOS 5

std::array <std::mutex, FILOSOFOS> palillos;
std::mutex sem_imprimir;

void accion_filosofo(int i){
    while (1)
    {
        sem_imprimir.lock();
        std::cout << "Filósofo " << i << " pensando\n";
        sem_imprimir.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(2));

        palillos[i].lock();
        palillos[(i+1)%FILOSOFOS].lock();

        sem_imprimir.lock();
        std::cout << "Filósofo " << i << " comiendo\n";
        sem_imprimir.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(2));

        palillos[i].unlock();
        palillos[(i+1)%FILOSOFOS].unlock();

    
    }
    
}

int main(){

    std::vector <std::thread> vhilos;
    for(int i = 0; i < FILOSOFOS; i++){
        vhilos.push_back(std::thread(accion_filosofo, i));
    }
    std::for_each(vhilos.begin(), vhilos.end(), std::mem_fn(&std::thread::join));
}