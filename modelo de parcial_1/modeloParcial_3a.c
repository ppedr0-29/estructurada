#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define TAM 25
#define CANT_VEND 50

typedef struct {
    int num;
    char nombre[TAM];
    char sec;
    int porcentaje;
    float comision;
} vend;

// PROTOTIPOS
int norepite(vend[], int, int);
int leeyValidaEntre2cf(int, int, int);
int ingreso(vend[], int);
vend ingresoStruct(vend[], int);
void leertexto(char[], int);
void validarVacio(char[], int);
char leeyValidaChar();
int leeyValidaEntre2(int, int);
float leeyValidaFloat(float);
void ventas(vend[], int, float[][21]);
void listado(vend[], int, float[][21]);
void mostrarMenor(vend[], int);
float menor(vend[], int);
void mostrarSector(vend[], int);
void categorias(vend[], int, float[]);

int main() {
    vend info[CANT_VEND];
    int cantV = ingreso(info, CANT_VEND);
    float venxM[CANT_VEND][21] = {0};

    ventas(info, cantV, venxM);
    listado(info, cantV, venxM);
    mostrarMenor(info, cantV);
    mostrarSector(info, cantV);

    return 0;
}

// ================= INGRESO =================

int ingreso(vend info[], int ce) {
    vend aux;
    int i = 0;
    int flag = 0;

    while (flag == 0 && i < ce) {
        aux = ingresoStruct(info, i);

        if (aux.num != 0) {
            info[i] = aux;
            i++;
        } else {
            flag = 1;
        }
    }
    return i;
}

vend ingresoStruct(vend info[], int ce) {
    vend aux;

    printf("Ingrese el num del vendedor: ");
    aux.num = leeyValidaEntre2cf(10, 99, 0);

    while (norepite(info, ce, aux.num) !=-1) {
        printf("El cod ya existe reingrese: ");
        aux.num = leeyValidaEntre2cf(10, 99, 0);
    }
    if (aux.num != 0) {
        printf("Ingrese el nombre del vendedor: ");
        leertexto(aux.nombre, TAM);
        validarVacio(aux.nombre, TAM);

        printf("Ingrese el sector (E-M-V-T): ");
        aux.sec = leeyValidaChar();

        printf("Ingrese el porcentaje: ");
        aux.porcentaje = leeyValidaEntre2(5, 15);

        printf("Ingrese la comision a cobrar: $ ");
        aux.comision = leeyValidaFloat(0);
    } else {
        printf("Carga finalizada");
    }

    return aux;
}

// ================= VENTAS =================

void ventas(vend info[], int cv, float m[][21]) {
    int num, pos;
    float tot;

    printf("Ingreso ventas x mes (21 dias)\n");
    
    num = leeyValidaEntre2cf(10, 99, 0);

    while (num != 0) {
        pos = norepite(info, cv, num);

        if (pos != -1) {
            for (int i = 0; i < 21; i++) {
                printf("ventas dia %d: $", i + 1);
                tot = leeyValidaFloat(0);
                m[pos][i]=tot*(info[pos].porcentaje/100.0);
                info[pos].comision+=m[pos][i];
            }
            printf("Ingrese num vendedor: ");
        } else {
            printf("El num no existe. Reingrese: ");
        }

        num = leeyValidaEntre2cf(10, 99, 0);
    }
}

// ================= LISTADO =================

void listado(vend info[], int cv, float m[][21]) {
    for (int i = 0; i < cv; i++) {
        printf("Vendedor num: %d\n", info[i].num);

        for (int j = 0; j < 21; j++) {
            printf("Dia %d comision: $%.2f\n", j + 1, m[i][j]);
        }
    }
}

// ================= MENOR =================

void mostrarMenor(vend info[], int cv) {
    float min = menor(info, cv);

    for (int i = 0; i < cv; i++) {
        if (info[i].comision == min) {
            printf("%s es el vendedor con menor comision total\n", info[i].nombre);
        }
    }
}

float menor(vend info[], int cv) {
    float min = info[0].comision;

    for (int i = 1; i < cv; i++) {
        if (info[i].comision < min) {
            min = info[i].comision;
        }
    }
    return min;
}

// ================= SECTOR =================

void mostrarSector(vend info[], int cv) {
    float importexSec[4] = {0};

    categorias(info, cv, importexSec);

    printf("$%.2f a pagar de E\n", importexSec[0]);
    printf("$%.2f a pagar de M\n", importexSec[1]);
    printf("$%.2f a pagar de V\n", importexSec[2]);
    printf("$%.2f a pagar de T\n", importexSec[3]);
}

void categorias(vend info[], int cv, float rec[]) {
    for (int i = 0; i < cv; i++) {
        switch (info[i].sec) {
            case 'E':
                rec[0] += info[i].comision;
                break;
            case 'M':
                rec[1] += info[i].comision;
                break;
            case 'V':
                rec[2] += info[i].comision;
                break;
            case 'T':
                rec[3] += info[i].comision;
                break;
        }
    }
}

// ================= VALIDACIONES =================

int leeyValidaEntre2cf(int min, int max, int cf) {
    int dato;
    scanf("%d", &dato);

    while (dato != cf && (dato < min || dato > max)) {
        printf("Num invalido. Reingrese: ");
        scanf("%d", &dato);
    }
    return dato;
}

int norepite(vend info[], int ce, int num) {
    int i = 0;
    int flag = -1;

    while (flag == -1 && i < ce) {
        if (info[i].num == num)
            flag = i;
        else
            i++;
    }
    return flag;
}

void leertexto(char texto[], int largo) {
    fflush(stdin);
    fgets(texto, largo, stdin);

    int i = 0;
    while (texto[i] != '\0') {
        if (texto[i] == '\n')
            texto[i] = '\0';
        else
            i++;
    }
}

void validarVacio(char texto[], int largo) {
    while (strlen(texto) == 0) {
        printf("El texto no puede ser vacio. Reingrese: ");
        leertexto(texto, largo);
    }
}

char leeyValidaChar() {
    char dato;

    fflush(stdin);
    scanf("%c", &dato);
    dato = toupper(dato);

    while (dato != 'E' && dato != 'M' && dato != 'V' && dato != 'T') {
        printf("Sector incorrecto. Reingrese: ");
        fflush(stdin);
        scanf("%c", &dato);
        dato = toupper(dato);
    }

    return dato;
}

int leeyValidaEntre2(int min, int max) {
    int dato;
    scanf("%d", &dato);

    while (dato < min || dato > max) {
        printf("Numero invalido. Reingrese: ");
        scanf("%d", &dato);
    }
    return dato;
}

float leeyValidaFloat(float lim) {
    float dato;
    scanf("%f", &dato);

    while (dato < lim) {
        printf("Num invalido. Reingrese: ");
        scanf("%f", &dato);
    }
    return dato;
}