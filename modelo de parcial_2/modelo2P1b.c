/*Una empresa de transporte logístico necesita actualizar los montos atrasados de sus choferes tercerizados. 
Para ello cuenta con un archivo llamado fleteros.dat con la siguiente estructura:
-CODIGO (string 3 caracteres)
-Nombre (string 30 caracteres)
-Monto (real)
-Condición (char 'A' o 'B')
Por otro lado, los viajes rendidos en el día se encuentran en viajes.dat (ordenados por código) con la estructura :
-CODIGO (string 3 caracteres)
-Cant viajes (int)
-Tarifa por viaje (real)
Se solicita actualizar el monto a liquidar de fleteros.dat. Si un chofer que rindió viajes no 
figura en el archivo maestro se debe registrar la anomalía en un archivo de texto "rechazos.txt" 
guardando el código de chofer. Al final eliminar de "fleteros.dat" a los choferes de baja "B"

leo viaje
busco codigoV en codigoF
    si no existe
        rechazos.txt(printear codigo)
    si si existe
        hago corte de control para acumular cant * tarifa
            fwrite de monto(me tengo que ya haber traido los otros datos para hacer fwrite)
eliminar fleteros B

*/

#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <conio.h>

typedef struct 
{
    char codigo[4];
    char nombre[31];
    float monto;
    char cond;
}Chofer;

typedef struct 
{
    char codigo[4];
    int cant;
    float tarifa;
}Viaje;

long busqueda(char [], FILE*, Chofer*);
void procesarArchivos();
void rechazos(char []);
void eliminarFleterosB();
void mostrarFleteros();
void mostrarViajes();
void mostrarRechazos();

int main(){
    printf("--- ANTES ---");
    mostrarFleteros();
    mostrarViajes();

    procesarArchivos();
    eliminarFleterosB();

    printf("\n--- DESPUES ---");
    mostrarFleteros();
    mostrarRechazos();
    
    return 0;

}

void eliminarFleterosB(){
    Chofer datos;
    FILE *arch;
    FILE * temp;
    arch=fopen("fleteros.dat", "rb");
    temp=fopen("FLETEROS.tmp", "wb");
    if(arch==NULL||temp==NULL){
        printf("Error");
        getch();
        exit(1);
    }
    fread(&datos, sizeof(datos), 1, arch);
    while(!feof(arch)){
        if(datos.cond!='B'){
            fwrite(&datos, sizeof(datos), 1, temp);
        }
        fread(&datos, sizeof(datos), 1, arch);
    }
    fclose(arch);
    fclose(temp);
    remove("fleteros.dat");
    rename("FLETEROS.tmp", "fleteros.dat");
    

}

void procesarArchivos(){
    Chofer choferes;
    Viaje viajes;
    FILE *archF;
    FILE *archV;
    Chofer *pchoferes = &choferes;
    long pos;
    char codAnt[4];
    char codAntRechazo[4];
    float acum;
    archF=fopen("fleteros.dat", "r+b");
    archV=fopen("viajes.dat", "rb");
    if(archF==NULL||archV==NULL){
        printf("Error");
        getch();
        exit(1);
    }
    fread(&viajes, sizeof(viajes), 1, archV);
    while (!feof(archV)){
        pos=busqueda(viajes.codigo, archF, pchoferes);
        if(pos ==-1){
            
            rechazos(viajes.codigo);
            strcpy(codAntRechazo, viajes.codigo);
            while ((strcmpi(codAntRechazo, viajes.codigo)==0) && !feof(archV))
            {
                fread(&viajes, sizeof(viajes), 1, archV);
            }
        }else{
            strcpy(codAnt, viajes.codigo);
            acum=0;
            while(strcmpi(codAnt, viajes.codigo)==0 && !feof(archV)){
                acum+=viajes.cant*viajes.tarifa;
                fread(&viajes, sizeof(viajes), 1, archV);
            }
            choferes.monto+=acum;
            fseek(archF, pos, SEEK_SET);
            fwrite(&choferes, sizeof(choferes), 1, archF);
            fflush(archF);
        }
    }
    fclose(archV);
    fclose(archF);
    
}

void rechazos(char codigo[]){
    FILE *arch;
    arch=fopen("rechazos.txt", "at");
    if(arch==NULL){
        printf("Error");
        getch();
        exit(1);
    }
    fprintf(arch, "%s\n", codigo);
    fclose(arch);
}

long busqueda(char codigo[], FILE*arch, Chofer *pchoferes){
    Chofer choferes;
    long pos =-1;
    int flag =0;
    rewind(arch);
    fread(&choferes, sizeof(choferes), 1, arch);
    while(!feof(arch) && flag ==0){
        if(strcmpi(codigo, choferes.codigo)==0){
            flag =1;
            pos=ftell(arch)-sizeof(choferes);
            *pchoferes=choferes;
        }else{
            fread(&choferes, sizeof(choferes), 1, arch);
        }
    }
    return pos;

}

void mostrarFleteros(){
    Chofer datos;
    FILE *arch;
    arch = fopen("fleteros.dat", "rb");
    if(arch == NULL){
        printf("No se pudo abrir fleteros.dat\n");
        return;
    }
    printf("\n===== FLETEROS =====\n");
    printf("%-6s %-30s %-10s %-5s\n", "COD", "NOMBRE", "MONTO", "COND");
    fread(&datos, sizeof(datos), 1, arch);
    while(!feof(arch)){
        printf("%-6s %-30s %-10.2f %-5c\n", datos.codigo, datos.nombre, datos.monto, datos.cond);
        fread(&datos, sizeof(datos), 1, arch);
    }
    fclose(arch);
}

void mostrarViajes(){
    Viaje datos;
    FILE *arch;
    arch = fopen("viajes.dat", "rb");
    if(arch == NULL){
        printf("No se pudo abrir viajes.dat\n");
        return;
    }
    printf("\n===== VIAJES =====\n");
    printf("%-6s %-10s %-10s\n", "COD", "CANT", "TARIFA");
    fread(&datos, sizeof(datos), 1, arch);
    while(!feof(arch)){
        printf("%-6s %-10d %-10.2f\n", datos.codigo, datos.cant, datos.tarifa);
        fread(&datos, sizeof(datos), 1, arch);
    }
    fclose(arch);
}

void mostrarRechazos(){
    char linea[10];
    FILE *arch;
    arch = fopen("rechazos.txt", "rt");
    if(arch == NULL){
        printf("No existe rechazos.txt todavia\n");
        return;
    }
    printf("\n===== RECHAZOS =====\n");
    while(fgets(linea, 10, arch)){
        printf("%s", linea);
    }
    fclose(arch);
}