/*5.5 Al programa anterior agregarle una función que reciba la dirección de inicio del vector y un número a buscar
y retorne un puntero al dato encontrado o NULL sino lo encuentra. En el main agregar un proceso de
búsqueda que se repita hasta ingresar un número negativo o cero a buscar. Si se lo encontró se debe
indicar en que posición del vector estaba (calcular dicha posición utilizando la dirección retornada)*/

#include <stdio.h>
#define TAM 10

void ingreso(int *, int );
void mostrar(int *, int );
int *busqueda(int *, int , int );

int main(){
    int v[TAM];
    int *pv=v;
    int numBusqueda, pos;
    ingreso( pv, TAM);
    mostrar( pv, TAM);
    printf("Ingrese el numero a buscar:");
    scanf("%d", &numBusqueda);
    int *resultado;
    while (numBusqueda>0)
    {   
        resultado=busqueda(pv, TAM, numBusqueda);
        if (resultado==NULL)
        {
            printf("No se encontro. Reingrese:");
        }else{
            pos=(resultado-pv);
            printf("El numero estaba en la posicion %d.", pos+1);
            printf("Ingrese otro numero a buscar:");
        }
        scanf("%d", &numBusqueda);
    }
    printf("El programa finalizo.");
    return 0;
}

int *busqueda(int *pv, int ce, int num){
    int i=0, pos=-1, *pr=NULL;
    while (pos==-1 && i<ce )
    {
        if (*(pv+i)==num)
        {
            pos=i;
            pr=pv+pos;
        }else{
            i++;
        }
    }
    return pr;
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