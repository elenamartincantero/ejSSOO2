#include <iostream>
#include <thread>

class Inc{
    public:
        int x;
        Inc(int x){
            this->x = x;
        }
        void incrementar(){
            this->x++;
        }
        void operator () () {
            incrementar();
            std::cout << "Desde el hilo: "<< x << std::endl;
        }
};

int main(){
    int x = 0;
    Inc c(x);
    std::cout << "Desde el main: "<< c.x << std::endl;
    std::thread hilo(c);
    hilo.join();
    std::cout << "Desde el main: "<< c.x << std::endl;
}