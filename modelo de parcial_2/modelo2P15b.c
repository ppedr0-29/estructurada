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
stock y precio unitario. El nombre de cada uno de estos archivos debe ser el nombre del rubro con extensión dat

abrir archivo r+b
ingreso de codigo
while(cod!=0){
    pos=busqueda(){
        if(pos!=-1){
            pedir cantidad
            stock+=cantidad;
            fseek;
            fwrite
            fflush
        }
        ingreso codigo
    }
}

cdc(FILE *arch){
    FILE *archRubro;
    PROD datos;
    char rubroAnt[];
    char nombrearch[25];
    rewind();
    fread():
    
    while(!feof(arch)){

        strcpy(rubroAnt,datos.rubro);
        strcpy(nombrearch,rubroAnt);
        strcat(nombrearch, ".dat");
        archRubro=abrirarchivo(nombrearch, "wb")
        while(!feof && strcmpi(rubroAnt, datos.rubro)==0){
            info.codigo=datos.codigo
            info.stock=datos.stock
            info.precio=datos.precio
            fwrite(info, archRubro);
            fread(datos, arch)
        }
        fclose(archRubro);
    }
}
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct
{
    int codProd;
    char desc[31];
    char rubro[21];
    float precioU;
    int stock;
}PROD;
typedef struct
{
    int codProd;
    float precioU;
    int stock;
}ARCHIVO;

FILE *abrirArchivo(char [], char []);
void procesarArchivo();
long busqueda(FILE *, PROD *, int );
void leeyvalInt(int , int *);
void cdc(FILE *);

int main(){
    procesarArchivo();

    return 0;
}

void cdc(FILE *arch){
    ARCHIVO info;
    FILE *archRubro;
    PROD datos;
    char rubroAnt[21];
    char nombreArch[25];
    rewind(arch);
    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch))
    {
        strcpy(rubroAnt, datos.rubro);
        strcpy(nombreArch, rubroAnt);
        strcat(nombreArch, ".dat");
        archRubro=abrirArchivo(nombreArch, "wb");
        while (!feof(arch) && strcmpi(rubroAnt, datos.rubro)==0)
        {
            info.codProd=datos.codProd;
            info.precioU=datos.precioU;
            info.stock=datos.stock;
            fwrite(&info, sizeof(info), 1, archRubro);
            fread(&datos, sizeof(datos), 1, arch);
        }
        fclose(archRubro);
    }
    
}

void procesarArchivo(){
    FILE *arch;
    arch=abrirArchivo("Productos.dat", "r+b");
    PROD datos;
    PROD *pdatos=&datos;
    ARCHIVO info;
    int cant;
    long pos;
    printf("Ingrese codigo del producto: ");
    leeyvalInt(0, &info.codProd);
    while (info.codProd!=0)
    {
        pos=busqueda(arch, pdatos, info.codProd);
        if (pos!=-1)
        {
            printf("Ingrese la cantidad: ");
            leeyvalInt(0, &cant);
            datos.stock+=cant;
            fseek(arch, pos, SEEK_SET);
            fwrite(&datos, sizeof(datos), 1, arch);
            fflush(arch);
            printf("Stock actualizado.");
        }
        printf("Ingrese codigo del producto: ");
        leeyvalInt(0, info.codProd);
    }
    cdc(arch);
    fclose(arch);
}

long busqueda(FILE *arch, PROD *pdatos, int cod){
    PROD datos;
    long pos=-1;
    int flag=0;
    rewind(arch);
    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch) && flag==0)
    {
        if (datos.codProd==cod)
        {
            flag=1;
            pos=ftell(arch)-sizeof(datos);
            *pdatos=datos;
        }
        fread(&datos, sizeof(datos), 1, arch);
    }
    return pos;
}

void leeyvalInt(int lim, int *dato){
    scanf("%d", dato);
    while (*dato<lim)
    {
        printf("Error. Reingrese: ");
        scanf("%d", dato);
    }
}

FILE *abrirArchivo(char nombre[], char tipo[]){
    FILE *arch;
    arch=fopen(nombre, tipo);
    if (arch==NULL)
    {
        printf("Error.");
        getch();
        exit(1);
    }
    return arch;
}

