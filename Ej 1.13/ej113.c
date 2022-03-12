#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define LECTURA 0
#define ESCRITURA 1

int main(){
    pid_t hijo;
    char cadenaEntrada[100];
    char bufferEntradaPadre[100];
    char wrTub[256];
    char rdTub[256];
    int tubEscPadre[2], tubEscHijo[2];

    printf("Introduzca una cadena: ");
    scanf("%s", cadenaEntrada);
    pipe(tubEscPadre);
    pipe(tubEscHijo);

    sprintf(wrTub,"%d",tubEscHijo[ESCRITURA]);
    sprintf(rdTub, "%d", tubEscPadre[LECTURA]);
    hijo = fork();
    switch (hijo)
    {
    case -1:
        perror("Error al crear el hijo");
        exit(EXIT_FAILURE);
        break;
    case 0:
        printf("Hijo creado\n");
        close(tubEscHijo[LECTURA]);
        close(tubEscPadre[ESCRITURA]);
        execl("./hijo", wrTub, rdTub, NULL);
        printf("Ha ocurrido un error");
        break;
    
    }
    close(tubEscHijo[ESCRITURA]);
    close(tubEscPadre[LECTURA]);
    write(tubEscPadre[ESCRITURA], cadenaEntrada, strlen(cadenaEntrada)+1);
    read(tubEscHijo[LECTURA], bufferEntradaPadre, sizeof(bufferEntradaPadre));
    printf("Cadena recibida por el hijo: %s\n", bufferEntradaPadre);
    exit(EXIT_SUCCESS);

}