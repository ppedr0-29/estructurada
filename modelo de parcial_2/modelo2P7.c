/*Se tiene un archivo binario que registra los sueldos de los empleados de una empresa
Con el siguiente diseño de registro
Legajo( int)
Nombre(45)
Antigüedad (en años int)
Sueldo básico (float)
Area( char 'A': administración, 'P': producción, 'C' comercial)
Realizar un programa en C que permita modificar directamente sobre el archivo (llamado sueldos.dat)los sueldos básicos de
los empleados según la siguiente escala de antigüedad
Mayor a 10 años 5%
Mayor a 20 años 6%
Una vez actualizado se debe generar un nuevo archivo, que solo contenga a los empleados del área administrativa
e informar la cantidad de registros de dicho archivo, utilizando las funciones vistas en el curso.

abrir archivo r+b
fread()
while(!feof){
    if(antiguedad>10 && antiguedad<=20)
    datos.sueldo*=1.05
    else if(antiguedad>20){
        datos.sueldo*=1.06
    }

}

nuevoArchivo(){
    FILE *arch en rb;
    FILE *archN en wb;
    EMP dato;
    fread
    while(!feof){
        if(datos.area=='A'){
            fwrite(&dato, archN);
            cantRegistro++;
        }
        fread();    
    }
    fclose(arch)
    fclose(archN)
}

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct
{
    int legajo;
    char nombre[46];
    int antig;
    float sueldo;
    char area;
}EMP;

FILE *abrirArchivo(char [], char []);
void procesarArchivo();
void nuevoArchivo();

int main(){
    procesarArchivo();
    nuevoArchivo();

    return 0;
}

void nuevoArchivo(){
    FILE*arch=abrirArchivo("sueldos.dat", "rb");
    FILE *archNuev=abrirArchivo("empleadosA.dat", "wb");
    EMP datos;
    int cantRegistros=0;
    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch))
    {
        if (datos.area=='A')
        {
            fwrite(&datos, sizeof(datos), 1, archNuev);
            cantRegistros++;
        }
        fread(&datos, sizeof(datos), 1, arch);
    }
    printf("La cantidad de registros son %d del archivo empleadosA.dat", cantRegistros);

    fclose(arch);
    fclose(archNuev);
}

void procesarArchivo(){
    FILE *arch;
    arch=abrirArchivo("sueldos.dat", "r+b");
    EMP datos;
    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch))
    {
        if (datos.antig>10 && datos.antig<=20)
        {
            datos.sueldo=(datos.sueldo*1.05);
        }else if(datos.antig>20){
            datos.sueldo=(datos.sueldo*1.06);
        }
        fseek(arch, -sizeof(datos), SEEK_CUR);
        fwrite(&datos, sizeof(datos), 1, arch);
        fflush(arch);
        fread(&datos, sizeof(datos), 1, arch);
    }
    
    fclose(arch);
}

FILE *abrirArchivo(char nombre[], char tipo[]){
    FILE *arch;
    arch=fopen(nombre, tipo);
    if (arch==NULL)
    {
        printf("Error.");
        getch();
        exit(1);
    }
    return arch;
}