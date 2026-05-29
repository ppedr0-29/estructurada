/*5.9 Desarrolle un programa que solicite el ingreso de un numero entero, que indica a su vez cuantos números
enteros ingresara el usuario. Crear en memoria dinámica el vector para almacenar el tamaño exacto de los
datos y leer los enteros que serán guardados en el vector “dinámico”. Informar el promedio de los datos
ingresados.*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (){
    int *vecInt, cantInt;
    int suma=0;

    printf("Ingrese la cantidad de numeros a ingresar:");
    scanf("%d", &cantInt);

    vecInt=(int*)(malloc(cantInt*sizeof(int)));

    if(vecInt==NULL){
        printf("Error al reservar memoria...");
        exit(1);
    }

    for (int i = 0; i < cantInt; i++)
    {
        printf("Ingrese valor para la posicion %d:", i+1);
        scanf("%d", vecInt+i);
        suma+=*(vecInt+i);
    }
    
    float promedio=(float)suma/cantInt;
    printf("El promedio es %.2f", promedio);
    
    free(vecInt);
    vecInt=NULL;

    return 0;
}

