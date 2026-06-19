/*7.3 Realizar un programa que genere un archivo llamado “agenda.txt” en el cual se almacene los siguientes datos
ingresados por teclado:
• Apellido
• Nombre
• Correo electrónico
• Teléfono
El ingreso se datos finaliza con apellido y nombre igual a “FINALIZAR”. Utilice el separador ; (punto y coma)
entre campos.*/

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
int leeyvalIntE2CF(int , int );

int main(){
    FILE* arch;
    Agenda datos;
    arch=fopen("agenda.txt", "wt");
    if (arch==NULL)
    {
        printf("Error.");
        getch();
        exit(1);
    }
    fprintf(arch, "NOMBRE;APELLIDO;CORREO;TELEFONO\n");
    printf("Ingrese nombre: ");
    leerTexto(datos.nombre, 100);
    printf("Ingrese apellido: ");
    leerTexto(datos.apellido, 100);
    while ((strcmpi(datos.apellido, "FINALIZAR") != 0 && strcmpi(datos.nombre, "FINALIZAR") != 0))
    {
        printf("Ingrese correo: ");
        leerTexto(datos.correo, 100);
        printf("Ingresa telefono: ");
        datos.tel=leeyvalIntE2CF(1100000000, 1199999999);
        fprintf(arch, "%d;%s;%s;%s\n",datos.tel, datos.nombre,datos.apellido, datos.correo);
        printf("Ingrese nombre: ");
        leerTexto(datos.nombre, 100);
        printf("Ingrese apellido: ");
        leerTexto(datos.apellido, 100);
    }
    
    fclose(arch);

    return 0;
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

int leeyvalIntE2CF(int min, int max){
    int dato;
    scanf("%d", &dato);
    while ((dato<min || dato>max))
    {
        printf("Error. Reingrese: ");
        scanf("%d", &dato);
    }
    return dato;
}