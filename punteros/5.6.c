/*5.6 Cargar un vector de enteros con números aleatorios de 3 cifras máximo.
Realizar una función que retorne un puntero al mayor valor del vector
Mostrar el máximo valor mediante el puntero y la posición en la cual se encuentra*/

#include <stdio.h>
#define TAM 10

int *mayor(int *, int );
void leeyvalIntE2(int *, int , int );

int main(){
    int v[TAM];
    int *pv=v;

    for (int i = 0; i < TAM; i++)
    {
        printf("Ingrese valor para la posicion %d:", i+1);
        leeyvalIntE2(pv+i, 0, 999);
    }
    int *posmayor= mayor(pv, TAM);
    printf("El maximo valor %d, se encuentra en la posicion %d", *posmayor, (posmayor-pv)+1);
}


int *mayor(int *pv, int ce){
    int max=*pv;
    int *pr;
    for (int i = 0; i < ce; i++)
    {
        if (*(pv+i)>max)
        {
            max=*(pv+i);
            pr=pv+i;
        }
    }
    return pr;
}

void leeyvalIntE2(int *pv, int min, int max){
    scanf("%d", pv);
    while (*pv<min || *pv>max)
    {
        printf("Error. Reingrese:");
        scanf("%d", pv);
    }
}