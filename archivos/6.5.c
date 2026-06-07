/*6.5 Se desea realizar un programa que permita actualizar la lista de precios de una empresa en forma individual
a cada uno de sus productos.
Los productos que están guardados en el archivo productos.dat con la siguiente estructura:
• Código (entero)
• Precio (float)
• Descripción (de hasta 50 caracteres)
Para modificar un precio se ingresa por teclado el código del producto y el nuevo precio. La modificación
de precios finaliza con un código de producto igual a 0. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

typedef struct 
{
    int codigo;
    float precio;
    char desc[51];
}Productos;

int leeyvalidaInt(int);
float leeyvalidaFloat(float);
long busqueda(int, FILE*, Productos*);
void mostrar(FILE*);


int main(){
    Productos datos;
    Productos * pdatos=&datos;
    FILE *arch;
    int cod;
    long pos;
    arch = fopen("PRODUCTOS.dat", "r+b");
    if (arch==NULL)
    {
        printf("Error al abrir el archivo");
        getch();
        exit(1);
    }
    printf("Ingrese el codigo del producto:");
    cod=leeyvalidaInt(0);
    while (cod!=0)
    {
        pos=busqueda(cod, arch, pdatos);
        if(pos==-1){
            printf("ERROR. CODIGO INEXISTENTE, REINGRESE: ");
        }else{
            printf("producto encontrado: %s", datos.desc);
            printf("Ingrese el nuevo precio del producto: ");
            datos.precio=leeyvalidaFloat(0);
            fseek(arch,pos-sizeof(datos), SEEK_SET);
            fwrite(&datos, sizeof(datos), 1, arch);
            fflush(arch);
            printf("Ingrese el codigo del producto");

        }
        cod=leeyvalidaInt(0);
    }
    mostrar(arch);
    return 0;
}
void mostrar(FILE*arch){
    Productos datos;
    rewind(arch);
    fread(&datos, sizeof(datos), 1, arch);
    printf("CODIGO\tPRECIO\tDESCRIPCION\n");
    while(!feof(arch)){
        printf("%6d\t$%-6.2f\t%10s\n", datos.codigo, datos.precio, datos.desc);
        fread(&datos, sizeof(datos), 1, arch);
    }
}
float leeyvalidaFloat(float lim){
    float dato;
    scanf("%f", &dato);
    while(dato<=lim){
        printf("Dato invalido, reingrese: ");
        scanf("%f",&dato);
    }
    return dato;
}
long busqueda(int cod, FILE *arch, Productos *pdatos){
    Productos datos;
    int flag=0;
    long pos=-1;
    rewind(arch);
    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch) && flag==0)
    {   
        
        if (datos.codigo == cod)
        {
            pos=ftell(arch);
            flag=1;
            *pdatos=datos;
        }else{ 
            pos=-1;
        }
        fread(&datos, sizeof(datos), 1, arch);
    }
    return pos;
}

int leeyvalidaInt(int lim){
    int dato;
    scanf("%d", &dato);
    while (dato<lim)
    {
        printf("Error. Reingrese:");
        scanf("%d", &dato);
    }
    return dato;
}
/*
CODIGO  PRECIO  DESCRIPCION
  1234  $80.25               I-PAD
  2234  $1500.20                MICROCOMPONENTE SANYO
  8834  $700.24         TABLET MAC DE 7"
  4052  $1000.00                CARTUCHO TINTA NEGRA HP
  7733  $15000.00               PLAY STATION V 
  2089  $800.20         PEN DRIVE 32 GB
  7159  $2000.00                DISCO RIGIDO EXTERNO 1TB TOSHIBA
  9461  $50.00          LECTOR USB DE MICROSD */
