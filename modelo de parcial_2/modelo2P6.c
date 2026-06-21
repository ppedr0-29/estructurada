/*Tenías un archivo Stock.dat que guardaba la info de los productos. El struct para los productos era: 
código de artículo (char[]), descripción (char[]),  tipo (char) y precio (float).
Tenías que actualizar el precio:
-Si el tipo era 'P', tenías que pedir que ingrese un nuevo precio (verificar con un do while que no pase precio<0) 
y actualizarlo.
-Si el tipo era 'H', había que sumarle un 8% al precio que ya estaba.
La actualización terminaba cuando se ingresaba como código "SALE".
Si el código de artículo que ingresbas no existía, tenías que guardarlo en Errores.dat. 
Ahí solo se guardaba el código, nada más (el struct de errores era solo un char[] para el código). Si ya habias
 guardado un codigo de articulo como error anteriormente, no se vuelve a guardar.
No pedían informar nada al final.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct 
{
    char codigo[4];//asumo que es de 3
    char descripcion[31];//asumo que de 30
    char tipo;
    float precio;
}STOCK;
typedef struct 
{
    char codigo[4];
}ERROR;


void leeyvalidaFloat(float * , float );
FILE*abrirArchivo(char [], char []);
void errores(char []);
void leerTexto(char [], int );
void leeyvalidaTexto(char [], int);
long busqueda(FILE*, char [], STOCK*);
void procesarArchivos();


int main(){
    procesarArchivos();
    return 0;
}

void procesarArchivos(){
    FILE*arch=abrirArchivo("stock.dat", "r+b");
    STOCK datos;
    long pos;
    printf("Ingrese el codigo: ");
    leeyvalidaTexto(datos.codigo, 4);
    while(strcmpi(datos.codigo, "SALE")!=0){
        pos=busqueda(arch, datos.codigo, &datos);
        if(pos==-1){
            errores(datos.codigo);
        }else{
            if(datos.tipo=='P'){
                printf("Ingrese el nuevo precio: ");
                leeyvalidaFloat(&datos.precio, 0);
            }else if(datos.tipo=='H'){
                    datos.precio*=1.08;
            }
            fseek(arch, pos, SEEK_SET);
            fwrite(&datos, sizeof(datos),1, arch);
            fflush(arch);
        }
        printf("Ingrese el codigo: ");
        leeyvalidaTexto(datos.codigo, 4);
    }
    fclose(arch);
}

long busqueda(FILE*arch, char codigo[], STOCK*pdatos){
    long pos=-1;
    int flag =0;
    STOCK datos;
    rewind(arch);
    fread(&datos, sizeof(datos), 1, arch);
    while(!feof(arch) && flag==0){
        if(strcmpi(datos.codigo, codigo)==0){
            flag =1;
            pos=ftell(arch)-sizeof(datos);
            *pdatos=datos;
        }
        else{
            fread(&datos, sizeof(datos), 1, arch);
        }
    }
    return pos;
}

void leerTexto(char texto[], int largo){
    fgets(texto, largo, stdin);
    int i=0;
    while(texto[i]!='\0'){
        if(texto[i]=='\n'){
            texto[i]='\0';
        }
        i++;
    }
}
void leeyvalidaTexto(char texto[], int largo){
    leerTexto(texto, largo);
    while(strlen(texto)==0){
        printf("el texto no puede ser vacio.");
        leerTexto(texto, largo);
    }
}

void errores(char codigo[]){
    FILE*arch=abrirArchivo("errores.dat", "a+b");
    ERROR dato;
    int flag=0;
    fread(&dato, sizeof(dato), 1, arch);
    while(!feof(arch)&&flag==0){
        if(strcmpi(dato.codigo, codigo)==0){
            flag=1;
        }
    fread(&dato, sizeof(dato), 1, arch);
    }
    if(flag==0){
        //fseek(arch, 1, SEEK_END); no es necesario porque el modo a+b siempre escribe al final.
        strcpy(dato.codigo, codigo);
        fwrite(&dato, sizeof(dato), 1, arch);
        fflush(arch);
    }
    fclose(arch);
}
FILE*abrirArchivo(char nombre[], char tipo[]){
    FILE*arch;
    arch=fopen(nombre, tipo);
    if(arch==NULL){
        printf("Error al abrir el archivo...");
        getch();
        exit(1);
    }
    return arch;
}
void leeyvalidaFloat(float * dato, float lim){
    do{
        scanf("%f", dato);
        if(*dato<lim)
            printf("REingrese: ");
    }while(*dato<lim);
}

