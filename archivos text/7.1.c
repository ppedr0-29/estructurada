/*7.1 Realizar un programa que genere el archivo “cadenas.txt” que guarde cadenas de caracteres que se ingresan
por teclado hasta ingresar la cadena “FINALIZAR”*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void leerTexto(char [], int );

int main(){
    FILE* arch;
    char aux[100];
    arch=fopen("cadenas.txt", "wt");
    if (arch==NULL)
    {   
        printf("Error al abrir el archivo");
        exit(1);
    }
    printf("Ingrese una cadena de texto(FINALIZAR para terminar):");
    leerTexto(aux,100);
    while (strcmpi(aux, "FINALIZAR")!=0)
    {
        //fputs(aux, arch);
        fprintf(arch, "%s\n", aux);
        printf("Ingrese una cadena de texto(FINALIZAR para terminar):");
        leerTexto(aux,100);
    }
    
    fclose(arch);

    return 0;
}

void leerTexto(char texto[], int largo){
    fflush(stdin);
    fgets(texto, largo, stdin);
    int i=0;
    while (texto[i]!='\0')
    {
        if (texto[i]=='\n')
        {
            texto[i]='\0';
        }else{
            i++;
        }   
    }
}