/*El DIIT quiere actualizar la información de los alumnos que han cursado este cuatrimestre. Para ello dispone de 2 archivos. El primer archivo se llama alumnos.dat y tiene registros con la siguiente estructura: DNI (entero), nombre y apellido (texto, 50 caracteres máximo), cantidad total de materias cursadas desde que ingresó a la facultad (entero), año de última cursada (entero), cuatrimestre de la última cursada (entero).

Por otro lado, se tiene el archivo CursadaPrimCuat.dat con la información de los alumnos que han cursado el primer cuatrimestre del 2025, este archivo contiene dos campos, DNI (entero) y código de materia (entero), de los alumnos que se han inscripto a las diferentes materias. El alumno puede inscribirse en ninguna o varias materias. Este archivo no se encuentra ordenado. Con estos dos archivos debe:

Actualizar el archivo alumnos.dat con los alumnos que han cursado el primer cuatrimestre del 2025. Si se trata de un alumno nuevo (ingresante), se deben solicitar los datos faltantes para poder agregar al archivo de alumnos.

Realizar un informe de aquellos alumnos que no han cursado el primer cuatrimestre del 2025, indicando DNI, nombre y apellido, cuatrimestre y año de última cursada.*/
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

typedef struct {
    int DNI;
    char NombreApellido[51];
    int Materias;
    int Anio_ultima_cursada;
    int Cuat_ultima_cursada;
} ALUMNO;

typedef struct {
    int DNI_Cursada;
    int Codigo_materia;
} CURSADA;

FILE *AbrirArchivo(char [], char []);
int Busqueda(FILE *, int);
void ActualizarDatos();
void Informar();

int main() {
    ActualizarDatos();
    Informar();
    
    return 0;
}

FILE *AbrirArchivo(char nombre[], char modo[]) {
    FILE *archivo;
    archivo = fopen(nombre, modo);
    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        getch();
        exit(1);
    }
    return archivo;
}

int Busqueda(FILE *archivo, int dni_buscado) {
    int num_registro = -1, i = 0;
    ALUMNO alum;
    rewind(archivo);
    fread(&alum, sizeof(ALUMNO), 1, archivo);
    
    while (!feof(archivo) && num_registro == -1) {
        if (alum.DNI == dni_buscado) {
            num_registro = i;
        } else {
            i++;
        }
        fread(&alum, sizeof(ALUMNO), 1, archivo);
    }
    
    return num_registro;
}

void ActualizarDatos() {
    FILE *archivo_alumnos, *archivo_cuat;
    ALUMNO alum;
    int pos;
    CURSADA cur;
    
    archivo_alumnos = AbrirArchivo("alumnos.dat", "r+b");
    archivo_cuat = AbrirArchivo("CursadaPrimCuat.dat", "rb");
    
    fread(&cur, sizeof(CURSADA), 1, archivo_cuat);
    while (!feof(archivo_cuat)) {
        pos = Busqueda(archivo_alumnos, cur.DNI_Cursada);
        
        if (pos != -1) {
            fseek(archivo_alumnos, pos * sizeof(ALUMNO), SEEK_SET);
            fread(&alum, sizeof(ALUMNO), 1, archivo_alumnos);
            
            alum.Materias++;
            alum.Anio_ultima_cursada = 2025;
            alum.Cuat_ultima_cursada = 1;
            
            fseek(archivo_alumnos, -1 * sizeof(ALUMNO), SEEK_CUR);
            fwrite(&alum, sizeof(ALUMNO), 1, archivo_alumnos);
        } else {
            printf("Ingrese el nombre y apellido del alumno de DNI %d: ", cur.DNI_Cursada);
            fflush(stdin);
            gets(alum.NombreApellido);
            
            alum.Anio_ultima_cursada = 2025;
            alum.Cuat_ultima_cursada = 1;
            alum.DNI = cur.DNI_Cursada;
            alum.Materias = 1;
            
            fseek(archivo_alumnos, 0, SEEK_END);
            fwrite(&alum, sizeof(ALUMNO), 1, archivo_alumnos);
        }
        fread(&cur, sizeof(CURSADA), 1, archivo_cuat);
    }
    
    fclose(archivo_alumnos);
    fclose(archivo_cuat);
}

void Informar() {
    FILE *archivo_alumnos;
    ALUMNO alum;
    
    archivo_alumnos = AbrirArchivo("alumnos.dat", "rb");
    
    printf("\n= Alumnos que no cursaron el primer cuatrimestre del 2025 =\n");
    printf("%-8s %-50s %-11s %11s\n", "DNI", "NOMBRE Y APELLIDO", "ULTIMO CUAT", "ULTIMO ANIO");
    
    fread(&alum, sizeof(ALUMNO), 1, archivo_alumnos);
    while (!feof(archivo_alumnos)) {
        if (alum.Anio_ultima_cursada < 2025) {
            printf("%-8d %-50s %-11d %-11d\n", alum.DNI, alum.NombreApellido, alum.Cuat_ultima_cursada, alum.Anio_ultima_cursada);
        }
        fread(&alum, sizeof(ALUMNO), 1, archivo_alumnos);
    }
    
    fclose(archivo_alumnos);
}