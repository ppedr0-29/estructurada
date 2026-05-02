/*Ejercicio: Sistema de Biblioteca
Una biblioteca registra información de sus socios y los libros que prestó durante el mes.
Se sabe que no son más de 50 socios. Para cada socio se ingresa:
DNI (entero de 8 dígitos). El ingreso finaliza con DNI = 0.
Nombre y apellido (máximo 40 caracteres, no puede estar vacío)
Cantidad de libros prestados en el mes (0 a 15)
Importe total abonado en el mes (mayor o igual a 0, puede no haber abonado nada)
Se solicita:
a) Mostrar el listado completo de socios que pidieron más de 5 libros en el mes, indicando nombre, 
cantidad de libros e importe abonado.
b) Determinar e informar el socio que más importe abonó en el mes. Si no hay socios cargados, 
mostrar un mensaje indicándolo.
c) Informar la cantidad de socios que no abonaron nada (importe = 0).
d) El usuario ingresa un DNI y el sistema debe informar si ese socio existe y en caso afirmativo mostrar 
su nombre e importe abonado. Repetir hasta ingresar DNI = 0.
Restricciones:
No pueden existir dos socios con el mismo DNI
Aplicar todos los paradigmas de la materia
Una función por tarea, prototipos al inicio*/

#include <stdio.h>
#include <string.h>
#define TAM 50
#define CARAC 40

typedef struct
{
    int dni; //8 digitos, ingreso finaliza =0
    char nya[CARAC];
    int cantLibros; //entre 0 a 15
    float importeMes; //mayor o igual a 0
}SOCIO;

int ingreso(SOCIO[], int);
SOCIO ingresoDatos(SOCIO[], int);
void informeA(SOCIO[], int);
void informeB(SOCIO[], int);
void informeC(SOCIO[], int);
void informeD(SOCIO[], int);
int busqueda(SOCIO[], int, int);
float maximoF(SOCIO[], int);
float leeyvalidaFloat(float);
int leeryvalidarentre2(int, int);
int leeryvalidarentre2CF(int, int, int);
int norepite(SOCIO[], int, int);
void leertexto(char[], int);
void validarVacio(char[], int);


int main(){
    SOCIO datos[TAM];
    int cantSocios=ingreso(datos, TAM);
    informeA(datos, cantSocios);
    informeB(datos, cantSocios);
    informeC(datos, cantSocios);
    informeD(datos, cantSocios);

    return 0;
}

int ingreso(SOCIO datos[], int ce){
    SOCIO aux;
    int i=0;
    int flag=0;
    while (flag == 0 && i<ce)
    {   
        aux=ingresoDatos(datos, i);
        if(aux.dni!=0){
            datos[i]=aux;
            i++; 
        }else
            flag=1;
    }
    return i;
}

SOCIO ingresoDatos(SOCIO datos[], int i){
    SOCIO info;
    printf("Ingrese el DNI:");
    info.dni=leeryvalidarentre2CF(10000000,99999999, 0);
    while (norepite(datos, i, info.dni)==1)
    {
        printf("DNI ya ingresado. Reingrese:");
        info.dni=leeryvalidarentre2CF(10000000,99999999, 0);
    }
    if (info.dni!=0)
    {
        printf("Ingrese nombre y apellido:");
        leertexto(info.nya, CARAC);
        validarVacio(info.nya, CARAC);
        printf("Ingrese la cantidad de libros prestados en el mes: ");
        info.cantLibros=leeryvalidarentre2(0,15);
        printf("Ingrese el importe total del mes: $");
        info.importeMes=leeyvalidaFloat(0.0);
        printf("Socio cargado.\n");
    }
    return info;
}

void informeA(SOCIO datos[], int cs){
    printf("--LISTADO CANT LIBROS MAYORES A 5--\n");
    for (int i = 0; i < cs; i++)
    {
        if (datos[i].cantLibros>5)
        {
            printf("-%s Cant Pedida %d Importe $%.2f\n", datos[i].nya, datos[i].cantLibros, datos[i].importeMes);
        }
    }
}

void informeB(SOCIO datos[], int cs){
    if(cs!=0){
        float max=maximoF(datos,cs);
        for(int i=0;i<cs;i++){
            if(datos[i].importeMes==max)
                printf("el socio con mayor importe al mes es %s con un importe de $%.2f\n", datos[i].nya, datos[i].importeMes);
        }
    }else{
        printf("No se ingresaron socios.");
    }
}

void informeC(SOCIO datos[], int cs){
    int acum=0;
    for (int i = 0; i < cs; i++)
    {
        if(datos[i].importeMes==0)
        acum++;
    }
    printf("La cantidad de socios que no abonaron fueron %d", acum);
}

void informeD(SOCIO datos[], int cs){
    int dni;
    int pos;
    printf("\n--BUSQUEDA DE SOCIOS--\n");
    printf("Ingrese el DNI a buscar: ");
    dni=leeryvalidarentre2CF(10000000,99999999,0);
    while(dni!=0){
        pos=busqueda(datos,cs,dni);
        if(pos==-1){
            printf("El DNI ingresado no existe. Reingrese:");
        }else{
            printf("El socio con el dni %d es %s con un total de $%.2f\n", dni, datos[pos].nya, datos[pos].importeMes);
            printf("Ingrese el DNI a buscar: ");
        }
        dni=leeryvalidarentre2CF(10000000,99999999,0);
    }
    printf("BUSQUEDA FINALIZADA");
}

int busqueda(SOCIO datos[], int cs, int dni){
    int pos=-1;
    int i=0;
    while(pos==-1 && i<cs){
        if(datos[i].dni==dni){
            pos=i;
        }else{
            i++;
        }
    }
    return pos;
}


float maximoF(SOCIO datos[], int cs){
    float max=datos[0].importeMes;
    for(int i=1;i<cs;i++){
        if(datos[i].importeMes>max)
            max=datos[i].importeMes;
    }
    return max;
}

float leeyvalidaFloat(float lim){
    float dato;
    scanf("%f", &dato);
    while (dato<lim)
    {
        printf("El importe no es valido. Reingrese: $");
        scanf("%f", &dato);
    }
    return dato;
}

int leeryvalidarentre2(int min, int max){
    int dato;
    scanf("%d", &dato);
    while(dato<min || dato>max){
        printf("ERROR-El dato debe pertenecer al rango[%d-%d]. Reingrese: ", min, max);
        scanf("%d", &dato);
    }
    return dato;
}

int norepite(SOCIO datos[], int i, int dni){
    int flag=0;
    int j=0;
    while(flag==0 &&j<i)
    {
        if (datos[j].dni==dni)
        {
            flag=1;
        }else
            j++;
        
    }
    
    return flag;
}

int leeryvalidarentre2CF(int min, int max, int cf){
    int dato;
    scanf("%d", &dato);
    while ((dato<min || dato>max) && dato!=cf)
    {
        printf("El dato no se encuentra dentro del rango[%d-%d]. Reingrese:", min,max);
        scanf("%d", &dato);
    }
   
    return dato;
}

void leertexto(char texto[], int largo){
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
        leertexto(texto, largo);
    }
}
