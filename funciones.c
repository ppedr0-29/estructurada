/*Funciones reutilizables*/
#include <stdio.h>
#include <stdbool>
//se usa nombre del dato=llamado de funcion
int leeyValidaInt(int lim){
    int dato;
    scanf("%d", &dato);
    while (dato<lim){
        printf("\nERROR - El dato ingresado tiene que ser mayor o igual a %d: \t", lim);
        scanf("%d", &dato);
    }
    return dato;
}
//se usa nombre del dato=llamado de funcion
float leeyValidaFloat(float lim){
    float dato;
    scanf("%f", &dato);
    while (dato<lim){
        printf("\nERROR - El dato ingresado tiene que ser mayor o igual a %d: \t", lim);
        scanf("%f", &dato);
    }
    return dato;
}
//se usa nombre del dato=llamado de funcion
int leeyValidaIntEntre2(int min, int max){
    int dato;
    scanf("%d", &dato);
    while (dato<=min || dato>=max){
        printf("\nERROR - El dato ingresado tiene que encontrarse dentro del rango[%d-%d]: \t", min, max);
        scanf("%d", &dato);
    }
    return dato;
}
//se usa nombre del dato=llamado de funcion
float leeyValidaFloatEntre2(float min, float max ){
    float dato;
    scanf("%f", &dato);
    while (dato<=min || dato >=max){
        printf("\nERROR - El dato ingresado tiene que encontrarse dentro del rango[%d-%d]: \t", min, max);
        scanf("%f", &dato);
    }
    return dato;
}
//busca un numero en un vec y devuelve la posicion
int busqueda(int vec[], int ce, int dato){
    int i=0;
    int p=-1;
    while(vec[i] != dato && i<ce)
        i++;
    if(i!=ce)
        p = i;
    return p;
}
//busca un char en un vec y devuelve la posicion
int busquedaCH(char vec[], int ce, char dato){
    int i=0;
    int p=-1;
    while(vec[i] != dato && i<ce)
        i++;
    if(i!=ce)
        p = i;
    return p;
}
//calcula el resto
int calculaResto(int dividendo, int divisor){
    int resto = dividendo%divisor;
    return resto;
}
//es par 1, es impar 0
int esPar(int num){
    int par=0;
    if(calculaResto(num,2)==0)
        par = 1;
    return par;
}
//es primo 1, no es primo 0
int esPrimo(int num){
    int primo =1;
    for (int i =2; i < num; i++){
        if(calculaResto(num,i)==0){
            primo = 0;
        }
    }
    return primo;
}
//hay que multiplicarlo por 100
float promedio (int acumulador, int contador){
    float prom =0.0;
    if(contador > 0)
        prom = (float)acumulador/contador;
    return prom;
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

int calculoEdad(int dH, int mH, int aH, int dN, int mN, int aN){
    int e = aH - aN;
    if (mH<mN || (mH==mN && dH<dN))
        e--;
    return e;
}

int buscarElementoMayor(int vec[], int ce){
    int mayor = vec[0];
    for (int i=0; i<ce;i++){
        if(vec[i]>mayor)
            mayor=vec[i];
    }
    return mayor;
}
int buscarPosicionElemMayor(int V[], int ce){
    int p, i, max;
    for(i=0; i<ce; i++)
    if(i==0 || V[i]>max){
        max=V[i];
        p=i;
    }
    return p;
}
int buscarPosicion(int vec[], int ce, int dato){
    int pos=-1;
    for(int i=0;i<ce;i++){
        if(vec[i]==dato)
            pos=i;
    }
    return pos;
}

//ordena de menor a mayor un vector 
void burbujeomaM (int V[], int ce)
{
    int AUX, j, cota = ce - 1;
    int desordenado = 1;

    while (desordenado)
    {
        desordenado = 0;
        for (j = 0; j < cota; j++)
        {
            if (V[j] > V[j + 1])
            {
                AUX = V[j];
                V[j] = V[j + 1];
                V[j + 1] = AUX;
                desordenado = j;
            }
        }
        cota = desordenado;
    }
}