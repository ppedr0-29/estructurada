/*5.2 Definir dos números enteros y dos punteros a dichos números. Accediendo mediante los punteros sumar
ambos números y mostrar el resultado por pantalla.*/

#include <stdio.h>


int main (){
    int num1=12;
    int num2=444;
    int suma;

    int *pnum1= &num1;
    int *pnum2= &num2;

    suma = *pnum1 + *pnum2;

    printf("El resultado es: %d", suma);

    return 0;
}

