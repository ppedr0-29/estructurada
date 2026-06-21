/*La empresa SALES dispone de un archivo llamado Stock.dat que contiene la información de los productos que vende.
El archivo contiene la siguiente información:
Código de artículo (string de 4 caracteres)
Descripción (50 caracteres máximo)
Stock (entero)
Luego se ingresan por teclado las compras realizadas indicando:
Código de artículo (string de 4 caracteres)
Cantidad vendida (entero mayor a cero)
La carga por teclado de las ventas finaliza con un código de artículo "SALE".
Por cada venta se debe controlar si existe el artículo (resolver en una Función llamada BUSCAR) si no existe solicitar nuevamente y si existe, 
actualizar el stock de dicho producto, sino hay stock suficiente grabar un registro en un archivo Errores.dat con la cantidad que no pudo vender, 
dicho registro debe contener:
Código de artículo
Cantidad
Si ya hay un registro previo en dicho archivo de errores con el mismo artículo debe incrementarse la cantidad. Informar al final la cantidad de 
ventas realizadas y la cantidad de ventas no realizadas utilizando la función INFORME.
Validar todos los datos que ingresan por teclado según lo indicado.
El código debe estar correctamente identado.

----PSEUDOCODIGO----
abrir archivo stock.dat r+b


ingreso codigo
while(codigo!=SALE){
    pos=busqueda()
    while(pos==-1){
        reingreso codigo
    }
    ingreso cantidad
    if(cant>stock){
        cantnoventas++;
        errores();
    }else{
        stock-=cant;
        cantventas++;
        fseek(pos)
        fwrite(stock)
        fflush(stock)
    }
    ingreso codigo
}
errores(ERRORES datos){
    ERRORES info;
    abrir archivo errores.dar w+b
    fread(errores)
    while(!feof && flag==0){
        if(datos.codigo==info.codigo){
            flag=1
            pos=ftell(arch)-sizeoff(info);
        }
        fread()
    }
    if(flag==0){
        fseek(arch, 0, seek_end)
        fwrite(datos);
    }else{
        info.cant+=datos.cant;
        fseek(arch,pos,seekset);
        fwrite(arch);
        fflush(arch);
    }

informe(){
    printf cantventas;
    printf cantnoventas;
}

}

}
*/



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

typedef struct
{
    char codArt[5];
    char desc[51];
    int stock;
}STOCK;

typedef struct
{
    char codArt[5];
    int cantVend;
}ERRORES;

void errores(ERRORES );
void procesarArchivo();
long BUSCAR(FILE *, STOCK *, char []);
void leerTexto(char [], int );
void leeyvalTexto(char [], int );
FILE* abrirArchivo(char [], char []);
void informe(int , int );
void leeyvalInt(int , int *);

int main(){
    procesarArchivo();

    return 0;
}

void errores(ERRORES info){
    ERRORES datos;
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
    if(flag==0){
        fseek(archE, 0, SEEK_END);
        fwrite(&info, sizeof(info), 1, archE);
    }else{
        info.cantVend+=datos.cantVend;
        fseek(archE,pos,SEEK_SET);
        fwrite(&info, sizeof(info), 1, archE);
        fflush(archE);
    }
    
    fclose(archE);
}

void procesarArchivo(){
    FILE *arch;
    STOCK datos;
    STOCK *pdatos=&datos;
    ERRORES info;
    int *pcant=&info.cantVend;
    long pos;
    int cantVentas=0, cantnoVentas=0;
    arch=abrirArchivo("stock.dat", "r+b");
    printf("Ingrese codigo del producto(SALE para terminar): ");
    leeyvalTexto(info.codArt, 5);
    while (strcmpi(info.codArt, "SALE")!=0)
    {
        pos=BUSCAR(arch, pdatos, info.codArt);
        while (pos==-1 && strcmpi(info.codArt, "SALE")!=0)
        {   
            printf("Reingrese el codigo del producto(SALE para terminar): ");
            leeyvalTexto(info.codArt, 5);
            pos=BUSCAR(arch, pdatos, info.codArt);
        }
        if (strcmpi(info.codArt, "SALE")!=0)
        {
            printf("Ingrese la cantidad vendida: ");
            leeyvalInt(0,pcant);
        
            if (*pcant>datos.stock)
            {
                cantnoVentas++;
                errores(info);
            }else{
                datos.stock-=*pcant;
                cantVentas++;
                fseek(arch, pos, SEEK_SET);
                fwrite(&datos, sizeof(datos), 1, arch);
                fflush(arch);
            }
        printf("Ingrese codigo del producto(SALE para terminar): ");
        leeyvalTexto(info.codArt, 5);
        }
        
    }
    informe(cantVentas, cantnoVentas);

    fclose(arch);
}

void leeyvalInt(int lim, int *dato){
    scanf("%d", dato);
    while (*dato<=lim)
    {
        printf("Error. Reingrese:");
        scanf("%d", dato);
    }
}

long BUSCAR(FILE *arch, STOCK *pdatos, char cod[]){
    STOCK datos;
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

void informe(int cantV, int cantNV){
    printf("Se realizaron %d ventas, y no puedieron completarse %d ventas", cantV, cantNV);
}