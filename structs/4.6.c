/*4.6 La fórmula 1 está compuesta por 20 pilotos y en el año se corrieron 23 carreras.
a) Se desea ingresar la información de cada piloto (nombre, escudería) y la posición en la que llegó dicho
piloto en cada una de las 23 carreras (1 a 20).
b) Luego se debe poder elegir el número de carrera del año y mostrar el listado de los 10 primeros puestos
de dicha carrera. Repetir el proceso con distintos números de carreras hasta ingresar un 0 como número
de carrera.*/

#include <stdio.h>
#include <string.h>
#define CANT_PILOTOS 20
#define CANT_CARRERAS 23
#define TAM 30
typedef struct
{
    char nombre[TAM];
    char escuderia[TAM];
    int posiciones[CANT_CARRERAS];
}PILOTOS;

int main(){
    PILOTOS datos[CANT_PILOTOS];


    return 0;
}

void INGRESO(PILOTOS datos[], int ce, int ce2){
    PILOTOS auxNombre;
    printf("--INGRESO DE PILOTOS--\n");
    for (int i = 0; i < ce; i++)
    {
        printf("Ingrese nombre de piloto:");
        leerTexto(auxNombre.nombre, TAM);
        validarVacio(auxNombre.nombre, TAM);
        while (noRepite(datos, i, auxNombre)==1)
        {
            printf("El piloto se repite. Reingrese:");
            leerTexto(auxNombre.nombre, TAM);
            validarVacio(auxNombre.nombre, TAM);
        }
        strcpy(datos[i].nombre,auxNombre.nombre);
        printf("Ingrese escuderia para el piloto %s", datos[i].nombre);
        leerTexto(datos[i].escuderia, TAM);
        validarVacio(datos[i].escuderia, TAM);
    }
    for (int i = 0; i < ce2; i++)
    {
        
    }
    
}

void leerTexto(char texto[], int largo){
    fflush(stdin);
    int i;
    fgets(texto, largo, stdin);
    i=0;
    while (texto[i]!='\0')
    {
        if (texto[i]=='\n')
        {
            texto[i]='\0';
        }else{
            i++;
        }
    }
}

int noRepite(PILOTOS datos[], int i, PILOTOS auxNombre){
    int flag=0;
    for (int j = 0; j < i; j++)
    {
        if (strcmpi(datos[j].nombre,auxNombre.nombre)==0)
        {
            flag=1;
        }
    }
    return flag;
}

void validarVacio(char texto[], int largo){
    while (strlen(texto)==0)
    {
        printf("El texto no puede ser vacio. Reingrese");
        leerTexto(texto, TAM);
    }
}