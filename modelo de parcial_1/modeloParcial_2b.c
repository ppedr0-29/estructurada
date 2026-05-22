/*Una fábrica de empanadas necesita controlar la venta de sus casi 20 gustos de empanada y 
para ello deben registrar y almacenar con la estructura adecuada:
Código de empanada (entero de 3 cifras no correlativo y sin repetidos)
Nombre Gusto (string de 25 caracteres)
Cocción (H – Horno, F – Fritas, S – Sin Cocción)
Cantidad Vendida (entero mayor a 0)
Precio (real mayor que cero)
La registración de gustos termina con el ingreso de un código de empanada igual a cero.
Luego por cada código de empanada se ingresará la venta que hizo por cada día de la semana (real mayor o igual que 0) 
en los 7 días de la semana y debe actualizar la cantidad vendida. La carga de las ventas finaliza con un código de empanada igual a cero.
Se necesita determinar e informar:
Listado de importe total vendido por día y código de empanada mostrando su nombre (resolver en una función).
El nombre del gusto que tuvo la mayor venta, en caso de ser más de uno mostrarlos a todos.
La cantidad total vendida por Cocción (resolver en una función).
Validar todos los datos que ingresan por teclado según lo indicado.
El código debe estar correctamente indentado.*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define TAM 20
#define LONG 25

typedef struct
{
    int codE;
    char nomGusto[LONG];
    char coccion;
    int cantV;
    float precio;
}EMP;

int ingreso(EMP [], int );
EMP ingresoDatos(EMP [], int );
int norepite(EMP [], int , int );
int leeyvalInt(int );
float leeyvalFloat(float );
float leeyvalFloat2(float );
int leeyvalIntE2CF(int , int , int );
void leerTexto(char [], int );
void valVacio(char [], int );
char valCat();
int busqueda(EMP [], int , int );
float maximo(float [], int );
void sumafM(float [][7], int , int , float []);
void cantxC(EMP [], int );
void MayGustVentas(EMP [], float [], int );
void listado(EMP [], float [][7], int , int );
void actCant(EMP [], float [][7], int );


int main(){
    EMP datos[TAM];
    float ventas[TAM][7]={{0}};
    float vf[TAM];

    int cantEmp=ingreso(datos, TAM);
    if (cantEmp!=0)
    {
        actCant(datos, ventas, cantEmp);
        listado(datos, ventas, cantEmp ,  7);
        sumafM(ventas, cantEmp,  7, vf);
        MayGustVentas( datos, vf, cantEmp);
        cantxC( datos, cantEmp);
    }
    printf("Programa finalizado.");
    return 0;
}


int ingreso(EMP datos[], int ce){
    EMP aux;
    int flag=0, i=0;
    printf("--REGISTRO EMPANADAS--\n");
    while (flag==0 && i<ce)
    {
        aux=ingresoDatos(datos, i);
        if (aux.codE!=0)
        {
            datos[i]=aux;
            i++;
        }else{
            flag=1;
        }
    }
    return i;
}


EMP ingresoDatos(EMP datos[], int i){
    EMP info;
    printf("Ingrese el codigo de empananda(0 fin):");
    info.codE=leeyvalIntE2CF(100,999,0);
    while (norepite(datos, i, info.codE)==1)
        {
            printf("El codigo se repite. Reingrese:");
            info.codE=leeyvalIntE2CF(100,999,0);
        }
    if (info.codE!=0)
    {   
        printf("Ingrese el gusto:");
        leerTexto(info.nomGusto, LONG);
        valVacio(info.nomGusto, LONG);
        printf("Ingrese su coccion(H-Horno, F-Frita, S-Sin coccion):");
        info.coccion=valCat();
        printf("Ingrese cantidad vendida:");
        info.cantV=leeyvalInt(0);
        printf("Ingrese precio de la empanada:");
        info.precio=leeyvalFloat2(0);
    }
    return info;
}

/*Luego por cada código de empanada se ingresará la venta que hizo por cada día de la semana (real mayor o igual que 0) 
en los 7 días de la semana y debe actualizar la cantidad vendida. La carga de las ventas finaliza con un código de empanada igual a cero.*/
void actCant(EMP datos[], float ventas[][7], int ce){
    int codE2, pos;
    float totVenta;
    printf("--VENTAS X DIAS--\n");
    printf("Ingrese codigo de empanda:");
    codE2=leeyvalIntE2CF(100,999,0);
    while (codE2!=0)
    {
        pos=busqueda(datos,ce,codE2);
        if (pos==-1)
        {
            printf("El codigo no se encontro. Reingrese:\n");
        }else{
            for (int i = 0; i < 7; i++)
            {
                printf("Ingrese las ventas del dia %d:", i+1);
                totVenta=leeyvalFloat(0);
                ventas[pos][i]=totVenta;
                datos[pos].cantV+=(int)(totVenta/datos[pos].precio);
                
            }
            printf("Venta guardada.");
            printf("Ingrese codigo de empanda:");
        }
        codE2=leeyvalIntE2CF(100,999,0);
    }
}

