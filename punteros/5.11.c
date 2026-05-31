/*5.11 Se debe realizar un programa para ingresar los DNI de los asistentes a un evento. Se cargan todos los DNI
hasta que se recibe un DNI igual 0. Al finalizar mostrar el listado de todos los DNI ingresados. Los datos
deben almacenarse en un vector en memoria dinámica al no saber la cantidad comenzar con un vector de 5
elementos y si es necesario y el vector se llena ir aumentando la capacidad del vector de 5 en 5.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 5

void mostrar_DNI(int *, int );
int leeyValidaE2CF(int , int , int );

int main (){
    int *vDNI, cant=TAM;

    vDNI=(int*)malloc(cant*sizeof(int));
    
    if(vDNI==NULL){
        printf("Error al reservar memoria...");
        exit(1);
    }

    int i=0, aux;
    printf("Ingrese DNI(0 para finalizar):");
    aux=leeyValidaE2CF(1000000,99999999,0);
        while (aux!=0)
        {
            vDNI[i]=aux;
            i++;
            if (i==cant)
            {
                cant+=TAM;
                printf("Ampliando capacidad a %d DNI...\n", cant);
                vDNI=(int*)realloc(vDNI, cant*sizeof(int));
                if(vDNI==NULL){
                printf("Error al reservar memoria...");
                exit(1);
                }
            }
            printf("Ingrese DNI(0 para finalizar):");
            aux=leeyValidaE2CF(1000000,99999999,0);
        }

    mostrar_DNI(vDNI, i);

        
        
        free(vDNI);
        vDNI=NULL;
}



int leeyValidaE2CF(int min, int max, int cf){
    int dato;
    scanf("%d", &dato);
    while((dato<min || dato > max) && dato!=cf){
        printf("Error- Reingrese:");
        scanf("%d", &dato);
    }
    return dato;
}

void mostrar_DNI(int *vDNI, int ce){
    printf("--DNIS DEL EVENTO--\n");
    for (int i = 0; i < ce; i++)
    {
        printf("El DNI del ingresado %d es %d\n", i+1, *(vDNI+i));
    }
}
