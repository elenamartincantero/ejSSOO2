#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <algorithm>
#include <queue>

#define CYAN     "\033[36m"
#define RED     "\033[31m"
#define RESET   "\033[0m"

#define PRODUCTORES 3
#define CONSUMIDORES 3

std::mutex sem_prod;
std::unique_lock<std::mutex> ul_prod (sem_prod);
std::condition_variable cv_prod;

std::mutex sem_cons;
std::unique_lock<std::mutex> ul_cons (sem_cons);
std::condition_variable cv_cons;

std::queue<int> buffer;

std::mutex sem_buffer;

void productor(){
    while(1){
        cv_prod.wait(ul_prod, []{return buffer.size() < PRODUCTORES;});
        int num = rand()%50;
        sem_buffer.lock();
        buffer.push(num);
        std::cout << CYAN << "Productor produce "<< num << RESET << std::endl;
        sem_buffer.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        cv_cons.notify_one();
    }
    
}

void consumidor(){
    while(1){
        cv_cons.wait(ul_cons, []{return !buffer.empty();});
        sem_buffer.lock();
        int elemento = buffer.front();
        buffer.pop();
        std::cout << RED << "Consumidor consume "<< elemento << RESET << std::endl;
        sem_buffer.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        cv_prod.notify_one();
    }
    
}

int main(){
    
    std::vector<std::thread> productores;
    std::vector<std::thread> consumidores;
    for (int i = 0; i < PRODUCTORES; i++)
    {
        productores.push_back(std::thread(productor));
    }
    cv_prod.notify_all();
    for (int i = 0; i < CONSUMIDORES; i++)
    {
        consumidores.push_back(std::thread(consumidor));
    }
    
    std::for_each(productores.begin(), productores.end(), std::mem_fn(&std::thread::join));
    std::for_each(consumidores.begin(), consumidores.end(), std::mem_fn(&std::thread::join));
    
}