#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[]){
    if (argc < 2){
        printf("ERROR. Se debe incluir la ruta al fichero");
        return -1;
    }
    char *ruta = argv[1];
    FILE *fd;
    fd = fopen(ruta, "r");
    if (fd != NULL){
        printf("El archivo %s existe\n", ruta);
        return 0;
    }else{
        printf("El archivo %s no existe\n", ruta);
        return -1;
    }
    return 0;
}