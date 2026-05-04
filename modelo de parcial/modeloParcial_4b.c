/*Una fábrica de pastas necesita actualizar el stock de sus casi 40 productos y para ello se deben registrar y 
almacenar con la estructura adecuada:
Numero de Producto (entero de 2 cifras no correlativo y sin repetidos)
Nombre Producto (string de 30 caracteres)
Rubro (F – Fideos, R – Pasta Rellena, S – Pasta Seca, T – Tucos y salsas)
Punto mínimo de reposición (entero entre 1 y 50)
Stock (entero positivo)
La carga del stock termina con el ingreso de un numero de Producto igual a cero.
Luego por cada producto se ingresará la cantidad vendida que tuvo por cada día de la semana (entero mayor o igual que 0) 
en los 7 días de la semana y debe actualizar stock. También finaliza con un numero de Producto igual a cero.
Se necesita determinar e informar:
Listado de stock por día y producto mostrando su nombre (resolver en una función).
El número y nombre de los productos que han quedado con stock superior al punto mínimo.
Los rubros que no tuvieron venta (resolver en una función).*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define TAM 40
#define CH 30
#define SEM 7
typedef struct {
    int numP;
    char nomP[CH];
    char rub;
    int pmr;
    int stock;
}PROD;

PROD ingresoDatos(PROD datos[], int i);
int ingreso(PROD datos[], int ce);
int noRepite(PROD datos[], int i, int num);
void actStock(PROD datos[], int cp, int m[][SEM], int rubro[]);
void listado(int m[][SEM], int cp, int c, PROD datos[]);
void stockSup(PROD datos[], int cp);
void noVenta(int rubro[]);
void categorizar(PROD datos[], int pos, int rubro[]);
int leeYvalE2CF(int min, int max, int cf);
int leeYvalE2(int min, int max);
int leeYvalInt(int lim);
void leerTexto(char texto[], int largo);
void valVacio(char texto[], int largo);
char valRub();
int busqueda(PROD datos[], int cp, int num);

int main() {
    PROD datos[TAM];
    int m[TAM][SEM]={{0}};
    int cantP = ingreso(datos, TAM);
    int rubro[4] = {0};
    if (cantP != 0) {
        actStock(datos, cantP, m, rubro);
        listado(m, cantP, 7, datos);
        stockSup(datos, cantP);
        noVenta(rubro);
    } 
        printf("Programa finalizado.");
    
    return 0;
}

PROD ingresoDatos(PROD datos[], int i) {
    PROD info;
    printf("Ingrese num producto (0 fin): ");
    info.numP = leeYvalE2CF(10, 99, 0);
    while (noRepite(datos, i, info.numP)) {
        printf("El num se repite. Reingrese: ");
        info.numP = leeYvalE2CF(10, 99, 0);
    }
    if (info.numP != 0) {
        printf("Ingrese nombre del producto: ");
        leerTexto(info.nomP, CH);
        valVacio(info.nomP, CH);
        printf("Ingrese rubro (F-R-S-T): ");
        info.rub = valRub();
        printf("Ingrese PMR: ");
        info.pmr = leeYvalE2(1, 50);
        printf("Ingrese stock: ");
        info.stock = leeYvalInt(0);
    }
    return info;
}

int ingreso(PROD datos[], int ce) {
    PROD aux;
    int flag = 0, i = 0;
    while (flag == 0 && i < ce) {
        aux = ingresoDatos(datos, i);
        if (aux.numP != 0) {
            datos[i] = aux;
            i++;
        } else {
            flag = 1;
        }
    }
    return i;
}

int noRepite(PROD datos[], int i, int num) {
    int flag = 0, s = 0;
    while (flag == 0 && s < i) {
        if (datos[s].numP == num) {
            flag = 1;
        } else {
            s++;
        }
    }
    return flag;
}

void actStock(PROD datos[], int cp, int m[][SEM], int rubro[]) {
    int num2, pos, totVentas;
    printf("--ACTUALIZACION STOCK--\n");
    printf("Ingrese num producto: ");
    num2 = leeYvalE2CF(10, 99, 0);
    
    while (num2 != 0) {
        pos = busqueda(datos, cp, num2);
        if (pos != -1) {
            for (int i = 0; i < 7; i++) {
                printf("Ingrese cant vend el dia %d: ", i + 1);
                totVentas = leeYvalInt(0);
                datos[pos].stock -= totVentas;
                m[pos][i] = datos[pos].stock;
                if(totVentas!=0){
                categorizar(datos, pos, rubro);
                }
            }
            printf("Stock actualizado.\n");
            printf("Ingrese num producto: ");
        } else {
            printf("No se encontro. Reingrese: ");
        }
        num2 = leeYvalE2CF(10, 99, 0);
    }
}

void listado(int m[][SEM], int cp, int c, PROD datos[]) {
    printf("STOCK X DIA\n");
    for (int i = 0; i < cp; i++) {
        for (int j = 0; j < c; j++) {
            printf("%s Dia %d stock: %d\n", datos[i].nomP, j + 1, m[i][j]);
        }
    }
}

void stockSup(PROD datos[], int cp) {
    printf("Stock superior PMR\n");
    for (int i = 0; i < cp; i++) {
        if (datos[i].stock > datos[i].pmr) {
            printf("%d - %s stock superior a pmr\n", datos[i].numP, datos[i].nomP);
        }
    }
}

void noVenta(int rubro[]) {
    char r[4] = {'F', 'R', 'S', 'T'};
    for (int i = 0; i < 4; i++) {
        if (rubro[i] == 0) {
            printf("No hubo venta en el rubro %c\n", r[i]);
        }
    }
}

void categorizar(PROD datos[], int pos, int rubro[]) {
    switch (datos[pos].rub) {
        case 'F':
            rubro[0]++;
            break;
        case 'R':
            rubro[1]++;
            break;
        case 'S':
            rubro[2]++;
            break;
        case 'T':
            rubro[3]++;
            break;
    }
}

char valRub() {
    char dato;
    fflush(stdin);
    scanf("%c", &dato);
    dato = toupper(dato);
    while (dato != 'F' && dato != 'R' && dato != 'S' && dato != 'T') {
        printf("Rubro invalido. Reingrese: ");
        fflush(stdin);
        scanf("%c", &dato);
        dato = toupper(dato);
    }
    return dato;
}

int busqueda(PROD datos[], int cp, int num) {
    int pos = -1, i = 0;
    while (pos == -1 && i < cp) {
        if (datos[i].numP == num) {
            pos = i;
        } else {
            i++;
        }
    }
    return pos;
}

int leeYvalE2CF(int min, int max, int cf) {
    int dato;
    scanf("%d", &dato);
    while ((dato < min || dato > max) && dato != cf) {
        printf("Numero invalido. Reingrese: ");
        scanf("%d", &dato);
    }
    return dato;
}

int leeYvalE2(int min, int max) {
    int dato;
    scanf("%d", &dato);
    while (dato < min || dato > max) {
        printf("Dato invalido. Reingrese: ");
        scanf("%d", &dato);
    }
    return dato;
}

int leeYvalInt(int lim) {
    int dato;
    scanf("%d", &dato);
    while (dato < lim) {
        printf("Stock invalido. Reingrese: ");
        scanf("%d", &dato);
    }
    return dato;
}

void leerTexto(char texto[], int largo) {
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
        leerTexto(texto, largo);
    }
}