#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void main(){
    int fd = open("1024.txt", O_WRONLY | O_CREAT , 0644);
    int cont = 0;
    char str = 'a';
    for(int i = 0; i <1024; i++){
        write(fd, &str, 1);
    }
    close(fd);
    fd = open("1024.txt",O_RDONLY, 0644);
    char buff[1025];  // 1024 + 1 para el \0
    ssize_t bytes_leidos = read(fd, buff, 1024);
    buff[1025] = '\0';
    printf("%s",buff);
    close(fd);
    return;
}