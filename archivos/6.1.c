/*6.1 Los datos de los alumnos de una comisión de Computación Transversal son:
• Número de DNI (entero)
• Nombre y Apellido (80 caracteres)
• Nota1, Nota2 (entero)
• Nota Promedio (real, calculado según Nota1 y Nota2)
a. Declarar un tipo de dato que contenga la información del alumno.
b. Con la información indicada para los alumnos. Grabar los datos en el archivo “ALUMNOS.dat”. Esta
información de grabación finaliza con DNI cero.
c. Leer los datos del archivo, mediante la Función LECTURA.*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h> // Agregado para solucionar el warning de getch()

#define TAM 81

typedef struct
{
    int dni;
    char nya[TAM];
    int nota1;
    int nota2;
    float promedio;
} Alumno;

int leeyValidaE2CF(int , int , int );
int leeyValidaE2(int , int );
void leerTexto (char [], int );
void validarVacio(char [], int );
void LECTURA();

int main (){
    Alumno datos;
    FILE *arch;

    arch = fopen("ALUMNOS.dat", "ab");
    if (arch == NULL)
    {
        printf("Error al abrir el archivo.");
        getch();
        exit(1);
    }
    
    printf("Ingrese DNI(0 para finalizar):");
    datos.dni = leeyValidaE2CF(10000000, 99999999, 0);
    
    while (datos.dni != 0)
    {
        printf("Ingrese nombre y apellido:");
        leerTexto(datos.nya, TAM);
        validarVacio(datos.nya, TAM);
        
        printf("Ingrese nota 1:");
        datos.nota1 = leeyValidaE2(1, 10);
        
        printf("Ingrese nota 2:");
        datos.nota2 = leeyValidaE2(1, 10);
        
        datos.promedio = (float)(datos.nota1 + datos.nota2) / 2;
        
        fwrite(&datos, sizeof(datos), 1, arch);
        
        printf("Ingrese DNI(0 para finalizar):");
        datos.dni = leeyValidaE2CF(10000000, 99999999, 0);
    }
    
    fclose(arch);
    
    LECTURA();
    
    return 0;
}

void LECTURA(){
    FILE *arch;
    Alumno datos;
    
    arch = fopen("ALUMNOS.dat", "rb");
    if (arch == NULL)
    {
        printf("Error al abrir el archivo.");
        getch();
        exit(1);
    }
    
    printf("\n--- LEYENDO ARCHIVO ---\n");
    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch))
    {   
        printf("DNI: %d | Nombre: %s | Nota 1: %d | Nota 2: %d | Promedio: %.2f\n", 
            datos.dni, datos.nya, datos.nota1, datos.nota2, datos.promedio);
        fread(&datos, sizeof(datos), 1, arch);
    }
    
    fclose(arch);
}

int leeyValidaE2CF(int min, int max, int cf){
    int dato;
    scanf("%d", &dato);
    while((dato < min || dato > max) && dato != cf){
        printf("Error- Reingrese:");
        scanf("%d", &dato);
    }
    return dato;
}

int leeyValidaE2(int min, int max){
    int dato;
    scanf("%d", &dato);
    while(dato < min || dato > max){
        printf("Error- Reingrese:");
        scanf("%d", &dato);
    }
    return dato;
}

void leerTexto (char texto[], int largo){
    int i;
    fflush(stdin);
    fgets(texto, largo, stdin);
    i = 0;
    while (texto[i] != '\0')
    {
        if (texto[i] == '\n')
        {
            texto[i] = '\0';
        } else {
            i++;
        }
    }
}

void validarVacio(char texto[], int largo){
    while(strlen(texto) == 0){
        printf("El texto no puede ser vacio. Reingrese:");
        leerTexto(texto, largo);
    }
}