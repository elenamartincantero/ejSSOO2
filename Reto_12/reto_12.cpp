#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <condition_variable>

#define HILOS 10

std::vector<std::thread> v_hilos;

int turno = -1;
std::condition_variable cv;

void hilo(int id){
    std::mutex semaforo;
    std::unique_lock<std::mutex> ul (semaforo);
    cv.wait(ul, [id]{return turno == id;});
    std::cout << "Hilo " << id << " ha ejecutado su turno" << std::endl;
    ul.unlock();
}

void generarTurnos(){
    for (int i = 0; i < HILOS; i++)
    {
        turno = i;
        cv.notify_all();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
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