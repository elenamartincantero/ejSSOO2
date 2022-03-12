#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>

#define LECTURA 0
#define ESCRITURA 1

int main(){
    pid_t hijo_mayor, hijo_menor;
    int tub_mayor[2], tub_menor[2], hijos[2];
    int status;
    const char *mensaje = "la comida está lista";
    char *buffer;

    pipe(tub_mayor);
    pipe(tub_menor);
    pipe(hijos);
    char fd_mayor[10], fd_menor[10], fd_esc_hijos[10], fd_lec_hijos[10];
    sprintf(fd_mayor, "%d", tub_mayor[LECTURA]);
    sprintf(fd_menor, "%d", tub_menor[ESCRITURA]);
    sprintf(fd_esc_hijos, "%d", hijos[ESCRITURA]);
    sprintf(fd_lec_hijos, "%d", hijos[LECTURA]);
    char *argv_mayor[] = {fd_mayor, fd_esc_hijos, NULL};
    char *argv_menor[] = {fd_lec_hijos,fd_menor, NULL};
    char *envp[] = {NULL};
    buffer = malloc(300UL);
    hijo_mayor = fork();
    
    switch (hijo_mayor)
    {
    case -1:
        perror("Error al crear el hijo\n");
        exit(EXIT_FAILURE);
    case 0:
        printf("Hijo Mayor creado");
        close(tub_mayor[ESCRITURA]);
        close(tub_menor[LECTURA]);
        close(tub_menor[ESCRITURA]);
        close(hijos[LECTURA]);
        execve("./hijo_mayor", argv_mayor, envp);
    }
    hijo_menor = fork();
    switch (hijo_menor)
    {
    case -1:
        perror("Error al crear el hijo\n");
        exit(EXIT_FAILURE);
    case 0:
        printf("Hijo Menor creado");
        close(tub_menor[LECTURA]);
        close(tub_mayor[LECTURA]);
        close(tub_mayor[ESCRITURA]);
        close(hijos[ESCRITURA]);
        execve("./hijo_menor", argv_menor, envp);
    }
    close(tub_mayor[LECTURA]);
    close(tub_menor[ESCRITURA]);
    write(tub_mayor[ESCRITURA], mensaje, strlen(mensaje));
    read(tub_menor[LECTURA], buffer, 8UL);
    printf("[PADRE] Mensaje recibido por el hijo menor: %s\n", buffer);
    waitpid(hijo_menor, &status, 0);
    exit(EXIT_SUCCESS);
}