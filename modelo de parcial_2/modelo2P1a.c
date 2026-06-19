/*Realizar programa que invoque función sin retorno y permita ingresar por teclado un 
código (int) y una marca (string). Las variables se muestran en el main luego de invocar la función*/

#include <stdio.h>
#include <string.h>
#define TAM 101
void funcion (int*, char* , int );
int main(){
    int codigo;
    char marca[TAM];//100 caracteres mas el /0
    int *pcodigo=&codigo;
    char *pmarca=marca;
    funcion(pcodigo, pmarca, TAM);
    printf("El codigo ingresado es: %d y la marca: %s", codigo, marca);
    return 0;
}
void funcion (int*pcod, char* pmarca, int tam){
    printf("Ingrese el codigo: ");
    scanf("%d", pcod);
    while(*pcod<0){
        printf("Error. reingrese: ");
        scanf("%d", pcod);
    }
    printf("Ingrese la marca: ");
    fflush(stdin);
    fgets(pmarca, tam, stdin);
    int i=0;
    while(pmarca[i]!='\0'){
        if(pmarca[i]=='\n'){
            pmarca[i]='\0';
        }
        i++;
    }
}