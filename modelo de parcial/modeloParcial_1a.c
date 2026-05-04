/*La Ferretería Industrial necesita actualizar por compras el stock de sus casi 80 productos 
y para ello se deben registrar y almacenar con la estructura adecuada a todo su inventario:

Número de Producto (entero de 3 cifras no correlativo y sin repetir)
Nombre Producto (string de 30 caracteres)
Categoría (R – Repuestos, Q – Químicos, A – Autopartes)
Cantidad Comprada (entero positivo)
Stock (entero mayor o igual a 0)

La carga de los Productos termina con el ingreso de Nombre Producto igual a "FINAL".

Luego para realizar la actualización se ingresarán por cada compra el Número de Producto
 y la cantidad comprada (entero mayor a 0). Con dicha información debe actualizar el stock de 
 cantidad comprada de cada producto. La actualización finaliza con un Número de Producto igual a 0.

Se necesita determinar e informar:

Listado de stock por Producto mostrando su Nombre, Categoría y Stock ordenado alfabéticamente por 
Nombre (resolver en una función).
El nombre del Producto con mayor stock, en caso de ser más de uno mostrarlos a todos 
(resolver en una función).
La cantidad total comprada por cada Categoría.

Validar todos los datos que ingresan por teclado según lo indicado.
El código debe estar correctamente indentado.*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define TAM 30
#define CANT_PRODUCTOS 80

typedef struct 
{
    int num;
    char nombre[TAM];
    char cat;
    int cant;
    int stock;
}prod;

int ingreso(prod[], int);
prod ingresoStruct(prod[], int);
void actualizacion(prod[], int);
void listado(prod[],int);
void mostrarMayor(prod[], int);
void mostrarCantxCat(prod[], int);
void cantidades(prod[], int, int[]);
int mayor(prod[], int);
void burbujeo(prod[], int);
int busqueda(prod[], int, int);
int leeyvalidaEntre2CF(int, int, int);
int leeyvalidaEntre2(int, int);
int leeyvalidaInt(int);
char leeyvalidaChar();
int norepite(prod[], int, int);
void leerTexto(char[], int);
void validarVacio(char[], int);


int main(){
    prod productos[CANT_PRODUCTOS];
    int cantProductos=ingreso(productos, CANT_PRODUCTOS);
    actualizacion(productos, cantProductos);
    listado(productos, cantProductos);
    mostrarMayor(productos, cantProductos);
    mostrarCantxCat(productos, cantProductos);
    return 0;
}

int ingreso(prod productos[], int ce){
    printf("--INVENTARIO FERRETERIA--\n");
    prod aux;
    int i=0;
    int flag=0;
    while(flag==0&&i<ce){
        aux=ingresoStruct(productos, i);
        if(strcmpi(aux.nombre, "FINAL")!=0){
            productos[i]=aux;
            i++;
        }else
            flag=1; 
    }
    printf("INGRESO FINALIZADO\n");
    return i;
}

prod ingresoStruct(prod productos[], int i){
    prod aux;
    printf("Ingrese el nombre del producto:\t");
    leerTexto(aux.nombre, TAM);
    validarVacio(aux.nombre, TAM);
    if(strcmpi(aux.nombre, "FINAL")!=0){
        printf("Ingrese el numero del producto:\t");
        aux.num=leeyvalidaEntre2(100,999);
        while(norepite(productos, i, aux.num)==1){
            printf("El numero ya existe. Reingrese: ");
            aux.num=leeyvalidaEntre2(100, 999);
        }
        printf("Ingrese la categoria(R-Repuestos, Q-Quimicos, A-Autopartes): ");
        aux.cat=leeyvalidaChar();
        printf("Ingrese cantidad comprada: ");
        aux.cant=leeyvalidaInt(1);
        printf("Ingrese el stock: ");
        aux.stock=leeyvalidaInt(0);
    }
    return aux;
}

void actualizacion(prod productos[], int cp){
    printf("ACTUALIZACION DE PRODUCTOS\n");
    int pos;
    prod aux;
    printf("Ingrese el numero del producto: ");
    aux.num=leeyvalidaEntre2CF(100,999,0);
    while(aux.num!=0){
        pos=busqueda(productos, cp,aux.num);
        if(pos==-1)
            printf("El numero ingresado no existe. Reingrese: ");
        else{
            printf("Ingrese la cantidad comprada: ");
            aux.cant=leeyvalidaInt(1);
            productos[pos].cant+=aux.cant;
            productos[pos].stock+=aux.cant;
            printf("Elemento actualizado");
            printf("\nIngrese el numero del producto: ");
        }
        aux.num=leeyvalidaEntre2CF(100,999,0);
    }
    printf("Actualizacion finalizada\n");
}

void listado(prod productos[], int cp){
    burbujeo(productos, cp);
    printf("LISTADO ORDENADO ALFABETICAMENTE\n");
    for(int i=0;i<cp;i++){
        printf("%d. %s cat: %c stock: %d\n", i+1, productos[i].nombre, productos[i].cat, productos[i].stock);
    }

}

void mostrarMayor(prod productos[], int cp){
    int max= mayor(productos, cp);
    int cantMax=0;
    for(int i=0;i<cp;i++){
        if(productos[i].stock==max)
            cantMax++;
    }
    for(int i=0;i<cp;i++){
        if(cantMax==1 && productos[i].stock==max)
            printf("%s es el nombre del producto de mayor stock.", productos[i].nombre);
        else 
            if(cantMax!=1&&productos[i].stock==max)
                printf("%s es el nombre de uno de los productos de mayor stock", productos[i].nombre);
    }
}

void mostrarCantxCat(prod productos[], int cp){
    int cantxCat[3]={0};
    printf("\n--CANTIDAD TOTAL COMPRADA X CAT--\n");
    cantidades(productos, cp, cantxCat);
    printf("%d de Repuestos\n", cantxCat[0]);
    printf("%d de Quimicos\n", cantxCat[1]);
    printf("%d de Autopartes\n", cantxCat[2]);
}
void cantidades(prod productos[], int cp, int vec[]){
    for(int i=0;i<cp;i++){
        switch (productos[i].cat)
        {
        case 'R':
            vec[0]+=productos[i].cant;
            break;
        case 'Q':
            vec[1]+=productos[i].cant;
            break;
        case 'A':
            vec[2]+=productos[i].cant;
            break;
        }
    }
}
int mayor(prod productos[], int cp){
    int mayor=productos[0].stock;
    for(int i=1;i<cp;i++){
        if(productos[i].stock>mayor)
            mayor=productos[i].stock;
    }
    return mayor;
}

void burbujeo(prod productos[], int cp){
    int cota=cp-1;
    int desordenado=1;
    int i;
    prod aux;
    while(desordenado){
        desordenado=0;
        for(i=0;i<cota;i++){
            
            if(strcmpi(productos[i].nombre, productos[i+1].nombre)>0){//primero mayor que el segundo >0
                //strcpy(aux.nombre, productos[i].nombre);
                aux=productos[i];
                productos[i]=productos[i+1];
                productos[i+1]=aux;
                desordenado=i;
            }
        }
        cota=desordenado;
    }
}

int busqueda(prod productos[], int cp, int num){
    int pos=-1;
    int i=0;
    while(pos==-1&&i<cp){
        if(productos[i].num==num)
            pos=i;
        else
            i++;
    }
    return pos;
}

int leeyvalidaEntre2CF(int min, int max, int cf){
    int dato;
    scanf("%d", &dato);
    while(dato!=cf && (dato<min || dato>max)){
        printf("numero incorrecto. por favor ingrese un numero dentro del rango [%d;%d] o %d para cortar", min, max, cf);
        scanf("%d", &dato);
    }
    return dato;
}

int leeyvalidaInt(int lim){
    int dato;
    scanf("%d", &dato);
    while(dato<lim){
        printf("numero incorrecto. ingrese un valor mayor o igual a %d", lim);
        scanf("%d", &dato);
    }
    return dato;
}

char leeyvalidaChar(){
    char dato;
    fflush(stdin);
    scanf("%c",&dato);
    dato=toupper(dato);
    while(dato!='A'&&dato!='R'&&dato!='Q'){
        printf("Ingrese una categoria correcta (R-Repuestos, Q-Químicos, A-Autopartes): ");
        fflush(stdin);
        scanf("%c",&dato);
        dato=toupper(dato);
    }
    return dato;
}
int norepite(prod productos[], int i, int num){
    int flag=0;
    int j=0;
    while(flag==0&&j<i){
        if(productos[j].num==num)
            flag=1;
        else
            j++;
    }
    return flag;
}

int leeyvalidaEntre2(int min, int max){
    int dato;
    scanf("%d", &dato);
    while(dato<min || dato>max){
        printf("El dato debe estar dentro del rango [%d-%d]. Reingrese: ", min, max);
        scanf("%d", &dato);
    }
    return dato;
}

void leerTexto(char texto[], int largo){
    fflush(stdin);
    int i=0;
    fgets(texto, largo, stdin);
    while(texto[i]!='\0'){
        if(texto[i]=='\n')
            texto[i]='\0';
        else
            i++;
    }   
}

void validarVacio(char texto[], int largo){
    while(strlen(texto)==0){
        printf("El texto no puede ser vacio. Reingrese:\t");
        leerTexto(texto, largo);
    }
}

