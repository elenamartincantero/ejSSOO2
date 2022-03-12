#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void){
    pid_t hijo;

    hijo = fork();
    if (hijo == -1){
        perror("Error al crear el proceso hijo");
    }else if (hijo == 0){
        char *arg_list [] = {NULL};
        char *envp [] = {NULL};
        execve("./copia", arg_list, envp);
    }
}