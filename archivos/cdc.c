/*1-Crear el archivo binario “ventas.dat” con las ventas efectuadas en el mes de abril de los productos. 
La información de las ventas es la siguiente y está ordenada por código de producto:
Código (entero)
Cantidad vendida (entero)
Día de venta (entero)
2-Realizar la lógica correcta para informar la cantidad total vendida y la cantidad de ventas para cada producto utilizando el archivo “ventas.dat”.*/


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct
{
    int codigo;
    int cantV;
    int diaV;
}Ventas;


int main(){
    Ventas datos;
    FILE *arch;
    int codAnt, cantTot=0, cantXProd=0;
    arch=fopen("ventas.dat", "rb");
    if (arch==NULL)
    {
        printf("Error al abrir el archivo.");
        getch();
        exit(1);
    }
    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch))
    {
        codAnt=datos.codigo;
        cantTot=0;
        cantXProd=0;
        while (codAnt==datos.codigo && !feof(arch))
        {
            cantTot+=datos.cantV;
            cantXProd++;
            fread(&datos, sizeof(datos), 1, arch);
        }
        printf("La cantidad total vendida del producto %d : %d\n", codAnt, cantTot);
        printf("La cantidad de ventas del producto %d: %d\n", codAnt, cantXProd);
    }
    
    fclose(arch);

    return 0;
}