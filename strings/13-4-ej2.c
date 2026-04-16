/*Ejercicio 2
Confeccionar un programa que ingrese el listado de apellidos de los alumnos del curso
en un vector vAlumnos[15][21] con datos únicos y una cadena sAlu[21].
Confeccionar una función que busque el apellido en el listado de alumnos mostrando el
orden en que aparece y luego una función que muestre el listado de alumnos en orden
alfabético (A-Z).*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define CANT_ALU 15
#define TAM 21

void leerTexto(char [], int);
void ingresoAlumnos(char [], char [][TAM], int);
int busqueda(char [], char [][TAM]);
void buscarAlu(char [][TAM]);
void burbujeo(char [][TAM], int);

int main()
{
    char vAlumnos[CANT_ALU][TAM];
    char sAlu[TAM];

    ingresoAlumnos(sAlu, vAlumnos, CANT_ALU);
    buscarAlu(vAlumnos);
    burbujeo(vAlumnos, CANT_ALU);

    return 0;
}

void leerTexto(char texto[], int largo)
{
    int i;
    fgets(texto, largo, stdin);
    i = 0;
    while (texto[i] != '\0')
    {
        if (texto[i] == '\n')
            texto[i] = '\0';
        else
            i++;
    }
}

void ingresoAlumnos(char sAlu[], char vAlumnos[][TAM], int ce)
{
    for (int i = 0; i < ce; i++)
    {
        printf("Ingrese apellido del alumno %d: ", i + 1);
        leerTexto(sAlu, TAM);
        while (busqueda(sAlu, vAlumnos) != -1)
        {
            printf("Apellido ya existe, reingrese: ");
            leerTexto(sAlu, TAM);
        }
        strcpy(vAlumnos[i], sAlu);
    }
}

/* devuelve posicion si lo encontro, -1 si no lo encontro */
int busqueda(char sAlu[], char vAlumnos[][TAM])
{
    int i = 0;
    int pos = -1;
    bool flag = false;

    while (flag == false && i < CANT_ALU)
    {
        if (strcmpi(sAlu, vAlumnos[i]) == 0)
        {
            pos = i;
            flag = true;
        }
        else
            i++;
    }
    return pos;
}

/* Busca el apellido en el listado de alumnos mostrando el orden en que aparece */
void buscarAlu(char vAlumnos[][TAM])
{
    char apellido[TAM];
    int pos;

    printf("\nIngrese apellido del alumno a buscar: ");
    leerTexto(apellido, TAM);
    pos = busqueda(apellido, vAlumnos);

    if (pos != -1)
        printf("El alumno se encuentra en el numero %d de la lista", pos + 1);
    else
        printf("\nEl alumno no se encuentra en la lista");
}

/* Muestra el listado de alumnos en orden alfabetico (A-Z) */
void burbujeo(char V[][TAM], int ce)
{
    char AUX[TAM];
    int j, cota = ce - 1;
    int desordenado = 1;

    while (desordenado)
    {
        desordenado = 0;
        for (j = 0; j < cota; j++)
        {
            if (strcmpi(V[j], V[j + 1]) > 0)
            {
                strcpy(AUX, V[j]);
                strcpy(V[j], V[j + 1]);
                strcpy(V[j + 1], AUX);
                desordenado = j;
            }
        }
        cota = desordenado;
    }

    printf("\nListado de alumnos ordenados alfabeticamente:");
    for (int i = 0; i < CANT_ALU; i++)
        printf("\n %d.\t%s", i + 1, V[i]);
}
