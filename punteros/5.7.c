/*5.7 Dada la siguiente estructura:
typedef struct
{
int codigo;
char descripcion[31];
float precio;
}sProductos
a. Crear una variable del tipo sProductos
b. Ingresar por teclado los campos
c. Crear un puntero a dicha estructura
d. Mostrar los datos ingresados mediante el puntero utilizando las dos nomenclaturas posibles*/

#include <stdio.h>

typedef struct 
{
    int codigo;
    char descripcion[31];
    float precio;
}sProductos;

int main(){
    sProductos prod; //a
    //b
    printf("Ingrese el codigo del producto: ");
    scanf("%d", &prod.codigo);
    fflush(stdin);
    printf("Ingrese la descripcion del producto: ");
    fgets(prod.descripcion, 31, stdin);
    printf("Ingrese el precio: $");
    scanf("%f", &prod.precio);
    //b
    sProductos *ptprod= &prod; //c

    printf("El codigo del producto es %d\nSu descripcion es: %s Su precio es de $%.2f ", (*ptprod).codigo, ptprod->descripcion, ptprod->precio);
    return 0;
}