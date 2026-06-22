/*Se tiene un archivo binario que registra los sueldos de los empleados de una empresa Con el siguiente diseño de registro
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
*/

/*
actualizarsueldo(){
fread
while(!feof){
    if(antiguedad > 10 && antiguedad <=20)
        sueldo*=1.05
    
    }else if(antiguedad mayor 20)
        sueldo *=1.06
    fread
}fclose
}

archivoAdmin(){
abrir archivo rb
abrir archivo en wb
contaodr=0
fread
while(!feof)
    if(area==A)
    fwrite 
    cont ++
fread
fclose(de ambos)
}
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef struct{
    int legajo;
    char nombre[46];
    int antiguedad;
    float sueldo;
    char area;
}EMP;

FILE *abrirArchivo(char nombre[], char tipo[]);
void actualizarSueldos();
void archivoAdmin();

int main(){
    actualizarSueldos();
    archivoAdmin();
    return 0;
}
void archivoAdmin(){
    FILE *archS=abrirArchivo("sueldos.dat", "rb");
    FILE*archA=abrirArchivo("administracion.dat", "wb");
    EMP datos;
    int cantRegistros=0;
    fread(&datos, sizeof(datos),1,archS);
    while(!feof(archS)){
        if(datos.area=='A'){
            cantRegistros++;
            fwrite(&datos, sizeof(datos), 1, archA);
        }
        fread(&datos, sizeof(datos), 1, archS);
    }
    printf("Se cargaron %d registros en admin", cantRegistros);
    fclose(archA);
    fclose(archS);
}
void actualizarSueldos(){
    FILE*arch=abrirArchivo("sueldos.dat", "r+b");
    EMP datos;
    fread(&datos, sizeof(datos), 1, arch);
    while(!feof(arch)){
        if(datos.antiguedad>10 && datos.antiguedad <=20){
            datos.sueldo*=1.05;
        }else if(datos.antiguedad>20){
            datos.sueldo*=1.06;
        }
        fseek(arch, -sizeof(datos), SEEK_CUR);
        fwrite(&datos, sizeof(datos), 1, arch);
        fflush(arch);
        fread(&datos, sizeof(datos), 1, arch);
    }
    fclose(arch);
}

FILE *abrirArchivo(char nombre[], char tipo[]){
    FILE*arch=fopen(nombre, tipo);
    if(arch==NULL){
        printf("Error al abrir el archivo...");
        getch();
        exit(1);
    }
    return arch;
}
