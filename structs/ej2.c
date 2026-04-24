/*Un laboratorio dispone de una lista con sus 50 medicamentos. De cada uno conoce:

Código del medicamento (entero, de 3 cifras).
Precio (real).
Stock (entero).
Se solicita:

Declarar un tipo de dato que contenga la información del medicamento. READY
Declarar un vector de estructura de tipo de datos creado en punto 1. READY
Cargar en un sector de estructuras, los datos referentes a los medicamentos. Función INGRESO. READY
Consultar el precio según código del medicamento. Función BUSQUEDA_MEDI. 
Informar los códigos de los medicamentos cuyo stock es inferior a 10 unidades. Función INFORME.*/

#include <stdio.h>
#include <string.h>

#define TAM 2

typedef struct
{
    int codigoMedi;
    float precioMedi;
    int stock;

}MEDICAMENTOS;

MEDICAMENTOS ingreso();
void INGRESO(MEDICAMENTOS [], int);
int busquedaSecuencial(MEDICAMENTOS  [], int , int );
void BUSQUEDA_MEDI(MEDICAMENTOS [], int );
int leeyValidaIntEntre2(int , int );
int leeyValidaInt(int);
float leeyValidaFloat(int);
void INFORME(MEDICAMENTOS [], int);


int main (){
    MEDICAMENTOS datos[TAM];
    INGRESO(datos, TAM);
    BUSQUEDA_MEDI(datos, TAM);
    INFORME(datos, TAM);

    return 0;
}

void INGRESO(MEDICAMENTOS datos[], int ce){
    for (int i = 0; i < ce; i++)
    {
        datos[i]=ingreso();
    }
    
}

MEDICAMENTOS ingreso(){
    MEDICAMENTOS medi;

        printf("Ingrese codigo del medicamento:");
        medi.codigoMedi= leeyValidaIntEntre2(100,999);
        printf("Ingrese precio del medicamento:");
        medi.precioMedi= leeyValidaFloat(0);
        printf("Ingrese stock del medicamento:");
        medi.stock=leeyValidaInt(0);

        return medi;
}

void BUSQUEDA_MEDI(MEDICAMENTOS datos[], int ce){
    int codigo2Medi, pos;
    printf("--CONSULTAR PRECIO--\n");
    printf("Ingrese codigo del medicamento:");
    codigo2Medi= leeyValidaIntEntre2(100,999);
    pos=busquedaSecuencial(datos, ce, codigo2Medi);
    while (pos == -1)
    {
        printf("El codigo no existe. Ingrese nuevamente:");
        codigo2Medi= leeyValidaIntEntre2(100,999);
        pos=busquedaSecuencial(datos, ce, codigo2Medi);
    }
    printf("El precio del medicamento %d es %.2f\n", codigo2Medi, datos[pos].precioMedi);
}

void INFORME(MEDICAMENTOS datos[], int ce){
    int i, acum=0;
    printf("--STOCK MENOR A 10--\n");
    for (i = 0; i < ce; i++)
    {
        if (datos[i].stock<10)
        {
            printf("Codigo %d", datos[i].codigoMedi);
            acum++;
        }
        
    }
    if (acum == 0)
    {
        printf("No hay stock menor a 10.");
    }
}

int leeyValidaIntEntre2(int min, int max){
    int dato;
    scanf("%d", &dato);
    while (dato<min || dato>max){
        printf("ERROR - El dato ingresado tiene que encontrarse dentro del rango[%d-%d]:", min, max);
        scanf("%d", &dato);
    }
    return dato;
}

int leeyValidaInt(int lim){
    int dato;
    scanf("%d", &dato);
    while (dato<lim){
        printf("ERROR - El dato ingresado tiene que ser mayor o igual a %d:", lim);
        scanf("%d", &dato);
    }
    return dato;
}

float leeyValidaFloat(int lim){
    float dato;
    scanf("%f", &dato);
    while (dato<lim){
        printf("\nERROR - El dato ingresado tiene que ser mayor o igual a %d: \t", lim);
        scanf("%f", &dato);
    }
    return dato;
}

int busquedaSecuencial(MEDICAMENTOS datos [], int ce, int codigo2Medi){
    int i=0, pos=-1;
    while (pos==-1 && i<ce){
        if (datos[i].codigoMedi == codigo2Medi){
        pos=i;
        }else{
            i++;
        }
    }
return pos;
}