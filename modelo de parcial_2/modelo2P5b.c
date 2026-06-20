/*Una entidad educativa dispone del archivo material.dat con la información del material para descargar por los alumnos. 
La información del archivo es la siguiente: (respetar nombre de campos)

codArch (entero, 4 dígitos) //Código del archivo
nomArch (char, 30 caracteres) //Nombre del archivo
nomMat (char, 30 caracteres) //Nombre de la materia
cantDesc (entero, inicializado en cero) //Cantidad de descargas

Luego dispone de un segundo archivo descargas.dat con las descargas efectuadas en el mes de Enero. 
Un archivo puede ser descargado ninguna o más de una vez. La información del archivo es la siguiente: (respetar nombre de campos)
nomArch (char, 30 caracteres) //Nombre del archivo
diaDesc (entero, 1 a 31) //Día de descarga

Se pide desarrollar un programa en lenguaje C que cumpla con las siguientes consignas:
Una función para actualizar el archivo material.dat con las descargas efectuadas.
Una función para generar el archivo sindescarga.dat que contenga los archivos que no tuvieron descargas.
Una función para generar el archivo descxdia.csv que contenga día y cantidad de descarga total.*/

/*
abrir archivo material.dat r+b
abrir archivo sindescarga a+b
fread(archM)
while(!feof){
    pos=busqueda(busco en descargas, que exista)
    if(pos!=-1){
        cantDesc++;
        fseek(pos)
        fwrite(archM)
        fflush(archM);
    }else{
        fwrite(archSin)
    }
}

descargasxDia(){
    v[30];
}

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

typedef struct 
{
    int codArch;
    char nomArch[31];
    char nomMat[31];
    int cantDesc;

}MATERIAL;

typedef struct
{
    char nomArch[31];
    int diaDesc;
}DESCARGAS;

