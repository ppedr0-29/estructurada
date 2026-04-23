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
void ventasMes(Productos productos[], int);
void mostrarLista(Productos productos[], int );
int busquedaSecuencial(Productos productos [], int , char []);
int leeyValidaInt(int);

int main() {
    Productos productos[TAM];
    int cantProductos;
    cantProductos = ingresarProductos(productos);
    if (cantProductos==0)
    {
        printf("No se ingresaron productos.");
    }else{
    ventasMes(productos, cantProductos);
    mostrarLista(productos, cantProductos);
    }
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
    printf("--CARGA DE PRODUCTOS FINALIZADA--\n");
    return i;
}

void ventasMes(Productos productos[], int cantProductos){
    int i=0, cantidadPedida, totalProducto, pos;
    char codigo2[6], codigo2Aux[10];
    printf("--VENTAS DEL MES--\n");
    printf("Ingrese la cantidad pedida del producto %d:", i+1);
    cantidadPedida=leeyValidaInt(0);
    while (cantidadPedida!=0){
        printf("Ingrese codigo de producto %d (5 cifras): ", i + 1);
        leerTexto(codigo2Aux, 6);
        validarVacio(codigo2Aux, 6);
        
        while (strlen(codigo2Aux) != 5) {
            printf("Codigo invalido. Ingrese nuevamente: ");
            leerTexto(codigo2Aux, 6);
        }
        strcpy(codigo2, codigo2Aux);
        pos=busquedaSecuencial(productos, cantProductos, codigo2);
        while (pos==-1)
        {
            printf("El codigo no existe. Ingrese nuevamente:");
            leerTexto(codigo2Aux, 6);
            while (strlen(codigo2Aux) != 5) {
            printf("Codigo invalido. Ingrese nuevamente: ");
            leerTexto(codigo2Aux, 6);
        }
            strcpy(codigo2, codigo2Aux);
            pos=busquedaSecuencial(productos, cantProductos, codigo2);
        }
        totalProducto = productos[pos].precio * cantidadPedida;
        productos[pos].totalVendido += totalProducto;
        productos[pos].cantVendidas += cantidadPedida; 
        i++;
        printf("Ingrese la cantidad pedida del producto %d:", i+1);
        cantidadPedida=leeyValidaInt(0);
    }
    
    printf("--INGRESO VENTAS FINALIZADO--\n");
}

void mostrarLista(Productos productos[], int cantProductos){
    printf("DESCRIPCION\t CANT.UNIDADE VENDIDAS\t IMPORTE TOTAL VENDIDO\n");
    for (int i = 0; i < cantProductos; i++)
    {   
        printf("%-30s\t %20d\t $%20.2f\n ", productos[i].descripcion, productos[i].cantVendidas, productos[i].totalVendido);
    }
    
}

int busquedaSecuencial(Productos productos [], int cantProductos, char codigo2[]){
    int i=0, pos=-1;
    while (pos==-1 && i<cantProductos){
        if (strcmpi(productos[i].codigo, codigo2)==0){
        pos=i;
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