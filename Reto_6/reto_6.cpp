#include <iostream>
#include <thread>
#include <ctime>
#include <vector>
#include <algorithm>
#include <functional>

int glob_suma = 0;
int limite = 100;
int num_hilos = 6;
std::vector<int> glob_numeros;
std::vector<std::thread> glob_hilos;

void sumar(int pos_inicio, int pos_final){
    int suma = 0;
    int i = pos_inicio;
    while(i < pos_final){
        suma += glob_numeros.at(i++);
    }
    glob_suma += suma;
}

void generar_numeros(){
    for (int i = 0; i < limite; i++)
    {
        glob_numeros.push_back(rand());
    }
    
}

int suma_manual(){
    int suma = 0;
    for (int i = 0; i < limite; i++)
    {
        suma += glob_numeros.at(i);
    }
    return suma;
}

void generar_hilos(){
    int trozos = limite / num_hilos;
    int i, inicio, fin;
    for(i = 0; i < num_hilos-1; i++){
        glob_hilos.push_back(std::thread(sumar, i*trozos, (i+1)*trozos));
    }

    glob_hilos.push_back(std::thread(sumar, i*trozos, limite));
}

void esperar_hilos(){
    std::for_each(glob_hilos.begin(), glob_hilos.end(), std::mem_fn(&std::thread::join));
}

void pedir_numeros(){
    std::cout << "Introduzca el número de hilos que desea ejecutar: ";
    std::cin >> num_hilos;
    std::cout << "Número de hilos: " << num_hilos << std::endl;
    std::cout << "Introduzca el tamaño del vector: ";
    std::cin >> limite;
    std::cout << "Tamaño del vector: " << limite << std::endl;

}
int main(){
    std::cout << "Número de hilos que se pueden ejecutar de manera simultánea: "<< std::thread::hardware_concurrency << std::endl;
    pedir_numeros();
    generar_numeros();
    int suma = suma_manual();
    std::cout << "Suma manual = " << suma << std::endl;
    unsigned t0, t1;
    t0 = clock();
    generar_hilos();
    esperar_hilos();
    t1 = clock();
    std::cout << "Suma con hilos = " << glob_suma << std::endl;
    std::cout << "Tiempo que tarda la ejecución: " << double(t1-t0)/CLOCKS_PER_SEC << std::endl;
}