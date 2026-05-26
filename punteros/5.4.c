/*5.4 Hacer un programa que cargue un vector de 10 enteros y lo muestre usando una función para cargar y otra
mostrar sin utilizar subíndices.*/

#include <stdio.h>
#define TAM 10

void ingreso(int *, int );
void mostrar(int *, int );

int main(){
    int v[TAM];
    int *pv=v;
    ingreso( pv, TAM);
    mostrar( pv, TAM);
}

void ingreso(int *pv, int ce){
    for (int i = 0; i < ce; i++)
    {
        printf("Ingrese valor para la posicion %d:", i+1);
        scanf("%d", (pv+i));
    }
}

void mostrar(int *pv, int ce){
    for (int i = 0; i < ce; i++)
    {
        printf("El valor de la posicion %d es: %d\n", i+1, *(pv+i));
    }
}