/*5.3 Realizar una función que permita ingresar por teclado un valor entero, un flotante y un carácter. La función
no debe retornar ningún valor. Las variables se declaran y se muestran en el programa principal.*/

#include <stdio.h>

void ingreso(int *, float *, char *);

int main (){
    int entero, *pentero=&entero;
    float f, *pf=&f;
    char c, *pc=&c;
    ingreso(pentero, pf, pc);
    printf("El entero es %d\n", *pentero);
    printf("El flotante es %.2f\n", *pf);
    printf("El caracter es %c\n", *pc);

    return 0;
}

void ingreso(int *pentero, float *pf, char *pc){
    printf("Ingrese el valor entero:");
    scanf("%d", pentero);
    printf("Ingrese un valor flotante:");
    scanf("%f", pf);
    fflush(stdin);
    printf("Ingrese un caracter:");
    scanf("%c", pc);
}