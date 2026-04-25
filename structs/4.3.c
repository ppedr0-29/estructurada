/*4.3 Se sabe que como máximo en una comisión de Elementos de Programación hay 80 alumnos. De cada
alumno se conoce:
• Número de DNI (entero).
• Apellido y Nombre (80 caracteres).
• Nota1, Nota2 (entero).
• Nota Promedio (real, calculado según Nota1 y Nota2).
Se solicita:
a. Declarar un tipo de dato que contenga la información del alumno.
b. Declarar un vector de estructuras del tipo de dato creado en el punto a.
c. Cargar en un vector de estructuras, los datos referentes a los alumnos de la comisión, esta
información termina con DNI igual al 0. Función INGRESO.
d. Indicar cuántos alumnos aprobaron (ambos parciales con nota >= 4 y cuántos reprobaron la
materia. Función RESULTADO.
e. Informar los datos de los alumnos de (DNI – Apellido y Nombre – Nota Promedio) de los alumnos.
PROMOCIONADOS (ambas notas >= 7). Función INFORME_PROMO.*/

#include <stdio.h>
#include <string.h>
#define TAM 80


typedef struct 
{
    int dniAlu;
    char apellidoyNombreAlu[TAM];
    int nota1, nota2;
    float promedioNotas;
}ALUMNOS;

ALUMNOS ingreso();
int INGRESO(ALUMNOS [], int );
int leeyValidaIntEntre2DNI(int , int );
int leeyValidaIntEntre2Notas(int , int );
void leerTexto(char [], int );
void validarVacio(char [], int );
void RESULTADO(ALUMNOS [], int );
void INFORME_PROMO(ALUMNOS [], int);

int main(){
    ALUMNOS informacion[TAM];
    int cantAlumnos;
    cantAlumnos= INGRESO(informacion, TAM);
    RESULTADO(informacion, cantAlumnos);
    INFORME_PROMO( informacion, cantAlumnos);

    return 0;
}

int INGRESO(ALUMNOS informacion[], int ce){
    ALUMNOS aux;
    int i=0, flag=0;
    while (flag==0 && i<ce)
    {
        aux=ingreso();
        if (aux.dniAlu!=0)
        {
            informacion[i]=aux;
            i++;
        }else{
            flag=1;
        }
    }
    return i;
}


ALUMNOS ingreso(){
    ALUMNOS datos;
    printf("Ingrese DNI del alumno(0 finalizar):");
    datos.dniAlu=leeyValidaIntEntre2DNI(1000000, 99999999);
    if (datos.dniAlu!=0)
    {
        printf("Ingrese apellido y nombre:");
        leerTexto(datos.apellidoyNombreAlu, TAM);
        validarVacio(datos.apellidoyNombreAlu, TAM);
        printf("Ingrese nota 1 del alumno:");
        datos.nota1=leeyValidaIntEntre2Notas(0,10);
        printf("Ingrese nota 2 del alumno:");
        datos.nota2=leeyValidaIntEntre2Notas(0,10);
        datos.promedioNotas= (float)(datos.nota1 + datos.nota2) / 2;
    }else{
        printf("--CARGA FINALIZADA.--\n");
    }

    return datos;
}

void RESULTADO(ALUMNOS informacion[], int cantAlumnos){
    int acum1=0, acum2=0;
    for (int i = 0; i < cantAlumnos; i++)
    {
        if (informacion[i].nota1 >=4 && informacion[i].nota2 >=4)
        {
            acum1++;
        }else{
            acum2++;
        }
    }
    printf("Los alumnos aprobados son %d\n", acum1);
    printf("Los alumnos reprobados son %d\n", acum2);
}

void INFORME_PROMO(ALUMNOS informacion[], int cantAlumnos){
    printf("-ALUMNOS PROMOCIONADOS-\n");
    int flag=0;
    for (int i = 0; i < cantAlumnos; i++)
    {   
        if (informacion[i].nota1 >=7 && informacion[i].nota2 >=7)
        {
            printf("DNI %10d, %-20s, Promedio %8.2f\n", informacion[i].dniAlu, informacion[i].apellidoyNombreAlu, informacion[i].promedioNotas);
            flag=1;
        }
    }
    if (flag==0)
    {
        printf("No hay alumnos promocionados.");
    }
    
}

int leeyValidaIntEntre2DNI(int min, int max){
    int dato;
    scanf("%d", &dato);
    while (getchar() != '\n');
    while ((dato<min || dato>max) && dato!=0){
        printf("ERROR - El DNI ingresado tiene que ser entre[%d-%d]:", min, max);
        scanf("%d", &dato);
        while (getchar() != '\n');
    }
    return dato;
}

int leeyValidaIntEntre2Notas(int min, int max){
    int dato;
    scanf("%d", &dato);
    while (getchar() != '\n');
    while (dato<min || dato>max){
        printf("ERROR - La nota ingresada tiene que ser entre[%d-%d]:", min, max);
        scanf("%d", &dato);
        while (getchar() != '\n');
    }
    return dato;
}


void leerTexto(char texto[], int largo) {
    int i;
    fgets(texto, largo, stdin); 
    i = 0;
    while (texto[i] != '\0') {
        if (texto[i] == '\n') { 
            texto[i] = '\0';
        } else {
            i++;
        }
    }
}

void validarVacio(char texto[], int largo) {
    while (strlen(texto) == 0) {
        printf("El texto no puede estar vacio. Ingrese nuevamente: ");
        leerTexto(texto, largo);
    }
}