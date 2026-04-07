#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void main() {
    // 1. Abrir (o crear) el archivo para escritura
    // O_WRONLY: Solo escritura
    // O_CREAT: Crear si no existe
    // O_TRUNC: Si existe, borrar su contenido previo
    // 0644: permisos -rw-r--r-- (dueño puede leer/escribir, otros solo leer)
    int fd = open("salida.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    
    if (fd == -1) {
        perror("Error al abrir el archivo");
        exit(1);
    }
    
    printf("Archivo abierto con FD = %d\n", fd);
    
    // 2. Preparar los datos a escribir
    char *mensaje = "Hola, archivo!\n";
    size_t longitud = strlen(mensaje);
    
    // 3. Escribir usando el FD
    ssize_t bytes_escritos = write(fd, mensaje, longitud);
    
    if (bytes_escritos == -1) {
        perror("Error al escribir");
        close(fd);
        exit(1);
    }
    
    printf("Se escribieron %ld bytes\n", bytes_escritos);
    
    // 4. Cerrar el archivo
    close(fd);
    printf("Archivo cerrado.\n");
    
    return;
}