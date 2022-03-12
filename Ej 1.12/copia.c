#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <time.h>

int main(){
    DIR *dir;
    FILE *copy_file, *original_file;
    struct dirent *file;
    struct stat stat_file;
    int cantidad;
    size_t size;
    char buffer [2048];
    char *dir_path, *file_path, *original_path;

    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char *time = asctime(tm);
    dir = opendir("./copiar");
    dir_path = malloc(sizeof(time));
    original_path = malloc(300UL);
    file_path = malloc(300UL);
    cantidad = 0;
    sprintf(dir_path, "./%s", time);
    mkdir(dir_path, 0700);
    
    while ((file = readdir(dir)) != NULL){
        
        sprintf(file_path, "%s/%s", dir_path, file->d_name);
        sprintf(original_path, "./copiar/%s", file->d_name);
        stat(original_path, &stat_file);
        if(S_ISREG(stat_file.st_mode)){
            copy_file = fopen(file_path, "w");
            original_file = fopen(original_path, "r");
            size = stat_file.st_size;
            while (cantidad < size){
                cantidad = fread(buffer,1,sizeof(buffer),original_file);
                fwrite(buffer,1, cantidad,copy_file);
            }
            fclose(original_file);
            fclose(copy_file);
        }

        
    }

}
