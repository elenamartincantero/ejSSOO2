#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>

#define LECTURA 0
#define ESCRITURA 1

int main(){
    int tubEliminar[2], tubCopiar[2], status;
    pid_t hijoEliminar, hijoCopiar;
    char *path_eliminar = "./eliminar";
    char *path_copiar = "./copiar";
    char *envp[] = {NULL};
    pipe(tubEliminar);
    pipe(tubCopiar);

    char fd_eliminar[100], fd_copiar[100];
    sprintf(fd_eliminar, "%d", tubEliminar[LECTURA]);
    sprintf(fd_copiar, "%d", tubCopiar[LECTURA]);
    char *argv_eliminar[] = {fd_eliminar, NULL};
    char *argv_copiar[] = {fd_copiar, NULL};
    hijoEliminar = fork();
    switch (hijoEliminar)
    {
    case -1:
        perror("Error al crear el hijo\n");
        exit(EXIT_FAILURE);
        break;
    case 0:
        printf("Hijo para eliminar archivos creado\n");
        close(tubEliminar[ESCRITURA]);
        close(tubCopiar[LECTURA]);
        close(tubCopiar[ESCRITURA]);
        execve("./borrar", argv_eliminar, envp);
        perror( "execve failed" );
        exit( EXIT_FAILURE );
        break;
    
    }

    hijoCopiar = fork();
    switch (hijoCopiar)
    {
    case -1:
        perror("Error al crear el hijo\n");
        exit(EXIT_FAILURE);
        break;
    case 0:
        printf("Hijo para copiar archivos creado\n");
        close(tubCopiar[ESCRITURA]);
        close(tubEliminar[LECTURA]);
        close(tubEliminar[ESCRITURA]);
        execve("./copia_seg", argv_copiar, envp);
        perror( "execve failed" );
        exit( EXIT_FAILURE );
        break;
    default:

        close(tubCopiar[LECTURA]);
        close(tubEliminar[LECTURA]);
        write(tubEliminar[ESCRITURA], path_eliminar, strlen(path_eliminar));
        write(tubCopiar[ESCRITURA], path_copiar, strlen(path_copiar));
        waitpid(hijoCopiar, &status, 0);
        waitpid(hijoEliminar, &status, 0);
    }
    

    exit(EXIT_SUCCESS);
}