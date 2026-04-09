/*2.4 La empresa de turismo GUADALAJARA VIAJES comercializa 10 diferentes tours a través de 15 agencias en todo
el país. Diariamente cada agencia envía la cantidad de ventas efectuadas de cada tour, indicando agencia,
tours y la cantidad de pasajes. Algunas agencias envían 0 en la cantidad cuando no existen pasajes para un
tour determinado, pero no en todas.
La información que se envía tiene los siguientes datos que se ingresan en forma desordenada:
• Código de agencia (de 1 a 15)
• Código de tour (1 a 10)
• Cantidad de pasajes (0 a 20)
Informar:
a. El total de pasajes vendidos por tour en cada agencia.
b. El número de agencia que obtuvo la máxima cantidad de pasajes vendidos. (puede repetirse)*/

#include <stdio.h>

void ingresoMatriz(int [][15], int, int);
int IngrDatoValRango(int , int);
int ingrDatoVal(int);
void mostrarMatriz(int [][15], int, int);


int main (){
    int m[10][15]= {{0}};
    ingresoMatriz(m, 10, 15);
    mostrarMatriz(m, 10, 15);

}

void ingresoMatriz(int m[][15], int f, int c){
    printf("Ingrese cantidad(entre 0 y 20):");
    int cant= IngrDatoValRango(0,20);
    int agencia, tour;

    while (cant!=0)
    {
        printf("Ingrese tour (entre 1 a 10):");
        tour=IngrDatoValRango(1,10);
        printf("Ingrese agencia (entre 1 a 15):");
        agencia= IngrDatoValRango(1,15);
        m[tour-1][agencia-1] += cant;
        printf("Ingrese cantidad(entre 0 y 20):");
        cant= IngrDatoValRango(0,20);
    }
    printf("Ingreso finalizado.");
}


int IngrDatoValRango(int min, int max ){
    int dato;
    scanf("%d", &dato);
    while(dato<min || dato>max){
        printf("Error. Ingrese un dato valido entre %d y %d:", min, max);
        scanf("%d", &dato);
    }
    return dato;
}

int ingrDatoVal(int lim){
    int dato;
    scanf("%d", &dato);
    while(dato<=lim){
        printf("Error. Ingrese un dato mayor a %d:", lim);
        scanf("%d", &dato);
    }
    return dato;
}

void mostrarMatriz(int m[][15], int f, int c){
    printf("\n-- PASAJES POR TOUR Y AGENCIA --\n");
    printf("        ");
    for(int j = 0; j < c; j++){
        printf("Ag%-4d", j+1);
    }
    printf("\n");
    for(int i = 0; i < f; i++){
        printf("Tour %-3d ", i+1);
        for(int j = 0; j < c; j++){
            printf("%-6d", m[i][j]);
        }
        printf("\n");
    }
}