/*4.5 De una persona se conoce los siguientes datos:
• Número de Legajo (int, entre 1 y 10.000)
• Apellido (string, 15 caracteres)
• Nombre (string, 15 caracteres)
• Altura (float, mayor de 0)
• Sexo (char, F o M)
• Día de Nacimiento (int, entre 1 y 31
• Mes de Nacimiento (int, ente 1 y 12)
• Año de Nacimiento (int, ente 1950 y 2019)
Se solicita realizar los siguientes procesos:
a. Con datos ingresados por teclado: Crear una Estructura de Datos con los datos enunciados
anteriormente y llamarla PERSONA. READY
b. Mostrar los datos de la Estructura de Datos del punto a. READY
c. Con datos ingresados por teclado: Modificar la Estructura de Datos del punto a., crear una Estructura
de Datos que contenga Nombre y Apellido y otra Estructura de Datos que contenga Día/Mes/Año
utilizarla en una nueva Estructurad de Datos llamada PERSONA2.READY
d. Mostrar los datos de la Estructura de Datos del punto c.READY
e. Crear una FUNCION que cargue los datos de la Estructurad de Datos del punto c y que retorne los datos
al programa principal (main).READY
f. Con datos ingresados por teclado: Modificar la Estructurad de Datos llamada PERSONA2 del punto c.
y agregarle un campo/miembro que contenga los códigos de las Materias Aprobadas (pueden llegar a
ser hasta 36 materias) y llamarla PERSONA3.
g. Crear una FUNCION que realice el punto f.
h. Mostrar los datos de la Lista creada en el punto f.
i. Crear una FUNCION que realice el punto h.*/


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MATERIAS 3

typedef struct
{
    int numLegajo;  // entre 1 y 10000
    char apell [16]; // de 15
    char nombre [16];  // de 15
    float altura; // mayor a 0
    char sex; // F, o M
    int dia; // entre 1 y 312¿
    int  mes; // entre 1 y 12
    int anio; // entre 1950 y 2019
}PERSONA;

typedef struct 
{
    char apell [16]; // de 15
    char nombre [16];  // de 15
}NyA;

typedef struct
{
    int dia; // entre 1 y 312¿
    int  mes; // entre 1 y 12
    int anio; // entre 1950 y 2019
}fecha;

typedef struct 
{
    int numLegajo;  // entre 1 y 10000
    NyA nombre2;
    float altura; // mayor a 0
    char sex; // F, o M
    fecha cumple;
}PERSONA2;

typedef struct 
{
    int numLegajo;  // entre 1 y 10000
    NyA nombre2;
    float altura; // mayor a 0
    char sex; // F, o M
    fecha cumple;
    int mAprobadas[MATERIAS];
}PERSONA3;


PERSONA INGRESO();
void mostrarDatos(PERSONA);
PERSONA2 INGRESO2();
void mostrarDatos2(PERSONA2);
PERSONA3 INGRESO3();
void mostrarDatos3(PERSONA3);
int leeyValidaIntEntre2(int , int);
float leeyValidaFloat(float);
void leerTexto(char [], int );
void validarVacio(char [], int );
char validarSexo();
bool validarFecha(int , int , int );
int cantDiasMes(int , int );
int esBisiesto(int );
int leeyvalidaInt(int);
int norepite(int, PERSONA3, int);
void ingresoMaterias(PERSONA3, int);
void mostrarMaterias(PERSONA3, int);

int main()
{
    PERSONA datos;
    PERSONA2 datos2;
    PERSONA3 datos3;
    datos= INGRESO();
    mostrarDatos(datos);
    datos2=INGRESO2();
    mostrarDatos2(datos2);
    datos3=INGRESO3();
    mostrarDatos3(datos3);


    return 0;
}


