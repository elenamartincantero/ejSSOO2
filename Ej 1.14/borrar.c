#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

int main(int argc, char *argv[], char *envp[]){
    char *buffer;
    DIR *dir;
    struct dirent *file;
    struct stat stat_file;
    char *path;
    path = malloc(300UL);
    buffer = malloc(300UL);
    read(atoi(argv[0]), buffer, 300UL);
    dir = opendir(buffer);
    while ((file = readdir(dir)) != NULL){
        sprintf(path, "%s/%s", buffer, file->d_name);
        stat(path, &stat_file);
        if(S_ISREG(stat_file.st_mode)){
            remove(path);
        }
    }

    exit(EXIT_SUCCESS);
}