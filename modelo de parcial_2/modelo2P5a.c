/*Una entidad educativa dispone del archivo material.dat con la información del material para descargar por los alumnos. 
La información del archivo es la siguiente: (respetar nombre de campos)

codArch (entero, 4 dígitos) //Código del archivo
nomArch (char, 30 caracteres) //Nombre del archivo
nomMat (char, 30 caracteres) //Nombre de la materia
cantDesc (entero, inicializado en cero) //Cantidad de descargas

Luego dispone de un segundo archivo descargas.dat con las descargas efectuadas en el mes de Enero. 
Un archivo puede ser descargado ninguna o más de una vez. La información del archivo es la siguiente: (respetar nombre de campos)
nomArch (char, 30 caracteres) //Nombre del archivo
diaDesc (entero, 1 a 31) //Día de descarga

Se pide desarrollar un programa en lenguaje C que cumpla con las siguientes consignas:
Una función para actualizar el archivo material.dat con las descargas efectuadas.
Una función para generar el archivo sindescarga.dat que contenga los archivos que no tuvieron descargas.
Una función para generar el archivo descxdia.csv que contenga día y cantidad de descarga total.*/

/*
abrir archivo material.dat r+b
abrir archivo descargas.dat rb
abrir archivo sindescarga.dat a+b
abrir archivo descxdia.cvs wt
fread(archM)
while(!feof){
    pos=busqueda(busco en descargas, que exista)
    if(pos!=-1){
        cantDesc++;
        fseek(pos)
        fwrite(archM)
        fflush(archM);
    }else{
        fwrite(archSin)
    }
}

descargasxDia(){
    v[31]=0;
    cantDTot=0;
    rewind(archD)
    fread(archD)
    while(!feof(archD)){
        v[dia-1]++;
        
    }
    for int i=0; i<31; i++´{
        fprintf(archDxD, "%d;%d\n", i+1, v[i]);
    }
}

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

typedef struct 
{
    int codArch;
    char nomArch[31];
    char nomMat[31];
    int cantDesc;

}MATERIAL;


typedef struct
{
    char nomArch[31];
    int diaDesc;
}DESCARGA;

void generarArchivosIniciales();
FILE* abrirArchivo(char [], char []);
void procesarArchivo();
int busqueda(FILE*, char []);
void sinDescargas(MATERIAL );
void desxDia();
void mostrarArchivosResultados();

int main(){
    generarArchivosIniciales();
    procesarArchivo();
    desxDia();
    mostrarArchivosResultados();
    return 0;
}

void desxDia(){
    FILE*archD=abrirArchivo("descargas.dat", "rb");
    FILE*archDxD=abrirArchivo("desxdia.csv","wt");
    DESCARGA descargas;
    int cantDescargas[31]={0};
    fread(&descargas, sizeof(descargas), 1, archD);
    fprintf(archDxD, "DIA;CANT\n");
    while(!feof(archD)){
        cantDescargas[descargas.diaDesc-1]++;
        fread(&descargas, sizeof(descargas), 1, archD);
    }
    for(int i=0;i<31;i++){
        fprintf(archDxD, "%d;%d\n", i+1, cantDescargas[i]);
    }
    fclose(archD);
    fclose(archDxD);
}

void procesarArchivo(){
    FILE*archD=abrirArchivo("descargas.dat", "rb");
    FILE*archM=abrirArchivo("material.dat", "r+b");
    MATERIAL materiales;
    int descarga;
    fread(&materiales, sizeof(materiales), 1, archM);
    while(!feof(archM)){
        descarga=busqueda(archD, materiales.nomArch);//todo cambio porque puede haber mas de una descarga
        if(descarga == 0){
            sinDescargas(materiales);
        }else{
            materiales.cantDesc+=descarga;
            fseek(archM, -sizeof(materiales), SEEK_CUR);
            fwrite(&materiales, sizeof(materiales), 1, archM);
            fflush(archM);
        }
        fread(&materiales, sizeof(materiales), 1, archM);
    }
    fclose(archM);
    fclose(archD);
}
void sinDescargas(MATERIAL materiales){
    FILE*arch=abrirArchivo("sindescargas.dat", "ab");
    fwrite(&materiales, sizeof(materiales), 1, arch);
    fclose(arch);
}

int busqueda(FILE*arch, char nombre[]){
    int cantDescargas=0;
    DESCARGA descargas;
    rewind(arch);
    fread(&descargas, sizeof(descargas), 1, arch);
    while(!feof(arch)){
        if(strcmpi(descargas.nomArch, nombre)==0){
            cantDescargas++;
        }
        fread(&descargas, sizeof(descargas), 1, arch);
    }
    return cantDescargas;
}

FILE* abrirArchivo(char nombre[], char tipo[]){
    FILE*arch;
    arch=fopen(nombre, tipo);
    if(arch==NULL){
        printf("Error al abrir el archivo...");
        getch();
        exit(1);
    }
    return arch;
}
void generarArchivosIniciales() {
    FILE *archM = fopen("material.dat", "wb");
    FILE *archD = fopen("descargas.dat", "wb");

    if (archM == NULL || archD == NULL) {
        printf("ERROR: No se pudieron crear los archivos de prueba.\n");
        exit(1);
    }

    // 1. Creamos 5 materiales de prueba (cantDesc empieza en 0 como pide el enunciado)
    MATERIAL listaMateriales[5] = {
        {1010, "Apunte_Algebra_U1.pdf",    "Algebra",                 0},
        {2020, "Guia_Analisis_Mat.pdf",    "Analisis Matematico I",   0},
        {3030, "Enunciado_TP1_Prog.pdf",   "Programacion",            0},
        {4040, "Fisica_Cinematica.pdf",    "Fisica I",                0}, // Este no va a tener descargas
        {5050, "Tablas_Quimica_Inorg.pdf", "Quimica General",         0}
    };

    // 2. Creamos un historial de descargas para el mes de Enero
    // Nota: El archivo 4040 ("Fisica_Cinematica.pdf") no aparece aca a proposito
    DESCARGA listaDescargas[8] = {
        {"Apunte_Algebra_U1.pdf",    5},  // Dia 5
        {"Guia_Analisis_Mat.pdf",    12}, // Dia 12
        {"Apunte_Algebra_U1.pdf",    5},  // Dia 5 (otra descarga el mismo dia)
        {"Enunciado_TP1_Prog.pdf",   18}, // Dia 18
        {"Tablas_Quimica_Inorg.pdf", 25}, // Dia 25
        {"Apunte_Algebra_U1.pdf",    14}, // Dia 14
        {"Guia_Analisis_Mat.pdf",    12}, // Dia 12
        {"Enunciado_TP1_Prog.pdf",   18}  // Dia 18
    };

    // Escribimos los bloques de estructuras en sus respectivos archivos
    fwrite(listaMateriales, sizeof(MATERIAL), 5, archM);
    fwrite(listaDescargas, sizeof(DESCARGA), 8, archD);

    fclose(archM);
    fclose(archD);
    
    printf(">> Archivos de prueba ('material.dat' y 'descargas.dat') creados con exito.\n\n");
}
void mostrarArchivosResultados() {
    FILE *archM = fopen("material.dat", "rb");
    FILE *archS = fopen("sindescargas.dat", "rb");
    MATERIAL mat;

    printf("\n===================================================================\n");
    printf("           CONTENIDO ACTUALIZADO DE: material.dat                  \n");
    printf("===================================================================\n");
    printf("%-8s %-30s %-10s\n", "CODIGO", "NOMBRE DEL ARCHIVO", "DESCARGAS");
    printf("-------------------------------------------------------------------\n");
    
    if (archM != NULL) {
        fread(&mat, sizeof(MATERIAL), 1, archM);
        while (!feof(archM)) {
            printf("%-8d %-30s %-10d\n", mat.codArch, mat.nomArch, mat.cantDesc);
            fread(&mat, sizeof(MATERIAL), 1, archM);
        }
        fclose(archM);
    } else {
        printf("No se pudo abrir el archivo material.dat o no existe.\n");
    }

    printf("\n===================================================================\n");
    printf("           CONTENIDO GENERADO EN: sindescargas.dat                 \n");
    printf("===================================================================\n");
    printf("%-8s %-30s %-10s\n", "CODIGO", "NOMBRE DEL ARCHIVO", "DESCARGAS");
    printf("-------------------------------------------------------------------\n");

    if (archS != NULL) {
        fread(&mat, sizeof(MATERIAL), 1, archS);
        while (!feof(archS)) {
            printf("%-8d %-30s %-10d\n", mat.codArch, mat.nomArch, mat.cantDesc);
            fread(&mat, sizeof(MATERIAL), 1, archS);
        }
        fclose(archS);
    } else {
        printf("El archivo sindescargas.dat esta vacio o no se creo (todos tuvieron descargas).\n");
    }
    printf("===================================================================\n\n");
}