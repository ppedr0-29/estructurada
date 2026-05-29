/*Dada la estructura alumno:
struct alumno
{
char nom[31];
int dni;
};
Realizar un programa que permita cargar alumnos y mostrarlos. Como máximo permitir 50 alumnos. 
El ingreso finaliza con un DNI igual a 0. Realizar una función para cargar y otra para mostrar 
usando notación de punteros*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 50

typedef struct 
{
    char nom[31];
    int dni;
}alu;

int ingreso(alu *pAlu, int);
alu cargarVec();
int leeyValidaEntre2(int , int , int );
void leerTexto (char [], int );
void validarVacio(char [], int );
void mostrarAlu(alu *pAlu, int);

int main(){
    alu alumnos[TAM];
    alu *pAlu = alumnos;
    printf("INGRESO DE ALUMNOS\n");
    int cantAlu = ingreso(pAlu, TAM);
    mostrarAlu(pAlu, cantAlu);
    return 0;
}

int ingreso(alu *ptr, int ce){
    int i=0;
    alu aux;
    aux=cargarVec();
    while(i<ce && aux.dni!=0){
        ptr[i]=aux;
        aux=cargarVec();
        i++;
    }
    return i;
}

alu cargarVec(){
    alu aux;
    printf("Ingrese el dni: ");
    aux.dni=leeyValidaEntre2(10000000,99999999, 0);
    if (aux.dni!=0){
        printf("Ingrese el nombre: ");
        leerTexto(aux.nom, 31);
        validarVacio(aux.nom, 31);
    }
    return aux;
}

void mostrarAlu(alu *ptr, int cantAlu){
    for (int i = 0; i < cantAlu; i++)
    {
        printf("DNI del alumno %d - %d y su nombre es %s\n", i+1, (ptr+i)->dni, (ptr+i)->nom);
    }
}

int leeyValidaEntre2(int min, int max, int cf){
    int dato;
    scanf("%d", &dato);
    while((dato<min || dato > max) && dato!=cf){
        printf("Error- REINGRESE:");
        scanf("%d", &dato);
    }
    return dato;
}
void leerTexto (char texto[], int largo){
    int i;
    fflush(stdin);
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
void validarVacio(char texto[], int largo){
    while(strlen(texto)==0){
        printf("El texto no puede ser vacio. Reingrese:");
        leerTexto(texto, largo);
    }
}