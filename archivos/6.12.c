/*6.12 Se dispone de un archivo con nombre Llamadas.dat que contiene llamadas telefónicas realizadas en una
empresa. Por cada llamada se dispone de la siguiente información:
• Sector (15 caracteres máximo)
• Duración en segundos (entero)
• Tipo de llamada (entero: 1 local, 2 larga distancia, 3 celular)
El archivo se encuentra organizado por Sector. Se solicita:
a. Calcular y mostrar por cada sector, la cantidad de llamadas realizadas de cada tipo.
b. Determinar cuál es el sector que habló la mayor cantidad de tiempo.
c. En un archivo llamado costos.dat hay un único registro que contiene los costos por segundo de los
tres tipos de llamadas (3 float). Se debe generar el archivo gastos.dat que totalice los gastos de
llamadas de cada sector.
d. Realizar una función que muestre los datos almacenados en gastos.dat en forma de listado.
e. Generar un archivo para cada sector con el detalle de llamadas valorizado. El archivo se debe
generar con nombresector.dat y debe contener:
• Duración en segundos (entero)
• Tipo de llamada (entero)
• Costo de la llamada (float)
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef struct
{
    char sector [16];
    int seg;
    int tipo;
}LLAMADA;

typedef struct 
{
    int seg;
    int tipo;
    float costo;
}SECTOR;

typedef struct
{
    float costoLocal;
    float costoLargaD;
    float costoCel;
}COSTO;

typedef struct
{   
    char sec[16];
    float gastosTot;
}GASTO;

void mostrarGastos();
void procesarArchivo();

int main (){

    procesarArchivo();
    mostrarGastos();

    return 0;
}

void mostrarGastos(){
    FILE *arch;
    GASTO datos;
    arch=fopen("GASTO.dat", "rb");
    if (arch==NULL)
    {
        printf("Error.");
        getch();
        exit(1);
    }
    fread(&datos, sizeof(datos), 1, arch);
    printf("--SECTOR\tGASTO TOTAL--\n");
    while (!feof(arch))
    {
        printf("%6s\t%6.2f\n", datos.sec, datos.gastosTot);
        fread(&datos, sizeof(datos), 1, arch);
    }
    fclose(arch);
}



void procesarArchivo(){
    FILE *arch;
    FILE *archC;
    FILE *archG;
    FILE *archS;
    COSTO costos;
    GASTO gastos;
    LLAMADA datos;
    SECTOR sectores;
    char nombresec[25];
    arch=fopen("LLAMADAS.dat", "rb");
    if (arch==NULL)
    {
        printf("Error.");
        getch();
        exit(1);
    }
    archC=fopen("COSTOS.dat", "rb");
    archG=fopen("GASTO.dat", "wb");
    if (archC==NULL || archG==NULL)
    {
        printf("Error.");
        getch();
        exit(1);
    }
    fread(&costos, sizeof(costos), 1, archC);
    fread(&datos, sizeof(datos), 1, arch);
    char secAnt[16], maxSec[16];
    int cantLlamadas1, cantLlamadas2, cantLlamadas3, seg1, seg2, seg3, primero=1, segTot=0, maxSeg;
    while (!feof(arch))
    {
        strcpy(secAnt, datos.sector);
        cantLlamadas1=0;
        cantLlamadas2=0;
        cantLlamadas3=0;
        seg1=0;
        seg2=0;
        seg3=0;
        segTot=0;
        strcpy(nombresec, secAnt);
        strcat(nombresec, ".dat");
        archS=fopen(nombresec, "wb");
        if (archS==NULL)
            {
                printf("Error.");
                getch();
                exit(1);
            }
        while (strcmpi(secAnt, datos.sector)==0 && !feof(arch))
        {   //inciso a
            sectores.seg=datos.seg;
            sectores.tipo=datos.tipo;
            if (datos.tipo==1)
            {
                cantLlamadas1++;
                seg1+=datos.seg;
                sectores.costo=(sectores.seg*costos.costoLocal);
            }else if (datos.tipo==2)
                {
                    cantLlamadas2++;
                    seg2+=datos.seg;
                    sectores.costo=(sectores.seg*costos.costoLargaD);
                }else{
                    cantLlamadas3++;
                    seg3+=datos.seg;
                    sectores.costo=(sectores.seg*costos.costoCel);
                }
            //inciso b
            segTot+=datos.seg;
            //inciso e
            fwrite(&sectores, sizeof(sectores), 1, archS);
            fread(&datos, sizeof(datos), 1, arch);
        }
        if (primero==1){
            strcpy(maxSec, secAnt);
            maxSeg=segTot;
            primero=0;
        }else if (segTot>maxSeg)
        {
            maxSeg=segTot;
            strcpy(maxSec, secAnt);
        }
        //inciso c
        gastos.gastosTot=(seg1*costos.costoLocal)+(seg2*costos.costoLargaD)+(seg3*costos.costoCel);
        strcpy(gastos.sec, secAnt);
        fwrite(&gastos, sizeof(gastos), 1, archG);
        printf("En el sector %s se hicieron: \n %d llamadas del tipo LOCAL\n %d llamadas del tipo LARGA DISTANCIA\n %d llamadas del tipo CELULAR\n", secAnt, cantLlamadas1, cantLlamadas2, cantLlamadas3);
        fclose(archS);
    }
    
    printf("El sector que mas segundos tuvo fue %s con %d segundos\n", maxSec, maxSeg);

    fclose(arch);
    fclose(archC);
    fclose(archG);
}