//Listado de importe total vendido por día y código de empanada mostrando su nombre (resolver en una función).
void listado(EMP datos[], float ventas[][7], int f, int c){
    printf("--LISTADO IMP TOT X DIA--\n");
    for (int i = 0; i < f; i++)
    {   
        for (int j = 0; j < c; j++)
        {   
            printf("%s. Dia %d= $%.2f\n", datos[i].nomGusto, j+1, ventas[i][j]);
        }
    }
}

//El nombre del gusto que tuvo la mayor venta, en caso de ser más de uno mostrarlos a todos.

void MayGustVentas(EMP datos[], float vc[], int ce){
    float max=maximo(vc,ce);
    for (int i = 0; i < ce; i++)
    {
        if(vc[i]==max){
            printf("El gusto %s tuvo/tuvieron la mayor venta con $%.2f.\n", datos[i].nomGusto, vc[i]);
        }
    }
    
}

//La cantidad total vendida por Cocción (resolver en una función).
void cantxC(EMP datos[], int ce){
    int cantH=0, cantF=0, cantS=0;
    printf("--CANTIDAD VENDIDA X COCCION--\n");
    for (int i = 0; i < ce; i++)
    {
        if (datos[i].coccion=='H')
        {
            cantH+=datos[i].cantV;
        }
        if (datos[i].coccion=='F')
        {
            cantF+=datos[i].cantV;
        }
        if (datos[i].coccion=='S')
        {
            cantS+=datos[i].cantV;
        }
    }
    printf("%d Horneadas\n", cantH);
    printf("%d Fritas\n", cantF);
    printf("%d Sin coccion\n", cantS);
}

void sumafM(float ventas[][7], int f, int c, float vf[]){
    float suma;
    for (int j = 0; j < f; j++)
    {
        suma=0;
        for (int i = 0; i<c; i++)
        {
            suma += ventas[j][i];
        }
        vf[j]=suma;
    }
}

float maximo(float vc[], int ce){
    float max=vc[0];
    for (int i = 0; i < ce; i++)
    {
        if (vc[i]>max)
        {
            max=vc[i];
        }
        
    }
    return max;
}

int busqueda(EMP datos[], int ce, int codE2){
    int pos=-1;
    int i=0;
    while (pos==-1 && i<ce)
    {
        if (datos[i].codE==codE2)
        {
            pos=i;
        }else
            i++;
    }
    return pos;
}

int norepite(EMP datos[], int i, int cod){
    int j=0; 
    int flag=0;
    while (flag==0 && j<i)
    {
        if (datos[j].codE==cod)
        {
            flag=1;
        }else{
            j++;
        }
    }
    return flag;
}

int leeyvalInt(int lim){
    int dato;
    fflush(stdin);
    scanf("%d", &dato);
    while (dato<=lim)
    {
        printf("La cantidad es invalida. Reingrese:");
        fflush(stdin);
        scanf("%d", &dato);
    }
    return dato;
}

float leeyvalFloat(float lim){
    float dato;
    fflush(stdin);
    scanf("%f", &dato);
    while (dato<lim)
    {
        printf("El precio es invalido. Reingrese:");
        fflush(stdin);
        scanf("%f", &dato);
    }
    return dato;
}

float leeyvalFloat2(float lim){
    float dato;
    fflush(stdin);
    scanf("%f", &dato);
    while (dato<=lim)
    {
        printf("El precio es invalido. Reingrese:");
        fflush(stdin);
        scanf("%f", &dato);
    }
    return dato;
}

int leeyvalIntE2CF(int min, int max, int cf){
    int dato;
    fflush(stdin);
    scanf("%d", &dato);
    while ((dato<min || dato>max) && dato!=cf)
    {
        printf("El codigo es invalido. Reingrese:");
        fflush(stdin);
        scanf("%d", &dato);
    }
    return dato;
}

char valCat(){
    char dato;
    fflush(stdin);
    scanf("%c", &dato);
    dato=toupper(dato);
    while (dato!='H' && dato!='F' && dato!='S')
    {
        printf("La coccion no es valida. Reingrese:");
        fflush(stdin);
        scanf("%c", &dato);
        dato=toupper(dato);
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

void valVacio(char texto[], int largo){
    while (strlen(texto)==0)
    {
        printf("El texto no puede ser vacio. Reingrese:");
        leerTexto(texto, largo);
    }
}