PERSONA INGRESO(){
    PERSONA datos;
    int d,m,a;
    printf("Ingrese el numero de Legajo:");
    datos.numLegajo=leeyValidaIntEntre2(1, 10000);
    printf("Ingrese el apellido:");
    fflush(stdin);
    leerTexto(datos.apell, 15);
    validarVacio(datos.apell, 15);    
    printf("Ingrese el nombre:");
    fflush(stdin);
    leerTexto(datos.nombre, 15);
    validarVacio(datos.nombre, 15);    
    printf("Ingrese la altura:");
    datos.altura=leeyValidaFloat(0);
    printf("Ingrese el sexo:");
    datos.sex=validarSexo();
    fflush(stdin);
    printf("Ingrese la fecha con el siguiente formato (dd/mm/aaaa):");
    scanf("%d/%d/%d",&d, &m, &a);
    while(validarFecha(d,m,a)==false){
        printf("Fecha invalida, reingrese:");
        scanf("%d/%d/%d",&d, &m, &a);
    }
    datos.dia=d;
    datos.mes=m;
    datos.anio=a;

    return datos;
}

void mostrarDatos(PERSONA datos){
    printf("--DATOS INGRESADOS--\n");
    printf("%s: %d\n", "NUM LEGAJO", datos.numLegajo);
    printf("%s: %s\n", "APELLIDO", datos.apell);
    printf("%s: %s\n", "NOMBRE", datos.nombre);
    printf("%s: %.2f\n", "ALTURA", datos.altura);
    printf("%s: %c\n", "SEXO", datos.sex);
    printf("%s: %d/%d/%d\n", "NACIMIENTO", datos.dia, datos.mes, datos.anio);
}

PERSONA2 INGRESO2(){
    PERSONA2 datos;
    int d,m,a;
    printf("Ingrese el numero de Legajo:");
    datos.numLegajo=leeyValidaIntEntre2(1, 10000);
    printf("Ingrese el apellido:");
    fflush(stdin);
    leerTexto(datos.nombre2.apell, 15);
    validarVacio(datos.nombre2.apell, 15);    
    printf("Ingrese el nombre:");
    fflush(stdin);
    leerTexto(datos.nombre2.nombre, 15);
    validarVacio(datos.nombre2.nombre, 15);    
    printf("Ingrese la altura:");
    datos.altura=leeyValidaFloat(0);
    printf("Ingrese el sexo:");
    datos.sex=validarSexo();
    fflush(stdin);
    printf("Ingrese la fecha con el siguiente formato (dd/mm/aaaa):");
    scanf("%d/%d/%d",&d, &m, &a);
    while(validarFecha(d,m,a)==false){
        printf("Fecha invalida, reingrese:");
        scanf("%d/%d/%d",&d, &m, &a);
    }
    datos.cumple.dia=d;
    datos.cumple.mes=m;
    datos.cumple.anio=a;

    return datos;
}

void mostrarDatos2(PERSONA2 datos){
    printf("--DATOS INGRESADOS--\n");
    printf("%s: %d\n", "NUM LEGAJO", datos.numLegajo);
    printf("%s: %s\n", "APELLIDO", datos.nombre2.apell);
    printf("%s: %s\n", "NOMBRE", datos.nombre2.nombre);
    printf("%s: %.2f\n", "ALTURA", datos.altura);
    printf("%s: %c\n", "SEXO", datos.sex);
    printf("%s: %d/%d/%d\n", "NACIMIENTO", datos.cumple.dia, datos.cumple.mes, datos.cumple.anio);
}


PERSONA3 INGRESO3(){
    PERSONA3 datos;
    int d,m,a;
    printf("Ingrese el numero de Legajo:");
    datos.numLegajo=leeyValidaIntEntre2(1, 10000);
    printf("Ingrese el apellido:");
    fflush(stdin);
    leerTexto(datos.nombre2.apell, 15);
    validarVacio(datos.nombre2.apell, 15);    
    printf("Ingrese el nombre:");
    fflush(stdin);
    leerTexto(datos.nombre2.nombre, 15);
    validarVacio(datos.nombre2.nombre, 15);    
    printf("Ingrese la altura:");
    datos.altura=leeyValidaFloat(0);
    printf("Ingrese el sexo:");
    datos.sex=validarSexo();
    fflush(stdin);
    printf("Ingrese la fecha con el siguiente formato (dd/mm/aaaa):");
    scanf("%d/%d/%d",&d, &m, &a);
    while(validarFecha(d,m,a)==false){
        printf("Fecha invalida, reingrese:");
        scanf("%d/%d/%d",&d, &m, &a);
    }
    datos.cumple.dia=d;
    datos.cumple.mes=m;
    datos.cumple.anio=a;
    ingresoMaterias(datos, MATERIAS);
    

    return datos;
}

