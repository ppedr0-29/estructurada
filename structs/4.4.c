/*4.4 Se ingresan las ventas de un comercio de insumos de computación. Por cada venta se ingresa:
• Número de cliente (entero de 4 dígitos no correlativos).
• Importe (mayor a cero).
• Número de vendedor (entero de 1 a 10).
El ingreso de datos finaliza con un número de cliente 999.
Se sabe que no son más de 100 clientes, la carga de los clientes se debe realizar al inicio del programa con la
función CARGA_CLIENTE () y para cada uno se ingresa:
• Código de cliente (entero de 4 dígitos no correlativos).
• Nombre y Apellido (50 caracteres máximo).
Se solicita:
a. Determinar la cantidad de ventas realizadas por cliente.
b. La cantidad de ventas realizadas por vendedor.
c. Informar en forma ordenada por total facturado (modo descendente), el total facturado a cada
cliente, informando:
CODIGO DE CLIENTE NOMBRE Y APELLIDO TOTAL FACTURADO
X XXXXX XXXXXXXX $ XXXXXXXXX,XX*/

#include <stdio.h>
#include <string.h>
#define TAM 100

typedef struct 
{
    int codCliente;
    char nombreyApellido [50];
}CLIENTE;


typedef struct
{
    int numCliente;
    float importe;
    int numVendedor;
}VENTAS;

CLIENTE CARGA_CLIENTE ();
int Ingreso_Cliente(CLIENTE [], int );
int leeyValidaIntEntre2(int , int );
void leerTexto(char [], int );
void validarVacio(char [], int );

int main (){
    CLIENTE maxclientes[TAM];
    int cantClientes;
    cantClientes= Ingreso_Cliente(maxclientes,TAM);
}

int Ingreso_Cliente(CLIENTE maxclientes[], int ce){
    int i;
    for (i = 0; i < ce; i++)
    {
        maxclientes[i]=CARGA_CLIENTE();
    }
    return i;
}

CLIENTE CARGA_CLIENTE (){
    CLIENTE clientes;
    char nomAux [50];
    printf("--CARGA DE CLIENTES--\n");
    printf("Ingrese codigo de cliente(4 cifras):");
    clientes.codCliente=leeyValidaIntEntre2(1000,9999);
    fflush(stdin);
    printf("Ingrese nombre y apellido del cliente:");
    leerTexto(nomAux, 50);
    validarVacio(nomAux, 50);
    strcpy(clientes.nombreyApellido, nomAux);

    return clientes;
}

int leeyValidaIntEntre2(int min, int max){
    int dato;
    scanf("%d", &dato);
    while (dato<min || dato>max){
        printf("\nERROR - El codigo ingresado tiene que encontrarse dentro del rango[%d-%d]: \t", min, max);
        scanf("%d", &dato);
    }
    return dato;
}

void leerTexto(char texto[], int largo){
    int i;
    fgets(texto, largo, stdin);
    i=0;
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

void validarVacio(char texto[], int largo){
    while (strlen(texto)==0)
    {
        printf("El texto no puede estar vacio. Ingrese nuevamente:");
        leerTexto(texto, largo);
    }
    
}