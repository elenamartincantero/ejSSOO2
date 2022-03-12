#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    pid_t hijo;
    int salida_hijo;
    int estado;

    hijo = fork();

    switch (hijo)
    {
    case -1:
        perror("Error al crear el proceso hijo\n");
        break;
    case 0:
        printf("Empieza el proceso hijo\n");
        salida_hijo = rand() % 2;
        printf("Hijo saliendo en modo: %d\n", salida_hijo);
        exit(salida_hijo);
        break;
    default:
        printf("Empieza el proceso padre\n");
        wait(&estado);
        printf("Hijo terminado\n");
        salida_hijo = WEXITSTATUS(estado);
        printf("Padre saliendo en el mismo modo que hijo: %d\n", salida_hijo);
        exit(salida_hijo);
    }
}