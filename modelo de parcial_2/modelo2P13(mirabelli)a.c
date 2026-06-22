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
Validar todos los datos que ingresan por teclado según lo indicado.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct{
    char codigo [4];
    char descripcion [51];
    int stock;
}PROD;

typedef struct{
    char codigo [4];
    int cout;
}ERROR;

void leerTexto(char [], int);
void leeyValidaTex(char [], int);

FILE * abrirArchivo (char [], char []);
void INFORME(int, int);
void leeyValidaInt(int*, int);
long busqueda(FILE *, char [], PROD *);
void Errores(ERROR);
long busquedaE(FILE *arch, char cod [], ERROR *pdato);

int main (){
    procesarArchivos();
    return 0;
}

void leeyValidaInt(int* dato, int lim){
    scanf("%d", dato);
    while(*dato < lim){
        Printf("Reingrese: ");
        scanf("%d", dato);
    }
}

void procesarArchivos(){
    FILE *arch = abrirArchivo("stock.dat", "r+b");
    PROD datos;
    ERROR errores;
    long pos;
    int coutC = 0, coutE = 0;

    printf("Ingrese el codigo: ");
    leeyValidaTex(errores.codigo, 4);
    while(stricmp(errores.codigo, "FIN") != 0){
        printf("Ingrese la cout: ");
        leeyValidaInt(&errores.cout, 0);
        pos = busqueda(arch, errores.codigo, &datos);

        if(pos == -1){
            Errores(errores);
            coutE++;
        }else{
            datos.stock += errores.cout;
            coutC++;
            fseek(arch, pos, SEEK_SET);
            fwrite(&datos, sizeof(datos), 1, arch);
            fflush(arch);
        }
        printf("Ingrese el codigo: ");
        leeyValidaTex(errores.codigo, 4);
    }
    INFORME(coutC, coutE);
}

FILE * abrirArchivo (char nombre [], char tipo[]){
    FILE*arch = fopen(nombre,tipo);
    if(arch == NULL){
        printf("Error al abrir el archivo");
        getch();
        exit(1);
    }
    return arch;
}

void INFORME(int coutC, int coutE){
    printf("Se realizaron %d compras exitosas y %d fueron errores", coutC, coutE);
}

void leeyValidaTex(char texto [], int largo){
    leerTexto(texto, largo);
    while(strlen(texto) == 0){
        printf("ERROR, el texto esta vacio");
        leerTexto(texto, largo);
    }
}

void leerTexto(char texto [], int largo){
    fflush(stdin);
    fgets(texto, largo, stdin);
    int i = 0;
    while(texto[i] != '\0'){
        if(texto[i] == '\n')
            texto[i] = '\0';
        i++;
    }
}

long busqueda(FILE *arch, char cod [], PROD *pdato){
    long pos = -1;
    int flag = 0;
    PROD datos;
    rewind(arch);
    fread(&datos, sizeof(datos), 1, arch);
    while(!feof(arch) && flag == 0){
        if(stricmp(datos.codigo, cod) == 0){
            flag = 1;
            pos = ftell(arch) - sizeof(datos);
            *pdato = datos;
        }
        fread(&datos, sizeof(datos), 1, arch);
    }
    return pos;
}

long busquedaE(FILE *arch, char cod [], ERROR *pdato){
    long pos = -1;
    int flag = 0;
    ERROR datos;
    rewind(arch);
    fread(&datos, sizeof(datos), 1, arch);
    while(!feof(arch) && flag == 0){
        if(stricmp(datos.codigo, cod) == 0){
            flag = 1;
            pos = ftell(arch) - sizeof(datos);
            *pdato = datos;
        }
        fread(&datos, sizeof(datos), 1, arch);
    }
    return pos;
}

void Errores(ERROR errores){
    FILE *arch = fopen("errores.dat", "r+b");
    if(arch == NULL){
        arch = abrirArchivo("errores.dat", "w+b");
    }
    ERROR datos;
    fread(&datos, sizeof(datos), 1, arch);
    long pos = busquedaE(arch, errores.codigo, &datos);

    if(pos == -1){
        fseek(arch, pos, SEEK_END);
        fwrite(&errores, sizeof(errores), 1, arch);
        fflush(arch);
    }else{
        errores.cout += datos.cout;
        fseek(arch, pos, SEEK_END);
        fwrite(&errores, sizeof(errores), 1, arch);
        fflush(arch);
    }
}