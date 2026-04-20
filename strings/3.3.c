/*3.3 Ingresar nombre y DNI de los alumnos de un curso. Como máximo el curso puede tener 50 alumnos. La
carga finaliza con un alumno de nombre FIN. Luego de cargar los alumnos se pide:
a. Ingresar nombres de a uno en uno y buscarlos. Si el nombre está en el curso mostrar su DNI y sino
informar que no está. Seguir ingresando nombres hasta que se ingrese un nombre igual a
NOBUSCARMAS.
b. Mostrar el listado de alumnos ordenado alfabéticamente de menor a mayor.*/

#include <stdio.h>
#include <string.h>

#define TAM 50
#define LARGO_NOMBRE 30

int ingresaDatos(char [][LARGO_NOMBRE], int []);
void leerTexto(char [], int);
int leeyValidaIntEntre2(int, int);
int busquedaSecuencial(char [][LARGO_NOMBRE], char [], int );
void mostrarDNI(char [], int , char [][LARGO_NOMBRE], int []);
void validarVacio(char [], int );
void burbujeo(char [][LARGO_NOMBRE], int [],int );
void mostrarListado(char [][LARGO_NOMBRE], int [], int);

int main(){
    char nombre[TAM][LARGO_NOMBRE], nombre2[LARGO_NOMBRE];
    int dni[TAM]; //preguntar al profesor como es el tipo de dato para DNI
    int cant;
    cant=ingresaDatos(nombre, dni);
    printf("--BUSQUEDA DE ALUMNOS--\n");
    mostrarDNI( nombre2, cant, nombre, dni);
    mostrarListado(nombre, dni, cant);
}

int ingresaDatos(char nombre[][LARGO_NOMBRE], int dni[]){
    int i=0;
    char nombreAux[LARGO_NOMBRE];
    printf("Ingrese nombre del alumno %d:", i+1);
    leerTexto(nombreAux, LARGO_NOMBRE);
    validarVacio(nombreAux, LARGO_NOMBRE);
    while (strcmpi(nombreAux, "FIN") !=0 && i<TAM)
    {
        strcpy(nombre[i], nombreAux);
        printf("Ingrese DNI del alumno %d:", i+1);
        dni[i]=leeyValidaIntEntre2(1000000, 99999999);
        i++;
        printf("Ingrese nombre del alumno %d:", i+1);
        leerTexto(nombreAux, LARGO_NOMBRE);
        validarVacio(nombreAux, LARGO_NOMBRE);
    }
    return i;
}

void leerTexto (char texto[], int largo){
    int i;
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

int leeyValidaIntEntre2(int min, int max){
    int dato;
    scanf("%d", &dato);
    while (getchar() != '\n');
    while (dato<=min || dato>=max){
        printf("ERROR - El DNI ingresado tiene que ser entre[%d-%d]:", min, max);
        scanf("%d", &dato);
        while (getchar() != '\n');
    }
    return dato;
}

int busquedaSecuencial(char nombre[][LARGO_NOMBRE], char nombre2[], int cant){
    int i=0, pos=-1;
    while (pos==-1 && i<cant){
        if (strcmpi(nombre[i], nombre2)==0){
        pos =i;
        }else{
            i++;
        }
    }
return pos;
}

void mostrarDNI(char nombre2[], int cant, char nombre[][LARGO_NOMBRE], int dni[]){
    int pos;
    printf("Ingrese nombre a buscar:");
    leerTexto(nombre2, LARGO_NOMBRE);
    //validarVacio(nombre2, LARGO_NOMBRE);
    while (strcmpi(nombre2, "NOBUSCARMAS") !=0)
    {
        pos= busquedaSecuencial(nombre, nombre2, cant);
        if (pos!=-1)
        {
            printf("DNI %d correspondiente al alumno %s\n", dni[pos], nombre2);
        }else{
            printf("El alumno %s no fue encontrado.\n", nombre2);
        }
        printf("Ingrese nombre a buscar:");
        leerTexto(nombre2, LARGO_NOMBRE);
    }
    printf("\nCarga finalizada.\n");
}

void burbujeo(char nombre[][LARGO_NOMBRE], int dni[],int ce)//ordenar alfabeticamente
{
    char AUX[TAM];
    int dniAux;
    int j, cota = ce - 1;
    int desordenado = 1;

    while (desordenado)
    {
        desordenado = 0;
        for (j = 0; j < cota; j++)
        {
            if (strcmpi(nombre[j], nombre[j + 1]) > 0)
            {
                strcpy(AUX, nombre[j]);
                strcpy(nombre[j], nombre[j + 1]);
                strcpy(nombre[j + 1], AUX);
                dniAux=dni[j];
                dni[j]=dni[j+1];
                dni[j+1]=dniAux;
                desordenado = j;
            }
        }
        cota = desordenado;
    }
}

void mostrarListado(char nombre[][LARGO_NOMBRE], int dni[], int cant){
    burbujeo(nombre, dni, cant);
    printf("---LISTADO DE ALUMNOS(A-Z)---");
    for (int i = 0; i < cant; i++)
    {
        printf("\n%s", nombre[i]);
    }
    
}

void validarVacio(char texto[], int largo){
    while (strlen(texto)==0)
        {
            printf("El texto no puede estar vacio. Ingrese nuevamente:");
            leerTexto(texto, largo);
        }
}