/*6.3 El archivo ventas.dat contiene información histórica de las ventas realizadas por una empresa desde el año
2014 al 2023. El formato de registro es el siguiente:
• Mes (entero)
• Año (entero)
• Dia (entero)
• Código de Producto (entero)
• Importe de la venta (real)
Se pide ingresar un rango de años y mostrar un cuadro ventas realizadas en cada mes de cada año. Por ejemplo,
si se ingresa desde 2020 a 2022 debe mostrar lo siguiente:
Mes 1 Mes 2 Mes 3 ……. Mes 12
2020 xxx xxx xxx xxx
2021 xxx xxx xxx xxx
2022 xxx xxx xxx xxx
Una vez configurados los años debe poder cambiarse la vista para en lugar de visualizar cantidad de ventas, ver el
detalle de importe por mes/año. El usuario podrá alternar las vistas las veces que quiera. Agregar una opción
para finalizar el programa.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct 
{
    int mes;
    int anio;
    int dia;
    int codigo;
    float importe;
}ventas;


int main (){
    ventas registro;
    FILE *arch;
    int anioI;
    int anioF;
    int mCantV[10][12]={{0}};
    float mImporte [10][12]={{0}};

    arch = fopen("VENTAS.dat", "rb");
    if(arch ==NULL){
        printf("Error al abrir el archivo...");
        getch();
        exit(1);
    }
    printf("Ingrese anio de comienzo (anio=0 para finalizar):");
    anioI=leeyValidaE2CF(2014,2023,0);
    while (anioI!=0)
    {
        printf("Ingrese anio de fin:");
        anioF=leeyValidaE2(2014,2023);
        fread(&registro, sizeof(registro), 1, arch);
        while(!feof(arch)){
            ////calculo anio. anio-2014= fila matriz 2014 =0, 2015=1
            if(registro.anio>=anioI && registro.anio<=anioF){
                mCantV[registro.anio-2014][registro.mes-1]++;
                mImporte[registro.anio-2014][registro.mes-1]+=registro.importe;
            }
            fread(&registro, sizeof(registro), 1, arch);
        }
        printf("///////// %-4s %4s %4s %4s %4s %4s %4s %4s %4s %4s %4s %4s",  "Mes1", "Mes2", "Mes3", "Mes4", "Mes5", "Mes6",
        "Mes7", "Mes8", "Mes9", "Mes10", "Mes11", "Mes12");
        for(int i=0; i<anioF-anioI;i++){
            for(int j=0; j<12;j++){
                printf("%d    %-4d %4d %4d %4d %4d %4d %4d %4d %4d %4d %4d %4d", anioI+i, mCantV[anioI+i][j]);
            }
            
        }
    }
    
    
}

int leeyValidaE2CF(int min, int max, int cf){
    int dato;
    scanf("%d", &dato);
    while((dato < min || dato > max) && dato != cf){
        printf("Error- Reingrese:");
        scanf("%d", &dato);
    }
    return dato;
}

int leeyValidaE2(int min, int max){
    int dato;
    scanf("%d", &dato);
    while(dato < min || dato > max){
        printf("Error- Reingrese:");
        scanf("%d", &dato);
    }
    return dato;
}