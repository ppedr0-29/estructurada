/*La empresa TRASH dispone de un archivo llamado Stock.dat que contiene la información de los productos 
que comercializa.
El archivo contiene la siguiente información:
Código de artículo (string de 3 caracteres)
Descripción (50 caracteres máximo)
Stock (entero)
Luego se ingresan por teclado las compras realizadas indicando:
Código de artículo (string de 3 caracteres)
Cantidad (entero mayor a cero)
La carga por teclado de las compras finaliza con un código de artículo "FIN".
Por cada compra se debe controlar si existe el articulo (resolver en una Función llamada BUSCAR) y si existe, 
actualizar el stock de dicho producto, sino existe el articulo grabar un registro en un archivo Errores.dat 
con la cantidad que no pudo registrar, dicho registro debe contener:
Código de artículo
Cantidad
Si ya hay un registro previo en dicho archivo de errores con el mismo artículo debe incrementarse la cantidad. 
Informar al final la cantidad de artículos actualizados y la cantidad de errores utilizando la función INFORME.
Validar todos los datos que ingresan por teclado según lo indicado.

abrir archivo Stock.dat r+b
ingreso codArt
while codart!=FIN{
    ingreso cantidad validada
    pos=busqueda()
    if(pos!=-1){
        cantArtAct++;
        stock+=cantidad
    }else{
        errores();
        cantErrores++;
    }
        ingresocodArt
}
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

typedef struct
{
    char codArt[4];
    char desc[51];
    int stock;
}PROD;

typedef struct
{
    char codArt[4];
    int cant;
}ERROR;

void errores(ERRORES );
void procesarArchivo();
long BUSCAR(FILE *, PROD *, char []);
void leerTexto(char [], int );
void leeyvalTexto(char [], int );
FILE* abrirArchivo(char [], char []);
void informe(int , int );
void leeyvalInt(int , int *);

int main(){
    procesarArchivo();
}

void errores(ERROR info){
    ERROR datos;
    FILE *archE;
    int flag=0;
    long pos;
    archE=fopen("Errores.dat", "r+b");
    if (archE==NULL)
    {
        archE=abrirArchivo("Errores.dat", "w+b");
    }
    fread(&datos, sizeof(datos), 1, archE);
    while (!feof(archE) && flag==0)
    {
        if (strcmpi(datos.codArt, info.codArt)==0)
        {
            flag=1;
            pos=ftell(archE)-sizeof(datos);
        }
        fread(&datos, sizeof(datos), 1, archE);
    }
    if (flag==0)
    {
        fseek(archE, 0, SEEK_END);
        fwrite(&info, sizeof(info), 1, archE);
        fflush(archE);
    }else{
        info.cant+=datos.cant;
        fseek(archE, pos, SEEK_SET);
        fwrite(&info, sizeof(info), 1, archE);
        fflush(archE);
    }
    fclose(archE);
}

void procesarArchivo(){
    FILE *arch;
    PROD datos;
    ERROR info;
    PROD *pdatos=&datos;
    int *pcant=&info.cant;
    long pos;
    int cantArtAct=0, cantErrores=0;
    arch=abrirArchivo("Stock.dat", "r+b");
    printf("Ingrese codigo del articulo: ");
    leeyvalTexto(info.codArt, 4);
    while (strcmpi(info.codArt, "FIN")!=0)
    {
        printf("Ingrese la cantidad comprada: ");
        leeyvalInt(0, pcant);
        pos=BUSCAR(arch, pdatos, info.codArt);
        if (pos!=-1)
        {
            datos.stock+=*pcant;
            cantArtAct++;
            fseek(arch, pos, SEEK_SET);
            fwrite(&datos, sizeof(datos), 1, arch);
            fflush(arch);
        }else{
            errores(info);
            cantErrores++;
        }
        printf("Ingrese codigo del articulo: ");
        leeyvalTexto(info.codArt, 4);
    }
    informe(cantArtAct, cantErrores);

    fclose(arch);
}

void informe(int cant, int cant2){
    printf("Se actualizar %d articulos, y %d fue la cantidad de errores", cant, cant2);
}

void leeyvalInt(int lim, int *dato){
    scanf("%d", dato);
    while (*dato<=lim)
    {
        printf("Error. Reingrese:");
        scanf("%d", dato);
    }
}

long BUSCAR(FILE *arch, PROD *pdatos, char cod[]){
    PROD datos;
    long pos=-1;
    int flag=0;
    rewind(arch);
    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch) && flag==0)
    {
        if (strcmpi(datos.codArt, cod)==0)
        {
            flag=1;
            pos=ftell(arch)-sizeof(datos);
            *pdatos=datos;
        }
        fread(&datos, sizeof(datos), 1, arch);
    }
    return pos;
}

void leerTexto(char texto[], int largo){
    fflush(stdin);
    fgets(texto, largo, stdin);
    int i=0;
    while (texto[i]!='\0')
    {
        if (texto[i]=='\n')
        {
            texto[i]='\0';
        }
        i++;
    }
}

void leeyvalTexto(char texto[], int largo){
    leerTexto(texto, largo);
    while (strlen(texto)==0)
    {
        printf("Reingrese: ");
        leerTexto(texto, largo);
    }
}

FILE* abrirArchivo(char nombre[], char tipo[]){
    FILE *arch;
    arch=fopen(nombre,tipo);
    if (arch==NULL)
    {
        printf("Error.");
        getch();
        exit(1);
    }
    return arch;
}