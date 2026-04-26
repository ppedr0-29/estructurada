/*4.4 Se ingresan las ventas de un comercio de insumos de computación. Por cada venta se ingresa:
• Número de cliente (entero de 4 dígitos no correlativos).
• Importe (mayor a cero).
• Número de vendedor (entero de 1 a 10).
El ingreso de datos finaliza con un número de cliente 999.
Se sabe que no son más de 100 clientes, la carga de los clientes se debe realizar al inicio del programa con la
función CARGA_CLIENTE () y para cada uno se ingresa:
• Código de cliente (entero de 4 dígitos no correlativos). //preguntar al profesor sobre correlativos
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
VENTAS INGRESO_VENTAS (CLIENTE []);
void Ingreso_Cliente(CLIENTE [], int );
int leeyValidaIntEntre2(int , int );
void leerTexto(char [], int );
void validarVacio(char [], int );
int Ingreso_Ventas(VENTAS[], int, CLIENTE []);

int main (){
    CLIENTE maxclientes[TAM];
    VENTAS datosVentas[TAM];
    int cantVentas;
    Ingreso_Cliente(maxclientes,TAM);
    cantVentas=Ingreso_Ventas(datosVentas, TAM, maxclientes);
}

void Ingreso_Cliente(CLIENTE maxclientes[], int ce){
    int i;
    for (i = 0; i < ce; i++)
    {
        maxclientes[i]=CARGA_CLIENTE();
    }
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

int Ingreso_Ventas(VENTAS datosVentas[], int ce, CLIENTE maxclientes[]){
    VENTAS aux;
    int i=0, flag=0;
    while (flag==0 && i<ce)
    {
        aux=INGRESO_VENTAS(maxclientes);
        if (aux.numCliente!=999)
        {
            datosVentas[i]=aux;
            i++;
        }else{
            flag=1;
        }
    }
    printf("Ingreso ventas finalizado.");
    return i;
}

VENTAS INGRESO_VENTAS(CLIENTE maxclientes[]){ //preguntar si es mejor buscar y printear no existe, o primero validar todo, y luego buscar.
    VENTAS datos;
    int pos=-1;
    printf("--VENTAS--");
    printf("Ingrese numero del cliente:");
    datos.numCliente=leeyValidaIntEntre2Ventas(1000, 9999);
    while(datos.numCliente!=999 &&pos==-1 ){
        pos=busquedaSecuencial(maxclientes, TAM, datos.numCliente);
        if(pos!=-1){
            printf("Ingrese importe de la venta:");
            datos.importe=leeyValidaFloat(0);
            printf("Ingrese numero del vendedor");
            datos.numVendedor=leeyValidaIntEntre2(0,11);
        }else{
            printf("El codigo no existe. Ingrese nuevamente:");
            datos.numCliente=leeyValidaIntEntre2Ventas(1000, 9999);
        }
    }
    return datos;
}

float leeyValidaFloat(float lim){
    float dato;
    scanf("%f", &dato);
    getchar();
    while (dato<lim){
        printf("\nERROR - El importe ingresado tiene que ser mayor a %d: \t", lim);
        scanf("%f", &dato);
        getchar();
    }
    return dato;
}

int busquedaSecuencial(CLIENTE maxclientes[], int ce, int numCliente){
    int i=0, pos=-1;
    while (pos==-1 && i<ce){
        if (maxclientes[i].codCliente == numCliente){
        pos=i;
        }else{
            i++;
        }
    }
return pos;
}

int leeyValidaIntEntre2(int min, int max){
    int dato;
    scanf("%d", &dato);
    getchar();
    while (dato<min || dato>max){
        printf("\nERROR - El dato ingresado tiene que encontrarse dentro del rango[%d-%d]: \t", min, max);
        scanf("%d", &dato);
        getchar();
    }
    return dato;
}

int leeyValidaIntEntre2Ventas(int min, int max){
    int dato;
    scanf("%d", &dato);
    getchar();
    while ((dato<min || dato>max) && dato!=999){
        printf("\nERROR - El numero ingresado tiene que encontrarse dentro del rango[%d-%d]: \t", min, max);
        scanf("%d", &dato);
        getchar();
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