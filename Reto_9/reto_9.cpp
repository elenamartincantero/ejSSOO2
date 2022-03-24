#include <iostream>
#include <thread>
#include "sem_cont.cpp"
#include <vector>
#include <chrono>
#include <algorithm>
#include <functional>

sem_cont sem (3);

void seccion_critica(int id){
    while(1){
        sem.wait();
        std::cout << id << "\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));
        sem.signal();
    }
}
int main(){
    std::vector<std::thread> hilos;
    for(int i = 0; i < 10; i++){
        hilos.push_back(std::thread(seccion_critica, i));
    }
    std::for_each(hilos.begin(), hilos.end(), std::mem_fn(&std::thread::join));
    
}