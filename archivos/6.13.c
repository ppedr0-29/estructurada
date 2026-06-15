/*6.13 La empresa RED VIAL S.A. desea controlar el flujo vehicular en sus cabinas de peaje a lo largo del mes. Para
ello se debe procesar la información provista por las barreras que se encuentra almacenada en el archivo
barreras.dat que contiene la siguiente información:
• Día (entero)
• Hora (0 a 24)
• Número de barrera (entero)
Dentro del archivo la información se encuentra ordenada por día y hora. Determinar:
a. La cantidad de vehículos por cada hora.
b. La cantidad de vehículos de cada día.
c. Ingresar por teclado los precios del peaje para horario normal y horario pico (de 7 a 11 y de 17 a
19). Con esos valores guardar un archivo con la recaudación de cada día.*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct
{
    int dia;
    int hora;
    int num;
}BARRERA;
typedef struct 
{
    int dia;
    float recaudacion;
}ingreso;

void procesarArchivo();
float leeyvalidaFloat(float);
void inicializarVec(float[], float, int);
void ingresoPrecios(float[]);

int main (){

    
    procesarArchivo();

    return 0;
}

void procesarArchivo(){
    FILE *arch;
    FILE *archR;
    BARRERA datos;
    ingreso info;
    float precio[24];
    int diaAnt, horaAnt, cantVxH, cantVxD;
    arch=fopen("barreras.dat", "rb");
    archR=fopen("RECAUDACIONES.dat", "wb");
    if(arch==NULL || archR==NULL){
        printf("Error.");
        getch();
        exit(1);
    }
    ingresoPrecios(precio);
    
    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch))
    {
        diaAnt=datos.dia;
        cantVxD=0;
        info.recaudacion=0;
        while (diaAnt==datos.dia && !feof(arch))
        {
            horaAnt=datos.hora;
            cantVxH=0;
            while ((diaAnt==datos.dia && !feof(arch)) && horaAnt==datos.hora)
            {
                cantVxH++;
                fread(&datos, sizeof(datos), 1, arch);
            }
            cantVxD+=cantVxH;
            info.recaudacion+=cantVxH*precio[horaAnt];
            printf("La cantidad de vehiculos en la hora %d el dia %d son %d\n", horaAnt, diaAnt, cantVxH);
        }
        info.dia=diaAnt;
        fwrite(&info,sizeof(info), 1, archR);
        printf("La cantidad de vehiculos en el dia %d son %d\n", diaAnt, cantVxD);
    }
    


    fclose(arch);
    fclose(archR);
}
void ingresoPrecios( float precio[]){
    float p;
    printf("Ingrese precio para horario normal: ");
    p=leeyvalidaFloat(0);
    inicializarVec(precio, p, 24);
    printf("Ingrese precio para horario pico((7 a 11 y 17 a 19): ");
    p=leeyvalidaFloat(0);
    for(int i =7; i<=11; i++){
        precio[i]=p;
    }
    for(int i =17; i<=19; i++){
        precio[i]=p;
    }
}
float leeyvalidaFloat(float lim){
    float dato;
    scanf("%f", &dato);
    while(dato<lim){
        printf("Error. Numero icorrecto, reingrese: ");
        scanf("%f", &dato);
    }
    return dato;
}
void inicializarVec(float vec[], float valor, int limite){
    for(int i=0; i<limite; i++){
        vec[i]=valor;
    }
}