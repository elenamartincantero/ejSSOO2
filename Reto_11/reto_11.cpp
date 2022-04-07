#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <algorithm>
#include <functional>

#define HILOS 10

std::vector<std::thread> v_hilos;
std::mutex m;
int turno = -1;
void esperarTurno(int id){
    std::unique_lock<std::mutex> lk(m);
    while(turno != id){
        lk.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        lk.lock();
    }

}

void hilo(int id){
    esperarTurno(id);
    std::cout << "Hilo " << id << " ha ejecutado su turno" << std::endl;
}

void generarTurnos(){
    for (int i = 0; i < HILOS; i++)
    {
        turno = i;
        if(v_hilos[i].joinable()) v_hilos[i].join();
    }
    
}

void generarHilos(){
    for (int i = 0; i < HILOS; i++)
    {
        v_hilos.push_back(std::thread(hilo, i));
    }
    
}
int main(){ 
    generarHilos();
    generarTurnos();
    return 0;
}