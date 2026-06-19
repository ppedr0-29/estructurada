/*7.4 Realizar un programa que permita buscar un contacto en el archivo de agenda generado en punto anterior,
por apellido o nombre y mostrar el / los datos coincidentes si los hay.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct
{
    char nombre[100];
    char apellido[100];
    char correo[100];
    int tel;
}Agenda;

void leerTexto(char [], int );

int main(){
    FILE* arch;
    Agenda datos;
    char auxT[100];
    arch=fopen("agenda.txt", "rt");
    if (arch==NULL)
    {
        printf("Error.");
        getch();
        exit(1);
    }
    fgets(auxT, 100, arch);
    printf("Ingrese el apellido a buscar: ");
    leerTexto(auxT, 100);
    fscanf(arch, "%d;%s;%s;%s", &datos.tel, datos.nombre, datos.apellido, datos.correo);
    while (!feof(arch))
    {   
        if (strcmpi(datos.apellido, auxT)==0)
        {
            printf("Nombre:%s\nApellido:%s\nCorreo:%s\nTel:%d\n", datos.nombre, datos.apellido, datos.correo, datos.tel);
        }else{
            printf("%s no es igual a %s\n", auxT, datos.apellido);//esto lo escribi para saber que leia y lee h
        }
        fscanf(arch, "%d;%s;%s;%s", &datos.tel, datos.nombre, datos.apellido, datos.correo);
    }
    
}



void leerTexto(char texto[], int largo){
    fflush(stdin);
    fgets(texto, largo, stdin);
    int i=0;
    while (texto[i]!='\0')
    {
        if (texto[i]=='\n')
        {
            texto[i]='\0';
        }else{
            i++;
        }   
    }
}