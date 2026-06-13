/*6.11 Se dispone de un archivo llamado Rating.dat que guarda la información de los puntos obtenidos de rating
en los distintos programas de canales de cable a lo largo del día. Cada registro contiene:
• Número de canal (entero)
• Programa (texto de 35 caracteres máximo)
• Rating (float)
El archivo se encuentra ordenado por canal.
Se solicita informar:
a. Aquellos canales que obtengan menos de 15 puntos en total.LISTO
b. El canal más visto. LISTO
c. Generar un archivo con el promedio de rating de cada canal que incluya dos campos:
• Número de canal.
• Promedio.*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct
{
    int numC;
    char prog[36];
    float rating;
}TV;

typedef struct
{
    int numC;
    float prom;
}RatProm;

void mostrar(FILE *);
void mostrarP(FILE *);

int main(){
    TV datos;
    RatProm info;
    FILE *arch, *archP;
    float totRat=0.0;
    float ratMax;
    int canMax, primero=1, cantProg;
    arch= fopen("RATING.dat", "r+b");
    archP= fopen("promedio.dat", "w+b");
    if (arch==NULL || archP==NULL)
    {
        printf("Error al abrir alguno de los archivos");
        getch();
        exit(1);
    }
    mostrar(arch);
    int canAnt;
    rewind(arch);
    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch))
    {
        canAnt=datos.numC;
        cantProg=0;
        while (canAnt==datos.numC && !feof(arch))
        {
            totRat+=datos.rating;
            cantProg++;
            fread(&datos, sizeof(datos), 1, arch);
        }
        if(primero==1){//solo primer canal para tomaer los primeros valores como maximos
            ratMax=totRat;
            canMax=canAnt;
            primero=0;
        }else
            if(totRat>ratMax){
                ratMax=totRat;
                canMax=canAnt;
            }
        if (totRat<15.0)
        {
            printf("El/los canales que obtuvieron un rating menor a 15 fueron: %d\n", canAnt);
        }
        info.prom=totRat/cantProg;
        info.numC=canAnt;
        fwrite(&info, sizeof(info), 1, archP);
        totRat=0;
    }
    printf("El canal %d tuvo el mayor rating con %.2f puntos", canMax, ratMax);
    mostrarP(archP);


    fclose(arch);
    fclose(archP);

    return 0;
}

void mostrar(FILE *arch){
    TV datos;
    rewind(arch);
    fread(&datos, sizeof(datos), 1, arch);
    printf("%7s\t%-8s\t%6s\n", "NUM CAN", "PROGRAMA", "RATING");
    while (!feof(arch))
    {
        printf("%7d\t%-8s\t%6.2f\n", datos.numC, datos.prog, datos.rating);
        fread(&datos, sizeof(datos), 1, arch);
    }
}
void mostrarP(FILE *arch){
    RatProm datos;
    rewind(arch);
    fread(&datos, sizeof(datos), 1, arch);
    printf("\n%7s\t%-8s\n", "NUM CAN", "PROMEDIO");
    while (!feof(arch))
    {
        printf("%7d\t%-7.2f\n", datos.numC, datos.prom);
        fread(&datos, sizeof(datos), 1, arch);
    }
}