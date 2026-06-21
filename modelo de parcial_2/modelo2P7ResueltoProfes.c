/*Se tiene un archivo binario que registra los sueldos de los empleados de una empresa
Con el siguiente diseño de registro
Legajo( int)
Nombre(45)
Antigüedad (en años int)
Sueldo básico (float)
Area( char 'A': administración, 'P': producción, 'C' comercial)
Realizar un programa en C que permita modificar directamente sobre el archivo (llamado sueldos.dat)los sueldos básicos de
los empleados según la siguiente escala de antigüedad
Mayor a 10 años 5%
Mayor a 20 años 6%
Una vez actualizado se debe generar un nuevo archivo, que solo contenga a los empleados del área administrativa
e informar la cantidad de registros de dicho archivo, utilizando las funciones vistas en el curso.
*/



#include <stdio.h>
#include <stdlib.h>

struct empleados {
    int legajo;
    char nombre[46];
    int antiguedad;
    float sueldo;
    char area;
};

void listarTodos();
void listaraAdministrativos();
int main() {
    struct empleados emp;
    FILE *Arch, *Arch2;
    int cant;

    Arch = fopen("Sueldos.dat", "r+b");
    if (Arch == NULL) {
        printf("Error al abrir archivo Sueldos.dat\n");
        getchar();
        exit(1);
    }

    /* ---- ACTUALIZAR SUELDOS DIRECTAMENTE ---- */

    fread(&emp, sizeof(struct empleados), 1, Arch);
    while (!feof(Arch))
        {


       if (emp.antiguedad >= 20)
        {

            emp.sueldo = emp.sueldo * 0.06+emp.sueldo;


            fseek(Arch, sizeof(emp)*-1, 1);
     //       fseek(Arch, 0, 1);
            fwrite(&emp, sizeof(struct empleados), 1, Arch);

        }else
            if (emp.antiguedad >= 10)
           {emp.sueldo = emp.sueldo * 0.05+emp.sueldo;

              fseek(Arch, sizeof(emp)*-1, 1);

            fwrite(&emp, sizeof(struct empleados), 1, Arch);


          }


       fseek(Arch, 0, 1);
           fread(&emp, sizeof(struct empleados), 1, Arch);

 }

    fclose(Arch);

    /* ---- LISTAR SUELDOS ACTUALIZADOS ---- */
    listarTodos();

    /* ---- NUEVO ARCHIVO SOLO DE ADMINISTRATIVOS ---- */

    Arch = fopen("Sueldos.dat", "rb");
    Arch2 = fopen("Administrativos.dat", "wb");

    if (Arch == NULL || Arch2 == NULL) {
        printf("Error al abrir archivos.\n");
        exit(1);
    }

    fread(&emp, sizeof(emp), 1, Arch);
    while (!feof(Arch)) {
        if (emp.area == 'A'||emp.area == 'a')
            fwrite(&emp, sizeof(struct empleados), 1, Arch2);

       fread(&emp, sizeof(struct empleados), 1, Arch);
    }

    /* Cantidad de registros */
    fseek(Arch2, 0, SEEK_END);
    cant = ftell(Arch2) / sizeof(emp);

    printf("\nCantidad de empleados administrativos: %d\n", cant);

    fclose(Arch);
    fclose(Arch2);
listaraAdministrativos();
    return 0;
}

/* -------- LISTAR ARCHIVO SUELDOS -------- */

void listarTodos() {
    struct empleados emp;
    FILE *Arch = fopen("Sueldos.dat", "rb");

    if (Arch == NULL) {
        printf("-Error al abrir archivo Sueldos.dat\n");
        exit(1);
    }

    printf("\n--- LISTADO COMPLETO DE EMPLEADOS ---\n");

    fread(&emp, sizeof(emp), 1, Arch);
    while (!feof(Arch)) {
        printf("%-8d %-20s %-5d %-10.2f %c\n",
               emp.legajo, emp.nombre, emp.antiguedad, emp.sueldo, emp.area);

        fread(&emp, sizeof(emp), 1, Arch);
    }

    fclose(Arch);
}

/* -------- LISTAR ARCHIVO ADMINISYTRATIVOS -------- */

void listaraAdministrativos() {
    struct empleados emp;
    FILE *Arch = fopen("Administrativos.dat", "rb");
;

    if (Arch == NULL) {
        printf("Error al abrir archivo Sueldos.dat\n");
        exit(1);
    }

    printf("\n--- LISTADO ADMINISTRATIVOS DE EMPLEADOS ---\n");

    fread(&emp, sizeof(emp), 1, Arch);
    while (!feof(Arch)) {
        printf("%-8d %-20s %-5d %-10.2f %c\n",
               emp.legajo, emp.nombre, emp.antiguedad, emp.sueldo, emp.area);

        fread(&emp, sizeof(emp), 1, Arch);
    }

    fclose(Arch);
}
