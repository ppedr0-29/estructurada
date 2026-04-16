/*Ejercicio 1
Ingresar dos Strings, uno con el nombre y el otro con el apellido de una persona.
Utilizando las funciones de la biblioteca string.h:
Copiar el nombre en una tercera variable.
Ingrese nuevamente el apellido en una cuarta variable y reingrese hasta asegurarse que sean iguales.
En una quinta variable unir nombre y apellido.
Generar un sexto string formado por: NOMBRE, APELLIDO (nombre coma espacio y apellido).
Muestre todas las variables cargadas.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 30

void leerTexto(char [], int);
void punto2(char [], char [], int);

int main()
{
    char nombre[TAM];
    char apellido[TAM];
    char nombre2[TAM];
    char apellido2[TAM];
    char nombreYapellido[TAM+TAM];
    char completo[TAM+TAM];

    printf("\nIngrese el nombre: ");
    leerTexto(nombre, TAM);

    printf("\nIngrese apellido: ");
    leerTexto(apellido, TAM);

    strcpy(nombre2, nombre);

    punto2(apellido2, apellido, TAM);

    strcpy(nombreYapellido, nombre);
    strcat(nombreYapellido, " ");
    strcat(nombreYapellido, apellido);

    strcpy(completo, nombre);
    strcat(completo, ", ");
    strcat(completo, apellido);

    printf("\nTodas las variables cargadas:\n");
    puts(nombre);
    puts(nombre2);
    puts(apellido);
    puts(apellido2);
    puts(nombreYapellido);
    puts(completo);

    return 0;
}

void leerTexto(char texto[], int largo)
{
    int i;
    fgets(texto, largo, stdin);
    i = 0;
    while (texto[i] != '\0')
    {
        if (texto[i] == '\n')
            texto[i] = '\0';
        else
            i++;
    }
}

void punto2(char textoN[], char textoV[], int largo)
{
    printf("\nIngrese el apellido nuevamente: ");
    leerTexto(textoN, largo);
    while (strcmpi(textoN, textoV) != 0)
    {
        printf("\nReingrese el apellido: ");
        leerTexto(textoN, largo);
    }
}