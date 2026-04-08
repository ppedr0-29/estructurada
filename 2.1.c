/*2.1 Ingresar una matriz de 3x3 por teclado y un número entero. 
Realizar el producto de la matriz por la constante.*/

#include <stdio.h>

void ingresoMatriz(int [][3], int, int);
int  ingresoEntero();
void producto(int [][3], int [][3], int, int, int);
void mostrarResultado(int [][3], int, int);


int main (){
    int m[3][3], mN[3][3], entero;
    
    ingresoMatriz(m,3,3);
    entero= ingresoEntero();
    producto(m, mN, 3, 3, entero);
    printf("El resultado es\n");
    mostrarResultado(mN, 3, 3);

}

void ingresoMatriz(int m[][3], int cf, int cc){
    int f, c;
    for (f=0; f < cf; f++)
    {
        for (c=0; c < cc; c++)
        {
            printf("Ingrese un numero para fila %d y para columna %d: ", f, c);
            scanf("%d", &m[f][c]);
        }
        
    }
    
}

int  ingresoEntero (){
    int dato;
    printf("Ingrese el entero:");
    scanf("%d", &dato);
    return dato;
}

void producto(int m[][3], int mN[][3], int cf, int cc, int entero){
    for (int f = 0; f<cf; f++)
    {
        for(int c=0; c<cc; c++){
            mN[f][c]= m[f][c]* entero;
        }
    }
}

void mostrarResultado(int mN[][3], int cf, int cc ){
    for (int i = 0; i < cf; i++)
    {
        for (int j = 0; j < cc; j++)
        {
            printf("%4d", mN[i][j]);
        }
        printf("\n");
    }
    
}