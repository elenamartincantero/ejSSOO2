#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


void calcFactorial(int n){
    int factorial = 1;
    for (int i = 1; i <= n; i++)
    {
        factorial *= i;
    }
    
    printf("El factorial de %d es %d\n", n, factorial);
}

int esPrimo(int numero){
    if (numero == 0 || numero == 1 || numero == 4) return 0;
    for (int x = 2; x < numero / 2; x++) {
        if (numero % x == 0) return 0;
    }
    return 1;
}

void printPrimos(int primos[], int len){
    printf("NÚMEROS PRIMOS:\n");
    if (sizeof(primos) < 1){
        printf("No hay numeros primos anteriores a n\n");
    }else{
        for (int i = 0; i < len; i++){
            printf("%d\n", primos[i]);
        }
    }
}

void numPrimos(int n){
    int len = 0;
    int pos = 0;
    for(int i = 0; i <= n; i++){
        if (esPrimo(i)){
            len++;
        }
    }
    int primos [len];
    for(int i = 0; i <= n; i++){
        if (esPrimo(i)){
            primos[pos++] = i;
        }
    }
    printPrimos(primos, len);

}


int main(int argc, char *argv[]){
    int estado;
    if (argc != 2){
        printf("Debe introducir un número\n");
        return EXIT_FAILURE;
    }
    long n = strtol(argv[1], NULL, 10);
    int n_int = n;
    pid_t hijo1 = 0, hijo2 = 0;
    hijo1 = fork();
    if (hijo1 == 0){
        printf("HIJO 1\n");
        calcFactorial(n_int);
    }else{
        hijo2 = fork();
        if (hijo2 == 0)
        {
            printf("HIJO 2\n");
            numPrimos(n_int);

        }else{
            printf("Esperando a los hijos\n");
            waitpid(hijo1, &estado, 0);
            printf("Hijo 1 finalizado\n");
            waitpid(hijo2, &estado, 0);
            printf("Hijo 2 finalizado\n");
            printf("Finalizando la ejecución\n");

        }
    }
    return 0;
}



