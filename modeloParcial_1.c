/*La empresa El Clavel que comercializa flores exóticas por mayor, desea analizar las ventas efectuadas
por sus 110 sucursales mensualmente a lo largo del país, en las principales ciudades.
Para ello, se tiene una lista para ingresar desde teclado con los datos de las 12 variedades de flores que
comercializa. Al comienzo del programa, por cada tipo de flor, se ingresa:
▪ Código de la variedad de la flor (entero, de 101 a 999)
▪ Precio de la flor por unidad (real, mayor que cero)
A continuación, ingresar el mes y año correspondiente a los datos a procesar.
Luego se ingresan los datos de las ventas del mes por teclado, con el siguiente detalle:
▪ Número de sucursal (entero, de 5001 a 5110)
▪ Código de la flor
▪ Cantidad vendida (entero, mayor que cero)
Estos datos no se ingresan ordenados y la lectura debe detenerse cuando se ingrese un número de
sucursal igual a 5000.
Se pide:
a. Informar los importes vendidos por cada sucursal con el siguiente diseño:
VENTAS DEL MES XX DE XXXX
Sucursal Importe vendido
xxx xxxx.xx
xxx xxxx.xx
…… …….
……. ……..
b. Código de la variedad de flor de la cual se vendieron más cantidad de flores. Si hubiere más
de una, informar la primera que aparezca en esa condición.
c. Informar cuántas sucursales vendieron flores por un importe superior al promedio de ventas
de todas las sucursales.
d. Informar el porcentaje de las flores de las cuales no se vendió nada en ninguna sucursal. */

#include<stdio.h>
#include <stdbool.h>

#define CANT_FLORES 12
#define CANT_SUC 110
#define COD_FLOR_MIN 101
#define COD_FLOR_MAX 999
#define PRECIO_MIN 0
#define NRO_SUC_MIN 5001
#define NRO_SUC_MAX 5110
#define NRO_SUC_CORTE 5000
#define CANT_MIN 0

void iniciarVecMin(int[], int, int);
int leeyValidaEntre2(int, int);
float leeyValidaFloat(float);
int leeyValidaInt(int);
int leeyValidaPorVector(int[], int);
int busqueda(int[], int, int);
void puntoA(int[], float[], int);
void puntoB(int[], int[], int);
void puntoC(float[], int[], int);
void puntoD(int[], int);
float promedio(float, int);



int main(){
    int codFlor[CANT_FLORES];
    float precio[CANT_FLORES]={0};
    int nroSucursal[CANT_SUC];
    int cantFlores[CANT_FLORES]={0};
    float importe[CANT_SUC]={0};
    int codigoFlor, nroSuc, cant, mes, anio, posFlor, posSuc;
    float precioUnidad;
    iniciarVecMin(nroSucursal, CANT_SUC, NRO_SUC_MIN);
    printf("\n//////Ingreso de datos por variedad de flor///////");
    for (int i=0;i<CANT_FLORES;i++){
        printf("\nIngrese codigo de flor:\t");
        codigoFlor=leeyValidaEntre2(COD_FLOR_MIN,COD_FLOR_MAX);
        printf("\nIngrese el precio por unidad:\t");
        precioUnidad=leeyValidaFloat(PRECIO_MIN);
        codFlor[i]=codigoFlor;
        precio[i]=precioUnidad;
    }
    printf("\n//////Ingreso de ventas del mes//////");
    printf("\nIngresar mes y anio con el siguiente formato mm/aaaa:\t");
    mes=leeyValidaEntre2(1,12);
    anio=leeyValidaInt(1900);
    printf("\nIngresar nro de sucursal(para finalizar ingrese %d):", NRO_SUC_CORTE);
    scanf("%d",&nroSuc);
    while(nroSuc!=NRO_SUC_CORTE){
        nroSuc=leeyValidaEntre2(NRO_SUC_MIN, NRO_SUC_MAX);
        printf("\nIngrese codigo de flor:\t");
        codigoFlor=leeyValidaPorVector(codFlor, CANT_FLORES);
        printf("\nIngrese la cantidad:\t");
        cant=leeyValidaInt(CANT_MIN);
        posFlor=busqueda(codFlor, CANT_FLORES, codigoFlor);
        posSuc=busqueda(nroSucursal, CANT_SUC, nroSuc);
        cantFlores[posFlor]+=cant;
        importe[posSuc]+=(cant*precio[posFlor]);
        printf("\nIngrese nro de sucursal(para finalizar ingrese %d):", NRO_SUC_CORTE);
        scanf("%d",&nroSuc);
    }
    printf("\nVentas del mes %d de %d", mes, anio);
    puntoA(nroSucursal, importe, CANT_SUC);
    puntoB(codFlor, cantFlores, CANT_FLORES);
    puntoC(importe, nroSucursal, CANT_SUC);
    puntoD(cantFlores, CANT_FLORES);
    return 0;
}

