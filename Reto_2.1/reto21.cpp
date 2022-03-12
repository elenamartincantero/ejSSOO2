#include <iostream>
#include <thread>

void holaEs(){
    std::cout << "Hola Mundo\n";
}
void holaEn(){
    std::cout << "Hello World\n";
}
void holaFr(){
    std::cout << "Salut Monde\n";
}
int main(){
    std::thread hEs(holaEs);
    std::thread hEn(holaEn);
    std::thread hFr(holaFr);
    hEs.join();
    hEn.join();
    hFr.join();

    return 0;
}