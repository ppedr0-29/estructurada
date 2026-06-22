/*Una empresa necesita liquidar los sueldos de sus empleados y para ello dispone del archivo personal.dat con la siguiente estructura:
Código de Empleado (string de 3 caracteres)
Nombre Empleado (string de 30 caracteres)
Categoría (A – Aprendiz, D – Directivo, E – Especialista, T – Técnico)
Importe por hora que cobra (real entre 1000 y 5000)
Sueldo a cobrar (real)
Luego por cada empleado se ingresarán por teclado el Código de Empleado y las horas que trabajó en el mes (entero de 0 a 168). 
En base a las horas trabajadas y el importe que cobra por hora se debe actualizar el sueldo a cobrar en el archivo. 
En caso de no encontrar el Empleado en el archivo debe guardarse el error en un archivo llamado Errores.dat con la siguiente estructura 
(Código de Empleado y Horas Trabajadas).
La liquidación de los sueldos termina con el ingreso de un empleado igual a "FIN".
Además, se necesita determinar e informar:
El nombre del empleado que cobra el máximo sueldo actualizado, en caso de ser más de uno mostrar el último.
El importe total a pagar por cada categoría (resolver en una función).
Validar todos los datos que ingresan por teclado según lo indicado.
El código debe estar correctamente identado.

abrir archivo r+b
ingreso codEmp
ERROR info;
int *pcant=&info.cantH;
while(codEmp!=FIN){
    ingreso canthoras=leeyval(0, 168)
    pos=busqueda()
    if(pos!=-1){
        sueldo=(imp *cant)
        datos.sueldo=(datos.imp*(*pcant)) 
        i=indice() //A-D-E-T
        impTotal[i]+=sueldo;
        fseek(pos)
        fwrite(arch)
        fflush(arch)
    }else{
        fseek(archE, 0, seek_end);
        fwrite();
    }
}
maximo();
informe(float impTotal[]){
    for(int i=0 i<4){
        
    }
}

maximo(FILE *arch){
    PROD datos;
    char auxnombre[31];
    float max;
    rewind(arch)
    fread(&datos,arch)
    max=datos.sueldo
    strcpy(auxnombre,datos.nombre);
    while(!feof){
        if(datos.sueldo>=max){
            max=datos.sueldo
            strcpy(auxnombre,datos.nombre);
        }
    }
        printf();
}
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

// ================= ESTRUCTURAS =================
typedef struct {
    char codEmp[4];
    char nomEmp[31];
    char cat;
    float impXh;
    float sueldo;
} EMP;

typedef struct {
    char codEmp[4];
    int horas;
} ERROR;

// ================= PROTOTIPOS ==================
FILE * abrirArchivo(char nombre[], char tipo[]);
void procesarArchivo();
void errores(ERROR info);
void maximo(FILE *arch);
void leerTexto(char texto[], int largo);
void leeYValTexto(char texto[], int largo);
void leeYVal(int min, int max, int *dato);
long busqueda(FILE *arch, EMP *pdatos, char cod[]);
int indice(char cat);
void informe(float impTotal[], int ce);

// ==================== MAIN =====================
int main() {
    procesarArchivo();
    return 0;
}

// ================= FUNCIONES ===================

void procesarArchivo() {
    FILE *arch;
    arch = abrirArchivo("personal.dat", "r+b");
    EMP datos;
    EMP *pdatos = &datos;
    ERROR info;
    int *phoras = &info.horas;
    int i;
    // Inicializamos en 0 para evitar que acumule valores basura de la memoria
    float impTot[4] = {0}; 
    long pos;

    printf("Ingrese el cod del empleado: ");
    leeYValTexto(info.codEmp, 4);

    while (strcmpi(info.codEmp, "FIN") != 0) {
        printf("Ingrese cantidad de horas: ");
        leeYVal(0, 168, phoras);
        pos = busqueda(arch, pdatos, info.codEmp);

        if (pos != -1) {
            datos.sueldo = (datos.impXh * (*phoras));
            i = indice(datos.cat);
            impTot[i] += datos.sueldo;
            fseek(arch, pos, SEEK_SET);
            fwrite(&datos, sizeof(datos), 1, arch);
            fflush(arch);
        } else {
            errores(info);
        }

        printf("\Ingrese cod del empleado ('FIN' para salir): ");
        leeYValTexto(info.codEmp, 4);
    }

    maximo(arch);
    informe(impTot, 4);

    fclose(arch);
}

FILE * abrirArchivo(char nombre[], char tipo[]) {
    FILE *arch;
    arch = fopen(nombre, tipo);
    if (arch == NULL) {
        printf("Error.");
        getch();
        exit(1);
    }
    return arch;
}

void errores(ERROR info) {
    FILE *arch;
    arch = abrirArchivo("Errores.dat", "ab");
    fwrite(&info, sizeof(info), 1, arch);
    fclose(arch);
}

void maximo(FILE *arch) {
    EMP datos;
    char auxNom[31];
    float max;

    rewind(arch);
    fread(&datos, sizeof(datos), 1, arch);
    max = datos.sueldo;
    strcpy(auxNom, datos.nomEmp);

    while (!feof(arch)) {
        if (datos.sueldo >= max) {
            max = datos.sueldo;
            strcpy(auxNom, datos.nomEmp);
        }
        // Nota: Agregué el fread acá al final del while (en la hoja estaba tachado) 
        // para que no se quede en un bucle infinito.
        fread(&datos, sizeof(datos), 1, arch); 
    }
    
    printf("\nEl empleado que cobra el mayor sueldo es: %s\n", auxNom);
}

void leerTexto(char texto[], int largo) {
    fflush(stdin);
    fgets(texto, largo, stdin);
    int i = 0;
    while (texto[i] != '\0') {
        if (texto[i] == '\n') {
            texto[i] = '\0';
        }
        i++;
    }
}

void leeYValTexto(char texto[], int largo) {
    leerTexto(texto, largo);
    while (strlen(texto) == 0) {
        printf("Reingrese: ");
        leerTexto(texto, largo);
    }
}

void leeYVal(int min, int max, int *dato) {
    scanf("%d", dato);
    while (*dato < min || *dato > max) {
        printf("Error. Reingrese: ");
        scanf("%d", dato);
    }
}

long busqueda(FILE *arch, EMP *pdatos, char cod[]) {
    EMP datos;
    long pos = -1;
    int flag = 0;

    rewind(arch);
    fread(&datos, sizeof(datos), 1, arch);

    while (!feof(arch) && flag == 0) {
        if (strcmpi(datos.codEmp, cod) == 0) {
            flag = 1;
            pos = ftell(arch) - sizeof(datos);
            *pdatos = datos;
        }
        fread(&datos, sizeof(datos), 1, arch);
    }
    return pos;
}

int indice(char cat) {
    int i;
    switch (cat) {
        case 'A': i = 0; break;
        case 'D': i = 1; break;
        case 'E': i = 2; break;
        case 'T': i = 3; break;
    }
    return i;
}

void informe(float impTotal[], int ce) {
    printf("\n--- INFORME DE SUELDOS ---\n");
    for (int i = 0; i < ce; i++) {
        if (i == 0) {
            printf("En la cat Aprendiz se debe pagar %.2f\n", impTotal[i]);
        } else if (i == 1) {
            printf("En la cat Directivo pagar %.2f\n", impTotal[i]);
        } else if (i == 2) {
            printf("En la cat Especialista pagar %.2f\n", impTotal[i]);
        } else {
            printf("En la cat Tecnico pagar %.2f\n", impTotal[i]);
        }
    }
}