void iniciarVecMin(int vec[], int ce, int min){
    for(int i=0;i<ce;i++){
        vec[i]=(min+i);
    }
}

int leeyValidaEntre2(int min, int max){
    int dato;
    scanf("%d", &dato);
    while(dato<min || dato > max){
        printf("\nERROR-Ingrese un numero entre %d y %d", min, max);
        scanf("%d", &dato);
    }
    return dato;
}
float leeyValidaFloat(float lim){
    float dato;
    scanf("%f",&dato);
    while(dato<lim){
        printf("\nERROR-Ingrese un dato mayor o igual a %f", lim);
        scanf("%f", &dato);
    }
    return dato;
}
int leeyValidaInt(int lim){
    int dato;
    scanf("%d", &dato);
    while(dato<lim){
        printf("\nERROR-ingrese un dato mayor o igual a %d", lim);
        scanf("%d",&dato);
    }
    return dato;
}
int leeyValidaPorVector(int vec[], int ce){
    int dato;
    scanf("%d", &dato);
    while(busqueda(vec, ce, dato)==-1){
        printf("\nERROR-ese numero no se encuentra registrado, ingrese otro:");
        scanf("%d", &dato);
    }
    return dato;
}
int busqueda(int vec[], int ce, int dato){
    int pos=-1;
    int i=0;
    while(i < ce && vec[i] != dato)
        i++;
    if(i!=ce)
        pos=i;
    return pos;
}


void puntoA(int suc[], float importe[], int ce){
    printf("\n SUC\tIMPORTE");
    for(int i =0;i<ce;i++)
        printf("%4d\t%4.2f", suc[i], importe[i]);
}
void puntoB(int cod[], int cant[], int ce){
    int max=cant[0];
    int pos = 0;
    for(int i=0;i<ce;i++){
        if(cant[i]>max){
            max=cant[i];
            pos=i;
        }
    }
    printf("\n La flor que mas se vendio fue la %d con una cantidad total de %d", cod[pos], cant[pos]);
}
void puntoC(float importe[], int suc[], int ce){
    float prom;
    float acum=0;
    for(int i=0;i<ce;i++)
        acum+=importe[i];
    prom=promedio(acum, ce);
    printf("\n El promedio de ventas fue %f", prom);
    printf("\nLas sucursales que superaron el promedio son:");
    for(int i =0; i<ce;i++){
        if(importe[i]>prom)
            printf("\n%d", suc[i]);
    }
}
void puntoD(int cant[], int ce){
    float acum=0.0;
    float porcentaje;
    for(int i = 0; i<ce;i++){
        if(cant[i]==0)
            acum++;
    }
    porcentaje = (acum*100)/ce;
    printf("\nEl porcentaje de las flores que no se vendieron es de %2.2f%%", porcentaje);
}
float promedio(float acum, int cont){
    float prom=0.0;
    if(cont>0)  
        prom=acum/cont;
    return prom;
}