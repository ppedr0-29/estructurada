/*7.2 Realizar un programa que lea el contenido del archivo “cadenas.txt” creado en el punto anterior.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

int main(){
    FILE* arch;
    arch=fopen("cadenas.txt", "rt");
    char text[100];
    if (arch==NULL)
    {
        printf("Error al abrir el archivo");
        getch();
        exit(1);
    }
    
    fgets(text,100, arch);
    while (!feof(arch))
    {
        printf("%s", text);
        fgets(text,100, arch);
    }
    
    fclose(arch);
    return 0;
}