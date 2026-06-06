/*6.6 Dado el archivo productos.dat con la siguiente estructura:
• Código (entero)
• Precio (float)
• Descripción (de hasta 50 caracteres)
Realizar un programa que permita eliminar productos dado su código*/
#include<stdio.h>

typedef struct 
{
    int codigo;
    float precio;
    char desc[51];
}prod;

int main(){
    prod datos;
    FILE *arch;
    FILE *archT;
    prod *pdatos=&datos;
    int cod;
    long pos;
    arch=fopen("productos.dat", "rb");
    archT=fopen("ProductosT.dat", "wb");
    if(arch ==NULL || archT == NULL){
        printf("Error al abrir el archivo");
        getch();
        exit (1);
    }
    printf("Ingrese el codigo del producto a eliminar (0 para finalizar): ");
    cod=leeyvalidaInt(0);
    while(cod!=0){
        pos=busqueda(cod, arch, pdatos);
        if(pos == -1){
            printf("Error. CODIGO INEXISTENTE; REINGRESE: ");
        }else{
            if(datos.codigo!=cod)
                fwrite(&datos, sizeof())
        }
        cod=leeyvalidaInt(0);
    }
    return 0;
}

long busqueda(int cod, FILE *arch, prod *pdatos){
    prod datos;
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
    while(dato<lim){
        printf("Error. reingrese: ");
        scanf("%d", &dato);
    }
    return dato;
}