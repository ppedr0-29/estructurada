/*Una agencia necesita liquidar las comisiones de sus vendedores y para ello dispone del archivo ventas.dat con la siguiente estructura:
Vendedor (string de 4 caracteres)
Nombre Vendedor (string de 30 caracteres)
Sector (H – Hogar, E – Electrodomésticos, B – Bazar, T – Telefonía)
Porcentaje de comisión (entero entre 5 y 30)
Comisión a cobrar (real)
Luego por cada vendedor se ingresa por teclado el Vendedor, Sector y el importe vendido en el mes (real positivo). 
En base al porcentaje de comisión y el importe vendido se debe actualizar la comisión a cobrar en el archivo. 
En caso de no encontrar el Vendedor en el archivo debe guardarse el error en un archivo llamado Errores.dat con la siguiente estructura 
(Vendedor, Sector y el importe vendido) .
El ingreso de las ventas termina con el ingreso de un vendedor igual a "FFFF".
Además, se necesita determinar e informar:
El nombre del vendedor que cobra la mínima comisión actualizada, en caso de ser más de uno mostrar a todos.
El porcentaje de comisiones a pagar por cada sector respecto del total vendido (resolver en una función).
Validar todos los datos que ingresan por teclado según lo indicado.
El código debe estar correctamente identado.*/

