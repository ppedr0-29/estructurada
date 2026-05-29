/*5.10 Utilizando la siguiente definición de estructura, realice un programa que solicite memoria para 5 alumnos.
struct alumno
{
    int legajo;
    char sexo;
    char nombre[30];
    float promedio;
};
El usuario ingresara por teclado los datos que se cargara en la estructura- Mostrar el nombre de los alumnos
uno debajo del otro. A continuación, mostrar el alumno con mejor promedio.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    int legajo;
    char sexo;
    char nombre[30];
    float promedio;
}alumno;

alumno *mayor(alumno *, int );
char valSexo();
float leeyvalidaE2F(float , float );
void leerTexto (char [], int );
void validarVacio(char [], int );

int main (){
    alumno *v;
    int cantAlu=5;

    v=(alumno*)malloc(cantAlu*sizeof(alumno));
    for (int i = 0; i < cantAlu; i++)
    {
        printf("Ingrese legajo del alumno: ");
        scanf("%d", &(v+i)->legajo);
        printf("Ingrese sexo del alumno: ");
        (v+i)->sexo=valSexo();
        printf("Ingrese el nombre del alumno: ");
        leerTexto((v+i)->nombre, 30);
        validarVacio((v+i)->nombre, 30);
        printf("Ingrese el promedio: ");
        (v+i)->promedio=leeyvalidaE2F(1,10);
    }
    for (int i = 0; i < cantAlu; i++)
    {
        printf("El alumno %d se llama: %s\n", i+1, (v+i)->nombre);
    }
    alumno *mayorProm= mayor(v, cantAlu);
    printf("El alumno con mejor promedio es %s con %.2f\n", mayorProm->nombre, mayorProm->promedio);

    return 0;
}

alumno *mayor(alumno *v, int ce){
    float max= v->promedio;
    alumno *pr=v;
    for (int i = 0; i < ce; i++)
    {
        if ((v+i)->promedio>max)
        {
            max=(v+i)->promedio;
            pr=(v+i);
        }
    }
    return pr;
}

char valSexo(){
    char dato;
    fflush(stdin);
    scanf("%c", &dato);
    dato= toupper(dato);
    while (dato!='F' && dato!='M')
    {
        printf("Error. Reingrese:");
        fflush(stdin);
        scanf("%c", &dato);
        dato= toupper(dato);
    }
    return dato;
}

float leeyvalidaE2F(float min, float max){
    float dato;
    scanf("%f", &dato);
    while (dato<min || dato>max)
    {
        printf("Error. Reingrese:");
        scanf("%f", &dato);
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