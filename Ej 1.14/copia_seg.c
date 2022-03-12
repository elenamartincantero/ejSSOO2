#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

int main(int argc, char *argv[], char *envp[])
{
    DIR *dir;
    FILE *copy_file, *original_file;
    struct dirent *file;
    struct stat stat_file;
    int cantidad;
    int leido;
    size_t size;
    char *buffer_tub;
    char *buffer[100];
    char *dir_path = "./copia_seguridad";
    char *file_path, *original_path;
    buffer_tub = malloc(300UL);
    //buffer = malloc(1000UL);
    read(atoi(argv[0]),buffer_tub,sizeof(buffer_tub));
    dir = opendir(buffer_tub);
    original_path = malloc(300UL);
    file_path = malloc(300UL);
    mkdir(dir_path, 0700);
    while((file = readdir(dir)) != NULL){
        memset(buffer, 0, 2048);
        cantidad = 0;
        sprintf(file_path, "%s/%s", dir_path, file->d_name);
        sprintf(original_path, "./copiar/%s", file->d_name);
        stat(original_path, &stat_file);
        if(S_ISREG(stat_file.st_mode)){
            copy_file = fopen(file_path, "w");
            original_file = fopen(original_path, "r");
            size = stat_file.st_size;
            while (cantidad < size){
                leido = fread(buffer,1,size,original_file);
                cantidad += leido;
            }
            
            fwrite(buffer,1, cantidad,copy_file);
            fclose(original_file);
            fclose(copy_file);
        }
    }

    exit(EXIT_SUCCESS);
}