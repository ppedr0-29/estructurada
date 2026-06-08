/*6.8 Se dispone de un archivo que contiene información de los vuelos realizados por las distintas aerolíneas a lo
largo del mes. El archivo se denomina Vuelos.dat y guarda los registros con la siguiente estructura:
• Código Aerolínea (alfanumérico de 10 caracteres máximo)
• Día (entero)
• Número de Vuelo (entero)
• Costo del pasaje (real)
• Pasajeros (inicialmente en el archivo viene en 0)
Luego se dispone de un segundo archivo llamado Pasajeros.dat que incluye la información de los viajeros del mes
para la aerolínea con código “Aero1”, el archivo contiene los siguientes campos:
• DNI (entero)
• Número de Vuelo (entero)
Se desea realizar un programa que actualice la cantidad de pasajeros de la aerolínea con código “Aero1”
con la información de los pasajeros que realizaron los viajes. Tenga en cuenta que los números de vuelo se
repiten entre las distintas aerolíneas. */

#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include <conio.h>

typedef struct 
{
    char codigo[11];
    int dia;
    int numero;
    float costo;
    int pasajeros;
}Vuelo;

typedef struct 
{
    int dni;
    int numero;
}Pasaje;

long busqueda(FILE*, int, Vuelo *);
void mostrarV(FILE*);
void mostrarP(FILE*);

int main(){
    FILE*archV;
    FILE*archP;
    Vuelo datosV;
    Pasaje datosP;
    Vuelo *pdatosV=&datosV;
    long pos;
    archV=fopen("VUELOS.dat","r+b");
    archP=fopen("PASAJEROS.dat", "rb");
    if(archP==NULL||archV==NULL){
        printf("Error al abrir el archivo...");
        getch();
        exit(1);
    }
    fread(&datosP, sizeof(datosP), 1, archP);
    while(!feof(archP)){
        pos=busqueda(archV, datosP.numero, pdatosV);
        if(pos!=-1){
                datosV.pasajeros++;
                fseek(archV, pos, SEEK_SET);
                fwrite(&datosV, sizeof(datosV), 1, archV);
                fflush(archV);
            }
        
        fread(&datosP, sizeof(datosP), 1, archP);
    }  

    mostrarP(archP);
    mostrarV(archV);
    fclose(archP);
    fclose(archV);
    return 0;
}
void mostrarP(FILE*arch){
    Pasaje datos;
    rewind(arch);
    printf("--------PASAJEROS AERO 1----------\n");
    printf("DNI\tNumero\n");
    fread(&datos, sizeof(datos), 1, arch);
    while(!feof(arch)){
        printf("%8d\t%-6d\n", datos.dni, datos.numero);
        fread(&datos, sizeof(datos), 1, arch);
    }
}
void mostrarV(FILE*arch){
    Vuelo datos;
    rewind(arch);
    printf("--------VUELOS----------\n");
    printf("CODIGO\tNUMERO\tPASAJEROS\n");
    fread(&datos, sizeof(datos), 1, arch);
    while(!feof(arch)){
        printf("%6s\t%-6d\t%9d\n", datos.codigo, datos.numero, datos.pasajeros);
        fread(&datos, sizeof(datos), 1, arch);
    }
}
long busqueda(FILE*arch, int codigo, Vuelo *vec){
    long pos =-1;
    Vuelo datos;
    int flag =0;
    rewind(arch);
    fread(&datos, sizeof(datos), 1, arch);
    while(!feof(arch)&&flag==0){
        if(datos.numero==codigo && strcmpi(datos.codigo,"Aero1")==0){
            flag=1;
            pos=ftell(arch)-sizeof(datos);
            *vec=datos;
        }
        fread(&datos, sizeof(datos), 1, arch);
    }
    return pos;
}
