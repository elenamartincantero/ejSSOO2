#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>


/*0-> write, 1->read*/

int main(int argc, char *argv[]){
    char bufferEntrada[100];
    char cadenaFinal[100];
    int i = 0, bytes;
    bytes = read(atoi(argv[1]),bufferEntrada,sizeof(bufferEntrada));
    while(bufferEntrada[i]){
        cadenaFinal[i] = toupper(bufferEntrada[i]);
        i++;
    }
    write(atoi(argv[0]), cadenaFinal, strlen(cadenaFinal));
    exit(EXIT_SUCCESS);
}