/*2.3 Cargar de forma aleatoria una matriz de 5 x 8 con números de 2 cifras. Determinar el máximo valor
almacenado en la matriz indicando cuantas veces se repite y en que posiciones.*/

#include <stdio.h> 
#include <time.h>

void cargaAleatoria(int [][], int, int, int);

int main(){
    int m[5][8];
    srand(time(NULL));
    cargaAleatoria(m, 5, 8, 100);
    return 0;
}


void cargaAleatoria(int m[][8], int f, int c, int max){
    for (int i = 0; i < f; i++)
    {
        for (int j = 0; j < c; j++)
        {
            m[i][j]=rand()%max;
        }
    }
    
}