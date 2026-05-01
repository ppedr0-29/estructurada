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

void INGRESO(PILOTOS [], int);
int leeryvalidarIntRango(int , int );
int leeryvalidarIntRango2(int , int );
void leerTexto(char [], int );
int noRepitePos(PILOTOS [], int , int , int );
int noRepite(PILOTOS [], int , PILOTOS );
void validarVacio(char [], int );
void informeCarrera(PILOTOS [], int);

int main(){
    PILOTOS datos[CANT_PILOTOS];
    INGRESO(datos, CANT_PILOTOS);
    informeCarrera(datos, CANT_PILOTOS);

    return 0;
}

void INGRESO(PILOTOS datos[], int ce){
    PILOTOS auxNombre; 
    int auxPos;
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
        printf("Ingrese escuderia para el piloto %s:", datos[i].nombre);
        leerTexto(datos[i].escuderia, TAM);
        validarVacio(datos[i].escuderia, TAM);
        for (int j = 0; j < CANT_CARRERAS; j++)
        {
            printf("Ingrese posicion de %s de la carrera %d:", datos[i].nombre, j+1 );
            auxPos=leeryvalidarIntRango(1,20);
            while (noRepitePos(datos, auxPos, i, j)==1)
            {
                printf("La posicion ya fue ingresada. Reingrese:");
                auxPos=leeryvalidarIntRango(1,20);
            }
            datos[i].posiciones[j]=auxPos;
        }
    }
}

void informeCarrera(PILOTOS datos[], int ce){
    int auxCarrera;
    printf("--RESULTADOS CARRERA--\n");
    printf("Ingrese numero de carrera a buscar:");
    auxCarrera=leeryvalidarIntRango2(1,23);
    while (auxCarrera!=0)
    {
        
        for (int j = 1; j<=10; j++){
            for (int i = 0; i < ce; i++)
            {
                if (datos[i].posiciones[auxCarrera-1]==j)
                {
                    printf("%d-%s (%s)\n", datos[i].posiciones[auxCarrera-1], datos[i].nombre, datos[i].escuderia);
                }
            }
        }
        printf("Ingrese numero de carrera a buscar:");
        auxCarrera=leeryvalidarIntRango2(1,23);
    }
    printf("Programa finalizado.");
}


int leeryvalidarIntRango(int min, int max){
    int dato;
    scanf("%d", &dato);
    while (dato<min || dato>max)
    {
        printf("Posicion no valida. Reingrese:");
        scanf("%d", &dato);
    }
    return dato;
}

int leeryvalidarIntRango2(int min, int max){
    int dato;
    scanf("%d", &dato);
    while ((dato<min || dato>max) && dato!=0)
    {
        printf("Carrera no valida. Reingrese:");
        scanf("%d", &dato);
    }
    return dato;
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

int noRepitePos(PILOTOS datos[], int posIngresada, int i, int j){
    int flag=0;
    for (int k = 0; k < i; k++)
    {
        if (datos[k].posiciones[j]==posIngresada)
        {
            flag=1;
        }
    }
    return flag;
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
        printf("El texto no puede ser vacio. Reingrese:");
        leerTexto(texto, TAM);
    }
}