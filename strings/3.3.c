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

int main(){
    char nombre[TAM][LARGO_NOMBRE], nombre2[LARGO_NOMBRE];
    int dni[TAM];
    int cant;
    int pos;
    cant=ingresaDatos(nombre, dni);
    printf("Ingrese nombre a buscar:");
    leerTexto(nombre2, LARGO_NOMBRE);
    while (strcmpi(nombre2, "NOBUSCARMAS") !=0)
    {
        pos= busquedaSecuencial(nombre, nombre2, cant);
    }
    
}

int ingresaDatos(char nombre[][LARGO_NOMBRE], int dni[]){
    int i=0;
    printf("Ingrese nombre del alumno %d:", i+1);
    leerTexto(nombre[i], LARGO_NOMBRE);
    while (strcmpi(nombre[i], "FIN") !=0 && i<TAM)
    {
        while (strlen(nombre[i])==0)
            {
            printf("El nombre no puede ser vacio. Ingrese nuevamente:");
            leerTexto(nombre[i], LARGO_NOMBRE);
        }
        printf("Ingrese DNI del alumno %d:", i+1);
        dni[i]=leeyValidaIntEntre2(1000000, 99999999);
        i++;
        printf("Ingrese nombre del alumno %d:", i+1);
        leerTexto(nombre[i], LARGO_NOMBRE);
    }
    printf("El programa finalizo.");
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

void mostrarDNI(char nombre2[], int pos, int cant, char nombre[][LARGO_NOMBRE]){
    printf("Ingrese nombre a buscar:");
    leerTexto(nombre2, LARGO_NOMBRE);
    while (strcmpi(nombre2, "NOBUSCARMAS") !=0)
    {
        pos= busquedaSecuencial(nombre, nombre2, cant);
    }
    printf("Carga finalizada.");
}