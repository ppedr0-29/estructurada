/*La Ferretería Industrial necesita actualizar por compras el stock de sus casi 80 productos y para ello 
se deben registrar y almacenar con la estructura adecuada a todo su inventario:
Número de Producto (entero de 3 cifras no correlativo y sin repetir)
Nombre Producto (string de 30 caracteres)
Categoría (R – Repuestos, Q – Químicos, A – Autopartes)
Cantidad Comprada (entero positivo)
Stock (entero mayor o igual a 0)
La carga de los Productos termina con el ingreso de Nombre Producto igual a "FINAL".
Luego para realizar la actualización se ingresarán por cada compra el Número de Producto y la cantidad comprada (entero mayor a 0). 
Con dicha información debe actualizar el stock de cantidad comprada de cada producto. 
La actualización finaliza con un Número de Producto igual a 0.
Se necesita determinar e informar:
Listado de stock por Producto mostrando su Nombre, Categoría y Stock ordenado alfabéticamente por Nombre (resolver en una función).
El nombre del Producto con mayor stock, en caso de ser más de uno mostrarlos a todos (resolver en una función).
La cantidad total comprada por cada Categoría.
Validar todos los datos que ingresan por teclado según lo indicado.
El código debe estar correctamente indentado. READY*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define TAM 80
#define CARAC 30

typedef struct
{
    int numProd;//3 cifras y no repetir
    char nombreProd[CARAC];
    char categoria;
    int cantComprada; // >0
    int stock; //>=0
}PRODUCTOS;

void validarVacio(char [], int );
int ingreso(PRODUCTOS [], int );
PRODUCTOS ingresoDatos(PRODUCTOS [], int );
int norepite(PRODUCTOS [], int , int);
int leeyvalidaInt(int );
char validarCat();
int leeyvalidaentre2(int , int );
int leeyvalidaentre2cf(int , int , int );
void leerTexto(char [], int );
void validarVacio(char [], int );
void actualizacion(PRODUCTOS [], int);
int busquedaSecuencial(PRODUCTOS [], int , int );
void listado(PRODUCTOS [], int );
void mayorStock(PRODUCTOS [], int );
void cantCategoria(PRODUCTOS [], int );
int maximo(PRODUCTOS [], int );
void burbujeo(PRODUCTOS [], int );


int main(){
    PRODUCTOS datos[TAM];
    int cantProductos=ingreso(datos, TAM);
    actualizacion(datos, cantProductos);
    listado(datos, cantProductos);
    mayorStock( datos, cantProductos);
    cantCategoria(datos, cantProductos);
}


int ingreso(PRODUCTOS datos[], int ce){
    PRODUCTOS aux;
    int flag=0, i=0;
    printf("--INVENTARIO FERRETERIA--\n");
    while(flag==0 && i<ce)
    {   
        aux=ingresoDatos(datos, i);
        if (strcmpi(aux.nombreProd, "FINAL")!=0)
        {
            datos[i]=aux;
            i++;
        }else{
            flag=1;
        }
    }
    return i;
}

PRODUCTOS ingresoDatos(PRODUCTOS datos[], int i){
    PRODUCTOS info;
    printf("Ingrese nombre de producto(FINAL para terminar):");
    leerTexto(info.nombreProd, CARAC);
    validarVacio(info.nombreProd, CARAC);
    if (strcmpi(info.nombreProd, "FINAL")!=0)
    {   
        printf("Ingrese numero de producto:");
        info.numProd=leeyvalidaentre2(100,999);
        while (norepite(datos, i, info.numProd)==1)
        {
            printf("El numero se repite. Reingrese:");
            info.numProd=leeyvalidaentre2(100,999);
        }
        printf("Ingrese una categoria(R-Q-A):");
        info.categoria=validarCat();
        printf("Ingrese la cantidad comprada:");
        info.cantComprada=leeyvalidaInt(1);
        printf("Ingrese el stock:");
        info.stock=leeyvalidaInt(0);
    }
    return info;
}

void actualizacion(PRODUCTOS datos[], int cantProductos){
    int actNum, actCant;
    int pos;
    printf("--ACTUALIZACION DE CANTIDAD--\n");
    printf("Ingrese el numero del producto:");
    actNum=leeyvalidaentre2cf(100,999, 0);
    while (actNum!=0)
    {   
        pos=busquedaSecuencial(datos, cantProductos, actNum);
        if(pos==-1){
            printf("El numero no existe. Reingrese:");
        }else{
        printf("Ingrese cantidad comprada:");
        actCant=leeyvalidaInt(1);
        datos[pos].cantComprada+=actCant;
        datos[pos].stock+=actCant;
        printf("Producto actualizado.");
        printf("Ingrese el numero del producto:");
        }
        actNum=leeyvalidaentre2cf(100,999, 0);
    }
}

//Listado de stock por Producto mostrando su Nombre, Categoría y Stock ordenado alfabéticamente por Nombre (resolver en una función).
void listado(PRODUCTOS datos[], int cantProductos){
    burbujeo(datos, cantProductos);
    printf("--LISTADO STOCK--\n");
    for (int i = 0; i < cantProductos; i++)
    {
        printf("%s CAT-%c Stock-%d\n", datos[i].nombreProd, datos[i].categoria, datos[i].stock);
    }
}

//El nombre del Producto con mayor stock, en caso de ser más de uno mostrarlos a todos (resolver en una función).
void mayorStock(PRODUCTOS datos[], int cantProductos){
    int max = maximo(datos, cantProductos);
    printf("--MAYOR STOCK--\n");
    for (int i = 0; i < cantProductos; i++)
    {
        if (datos[i].stock==max)
        {
            printf("%s es el nombre del producto/s con mayor stock\n", datos[i].nombreProd);
        }
    }
}

//La cantidad total comprada por cada Categoría.

void cantCategoria(PRODUCTOS datos[], int cantProductos){
    int acumR=0, acumQ=0, acumA=0;
    printf("-CANT POR CATEGORIAS--\n");
    for (int i = 0; i < cantProductos; i++)
    {
        if (datos[i].categoria=='R')
        {
            acumR+=datos[i].cantComprada;
        }
        if (datos[i].categoria=='Q')
        {
            acumQ+=datos[i].cantComprada;
        }
        if (datos[i].categoria=='A')
        {
            acumA+=datos[i].cantComprada;
        }
    }
    printf("La cantidad de la categoria Repuestos es %d\n", acumR);
    printf("La cantidad de la categoria Quimicos es %d\n", acumQ);
    printf("La cantidad de la categoria Autopartes es %d\n", acumA);
}

int maximo(PRODUCTOS datos[], int cantProductos){
    int max=datos[0].stock;
    for (int i = 1; i < cantProductos; i++)
    {
        if (datos[i].stock>max)
        {
            max=datos[i].stock;
        }
    }
    return max;
}

void burbujeo(PRODUCTOS datos[], int cantProductos){
    int cota=cantProductos-1;
    int desordenado=1;
    int i;
    PRODUCTOS aux;
    while(desordenado){
        desordenado=0;
        for(i=0;i<cota;i++){
            if(strcmpi(datos[i].nombreProd, datos[i+1].nombreProd)>0){//primero mayor que el segundo >0
                //strcpy(aux.nombre, productos[i].nombre);
                aux=datos[i];
                datos[i]=datos[i+1];
                datos[i+1]=aux;
                desordenado=i;
            }
        }
        cota=desordenado;
    }
}

int busquedaSecuencial(PRODUCTOS datos[], int cantProductos, int actNum){
    int pos=-1, i=0;
    while (pos==-1 && i<cantProductos)
    {
        if (datos[i].numProd==actNum)
        {
            pos=i;
        }else
                i++;
    }
    return pos;
}

int norepite(PRODUCTOS datos[], int i, int num){
    int j=0; 
    int flag=0;
    while (flag==0 && j<i)
    {
        if (datos[j].numProd==num)
        {
            flag=1;
        }else{
            j++;
        }
    }
    return flag;
}

int leeyvalidaInt(int lim){
    int dato;
    scanf("%d", &dato);
    while (dato<lim)
    {
        printf("La cantidad es invalida. Reingrese:");
        scanf("%d", &dato);
    }
    return dato;
}

char validarCat(){
    fflush(stdin);
    char dato;
    scanf("%c", &dato);
    dato=toupper(dato);
    while (dato!='R' && dato!='Q' && dato!='A')
    {
        printf("La categoria no es valida. Reingrese:");
        fflush(stdin);
        scanf("%c", &dato);
        dato=toupper(dato);
    }
    return dato;
}

int leeyvalidaentre2cf(int min, int max, int cf){
    int dato;
    scanf("%d", &dato);
    while ((dato<min || dato>max) && dato!=cf)
    {
        printf("El numero no esta dentro del rango(%d-%d). Reingrese:", min, max);
        scanf("%d", &dato);
    }
    return dato;
}

int leeyvalidaentre2(int min, int max){
    int dato;
    scanf("%d", &dato);
    while (dato<min || dato>max)
    {
        printf("El numero no esta dentro del rango(%d-%d). Reingrese:", min, max);
        scanf("%d", &dato);
    }
    return dato;
}

void leerTexto(char texto[], int largo){
    fflush(stdin);
    int i=0;
    fgets(texto, largo, stdin);
    while (texto[i]!='\0')
    {
        if (texto[i]=='\n')
        {
            texto[i]='\0';
        }else
            i++;
    }
}

void validarVacio(char texto[], int largo){
    while (strlen(texto)==0)
    {
        printf("El texto no puede ser vacio. Reingrese:");
        leerTexto(texto, largo);
    }
}