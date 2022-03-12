#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
int main(void){
    DIR *dir;
    char *ext;
    char *path;
    char temp [4] = "tmp";
    int result = 1;
    struct dirent *file;
    dir = opendir(".");
    while ((file = readdir(dir)) != NULL){
        path = strcpy(path, file->d_name);
        
        ext = strtok(file->d_name,".");
        ext = strtok(NULL, " ");
        if(ext){
            result = strcmp(ext, temp);
            if (result == 0){               
                remove(path);
            }
        }
        
    }
    exit(0);
}