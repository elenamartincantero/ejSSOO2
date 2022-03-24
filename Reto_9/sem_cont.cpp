#include <iostream>
#include <mutex>
#include <thread>
#include <atomic>

class sem_cont
{
private:
    std::atomic<int> value;
    std::mutex sem_mutex;
public:
    sem_cont(int var){
        this->value = var;
    }
    void wait(){
        --this->value;
        if(value < 1){
            sem_mutex.lock();
        }
    }
    void signal(){
        ++this->value;
        if (value < 0){
            sem_mutex.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    }
};

