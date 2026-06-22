/*/*Una empresa necesita liquidar los sueldos de sus empleados y para ello dispone del archivo personal.dat con la
 siguiente estructura:

Código de Empleado (string de 3 caracteres)

Nombre Empleado (string de 30 caracteres)

Categoría (A – Aprendiz, D – Directivo, E – Especialista, T – Técnico)

Importe por hora que cobra (real entre 1000 y 5000)

Sueldo a cobrar (real)

Luego por cada empleado se ingresarán por teclado el Código de Empleado y las horas que trabajó en el mes (entero de 0 a 168). 
En base a las horas trabajadas y el importe que cobra por hora se debe actualizar el sueldo a cobrar en el archivo. En caso de no encontrar el 
Empleado en el archivo debe guardarse el error en un archivo llamado Errores.dat con la siguiente estructura (Código de Empleado y 
Horas Trabajadas).

La liquidación de los sueldos termina con el ingreso de un empleado igual a "FIN".
Además, se necesita determinar e informar:
El nombre del empleado que cobra el máximo sueldo actualizado, en caso de ser más de uno mostrar el último.
El importe total a pagar por cada categoría (resolver en una función).
Validar todos los datos que ingresan por teclado según lo indicado.
El código debe estar correctamente identado.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct {
    char codigo[4];
    char nombre[31];
    char cat;
    float importeXh;
    float sueldo;
} Empi;

typedef struct {
    char codigo[4];
    int cont;
} ERROR;

// Prototipos
void procesarArchivo();
FILE* abrirArchivo(char nombre[], char tipo[]);
void leeyValidaText(char texto[], int largo);
void leerTexto(char texto[], int L);
void leeyValidaIntEntre2(int* dato, int min, int max);
long busqueda(FILE* arch, char codigo[], Empi* dato);
int indice(char letra);
void Errores(ERROR e);
void maximo();
void INFORME(float impTot[]);

int main() {
    procesarArchivo();
    return 0;
}

// Implementación de funciones

FILE* abrirArchivo(char nombre[], char tipo[]) {
    FILE* arch = fopen(nombre, tipo);
    if (arch == NULL) {
        printf("Error al abrir el archivo\n");
        getch();
        exit(1);
    }
    return arch;
}

void leerTexto(char texto[], int L) {
    fflush(stdin);
    fgets(texto, L, stdin);
    int i = 0;
    while (texto[i] != '\0') {
        if (texto[i] == '\n') {
            texto[i] = '\0';
        }
        i++;
    }
}

void leeyValidaText(char texto[], int largo) {
    leerTexto(texto, largo);
    while (strlen(texto) == 0) {
        printf("El texto no puede ser vacio\n");
        leerTexto(texto, largo);
    }
}

int indice(char letra) {
    int i = 0; // Se inicializa para evitar basura
    switch (letra) {
        case 'A': i = 0; break;
        case 'D': i = 1; break;
        case 'E': i = 2; break;
        case 'T': i = 3; break;
    }
    return i;
}

void leeyValidaIntEntre2(int* dato, int min, int max) {
    scanf("%d", dato);
    while (*dato < min || *dato > max) {
        printf("Error, reingrese:");
        scanf("%d", dato);
    }
}

void procesarArchivo() {
    FILE* arch = abrirArchivo("personal.dat", "r+b");
    float impTotal[4] = {0};
    Empi datos;
    ERROR errores;
    long pos;

    printf("Ingrese el codigo: ");
    leeyValidaText(errores.codigo, 4);
    
    while (strcmpi(errores.codigo, "FIN") != 0) {
        printf("Ingrese la cant:");
        leeyValidaIntEntre2(&errores.cont, 0, 168);
        
        pos = busqueda(arch, errores.codigo, &datos);
        
        if (pos == -1) {
            Errores(errores);
        } else {
            int i = indice(datos.cat);
            datos.sueldo += (datos.importeXh * errores.cont);
            impTotal[i] += datos.sueldo;
            
            fseek(arch, pos, SEEK_SET);
            fwrite(&datos, sizeof(datos), 1, arch);
            fflush(arch);
        }
        printf("Ingrese el codigo: ");
        leeyValidaText(errores.codigo, 4);
    }
    maximo();
    INFORME(impTotal);
    fclose(arch);
}

void Errores(ERROR e) {
    FILE* arch = abrirArchivo("errores.dat", "ab");
    fwrite(&e, sizeof(e), 1, arch);
    fclose(arch);
}

long busqueda(FILE* arch, char codigo[], Empi* pdato) {
    long pos = -1;
    int flag = 0;
    Empi dato;
    rewind(arch);
    
    fread(&dato, sizeof(dato), 1, arch);
    while (!feof(arch) && flag == 0) {
        if (strcmpi(dato.codigo, codigo) == 0) {
            flag = 1;
            pos = ftell(arch) - sizeof(dato);
            *pdato = dato;
        }
        fread(&dato, sizeof(dato), 1, arch);
    }
    return pos;
}

void maximo() {
    FILE* arch = abrirArchivo("personal.dat", "rb");
    Empi dato;
    fread(&dato, sizeof(dato), 1, arch);
    
    float max = dato.sueldo;
    char nombreMax[31];
    strcpy(nombreMax, dato.nombre);
    
    while (!feof(arch)) {
        if (dato.sueldo >= max) {
            max = dato.sueldo;
            strcpy(nombreMax, dato.nombre);
        }
        fread(&dato, sizeof(dato), 1, arch);
    }
    printf("El empleado %s fue el de mayor sueldo: %.2f\n", nombreMax, max);
    fclose(arch);
}

void INFORME(float impTot[]) {
    for (int i = 0; i < 4; i++) {
        switch (i) {
            case 0: printf("$%.2f para aprendices\n", impTot[0]); break;
            case 1: printf("$%.2f para directivos\n", impTot[1]); break;
            case 2: printf("$%.2f para especialistas\n", impTot[2]); break;
            case 3: printf("$%.2f para tecnicos\n", impTot[3]); break;
        }
    }
}