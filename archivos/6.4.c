/*6.4 Realizar un programa que permite actualizar una lista de precios en forma masiva, ingresando un porcentaje
de incremento. El archivo se llama precios.dat y fue generado utilizando la siguiente estructura:
• Código (entero)
• Precio (float)
• Descripción (de hasta 50 caracteres)*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

typedef struct 
{
    int codigo;
    float precio;
    char desc[51];
}ART;

int leeyvalInt(int);

int main(){
    int porcentaje;
    float incremento;
    ART datos;
    FILE *art;
    printf("Ingrese porcentaje de incremento:");
    porcentaje=leeyvalInt(0);

    art=fopen("precios.dat", "r+b");
    if (art==NULL)
    {
        printf("Error al abrir el archivo.");
        getch();
        exit(1);
    }
    
    fread(&datos, sizeof(datos), 1, art);
    while (!feof(art))
    {
        incremento = (porcentaje*datos.precio)/100.0;
        datos.precio+=incremento;
        fseek(art, (long)-sizeof(datos), SEEK_CUR);
        fwrite(&datos, sizeof(datos), 1, art);
        fflush(art);
        fread(&datos, sizeof(datos), 1, art);
    }
    
    fclose(art);
}

int leeyvalInt(int lim){
    int dato;
    scanf("%d", &dato);
    while (dato<=lim)
    {
        printf("Error. Reingrese");
        scanf("%d", &dato);
    }
    return dato;
}