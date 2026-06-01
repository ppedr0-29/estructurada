/*6.2 Tomando como base el archivo ALUMNOS.DAT creado en el ejercicio anterior se desea desarrollar un
programa que, basado en la información del archivo, genere 3 archivos:
• Uno con los alumnos PROMOCIONADOS (ambas notas mayores o igual a 7).
• Otro archivo con los alumnos en condición CURSADO (ambas notas mayores o igual a 4 pero no
promocionados).
• Y un tercer archivo con los REPROBADOS (al menos una nota, menor que 4).
Para comprobar los datos guardados realizar una función que reciba por parámetro el nombre del archivo
a mostrar, lo abre y muestre su contenido. Se debe invocar a la función 3 veces para mostrar todos los
archivos generados.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define TAM 81

typedef struct
{
    int dni;
    char nya[TAM];
    int nota1;
    int nota2;
    float promedio;
} Alumno;

void LECTURA(const char []);

int main (){
    Alumno datos;
    FILE *archAlu;
    FILE *archProm;
    FILE *archCurs;
    FILE *archRepr;

    archAlu= fopen("ALUMNOS.dat", "rb");
    if (archAlu==NULL)
    {
        printf("Error al abrir el archivo.");
        getch();
        exit(1);
    }
    archProm= fopen("PROMOCIONADOS.dat", "wb");
    if (archProm==NULL)
    {
        printf("Error al abrir el archivo.");
        getch();
        exit(1);
    }
    archCurs= fopen("CURSADO.dat", "wb");
    if (archCurs==NULL)
    {
        printf("Error al abrir el archivo.");
        getch();
        exit(1);
    }
    archRepr= fopen("REPROBADOS.dat", "wb");
    if (archRepr==NULL)
    {
        printf("Error al abrir el archivo.");
        getch();
        exit(1);
    }
    fread(&datos, sizeof(datos), 1, archAlu);
    while(!feof(archAlu)){
        if (datos.nota1>=7 && datos.nota2>=7)
        {
            fwrite(&datos, sizeof(datos), 1, archProm);
        }else if(datos.nota1 >=4 && datos.nota2>=4){
            fwrite(&datos, sizeof(datos), 1, archCurs);
        }else{
            fwrite(&datos, sizeof(datos), 1, archRepr);
        }
        fread(&datos, sizeof(datos), 1, archAlu);
    }
    fclose(archAlu);
    fclose(archCurs);
    fclose(archProm);
    fclose(archRepr);
    LECTURA("PROMOCIONADOS.dat");
    LECTURA("CURSADO.dat");
    LECTURA("REPROBADOS.dat");
}

void LECTURA(const char texto[]){
    FILE *arch;
    Alumno datos;
    arch=fopen(texto, "rb");
    if (arch==NULL)
    {
        printf("Error al abrir el archivo");
        getch();
        exit(1);
    }
    printf("Abriendo archivo %s....\n ", texto);
    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch))
    {
        printf("DNI: %d | Nombre: %s | Nota 1: %d | Nota 2: %d | Promedio: %.2f\n", 
               datos.dni, datos.nya, datos.nota1, datos.nota2, datos.promedio);
        fread(&datos, sizeof(datos), 1, arch);
    }
    fclose(arch);
}