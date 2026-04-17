/*3.1 Ingresar una frase de hasta 500 caracteres y contar cuántas palabras contiene dicha frase.
a. Considerar que las palabras están separadas por un único espacio.
b. Considerar que las palabras pueden estar separadas por más de un espacio consecutivo.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 500

void ingresoFrase(char []);
void leerTexto(char [], int);
int contarPalabras(char []);


int main(){
    char frase[TAM];
    int cant;
    ingresoFrase(frase);
    cant = contarPalabras(frase);
    printf("La cantidad de palabras es %d", cant);
}

void ingresoFrase(char frase[]){
    printf("Ingrese una frase (hasta 500 caracteres):");
    leerTexto(frase, TAM);
    while (strlen(frase)==0)
    {
        printf("\nLa frase no puede estar vacia. Ingrese nuevamente:");
        leerTexto(frase, TAM);
    }
    
}


void leerTexto(char texto[], int largo) //lee y guarda frase ingresada
{
    int i;
    fgets(texto, largo, stdin);
    i = 0;
    while (texto[i] != '\0')
    {
        if (texto[i] == '\n')
            texto[i] = '\0';
        else
            i++;
    }
}

int contarPalabras(char frase[]){
    char anterior=' '; //arrancamos con un espacio anterior
    int cant=0; //variable acum
    for (int i = 0; frase[i]!='\0'; i++) //recorre mientras la frase no finalice
    {
        if (frase[i]!=' ' && anterior==' ')
        {
            cant= cant+1;
        }
        anterior= frase[i]; //guardamos la frase en la variable anterior
    }
    return cant;
}