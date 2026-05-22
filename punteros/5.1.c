/*5.1 Crear una variable entera y un puntero a dicha variable
Asignar el valor 10 a la variable mediante el puntero
Mostrar:
a) la dirección de la variable
b) la dirección del puntero
c) el contenido de la variable
d) el contenido de la variable accediendo mediante el puntero
e) el contenido del puntero*/

#include <stdio.h>
#include <stdlib.h>

int main(){
    int entero=10, *ptr;
    
    ptr = &entero;

    printf("Direccion de la variable: %p\n", ptr);
    printf("Direccion del puntero: %p\n", &ptr);
    printf("Contenido de la variable: %d\n", entero);
    printf("Contenido de la variable por puntero: %d\n", *ptr);
    printf("Contenido del puntero: %p\n", ptr);

    return 0;
}