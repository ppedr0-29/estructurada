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

int main(){

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
        while (pos==-1)
        {   
            printf("Reingrese el codigo del producto(SALE para terminar): ");
            leeyvalTexto(info.codArt, 5);
            pos=BUSCAR(arch, pdatos, info.codArt);
        }
        if (strcmpi(info.codArt, "SALE")!=0)
        {
            do
            {
                printf("Ingrese la cantidad vendida: ");
                scanf("%d", pcant);
            } while (*pcant<0);
            if (*pcant>datos.stock)
            {
                cantnoVentas++;
                errores();
            }else{
                datos.stock-=*pcant;
                cantVentas++;
                fseek(arch, pos, SEEK_SET);
                fwrite(&datos, sizeof(datos), 1, arch);
                fflush(arch);
            }
        }
        printf("Ingrese codigo del producto(SALE para terminar): ");
        leeyvalTexto(info.codArt, 5);
    }
    
}


long BUSCAR(FILE *arch, STOCK *pdatos, char cod[]){
    STOCK datos;
    long pos;
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
    int i;
    while (texto[i]!='\0')
    {
        if (texto[i]=='\n')
        {
            texto[i]='0';
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