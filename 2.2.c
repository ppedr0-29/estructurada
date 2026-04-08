/*2.2 Ingresar una matriz de 5x4 por teclado. 
Realizar una función que genere un vector 
con la suma por fila de
dicha matriz y otra función que calcule la suma 
por columna en otro vector.*/

#include <stdio.h>

void ingresarMatriz(int [5][4], int , int);
void sumafilaM(int [][4], int , int , int []);
void MostrarVecF(int [], int);
void sumacolM(int [][4], int , int , int []);
void MostrarVecC(int [], int);


int main(){
    int m[5][4];
    int vf[5];
    int vc[4];
    ingresarMatriz(m, 5, 4);
    sumafilaM(m, 5, 4, vf);
    MostrarVecF( vf, 5);
    sumacolM(m, 5, 4, vc);
    MostrarVecC( vc, 4);

}

void ingresarMatriz(int m[5][4], int f, int c){
    for (int i = 0; i < f; i++)
    {
        for (int j = 0; j < c; j++)
        {
            printf("Ingrese un numero para fila %d y para columna %d: ", i, j);
            scanf("%d", &m[i][j]);
        }
        
    }
    
}

void sumafilaM(int m[5][4], int f, int c, int vf[]){
    int suma;
    for (int i = 0; i < f; i++)
    {
        suma=0;
        for (int j = 0; j<c; j++)
        {
            suma += m[i][j];
        }
        vf[i]=suma;
    }
    
}

void MostrarVecF(int vf[],int f){
    printf("\nSuma por filas:\n");
    for(int i=0;i<f;i++){
        printf("%d ",vf[i]);
    }
}

void sumacolM(int m[5][4], int f, int c, int vc[]){
    int suma;
    for (int j = 0; j < c; j++)
    {
        suma=0;
        for (int i = 0; i<f; i++)
        {
            suma += m[i][j];
        }
        vc[j]=suma;
    }
    
}

void MostrarVecC(int vc[],int c){
    printf("\nSuma por columnas:\n");
    for(int j=0;j<c;j++){
        printf("%d ",vc[j]);
    }
}