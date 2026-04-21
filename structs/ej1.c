/*Una empresa que vende neumáticos desea realizar un programa para actualizar el
total de ventas del mes de sus productos. Para ello primeramente se ingresan la información de los productos formados por:
-Código (5 caracteres)
-Precio (real)
-Descripción (30 caracteres)
-Cantidad de unidades vendidas (al mes anterior, entero)
-Importe Total Vendido (al mes anterior, real)
Se sabe que la empresa no vende más de 50 productos. El ingreso de la carga de
productos finaliza con un producto con descripción “FIN”.
Luego ingresan las ventas del mes:
-Código de Producto (5 caracteres)
-Cantidad pedida.
El ingreso de datos de las ventas finaliza con una cantidad igual a 0.
Se solicita:
Actualizar la información de los productos con las ventas realizadas en el mes.
Al finalizar, mostrar el listado de productos actualizado, informando:
DESCRIPCION   CANT.UNIDADE VENDIDAS   IMPORTE TOTAL VENDIDO
XXXXX            XXXX                     $XXXXX,XX.*/
#include <stdio.h>
#include <string.h>

#define TAM 50

typedef struct {
    char codigo[6];
    float precio;
    char descripcion[31];
    int cantVendidas;
    float totalVendido;
} Productos;

int ingresarProductos(Productos productos[]);
void leerTexto(char[], int);
void validarVacio(char[], int);
int ventasMes(Productos productos[], int cantProductos);

int main() {
    Productos productos[TAM];
    int cantProductos;
    cantProductos = ingresarProductos(productos);
    
    return 0;
}

int ingresarProductos(Productos productos[]) {
    int i = 0;
    int cantVendidasAux;
    char descripcionAux[31], codigoAux[6];
    float precioAux, totalVendidoAux;
    printf("Ingrese descripcion del producto %d (FIN para terminar): ", i + 1);
    leerTexto(descripcionAux, 31);
    validarVacio(descripcionAux, 31);
    
    while (strcmpi(descripcionAux, "FIN") != 0 && i < TAM) {
        strcpy(productos[i].descripcion, descripcionAux);
        
        printf("Ingrese codigo de producto %d (5 cifras): ", i + 1);
        leerTexto(codigoAux, 6);
        validarVacio(codigoAux, 6);
        
        while (strlen(codigoAux) != 5) {
            printf("Codigo invalido. Ingrese nuevamente: ");
            leerTexto(codigoAux, 6);
        }
        strcpy(productos[i].codigo, codigoAux);
        printf("Ingrese precio del producto %d:", i+1);
        scanf("%f", &precioAux);
        while (getchar() != '\n');
        while (precioAux<=0)
        {
            printf("Precio invalido. Ingrese nuevamente:");
            scanf("%f", &precioAux);
            while (getchar() != '\n');
        }
        productos[i].precio=precioAux;
        printf("Ingrese cantidad vendidas del producto %d el mes anterior:", i+1);
        scanf("%d", &cantVendidasAux);
        while (getchar() != '\n');
        while (cantVendidasAux<0)
        {
            printf("Cantidad invalida. Ingrese nuevamente:");
            scanf("%d", &cantVendidasAux);
            while (getchar() != '\n');
        }
        productos[i].cantVendidas=cantVendidasAux;
        printf("Ingrese total vendido del producto %d el mes anterior:", i+1);
        scanf("%f", &totalVendidoAux);
        while (getchar() != '\n');
        while (totalVendidoAux<0)
        {
            printf("Total invalido. Ingrese nuevamente:");
            scanf("%f", &totalVendidoAux);
            while (getchar() != '\n');
        }
        productos[i].totalVendido=totalVendidoAux;
        
        
        i++;
        printf("Ingrese descripcion del producto %d (FIN para terminar): ", i + 1);
        leerTexto(descripcionAux, 31);
        validarVacio(descripcionAux, 31);
    }
    printf("Programa finalizado.");
    return i;
}

int ventasMes(Productos productos[], int cantProductos){
    int i=0, cantidadPedida;
    printf("--VENTAS DEL MES--\n");
    printf("Ingrese la cantidad pedida del producto:");
    cantidadPedida=leeyValidaInt(0);
    while (cantidadPedida!=0)
    {
        printf("Ingrese codigo del producto:");
    }
    
}

int busquedaSecuencial(Productos productos [], int cantProductos){
    int i=0, pos=-1;
    while (pos==-1 && i<cantProductos){
        if (strcmpi(nombre[i], codigo)==0){
        pos =i;
        }else{
            i++;
        }
    }
return pos;
}

void leerTexto(char texto[], int largo) {
    int i;
    fgets(texto, largo, stdin); 
    i = 0;
    while (texto[i] != '\0') {
        if (texto[i] == '\n') { 
            texto[i] = '\0';
        } else {
            i++;
        }
    }
}

int leeyValidaInt(int lim){
    int dato;
    scanf("%d", &dato);
    while (getchar() != '\n');
    while (dato<lim){
        printf("\nERROR - El dato ingresado tiene que ser mayor o igual a %d: \t", lim);
        scanf("%d", &dato);
        while (getchar() != '\n');
    }
    return dato;
}

void validarVacio(char texto[], int largo) {
    while (strlen(texto) == 0) {
        printf("El texto no puede estar vacio. Ingrese nuevamente: ");
        leerTexto(texto, largo);
    }
}