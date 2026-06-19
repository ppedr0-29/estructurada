/*7.5 Se dispone del archivo “sepadaroresVarios.txt” cuyas cadenas se encuentran separadas por punto, espacios
o comas. Realizar un programa para obtener e imprimir por pantalla cada cadena.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

int main(){
    FILE* arch;
    char c;
    char cadena[100];
    int i = 0;
    cadena[0] = '\0';
    arch=fopen("separadosVarios.txt", "rt");
    if (arch==NULL)
    {
        printf("Error.");
        getch();
        exit(1);
    }
    c=fgetc(arch);
    while (!feof(arch))
    {
        while (!feof(arch) && c!=',' && c!=' ' && c!='.')
        {
            cadena[i] = c;
            i++;
            c = fgetc(arch);
        }
        cadena[i] = '\0';
        printf("%s\n", cadena);
        i = 0;
        cadena[0] = '\0';
        c = fgetc(arch); 
    }
    
}