void mostrarDatos3(PERSONA3 datos){
    printf("--DATOS INGRESADOS--\n");
    printf("%s: %d\n", "NUM LEGAJO", datos.numLegajo);
    printf("%s: %s\n", "APELLIDO", datos.nombre2.apell);
    printf("%s: %s\n", "NOMBRE", datos.nombre2.nombre);
    printf("%s: %.2f\n", "ALTURA", datos.altura);
    printf("%s: %c\n", "SEXO", datos.sex);
    printf("%s: %d/%d/%d\n", "NACIMIENTO", datos.cumple.dia, datos.cumple.mes, datos.cumple.anio);
    mostrarMaterias(datos, MATERIAS);
}

void mostrarMaterias(PERSONA3 datos, int ce){
    printf("\n--LISTADO MATERIAS APROBADAS--");
    for(int i =0; i<ce;i++){
        printf("\n%d. %d", i+1, datos.mAprobadas[i]);
    }
}

void ingresoMaterias(PERSONA3 datos, int ce){
    int cod;
    printf("\n--INGRESO DE CODIGOS DE MATERIAS APROBADAS--");

    for (int i = 0; i <ce ; i++)
    {
        printf("\nIngrese el codigo %d:",i+1);
        cod=leeyvalidaInt(0);
        while(norepite(cod,datos,i)==1){
            printf("\nCODIGO REPETIDO. REINGRESE: ");
            cod=leeyvalidaInt(0);
        }
        datos.mAprobadas[i]=cod;
        
    }
    
}
int leeyvalidaInt(int lim){
    int dato;
    scanf("%d", &dato);
    while(dato<lim){
        printf("\n ERROR-El dato ingresado debe ser mayor a %d. Reingrese:", lim);
        scanf("%d", &dato);
    }
    return dato;
}



int norepite(int aux, PERSONA3 vec, int i){
    int flag=0, j;
    for(j=0; j<i && flag==0; j++){
        if (vec.mAprobadas[j]==aux)
            flag=1;
    }
    return flag;
}

int leeyValidaIntEntre2(int min, int max){
    int dato;
    scanf("%d", &dato);
    getchar();
    while (dato<min || dato>max){
        printf("ERROR - El dato ingresado tiene que encontrarse dentro del rango[%d-%d]: \t", min, max);
        scanf("%d", &dato);
        getchar();
    }
    return dato;
}

float leeyValidaFloat(float lim){
    float dato;
    scanf("%f", &dato);
    getchar();
    while (dato<lim){
        printf("ERROR - La altura ingresada tiene que ser mayor a %f: \t", lim);
        scanf("%f", &dato);
        getchar();
    }
    return dato;
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

void validarVacio(char texto[], int largo) {
    while (strlen(texto) == 0) {
        printf("El texto no puede estar vacio. Ingrese nuevamente: ");
        leerTexto(texto, largo);
    }
}

char validarSexo(){
    char dato;
    scanf("%c", &dato);
    dato=toupper(dato);
    while (dato!='F'&& dato!='M')
    {   
        fflush(stdin);
        printf("El dato no es F o M. Ingrese nuevamente:");
        scanf("%c", &dato);
        dato=toupper(dato);
    }
    return dato;
}

bool validarFecha(int dia, int mes, int anio){
    bool fechaValida = false;
    if (anio> 1900){
        if (mes >=1 && mes <=12){
            if (dia>=1 && dia <= cantDiasMes(mes, anio)){
                fechaValida = true;
            }
        }
    } return fechaValida;
}
int cantDiasMes(int mes, int anio){
    int cantDias =31;
    if(mes == 4 || mes == 6 || mes == 9 || mes == 11){
        cantDias = 30;
    }else{
        if(mes==2){
            cantDias= 28 + esBisiesto(anio);
        }
    }
        
    return cantDias;
}
int esBisiesto(int anio){
    int bisiesto =0;
    if ((anio%4==0 && anio%100!=0)||(anio%400==0))
        bisiesto = 1;
    return bisiesto;
}

