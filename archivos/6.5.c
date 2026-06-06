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

int main(){
    Productos datos;
    FILE *arch;
    int cod, Registro_actual;
    arch = fopen("PRODUCTOS.dat", "r+b");
    if (arch==NULL)
    {
        printf("Error al abrir el archivo");
        getch();
        exit(1);
    }
    printf("Ingrese el codigo del producto");
    cod=leeyvalInt(1);
    while (cod!=0)
    {


        printf("Ingrese el codigo del producto");
        cod=leeyvalInt(1);
    }
    
    
}

int busqueda(int cod, FILE *arch){
    Productos datos;
    int flag=0, pos;
    rewind(arch);
    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch) && flag==0)
    {   
        pos=ftell(arch);
        if (datos.codigo == cod)
        {
            flag=1;
        }else{ 
            pos=-1;
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

