/*Una cadena de artículos del hogar necesita liquidar comisiones de sus casi 50 vendedores y para ello se deben registrar 
y almacenar con la estructura adecuada:
Número de Vendedor (entero de 2 cifras no correlativo y sin repetidos)
Nombre Vendedor (string de 25 caracteres)
Sector (E – Electrodomésticos, M – Muebles, V – Vajillas, T – Telefonía)
Porcentaje de comisión (entero entre 5 y 15)
Comisión a cobrar (real)
La liquidación de comisiones termina con el ingreso de un número de vendedor igual a cero.
Luego por cada vendedor se ingresarán las ventas que hizo por cada día (real mayor o igual que 0) en los 21 días del mes y 
debe actualizar la comisión a cobrar. También finaliza con un número de vendedor igual a cero.
Se necesita determinar e informar:
Listado de comisiones cobradas por día y vendedor mostrando su nombre (resolver en una función).
El nombre del vendedor que cobra la menor comisión actualizada, en caso de ser más de uno mostrarlos a todos.
El importe total a pagar de comisiones por cada sector (resolver en una función).
Validar todos los datos que ingresan por teclado según lo indicado.
El código debe estar correctamente identado.*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define TAM 50
#define CARAC 25

typedef struct {
    int numVen;
    char nomVen[CARAC];
    char sector;
    int porCom;
    float comAcob;
}VENDEDOR;

VENDEDOR ingresoDatos(VENDEDOR datos[], int i);
int ingreso(VENDEDOR datos[], int ce);
int busqueda(VENDEDOR datos[], int cv, int numVen2);
void actCom(VENDEDOR datos[], int cv, float v[][21]);
void listado(float v[][21], int f, int c, VENDEDOR datos[]);
void menCom(VENDEDOR datos[], int cv);
void impTotal(VENDEDOR datos[], int cv);
void leertexto(char texto[], int largo);
void valVacio(char texto[], int largo);
int leeYvalIntE2CF(int min, int max, int cf);
int norepite(VENDEDOR datos[], int i, int num);
char valSector();
int leeYvalIntE2(int min, int max);
float leeYvalFloat(float lim);
float minimo(int cv, VENDEDOR datos[]);

int main() {
    VENDEDOR datos[TAM];
    float v[TAM][21];
    int cantVend = ingreso(datos, TAM);

    if (cantVend != 0) {
        actCom(datos, cantVend, v);
        listado(v, cantVend, 21, datos);
        menCom(datos, cantVend);
        impTotal(datos, cantVend);
    } else {
        printf("Programa finalizado.");
    }
    return 0;
}

VENDEDOR ingresoDatos(VENDEDOR datos[], int i) {
    VENDEDOR info;

    printf("Ingrese numero de vendedor (0 fin): ");
    info.numVen = leeYvalIntE2CF(10, 99, 0);
    while (norepite(datos, i, info.numVen) == 1) {
            printf("El num se repite. Reingrese: ");
            info.numVen = leeYvalIntE2CF(10, 99, 0);
        }
    if (info.numVen != 0) {
        printf("Ingrese Nombre del vendedor: ");
        leertexto(info.nomVen, CARAC);
        valVacio(info.nomVen, CARAC);
        printf("Ingrese sector (E-M-V-T): ");
        info.sector = valSector();
        printf("Ingrese porcentaje de comision: ");
        info.porCom = leeYvalIntE2(5, 15);
        info.comAcob=0;
    }
    return info;
}

int ingreso(VENDEDOR datos[], int ce) {
    VENDEDOR aux;
    int flag = 0, i = 0;
    printf("--LISTADO DE VENDEDORES--\n");
    while (flag == 0 && i < ce) {
        aux = ingresoDatos(datos, i);
        if (aux.numVen != 0) {
            datos[i] = aux;
            i++;
        } else {
            flag = 1;
        }
    }
    return i;
}

int busqueda(VENDEDOR datos[], int cv, int numVen2) {
    int pos = -1, i = 0;
    while (pos == -1 && i < cv) {
        if (datos[i].numVen == numVen2) {
            pos = i;
        } else {
            i++;
        }
    }
    return pos;
}

int norepite(VENDEDOR datos[], int i, int num) {
    int flag = 0, j = 0;
    while (flag == 0 && j < i) {
        if (datos[j].numVen == num) {
            flag = 1;
        } else {
            j++;
        }
    }
    return flag;
}

void actCom(VENDEDOR datos[], int cv, float v[][21]) {
    int numVen2, pos;
    float totVentas;
    printf("--ACTUALIZAR COMISIONES--\n");
    printf("Ingrese numero del vendedor: ");
    numVen2 = leeYvalIntE2CF(10, 99, 0);
    while (numVen2 != 0) {
        pos = busqueda(datos, cv, numVen2);
        if (pos == -1) {
            printf("No se encontro el vendedor. Reingrese: ");
        } else {
            for (int i = 0; i < 21; i++) {
                printf("Ingrese las ventas del dia %d: ", i + 1);
                totVentas = leeYvalFloat(0);
                v[pos][i] = totVentas*((float)datos[pos].porCom / 100);
                datos[pos].comAcob += v[pos][i];
            }
            printf("Ventas guardada\n");
            printf("Ingrese numero del vendedor: ");
        }
        numVen2 = leeYvalIntE2CF(10, 99, 0);
    }
}

void listado(float v[][21], int f, int c, VENDEDOR datos[]) {
    printf("--COMISIONES X DIA-- \n");
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            printf("%s Dia %d: $%.2f\n", datos[i].nomVen, j + 1, v[i][j]);
        }
    }
}

void menCom(VENDEDOR datos[], int cv) {
    float min = minimo(cv, datos);
    for (int i = 0; i < cv; i++) {
        if (datos[i].comAcob == min) {
            printf("El/los vendedor que cobra la menor comision %s con $%.2f\n", datos[i].nomVen, datos[i].comAcob);
        }
    }
}

void impTotal(VENDEDOR datos[], int cv) {
    float secE = 0, secM = 0, secV = 0, secT = 0;
    printf("IMPORTE TOTAL X SECTOR\n");

    for (int i = 0; i < cv; i++) {
        if (datos[i].sector == 'E') {
            secE += datos[i].comAcob;
        }
        if (datos[i].sector == 'M') {
            secM += datos[i].comAcob;
        }
        if (datos[i].sector == 'V') {
            secV += datos[i].comAcob;
        }
        if (datos[i].sector == 'T') {
            secT += datos[i].comAcob;
        }
    }

    printf("$%.2f para el sector E\n", secE);
    printf("$%.2f para el sector M\n", secM);
    printf("$%.2f para el sector V\n", secV);
    printf("$%.2f para el sector T\n", secT);
}

void leertexto(char texto[], int largo) {
    fflush(stdin);
    int i = 0;
    fgets(texto, largo, stdin);
    while (texto[i] != '\0') {
        if (texto[i] == '\n') {
            texto[i] = '\0';
        } else {
            i++;
        }
    }
}

void valVacio(char texto[], int largo) {
    while (strlen(texto) == 0) {
        printf("El texto no puede ser vacio. Reingrese: ");
        leertexto(texto, largo);
    }
}

int leeYvalIntE2CF(int min, int max, int cf) {
    int dato;
    scanf("%d", &dato);
    while ((dato < min || dato > max) && dato != cf) {
        printf("El numero no es valido. Reingrese: ");
        scanf("%d", &dato);
    }
    return dato;
}

char valSector() {
    fflush(stdin);
    char dato;
    scanf("%c", &dato);
    dato = toupper(dato);
    while (dato != 'E' && dato != 'M' && dato != 'V' && dato != 'T') {
        printf("Sector invalido. Reingrese: ");
        fflush(stdin);
        scanf("%c", &dato);
        dato = toupper(dato);
    }
    return dato;
}

int leeYvalIntE2(int min, int max) {
    int dato;
    scanf("%d", &dato);
    while (dato < min || dato > max) {
        printf("El dato no esta dentro del rango. Reingrese: ");
        scanf("%d", &dato);
    }
    return dato;
}

float leeYvalFloat(float lim) {
    float dato;
    scanf("%f", &dato);
    while (dato < lim) {
        printf("El dato no es valido. Reingrese: ");
        scanf("%f", &dato);
    }
    return dato;
}

float minimo(int cv, VENDEDOR datos[]) {
    float min = datos[0].comAcob;
    for (int i = 1; i < cv; i++) {
        if (datos[i].comAcob < min) {
            min = datos[i].comAcob;
        }
    }
    return min;
}