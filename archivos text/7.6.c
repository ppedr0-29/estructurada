/*7.6 Dado un archivo ventas.csv con ventas de productos que contiene producto;precio;cantidad;sucursal siendo
• Producto un string correspondiente al código de producto de máximo 10 caracteres
• Precio un valor real con el precio unitario el producto
• Cantidad la cantidad de productos vendida (entero)
• Sucursal, el código la sucursal de la venta (entero)
Calcular:
• La cantidad total de ventas realizadas
• La cantidad total de productos vendidos
• El importe total vendido por cada sucursal (usar un vector dinámico en memoria que pueda ir
creciendo para guarda estar información)
• Generar un archivo resumenVenta.txt que contenga, la información de los 3 items anteriores
Nota: para realizar los cálculos debe recuperar cada registro del archivo y pasarlo a una estructura en memoria*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct
{
    char codProd[11];
    float precio;
    int cant;
    int sucursal;
}Ventas;

int busqueda(int [], int , int );

int main(){
    FILE* arch;
    Ventas datos;
    int cantV=0, cantP=0, cantSuc=1;
    int pos;
    float *vDatos;
    vDatos=(float*)malloc(cantSuc*sizeof(float));
    int *vSucursales;
    vSucursales = (int*)malloc(cantSuc * sizeof(int));
    arch=fopen("ventas.csv", "rt");
    if (arch==NULL)
    {
        printf("Error");
        getch();
        exit(1);
    }
    fscanf(arch, "%s;%f;%d;%d", datos.codProd, &datos.precio, &datos.cant, &datos.sucursal);
    vSucursales[0]=datos.sucursal;
    vDatos[0]=0;
    while (!feof(arch))
    {
        cantV++;
        cantP+=datos.cant;
        pos=busqueda(vSucursales, datos.sucursal, cantSuc);
        if (pos!=-1)
        {
            vDatos[pos]+=datos.precio*datos.cant;
        }else{
            cantSuc++;
            vDatos=(float*)realloc(vDatos,cantSuc*sizeof(float));
            vSucursales=(int*)realloc(vSucursales,cantSuc*sizeof(int));
            vDatos[cantSuc-1]=datos.precio*datos.cant;
            vSucursales[cantSuc-1]=datos.sucursal;
        }
        fscanf(arch, "%s;%f;%d;%d", datos.codProd, &datos.precio, &datos.cant, &datos.sucursal);
    }
    FILE* archR;
    archR=fopen("resumenVentas.txt", "wt");
    if (archR==NULL)
    {
        printf("Error.");
        getch();
        exit(1);
    }
    fprintf(archR, "La cantidad total de ventas realizadas %d\n", cantV);
    fprintf(archR, "La cantidad de produtos vendidos %d\n", cantP);
    for (int i = 0; i < cantSuc; i++)
    {
        fprintf(archR,"En la sucursal %d se vendio $%.2f\n", vSucursales[i], vDatos[i]);
    }
    fclose(arch);
    fclose(archR);
    free(vSucursales);
    free(vDatos);
    return 0;
}

int busqueda(int v[], int dato, int ce){
    int pos=-1;
    int i=0;
    while (pos==-1 && i<ce)
    {
        if (v[i]==dato)
        {
            pos=i;
        }else{
            i++;
        }
        
    }
    return pos;
}