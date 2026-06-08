/*6.9 Se dispone de un archivo denominado INSCRIPTOS.dat que contiene la información de los inscriptos a un
curso de programación. El archivo aún no está completo ya que la inscripción se realiza por partes. Por cada
inscripto se tiene la siguiente información:
• DNI (entero)
• Apellido y Nombres (texto de 20 caracteres máximo)
• Pagado (campo entero donde 1 indica que pagó y 0 que aún adeuda la matrícula)
Se desea realizar un programa que cumpla con dos funciones:
a. Registrar los pagos de los alumnos ya inscriptos.
b. SI hay cupo, agregar nuevos inscriptos (el cupo máximo es de 60 alumno).
El programa solicitará el ingreso del DNI y lo buscará entre los inscriptos, en caso de que lo encuentre dará
la opción para registrar el pago (si es que no está pago ya). En caso de que no lo encuentre dará la opción
para inscribirlo al curso (el pago se realiza luego). En el momento que ya no quede cupo en el curso si llega
un nuevo inscripto se le preguntará si desea quedar registrado para un curso futuro, y en caso afirmativo
se le solicitará el teléfono y se guardará el nombre, DNI y teléfono en un archivo Interesados.dat.
El ingreso de datos finaliza con un DNI negativo. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct 
{
    int dni;
    char nya[21];
    int pago;
}Alu;
typedef struct 
{
    int dni;
    char nya[21];
    int tel;
}AluIn;

int leeyvalIntE2CF(int , int , int );
long busqueda(FILE *, int , Alu *);
int contarRegistros(FILE *);
void leerTexto(char[], int);
void valVacio(char[], int);
int leeyvalpago(int, int);
void mostrarInscriptos(FILE *);
void mostrarInteresados(FILE *);

int main(){
    FILE*arch;
    FILE*archInt;
    int cantR, dniAux, insc, listE;
    long pos;
    Alu datos, *pdatos=&datos;
    AluIn info;
    arch=fopen("INSCRIPTOS.dat", "r+b");
    archInt=fopen("INTERESADOS.dat", "r+b");
    if (arch==NULL)
    {
        printf("Error al abrir uno de los archivos.");
        getch();
        exit(1);
    }
    if (archInt==NULL)
    {
        archInt=fopen("INTERESADOS.dat", "wb");
        if (archInt==NULL)
        {
            printf("Error al abrir uno de los archivos.");
            getch();
            exit(1);
        }
        
    }
    mostrarInscriptos(arch);
    cantR=contarRegistros(arch);
    printf("Ingrese DNI: ");
    dniAux=leeyvalIntE2CF(10000000,99999999,0);
    while(dniAux>=0){
        pos=busqueda(arch,dniAux,pdatos);
        if (pos!=-1)
        {
            if(datos.pago==0){
                printf("Registrar pago(1-Pago, 0-No pago): ");
                datos.pago=leeyvalpago(1,0);
                fseek(arch, pos, SEEK_SET);
                fwrite(&datos, sizeof(datos), 1, arch);
            }else{
                printf("El alumno ya pago.\n");
            }
        }else{
            if (cantR<15)
            {
                printf("Desea inscribir al alumno?(1-SI y 0-NO):");
                insc=leeyvalpago(1,0);
                if (insc==1)
                {
                    printf("Ingrese nombre y apellido: ");
                    leerTexto(datos.nya, 21);
                    valVacio(datos.nya, 21);
                    datos.dni=dniAux;
                    datos.pago=0;
                    printf("Usuario inscripto.\n");
                    cantR++;
                    fseek(arch, 0, SEEK_END);
                    fwrite(&datos, sizeof(datos), 1, arch);
                }
                
            }else{
                printf("Cupos llenos. Desea ingresar en lista de espera?: ");
                listE=leeyvalpago(1,0);
                if (listE==1)
                {   
                    info.dni=dniAux;
                    printf("Ingrese nombre y apellido: ");
                    leerTexto(info.nya, 21);
                    valVacio(info.nya, 21);
                    printf("Ingrese numero de telefono: ");
                    info.tel=leeyvalIntE2CF(1100000000,1199999999,1100000000);
                    printf("Agregado a lista de espera. \n");
                    fseek(archInt, 0, SEEK_END);
                    fwrite(&info, sizeof(info), 1, archInt);
                }
            }
        }
        printf("Ingrese DNI: ");
        dniAux=leeyvalIntE2CF(10000000,99999999,0);
    }

    mostrarInscriptos(arch);
    mostrarInteresados(archInt);

    fclose(arch);
    fclose(archInt);

    return 0;
}

void leerTexto(char texto[], int largo){
    fflush(stdin);
    fgets(texto, largo, stdin);
    int i=0;
    while (texto[i]!='\0')
    {
        if (texto[i]=='\n')
        {
            texto[i]='\0';
        }else{
            i++;
        }   
    }
}

void valVacio(char texto[], int largo){
    while (strlen(texto)==0)
    {
        printf("Error. Reingrese: ");
        leerTexto(texto, largo);
    }
}

int leeyvalpago(int min, int max){
    int dato;
    scanf("%d", &dato);
    while (dato!=min && dato!=max)
    {
        printf("Error. Reingrese:");
        scanf("%d", &dato);
    }
    return dato;
}

long busqueda(FILE *arch, int dni, Alu *pdatos){
    long pos=-1;
    int flag=0;
    Alu datos;
    rewind(arch);
    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch) && flag==0)
    {
        if (datos.dni==dni)
        {
            pos=ftell(arch)-sizeof(datos);
            flag=1;
            *pdatos=datos;
        }
        fread(&datos, sizeof(datos), 1, arch);
    }
    return pos;
}

int leeyvalIntE2CF(int min, int max, int cf){
    int dato;
    scanf("%d", &dato);
    while ((dato<min || dato>max) && dato>=cf)
    {
        printf("Error. Reingrese: ");
        scanf("%d", &dato);
    }
    return dato;
}

int contarRegistros(FILE *arch){
    int bytes, registros;
    Alu datos;
    fseek(arch, 0, SEEK_END);
    bytes=ftell(arch);
    registros= bytes/sizeof(datos);
    
    return registros;
}

void mostrarInscriptos(FILE *arch) {
    Alu reg;
    rewind(arch);
    printf("\n==================================================\n");
    printf("             ALUMNOS INSCRIPTOS ACTUALES          \n");
    printf("==================================================\n");
    printf("%-10s | %-20s | %-6s\n", "DNI", "APELLIDO Y NOMBRE", "PAGO");
    printf("--------------------------------------------------\n");
    
    fread(&reg, sizeof(Alu), 1, arch);
    while (!feof(arch)) {
        printf("%-10d | %-20s | %-6s\n", 
               reg.dni, 
               reg.nya, 
               (reg.pago == 1) ? "SI" : "NO");
        fread(&reg, sizeof(Alu), 1, arch);
    }
}

void mostrarInteresados(FILE *archInt) {
    AluIn reg;
    rewind(archInt);
    printf("\n==================================================\n");
    printf("             LISTA DE ESPERA (INTERESADOS)        \n");
    printf("==================================================\n");
    printf("%-10s | %-20s | %-12s\n", "DNI", "APELLIDO Y NOMBRE", "TELEFONO");
    printf("--------------------------------------------------\n");
    
    fread(&reg, sizeof(AluIn), 1, archInt);
    while (!feof(archInt)) {
        printf("%-10d | %-20s | %-12d\n", reg.dni, reg.nya, reg.tel);
        fread(&reg, sizeof(AluIn), 1, archInt);
    }
    printf("==================================================\n");
}