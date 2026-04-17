/*3.2 Ingresar dos Strings, uno con el nombre y el otro con el apellido de una persona. Utilizando las funciones de
la biblioteca string.h generar un tercer string formado por: NOMBRE, APELLIDO (nombre coma espacio y
apellido) y mostrarlo*/

#include <stdio.h>
#include <string.h>

#define TAM 50

void leerTexto (char [], int);

int main (){

    char nombre[TAM];
    char apellido[TAM];
    char completo[TAM+TAM];

    printf("Ingrese nombre:");
    leerTexto(nombre, TAM);
    while (strlen(nombre)==0)
    {
        printf("El nombre no puede ser vacio. Ingrese nuevamente:");
        leerTexto(nombre, TAM);
    }
    printf("Ingrese apellido:");
    leerTexto(apellido, TAM);
    while (strlen(apellido)==0)
    {
        printf("El apellido no puede ser vacio. Ingrese nuevamente:");
        leerTexto(apellido, TAM);
    }
    strcpy(completo, nombre);
    strcat(completo, ", ");
    strcat(completo, apellido);
    puts(completo);

    return 0;
}

void leerTexto (char texto[], int largo){
    int i;
    fgets(texto, largo, stdin);
    i=0;
    while (texto[i]!='\0')
    {
        if (texto[i]=='\n')
        {
            texto[i]='\0';
        }else
        i++;
    }
    
}