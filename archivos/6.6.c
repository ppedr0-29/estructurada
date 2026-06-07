/*6.6 Dado el archivo productos.dat con la siguiente estructura:
• Código (entero)
• Precio (float)
• Descripción (de hasta 50 caracteres)
Realizar un programa que permita eliminar productos dado su código*/
#include<stdio.h>
#include<stdlib.h>
#include <conio.h>
#include <string.h>

typedef struct 
{
    int codigo;
    float precio;
    char desc[51];
}prod;

int leeyvalidaIntE2(int, int );
void mostrar(FILE*);

int main(){
    prod datos;
    FILE *arch;
    FILE *archT;
    int cod, encontrado=0;
    arch=fopen("PRODUCTOS.dat", "rb");
    archT=fopen("PRODUCTOS.tmp", "wb");
    printf("arch: %p\n", arch);
    printf("archT: %p\n", archT);
    if(arch ==NULL || archT == NULL){
        printf("Error al abrir el archivo");
        getch();
        exit (1);
    }
    mostrar(arch);
    printf("\nIngrese el codigo del producto a eliminar:");
    cod=leeyvalidaIntE2(1000,9999);
    rewind(arch);
    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch))
    {
        if (datos.codigo!=cod)
        {
            fwrite(&datos, sizeof(datos), 1, archT);
        }else{
            encontrado=1;
        }
        fread(&datos, sizeof(datos), 1, arch);
    }
    fclose(arch);
    fclose(archT);
    if (encontrado==1)
    {   
        remove("PRODUCTOS.dat");
        rename("PRODUCTOS.tmp", "PRODUCTOS.dat");
        printf("Producto eliminado.\n");
    }else{
        printf("Codigo inexistente\n");
        remove("PRODUCTOS.tmp");
    }
    arch=fopen("PRODUCTOS.dat", "rb");
    if(arch ==NULL){
        printf("Error al abrir el archivo");
        getch();
        exit (1);
    }
    mostrar(arch);
    fclose(arch);

    return 0;
}

void mostrar(FILE*arch){
    prod datos;
    rewind(arch);
    fread(&datos, sizeof(datos), 1, arch);
    printf("CODIGO\tPRECIO\tDESCRIPCION\n");
    while(!feof(arch)){
        printf("%6d\t$%-6.2f\t%10s\n", datos.codigo, datos.precio, datos.desc);
        fread(&datos, sizeof(datos), 1, arch);
    }
}


int leeyvalidaIntE2(int min, int max){
    int dato;
    scanf("%d", &dato);
    while(dato<min || dato>max){
        printf("Error. reingrese: ");
        scanf("%d", &dato);
    }
    return dato;
}