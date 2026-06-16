/*6.14 La empresa de colectivos línea 166 desea saber cuánto debe cobrar en un mes determinado según los
viajes realizados y registrados en el sistema mediante la tarjeta SUBE para ello dispone de un archivo
de viajes los viajes del mes que está ordenado por número de Interno (colectivo) que contiene la siguiente
información:
• Número de Interno (entero)
• Número tarjeta SUBE (entero)
• Código de Tarifa (texto de 10 caracteres máximo)
• Día (entero)
• Hora (entero)
Se dispone de un segundo archivo llamado tarifas.dat que contiene información de las tarifas por cada mes con
la siguiente estructura:
• Mes (entero)
• Código de Tarifa (texto de 10 caracteres máximo)
• Precio (float)
Se sabe que como máximo se manejan 8 tarifas distintas en cada mes.
Se solicita:
a. Ingresar por teclado el mes a procesar y recuperar las tarifas correspondientes
b. Mostrar el importe total a cobrar por la empresa
c. Generar un archivo que contenga la cantidad de viajes y la recaudación de cada interno en el mes.
d. Informar el interno que realizó menos cantidad de viajes
e. Por cada interno mostrar cuantos viajes se realizaron por cada tipo de tarifa ordenado por cantidad de
viajes en forma descendente.
Funciones obligatorias:
• CargaTarifas: que levanta a un vector en memoria las tarifas del mes ingresado por teclado.
• OrdenarViajes: para ordenar los viajes según lo pedido en el punto e.
• MostrarViajes: para mostrar en forma de listado los viajes ordenados del punto e.*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef struct
{
    int numInt;
    int numSube;
    char codTarifa[11];
    int dia;
    int hora;
}VIAJES;

typedef struct
{
    int mes;
    char codTarifa[11];
    float precio;
}TARIFA;

int main(){
    VIAJES datos;
    TARIFA total[8];
    int mesAux;
    printf("Ingrese mes a tarifar(1-12):");
    mesAux=leeyvalE2(1,12);
    int cantTarifas=CargaTarifas(total,mesAux);
}

int CargaTarifas(TARIFA v[], int mes){
    FILE *arch;
    TARIFA info;
    int i=0;
    arch=fopen("tarifas.dat", "rb");
    //rewind(arch);
    fread(&info, sizeof(info), 1, arch);
    while (!feof(arch) && i<8)
    {
        if (mes==info.mes)
        {
            i++;
            v[i]=info;
        }
        fread(&info, sizeof(info), 1, arch);
    }
    fclose(arch);
    return i;
}

int leeyvalE2(int min, int max){
    int dato;
    scanf("%d", &dato);
    while (dato<min || dato>max)
    {
        printf("Error. Reingrese:");
        scanf("%d", &dato);
    }
    return dato;
}