/*abrir ventas.dat ("r+b"), abrir Errores.dat ("wb")
impSector[4] = {0,0,0,0}   // H, E, B, T -> índices 0..3
comSector[4] = {0,0,0,0}

ingreso vendedor, sector, importe (con validación: sector debe ser H/E/B/T, importe>0)

while(vendedor != "FFFF")
    pos = busqueda(archVentas, vendedor, &reg)   // rewind interno, devuelve pos o -1

    si pos != -1{
        reg.comision += (importe * reg.porcentaje) / 100
        fseek(archVentas, pos, SEEK_SET)
        fwrite(&reg, sizeof(reg), 1, archVentas)
        fflush(archVentas)

        i = indiceSector(sector)        // mapea 'H','E','B','T' -> 0,1,2,3
        impSector[i] += importe
        comSector[i] += (importe * reg.porcentaje) / 100
    }
    si no{
        error.vendedor = vendedor
        error.sector = sector
        error.importe = importe
        fwrite(&error, sizeof(error), 1, archErrores)
    }

    ingreso vendedor, sector, importe (validado)
fin while

cerrar archVentas, archErrores

// recién ACÁ, fuera del while:
minimo = buscarMinimo(archVentas)        // recorre TODO el archivo, primero/flag, sin tocar impSector ni comSector
int primero=1
if(primero==1)
min=com
primero=0;
else
if com<min
min=com
mostrarMinimo(archVentas, minimo)        // recorre de nuevo, imprime nombre de cada uno con comision==minimo

porcentajePorSector(impSector, comSector)   // NO recibe el archivo, ya tiene todo acumulado
    for i = 0 hasta 3
        si impSector[i] > 0
            porcentaje = (comSector[i] / impSector[i]) * 100
            mostrar sector i, porcentaje
        si no
            mostrar "sector sin ventas este mes"*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct
{
    char vendedor[5];
    char nomVen[31];
    char sec;
    int por_com; //entre 5 y 30
    float com;
}VENTAS;

typedef struct
{
    char vendedor[5];
    char sec;
    float imp;
}ERRORES;

void mostrarMinimo(FILE *, float );
void procesarArchivo();
float buscarMinimo(FILE *);
int indice(char );
long busqueda(FILE *, char [], VENTAS *);
void leeyvalC(char *);
void leerTexto(char [], int );
void valVacio(char [], int );
void leeyvalF(float , float *);
FILE *abrirArchivo(char [], char []);
void porcxSector(float [], float []);

int main(){
    procesarArchivo();
}

void procesarArchivo(){
    FILE *arch;
    FILE *archE;
    VENTAS datos;
    VENTAS *pdatos=&datos;
    ERRORES aux;
    char *psec=&aux.sec;
    float *pimp=&aux.imp;
    long pos;
    int i;
    float minimo;
    float impSector[4]={0};
    float comSector[4]={0};
    arch=abrirArchivo("ventas.dat", "r+b");
    archE=abrirArchivo("errores.dat", "wb");
    printf("Ingrese vendedor(FFFF para finalizar): ");
    leerTexto(aux.vendedor, 5);
    valVacio(aux.vendedor, 5);
    while (strcmpi(aux.vendedor, "FFFF")!=0)
    {
        printf("Ingrese el sec (H-E-B-T): ");
        leeyvalC(psec);
        printf("Ingrese el importe: ");
        leeyvalF(0,pimp);
        pos=busqueda(arch, aux.vendedor, pdatos);
        if (pos!=-1)
        {
            datos.com+=(aux.imp*datos.por_com)/100;
            fseek(arch, pos, SEEK_SET);
            fwrite(&datos, sizeof(datos), 1, arch);
            fflush(arch);
            i=indice(*psec);
            impSector[i]+=*pimp;
            comSector[i]+=(*pimp*datos.por_com)/100;
        }else{
            fwrite(&aux, sizeof(aux), 1, archE);
        }
        printf("Ingrese vendedor(FFFF para finalizar): ");
        leerTexto(aux.vendedor, 5);
        valVacio(aux.vendedor, 5);
    }
    

    minimo= buscarMinimo(arch);
    mostrarMinimo(arch, minimo);
    porcxSector(impSector, comSector);

    fclose(arch);
    fclose(archE);
}

void porcxSector(float imp[], float com[]){
    float porcentaje;
    for (int i = 0; i < 4; i++)
    {
        if (imp[i]>0)
        {
            porcentaje=(com[i]/imp[i])*100;
            if (i==0)
            {
                printf("El porcentaje a cobrar es %.2f en el sector HOGAR\n", porcentaje);
            }
            else if (i==1)
            {
                printf("El porcentaje a cobrar es %.2f en el sector ELECTRODOMESTICOS\n", porcentaje);
            }
            else if (i==2)
            {
                printf("El porcentaje a cobrar es %.2f en el sector BAZAR\n", porcentaje);
            }else{
                printf("El porcentaje a cobrar es %.2f en el sector TELEFONIA\n", porcentaje);
            }
        }
        
    }
    
}

void mostrarMinimo(FILE *arch, float min){
    VENTAS datos;
    rewind(arch);
    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch))
    {
        if (datos.com==min)
        {
            printf("El vendedor %s cobra la minima comision %.2f actualizada\n", datos.vendedor, datos.com);
        }
        fread(&datos, sizeof(datos), 1, arch);
    }
    
}

float buscarMinimo(FILE *arch){
    VENTAS datos;
    float min;
    int primero=1;

    rewind(arch);
    fread(&datos, sizeof(datos), 1, arch);
    while(!feof(arch))
    {
        if(primero==1){
            min=datos.com;
            primero=0;
        }else{
            if(datos.com<min)
                min=datos.com;
        }
        fread(&datos, sizeof(datos), 1, arch);
    }
    return min;
}

int indice(char sector){
    int i;
    switch (sector)
    {
    case 'H':
        i=0;
        break;
    case 'E':
        i=1;
        break;
    case 'B':
        i=2;
        break;
    case 'T':
        i=3;
        break;
    }
    return i;
}

long busqueda(FILE *arch, char texto[], VENTAS *pdatos){
    VENTAS datos;
    long pos=-1;
    int flag=0;
    rewind(arch);
    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch) && flag==0)
    {
        if (strcmpi(texto,datos.vendedor)==0)
        {
            flag=1;
            pos=ftell(arch)-sizeof(datos);
            *pdatos=datos;
        }
        fread(&datos, sizeof(datos), 1, arch);
    }
    return pos;
}

void leeyvalC(char *dato){
    fflush(stdin);
    scanf("%c", dato);
    while (*dato!='H' && *dato!='E' && *dato!='B' && *dato!='T')
    {
        printf("Error. Reingrese: ");
        fflush(stdin);
        scanf("%c", dato);
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

void valVacio(char texto[], int largo){
    while (strlen(texto)==0)
    {
        printf("Error. Reingrese: ");
        leerTexto(texto, largo);
    }
}

void leeyvalF(float lim, float *dato){
    scanf("%f", dato);
    while (*dato<=lim)
    {
        printf("Error. Reingrese: ");
        scanf("%f", dato);
    }
}

FILE *abrirArchivo(char nombre[], char tipo[]){
    FILE *arch;
    arch=fopen(nombre, tipo);
    if (arch==NULL)
    {
        printf("Error.");
        getch();
        exit(1);
    }
    return arch;
}