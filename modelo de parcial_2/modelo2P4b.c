/*Una empresa necesita actualizar el stock de sus productos con las compras y para ello dispone del archivo stock.dat con la siguiente estructura:
Código de Producto (string de 3 caracteres)
Descripción (string de 30 caracteres)
Rubro (C – Construcción, E – Electricidad, P – Plomería, F – Fijaciones)
Stock Máximo (entero)
Stock (entero)
Luego por cada producto se ingresarán por teclado el Código de Producto y la cantidad comprada (entero positivo) en el mes. 
En base a la cantidad comprada se debe actualizar el stock en el archivo. En caso de no encontrar el Código de Producto en el archivo 
debe guardarse el error en un archivo llamado Errores.dat con la siguiente estructura (Código de Producto y Cantidad Comprada) .
La actualización de compras termina con el ingreso de un Código de Producto igual a "FIN".
Además, se necesita determinar e informar:
La descripción de los productos cuyo stock actualizado supera el stock máximo. (resolver en una función).
El rubro del que se compró la menor cantidad en total (resolver en una función).
Validar los datos que ingresan por teclado según lo indicado.
El código debe estar correctamente identado.

-----PSEUDOCODIGO------
procesarArchivos(){
abrir archivo r+b
ingreso cod
while(codP!=FIN){
    
    cantCom;
    pos=busqueda();
    if(pos!=-1){
        stock+=cantComp
        fseek(arch, pos, seek_set)
        fwrite();
        fflush();
        i=indice(rubro);
        cant[i]+=cantCom;
    }else{
        fwrite(archE);
    }
    ingreso cod
}
}

mostrarMinimo(){

}

minimo(){
    int min=cant[0];
    for(int i=0; i<4){
        if(can[i]<min){
            min=cant[i]
        }
    }
}

stockSuperado(){
    STOCK datos;
    rewind
    fread
    while(!feof){
        if(stock>stockMax){
            printf("...", datos.descripcion);
        }
            fread
    }
}

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

typedef struct
{
    char codProd[4];
    char descripcion[31];
    char rubro;
    int stockMax;
    int stock;
}STOCK;

typedef struct
{
    char codProd[4];
    int cantComp;
}ERROR;

long busqueda(FILE *, char [], STOCK *);
void procesarArchivo();
void stockSuperado(FILE *);
void leeyvalInt(int , int *);
void leerTexto(char [], int );
void valVacio(char [], int );
int minimo(int [], int );
int indice(char );
void mostrarMinimo(int [], int );

int main(){
    procesarArchivo();
    
    return 0;
}

FILE *abrirArchivo(char nombre[], char tipo[]){
    FILE *arch;
    arch=fopen(nombre, tipo);
    if (arch==NULL)
    {
        printf("Error.");
        getch();
        exit(1);
    }
    return arch;
}

void procesarArchivo(){
    FILE *arch;
    FILE *archE;
    STOCK datos;
    STOCK *pdatos=&datos;
    ERROR info;
    long pos;
    int *pcant=&info.cantComp;
    int cantTotal[4]={0}, i;
    arch=abrirArchivo("stock.dat", "r+b");
    archE=abrirArchivo("Errores.dat", "wb");
    printf("Ingrese codigo del producto(FIN para terminar): ");
    leerTexto(info.codProd, 4);
    valVacio(info.codProd, 4);
    while (strcmpi(info.codProd, "FIN")!=0)
    {
        printf("Ingrese la cantidad comprada: ");
        leeyvalInt(0, pcant);
        pos=busqueda(arch, info.codProd, pdatos);
        if (pos!=-1)
        {
            datos.stock+=*pcant;
            fseek(arch, pos, SEEK_SET);
            fwrite(&datos, sizeof(datos), 1, arch);
            fflush(arch);
            i=indice(datos.rubro);
            cantTotal[i]+=*pcant;
        }else{
            fwrite(&info, sizeof(info), 1, archE);
        }
        printf("Ingrese codigo del producto(FIN para terminar): ");
        leerTexto(info.codProd, 4);
        valVacio(info.codProd, 4);
    }
    stockSuperado(arch);
    mostrarMinimo(cantTotal, 4);
    
    fclose(arch);
    fclose(archE);
}

void mostrarMinimo(int v[], int ce){
    int min=minimo(v, ce);
    for (int i = 0; i < ce; i++)
    {
        if(v[i]==min){
            if (i==0)
            {
                printf("En el rubro Construccion se compro la menor cantidad con %d\n", v[i]);
            }
            if (i==1)
            {
                printf("En el rubro Electricidad se compro la menor cantidad con %d\n", v[i]);
            }
            if (i==2)
            {
                printf("En el rubro Plomeria se compro la menor cantidad con %d\n", v[i]);
            }
            if (i==3)
            {
                printf("En el rubro Fijaciones se compro la menor cantidad con %d\n", v[i]);
            }
        }
    }
}

int minimo(int v[], int ce){
    int min=v[0];
    for (int i = 0; i < ce; i++)
    {
        if (v[i]<min)
        {
            min=v[i];
        }
        
    }
    return min;
}

int indice(char rubro){
    int i;
    switch (rubro)
    {
    case 'C':
        i=0;
        break;
    case 'E':
        i=1;
        break;
    case 'P':
        i=2;
        break;
    case 'F':
        i=3;
        break;
    }
    return i;
}


void stockSuperado(FILE *arch){
    STOCK datos;
    rewind(arch);
    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch))
    {
        if (datos.stock>datos.stockMax)
        {
            printf("%s es el producto que supero el stock maximo.\n", datos.descripcion);
        }
        fread(&datos, sizeof(datos), 1, arch);
    }
    
}

long busqueda(FILE *arch, char cod[], STOCK *pdatos){
    STOCK datos;
    long pos=-1;
    int flag=0;
    rewind(arch);
    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch) && flag==0)
    {
        if (strcmpi(datos.codProd, cod)==0)
        {
            flag=1;
            pos=ftell(arch)-sizeof(datos);
            *pdatos=datos;
        }
        fread(&datos, sizeof(datos), 1, arch);
    }
    return pos;
}

void leeyvalInt(int lim, int *dato){
    scanf("%d", dato);
    while (*dato<=lim)
    {
        printf("Error. Reingrese: ");
        scanf("%d", dato);
    }
    
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
        }else{
            i++;
        }   
    }
}

void valVacio(char texto[], int largo){
    while (strlen(texto)==0)
    {
        printf("Error. Reingrese: ");
        leerTexto(texto, largo);
    }
}