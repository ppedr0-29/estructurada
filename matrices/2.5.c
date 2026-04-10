/*2.5 Se desea desarrollar un sistema de reservas de entradas para un cine. La sala consta de 12 filas numeradas de
la 1 a la 12 y cada fila tiene 9 butacas numeradas a partir de la columna central, con las butacas impares a la
derecha y las pares a la izquierda, como en el siguiente esquema:
8 6 4 2 1 3 5 7 9
Para la carga, se debe mostrar al usuario un esquema con las butacas disponibles y reservadas, marcando
con la letra D las disponibles y con la letra R las reservadas.
Por cada reserva se debe solicitar la fila y número de butaca a reservar. Cada vez que se realice una
reserva se deberá actualizar el esquema que muestra las butacas. Si la butaca seleccionada ya estaba
ocupada se debe informar al usuario para que seleccione otra. El proceso de reserva finaliza con una fila
con un número negativo.
Al finalizar mostrar:
a. la cantidad de asientos disponibles y la cantidad de asientos reservados.
b. los números de filas que quedaron vacías.
c. la o las filas con mayor cantidad de espectadores.
d. un listado con la cantidad de personas que se sentaron en los mismos números de butacas en
todo el cine ordenado de mayor a menor. Por ejemplo:
Butaca Cantidad
1         10
4         6
8         2
..............*/

#include <stdio.h> 

void mostrarMatriz(char [][9], int , int, int []);
void iniciarM(char [][9], int , int );
int IngrDatoValRango(int, int);
void ingresoReserva(char [][9], int, int, int []);
int leeyvalidafila(int, int);
int buscarColumna(int [], int, int);

int main (){
    char m[12][9];
    int orden[9] = {8, 6, 4, 2, 1, 3, 5, 7, 9}; //orden de columnas como se pide, vector y asigno valores en [i]
    iniciarM(m, 12,9);
    mostrarMatriz(m,12,9, orden);
    ingresoReserva(m,12,9,orden);
}

void iniciarM(char m[][9], int f, int c){ //forma de inicializar un char
    for(int i=0; i<f; i++){
        for(int j=0; j<c; j++){
            m[i][j]='D';
        }
    }
}

void mostrarMatriz(char m[][9], int f, int c, int orden[]){
    printf("\t    --BUTACAS DISPONIBLES--\n");
    printf("     ");  // espacio para alinear con los números de fila
    for(int j = 0; j < c; j++){
        printf("%4d", orden[j]); //primero recorro vector y printeo orden de columnas
    }
    printf("\n");
    for(int i = 0; i < f; i++){ //recorro fila x columna y printeo matriz
        printf("F%-3d ", i+1);  // número de fila
        for(int j = 0; j < c; j++){
            printf("%4c", m[i][j]);
        }
        printf("\n");
    }
}

int IngrDatoValRango(int min, int max ){
    int dato;
    scanf("%d", &dato);
    while(dato<min || dato>max){
        printf("Error. Ingrese un numero valido entre %d y %d:", min, max);
        scanf("%d", &dato);
    }
    return dato;
}


void ingresoReserva(char m[][9], int f, int c, int orden []){
    printf("Ingrese numero de fila entre 1 y 12:(menor a 0 para finalizar):");
    int fila= leeyvalidafila(0,12);
    int butaca;
    int columna;
    while (fila>0){
        printf("Ingrese numero de butaca entre 1 y 9:");
        butaca= IngrDatoValRango(1,9);
        columna = buscarColumna(orden, 9, butaca);
        if (m[fila-1][columna] == 'R')
        {
            printf("Butaca reservada.\n");
        }else{
            m[fila-1][columna] = 'R';
            printf("Reserva completa Fila %d Butaca %d\n", fila, orden[columna]);
            mostrarMatriz(m, 12, 9, orden);
        }
        printf("Ingrese numero de fila entre 1 y 12:(menor a 0 para finalizar):");
        fila= leeyvalidafila(0,12);
        }
    printf("Ingreso finalizado.");
    }

int buscarColumna(int orden [], int c, int butaca){
    int columna;
    for (int i = 0; i < c; i++)
        {
            if (butaca==orden[i])
            {
                columna=i;
            }
        }
    return columna;
}

int leeyvalidafila(int min, int max){
    int dato;
    scanf("%d", &dato);
    while (dato==min || dato>max)
    {
        printf("Error. Ingrese un valor permitido entre 1 y 12:");
        scanf("%d", &dato);
    }
    return dato;
}