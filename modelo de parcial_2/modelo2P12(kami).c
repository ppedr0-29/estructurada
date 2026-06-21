/*La empresa SALES dispone de un archivo llamado Stock.dat que contiene la información de los productos que vende.
El archivo contiene la siguiente información:
Código de artículo (string de 4 caracteres)
Descripción (50 caracteres máximo)
Stock (entero)
Luego se ingresan por teclado las compras realizadas indicando:
Código de artículo (string de 4 caracteres)
Cantidad vendida (entero mayor a cero)
La carga por teclado de las ventas finaliza con un código de artículo "SALE".
Por cada venta se debe controlar si existe el artículo (resolver en una Función llamada BUSCAR) si no existe solicitar nuevamente y si existe, 
actualizar el stock de dicho producto, sino hay stock suficiente grabar un registro en un archivo Errores.dat con la cantidad que no pudo vender, 
dicho registro debe contener:
Código de artículo
Cantidad
Si ya hay un registro previo en dicho archivo de errores con el mismo artículo debe incrementarse la cantidad. Informar al final la cantidad de 
ventas realizadas y la cantidad de ventas no realizadas utilizando la función INFORME.
Validar todos los datos que ingresan por teclado según lo indicado.
El código debe estar correctamente identado.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct {
    char codigo[5];
    char descripcion[51];
    int stock;
} PROD;

typedef struct {
    char codigo[5];
    int cantidad;
} ERROR;

// Declaración de funciones
void leerTexto(char[], int);
void leeyvalTex(char[], int);
void ProcesarArchivo();
FILE* abrirArchivo(char[], char[]);
long busqueda(FILE*, char[], PROD*);
void leeyvalInt(int*, int);
void errores(ERROR);
void INFORME(int, int);

int main() {
    ProcesarArchivo();
    return 0;
}

void ProcesarArchivo() {
    FILE* arch = abrirArchivo("stock.dat", "r+b");
    PROD datos;
    ERROR info;
    int cantVentas = 0, cantNoVentas = 0;
    long pos;

    printf("Ingrese el codigo: ");
    leeyvalTex(info.codigo, 5);
    while (strcmpi(info.codigo, "SALE") != 0) {
        pos = busqueda(arch, info.codigo, &datos);
        while (pos == -1) {
            printf("Reingrese: ");
            leeyvalTex(info.codigo, 5);
            pos = busqueda(arch, info.codigo, &datos);
        }
        
        printf("Ingrese la cant rendida: ");
        leeyvalInt(&info.cantidad, 0);
        
        if (info.cantidad > datos.stock) {
            cantNoVentas++;
            errores(info);
        } else {
            datos.stock -= info.cantidad;
            cantVentas++;
            fseek(arch, pos, SEEK_SET);
            fwrite(&datos, sizeof(datos), 1, arch);
            fflush(arch);
        }
        printf("Ingrese el codigo: ");
        leeyvalTex(info.codigo, 5);
    }
    INFORME(cantVentas, cantNoVentas);
    fclose(arch);
}

void INFORME (int cantVentas, int cantNoVentas){
    printf("Se realizaron %d ventas y %d ventas no pudieron realizarse\n", cantVentas, cantNoVentas);
}

void leeyvalTex(char texto[], int largo) {
    leerTexto(texto, largo);
    while (strlen(texto) == 0) {
        printf("El texto no puede ser vacio");
        leerTexto(texto, largo);
    }
}

long busqueda(FILE* arch, char cod[], PROD* pDatos) {
    long pos = -1;
    PROD datos;
    int flag = 0;
    rewind(arch);
    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch) && flag == 0) {
        if (strcmpi(datos.codigo, cod) == 0) {
            flag = 1;
            pos = ftell(arch) - sizeof(datos);
            *pDatos = datos;
        }
        fread(&datos, sizeof(datos), 1, arch);
    }
    return pos;
}

FILE* abrirArchivo(char nombre[], char tipo[]) {
    FILE* arch = fopen(nombre, tipo);
    if (arch == NULL) {
        printf("ERROR al abrir el archivo...");
        getch();
        exit(1);
    }
    return arch;
}

void leerTexto(char texto[], int largo) {
    fflush(stdin);
    fgets(texto, largo, stdin);
    int i = 0;
    while (texto[i] != '\0') {
        if (texto[i] == '\n')
            texto[i] = '\0';
        i++;
    }
}

void leeyvalInt(int* dato, int lim) {
    scanf("%d", dato);
    while (*dato <= lim) {
        printf("Error. Reingrese: ");
        scanf("%d", dato);
    }
}

void errores(ERROR info) {
    FILE* arch = fopen("errores.dat", "r+b");//no se puede llamar a abrir archivo porque si no existe sale del programa
    if (arch == NULL)
        arch = abrirArchivo("errores.dat", "w+b");
    
    ERROR datos;
    int flag = 0;
    long pos;
    
    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch)&&flag ==0) {
        if (strcmpi(datos.codigo, info.codigo) == 0) {
            flag = 1;
            pos = ftell(arch) - sizeof(datos);
        }
        fread(&datos, sizeof(datos), 1, arch);
    }

    if (flag == 0) {
        fseek(arch, 0, SEEK_END);
        fwrite(&info, sizeof(info), 1, arch);
        fflush(arch);
    } else {
        fseek(arch, pos, SEEK_SET);
        datos.cantidad += info.cantidad;
        fwrite(&datos, sizeof(datos), 1, arch);
        fflush(arch);
    }
    fclose(arch);
}