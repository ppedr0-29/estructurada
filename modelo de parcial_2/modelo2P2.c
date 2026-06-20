/*2do parcial verano, Sotelo Lorena

La empresa VoiYa de la comuna 1 de CABA desea contabilizar los viajes realizados por sus choferes en el 2025, cuenta con un archivo llamado 
infoChoferes.dat y cada registro se compone de la siguiente manera:
-Código de chofer (entero)
-Apellido y Nombre (50 caracteres)
-Antigüedad (entero)
-Kms recorridos (entero, inicializado en cero)

Además, dispone del archivo recorridos2025.dat con los recorridos realizados por los choferes en cada uno de los meses. 
Cada registro se compone de la siguiente manera:
-Código de chofer (entero)
-Kms recorridos (entero)
-Mes recorrido (entero)

Se pide realizar un programa en lenguaje C que cumpla con las siguientes consignas:
Actualizar el archivo infoChoferes.dat con la información del archivo recorridos.dat.
Informar el/los meses que mayor recorrido han tenido, informando mes y cantidad recorrida.*/

#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <conio.h>

typedef struct
{
    int codChofer;
    char ayn[51];
    int antig;
    int kmsR;
}CHOFERES;

typedef struct
{
    int codChofer;
    int kmsR;
    int mesR;
}RECORRIDOS;

void mostrarMax(int *, int );
long busqueda(int , CHOFERES *, FILE*);
int maximo(int *, int );
void procesarArchivos();

int main(){
    
    procesarArchivos();

    return 0;
}

void procesarArchivos(){
    FILE *archC;
    FILE *archR;
    CHOFERES datos;
    RECORRIDOS info;
    CHOFERES *pdatos=&datos;
    long pos;
    int meses[13]={0};
    int *mes=meses;
    archC=fopen("infoChoferes.dat", "r+b");
    archR=fopen("recorridos2025.dat", "rb");
    if (archC==NULL || archR==NULL)
    {
        printf("No pudo abrirse alguno de los archivos.");
        getch();
        exit(1);
    }
    fread(&info, sizeof(info), 1, archR);
    while (!feof(archR))
    {
        pos=busqueda(info.codChofer, pdatos, archC);
        if (pos!=-1)
        {
            datos.kmsR+=info.kmsR;
            fseek(archC, pos, SEEK_SET);
            fwrite(&datos, sizeof(datos), 1, archC);
            fflush(archC);
            meses[info.mesR]+=info.kmsR;
        }
        fread(&info, sizeof(info), 1, archR);
    }
    mostrarMax(mes, 13);

    fclose(archC);
    fclose(archR);
}

void mostrarMax(int *v, int ce){
    int max=maximo(v, ce);
    for (int i = 1; i < ce; i++)
    {
        if (v[i]==max)
        {
            printf("El mes %d tuvo el mayor recorrido con %d kms\n", i, v[i]);
        }
        
    }
    
}

int maximo(int *v, int ce){
    int max=v[1];
    for (int i = 1; i < ce; i++)
    {
        if (v[i]>max)
        {
            max=v[i];
        }
        
    }
    return max;
}

long busqueda(int cod, CHOFERES *pdatos, FILE*arch){
    long pos=-1;
    int flag=0;
    CHOFERES datos;
    rewind(arch);
    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch) && flag==0)
    {
        if (datos.codChofer==cod)
        {
            flag=1;
            pos=ftell(arch)-sizeof(datos);
            *pdatos=datos;
        }
        fread(&datos, sizeof(datos), 1, arch);
    }
    return pos;
}