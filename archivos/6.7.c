
/*6.7 Se dispone de un archivo llamado Stock.dat que contiene la información de los productos que vende una
fábrica. En el archivo se guarda:
• Código de artículo (entero)
• Descripción (50 caracteres máximo)
• Stock (entero)
Luego se ingresan por teclado las ventas a realizar indicando:
• Código de artículo
• Cantidad
 La carga por teclado de las ventas finaliza con un código de artículo igual a 0.
Por cada venta se debe controlar si hay stock suficiente y si lo hay, restar el stock de dicho producto, sino
hay stock se debe vender lo que quede disponible y grabar un registro en un archivo Faltantes.dat con la
cantidad que no pudo venderse, dicho registro debe contener:
• Código de artículo
• Cantidad faltante
Si ya hay un registro previo en dicho archivo de faltantes con el mismo producto debe incrementarse la
cantidad.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

typedef struct
{
    int cod;
    char desc[51];
    int stock;
}Prod;
typedef struct 
{
    int cod;
    int cantF;
}Venta;

long busqueda(FILE*, int, Prod *);
long busquedaF(FILE*, int, Venta*);
int leeyvalInt(int);
void mostrar(FILE*);
void mostrarF(FILE*);


int main (){
    Prod datos;
    Prod *pdatos=&datos;
    Venta info;
    Venta *pinfo=&info;
    FILE *archS;
    FILE *archF;
    int codigo, cantSoli, cantidad;
    long pos;
    archS=fopen("STOCK.dat", "r+b");
    archF=fopen("FALTANTES.dat", "r+b");
    if(archS==NULL){
        printf("Error al abrir el archivo...");
        getch();
        exit(1);
    }
    if(archF==NULL){
        archF=fopen("FALTANTES.dat", "w+b");
        if(archF==NULL){
            printf("Error al abrir el archivo...");
            getch();
            exit(1);
        }
    }
    mostrar(archS);
    printf("Ingrese codigo del producto: ");
    codigo=leeyvalInt(0);
    while(codigo!=0){
        pos=busqueda(archS, codigo, pdatos);
        if(pos==-1){
            printf("Codigo no existe. Reingrese: ");
        }else{
            printf("Ingrese la cantidad solicitada: ");
            cantSoli=leeyvalInt(1);
            if(datos.stock>=cantSoli){
                datos.stock-=cantSoli;
                printf("Cant vendida %d y stock act %d\n", cantSoli, datos.stock);
                fseek(archS, pos, SEEK_SET);
                fwrite(&datos, sizeof(datos), 1, archS);
                fflush(archS);
            }else{
                cantidad=(datos.stock-cantSoli)*(-1);
                printf("Se vendio el stock disponible %d, falto %d\n", datos.stock, cantidad);
                datos.stock=0;
                fseek(archS, pos, SEEK_SET);
                fwrite(&datos, sizeof(datos), 1, archS);
                fflush(archS);
                pos=busquedaF(archF, codigo, pinfo);
                if (pos==-1)
                {   
                    info.cod=codigo;
                    info.cantF=cantidad;
                    printf("\nSe agrego el producto %d a la lista faltantes. Faltan: %d\n", info.cod, info.cantF);
                    fseek(archF, 0, SEEK_END);
                    fwrite(&info, sizeof(info), 1, archF);
                    fflush(archF);

                }else{
                    info.cantF+=cantidad;
                    info.cod=codigo;
                    printf("\nSe actualizo el producto %d en la lista faltantes. Faltan: %d\n", info.cod, info.cantF);
                    fseek(archF, pos, SEEK_SET);
                    fwrite(&info, sizeof(info), 1, archF);
                    fflush(archF);
                }
                
            }
            printf("Ingrese el codigo del producto: ");
        }
        codigo=leeyvalInt(0);
    }
    printf("\n----------------- ARCHIVOS ACTUALIZADOS-----------------\n");
    mostrarF(archF);
    mostrar(archS);
    fclose(archF);
    fclose(archS);
    return 0;
}

void mostrar(FILE*arch){
    Prod datos;
    rewind(arch);
    fread(&datos, sizeof(datos), 1, arch);
    printf("CODIGO\tSTOCK\tDESCRIPCION\n");
    while(!feof(arch)){
        printf("%6d\t %-5d\t%10s\n", datos.cod, datos.stock, datos.desc);
        fread(&datos, sizeof(datos), 1, arch);
    }
}

void mostrarF(FILE*arch){
    Venta datos;
    rewind(arch);
    fread(&datos, sizeof(datos), 1, arch);
    printf("CODIGO\tCANT FALT\n");
    while(!feof(arch)){
        printf("%6d\t %-9d\n", datos.cod, datos.cantF);
        fread(&datos, sizeof(datos), 1, arch);
    }
}

long busqueda(FILE *arch, int cod, Prod *pdatos){
    Prod datos;
    int flag=0;
    long pos=-1;
    rewind(arch);
    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch) && flag==0)
    {
        if (datos.cod==cod)
        {
            pos=ftell(arch)-sizeof(datos);
            flag=1;
            *pdatos=datos;
        }
        fread(&datos, sizeof(datos), 1, arch);
    }
    return pos;
}
long busquedaF(FILE *arch, int cod, Venta *pdatos){
    Venta datos;
    int flag=0;
    long pos=-1;
    rewind(arch);
    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch) && flag==0)
    {
        if (datos.cod==cod)
        {
            pos=ftell(arch)-sizeof(datos);
            flag=1;
            *pdatos=datos;
        }
        fread(&datos, sizeof(datos), 1, arch);
    }
    return pos;
}

int leeyvalInt(int lim){
    int dato;
    scanf("%d", &dato);
    while (dato<lim)
    {
        printf("Error. Reingrese:");
        scanf("%d", &dato);
    }
    return dato;
}