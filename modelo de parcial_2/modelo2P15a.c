/*En un supermercado se tiene un archivo de productos "Productos.dat", ordenado alfabéticamente por código de rubro, 
con el siguiente diseño de registro:
Código de producto (entero)
Descripción (cadena de 30 caracteres)
Código de rubro (cadena de 20 caracteres, por ejemplo: LÁCTEOS, CONGELADOS, etc.)
Precio unitario (real)
Stock (int)
Se pide hacer un programa para:
Incrementar el stock de productos ingresando código y cantidad a incrementar por teclado. 
El programa debe permitir incrementar el stock de varios productos finalizando con un código de producto igual a 0.
Una vez actualizado el archivo "Productos.dat", generar un archivo de productos por rubro, donde cada registro tenga código de producto, 
stock y precio unitario. El nombre de cada uno de estos archivos debe ser el nombre del rubro con extensión dat*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<conio.h>

typedef struct 
{
    int cod;
    char descripcion[31];
    char rubro[21];
    float precio;
    int stock;
}PRODUCTOS;
typedef struct 
{
    int cod;
    int stock;
    float precio;
}PRODUCTOS_RUBRO;

FILE *abrirArchivo(char [], char []);
void leeyvalidaInt(int* , int );
long busqueda(FILE * , int , PRODUCTOS*);
void procesarArchivo();
void corteDeControl();

int main(){
    procesarArchivo();
    corteDeControl();
    return 0;
}

void corteDeControl(){
    FILE*arch=abrirArchivo("productos.dat", "rb");
    FILE*archR;
    PRODUCTOS datos;
    PRODUCTOS_RUBRO prod;
    char rubroAnt[21];
    char nombreArch[25];
    fread(&datos, sizeof(datos), 1, arch);
    while(!feof(arch)){
        strcpy(rubroAnt, datos.rubro);
        strcpy(nombreArch, rubroAnt);
        strcat(nombreArch, ".dat");
        archR=abrirArchivo(nombreArch, "wb");
        while(!feof(arch) && strcmpi(datos.rubro, rubroAnt)==0){
            prod.cod=datos.cod;
            prod.precio=datos.precio;
            prod.stock=datos.stock;
            fwrite(&prod, sizeof(prod), 1, archR);
            fread(&datos, sizeof(datos), 1, arch);
        }
        fclose(archR);
    }
}

void procesarArchivo(){
    FILE *arch=abrirArchivo("productos.dat", "r+b");
    PRODUCTOS datos;
    int cod, cant;
    long pos;
    printf("Ingrese el codigo: ");
    leeyvalidaInt(&cod, 0);
    while(cod!=0){
        pos=busqueda(arch, cod, &datos);
        if(pos!=-1){
            printf("Ingrese la cantidad: ");
            leeyvalidaInt(&cant, 1);
            datos.stock+=cant;
            fseek(arch, pos, SEEK_SET);
            fwrite(&datos, sizeof(datos), 1, arch);
            fflush(arch);
            printf("Ingrese el codigo: ");
        }else{
            printf("No existe, reingrese: ");
        }
        leeyvalidaInt(&cod, 0);
    }
    fclose(arch);
}
long busqueda(FILE * arch, int cod, PRODUCTOS*datos){
    long pos=-1;
    int flag=0;
    PRODUCTOS info;
    rewind(arch);
    fread(&info, sizeof(info), 1, arch);
    while(!feof(arch) && flag ==0){
        if(info.cod==cod){
            flag =1;
            pos=ftell(arch)-sizeof(info);
            *datos=info;
        }
        fread(&info, sizeof(info), 1, arch);
    }
    return pos;
}
void leeyvalidaInt(int* dato, int lim){
    scanf("%d", dato);
    while(*dato<lim){
        printf("Error, reingrese: ");
        scanf("%d", dato);
    }
}

FILE *abrirArchivo(char nombre[], char tipo[]){
    FILE * arch = fopen(nombre, tipo);
    if(arch == NULL){
        printf("Error al abrir el archivo");
        getch();
        exit(1);
    }
    return arch;
}

