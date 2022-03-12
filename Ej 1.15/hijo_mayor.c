#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#define LECTURA 0
#define ESCRITURA 1
 /*0-> lectura 1-> escritura*/
int main(int argc, char *argv[], char *envp[])
{
    char *buffer;
    buffer = malloc(300UL);
    read(atoi(argv[LECTURA]), buffer, 300UL);
    printf("[HIJO MAYOR] Mensaje recibido por el padre: %s\n", buffer);
    write(atoi(argv[ESCRITURA]), buffer, strlen(buffer));
    exit(EXIT_SUCCESS);
}