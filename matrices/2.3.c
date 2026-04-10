/*2.3 Cargar de forma aleatoria una matriz de 5 x 8 con números de 2 cifras. Determinar el máximo valor
almacenado en la matriz indicando cuantas veces se repite y en que posiciones.*/

#include <stdio.h> 
#include <time.h>

void cargaAleatoria(int [][8], int, int, int);
void mostrarMatriz(int [][8], int, int);
int Maximo(int [][8], int, int);
void repite(int [][8], int, int, int);

int main(){
    int m[5][8], maximo;
    srand(time(NULL));
    cargaAleatoria(m, 5, 8, 90);
    mostrarMatriz(m, 5,8);
    maximo= Maximo(m, 5,8);
    repite(m, 5,8, maximo);

    return 0;
}

void cargaAleatoria(int m[][8], int f, int c, int max){
    for (int i = 0; i < f; i++)
    {
        for (int j = 0; j < c; j++)
        {
            m[i][j]=rand()%max + 10;
        }
    }
}

void mostrarMatriz(int m[][8], int f, int c ){
    for (int i = 0; i < f; i++)
    {
        for (int j = 0; j < c; j++)
        {
            printf("%4d", m[i][j]);
        }
        printf("\n");
    }
}

int Maximo(int m[][8], int f, int c){
    
    int max= m[0][0];
    for (int i = 0; i < f; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (max<m[i][j])
            {
                max=m[i][j];
            }
        }
    }
    return max;
}

void repite(int m[][8], int f, int c, int max){
    int cantp=0;
    for (int i = 0; i < f; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if(m[i][j]==max){
                cantp++;
                printf("\nEl maximo se encuentra en la fila %d y la columna %d", i, j);
            }
        }
}
    if(cantp==1){
    printf("\nNo se repite el maximo.");
        }else{
    printf("\nSe repite %d veces", cantp);
    }
}