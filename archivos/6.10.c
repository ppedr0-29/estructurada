/*6.10 Dado el archivo pagos.dat con los pagos realizados por los alumnos a un curso, se desea registrar los
pagos de las cuotas. El archivo tiene el siguiente formato:
• DNI
• Fecha de último pago (3 enteros, día, mes y año)
Para registrar los pagos se ingresa el número de DNI (7 a 8 dígitos) y la fecha de pago. Se debe actualizar el
archivo de pagos, y si el DNI no se encuentra se pregunta al usuario si desea agregar un nuevo alumno. En caso
afirmativo se debe agregar un nuevo registro en dicho archivo con el nuevo pago y además agregar el nuevo
alumno al archivo alumnos.dat, dicho archivo contiene el DNI y nombre completo del alumno (40 caracteres
máximo).
Todos los datos de ingreso deben estar validados (para simplificar al validar la fecha considerar día de 1 a 31
para todos los meses).
Se procesan varios pagos hasta que se ingresa un DNI 0. Al finalizar mostrar un listado de los alumnos, DNI y
nombre de todos aquellos que adeudan la última cuota (del mes de mayo 2026). */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>

typedef struct
{
    int dia;
    int mes;
    int anio;
}ddmmaa;

typedef struct
{
    int dni;
    ddmmaa fecha;
}pagos;

typedef struct
{
    int dni;
    char nomb[41];
}Alu;

long busqueda2(FILE *, int , Alu *);
long busqueda(FILE *, int , pagos *);
void leerTexto(char [], int );
void valVacio(char [], int );
int leeyvalIntE2CF(int , int , int );
bool validarFecha(int , int , int );
int cantDiasMes(int , int );
int esBisiesto(int );
void mostrar(FILE *, FILE *);

int main(){
    pagos datos;
    ddmmaa fecha;
    pagos *pdatos=&datos;
    FILE *arch, *archalu;
    Alu info;
    int dniAux, vf;
    long pos;
    arch=fopen("pagos.dat", "r+b");
    archalu=fopen("ALUMNOS.dat", "a+b");
    if (arch==NULL || archalu==NULL)
    {
        printf("Error al abrir alguno de los archivos");
        getch();
        exit(1);
    }
    printf("Ingrese DNI del alumno: ");
    dniAux=leeyvalIntE2CF(1000000,99999999,0);
    while (dniAux!=0)
    {
        pos=busqueda(arch, dniAux, pdatos);
        if (pos!=-1)
        {
            printf("Ingrese la fecha de pago(dd/mm/aaaa): ");
            scanf("%d/%d/%d", &fecha.dia, &fecha.mes, &fecha.anio);
            while (!validarFecha(fecha.dia, fecha.mes, fecha.anio))
            {
                printf("Fecha invalida. Reingrese:");
                scanf("%d/%d/%d", &fecha.dia, &fecha.mes, &fecha.anio);
            }
            fseek(arch, pos, SEEK_SET);
            datos.dni=dniAux;
            datos.fecha.dia=fecha.dia;
            datos.fecha.mes=fecha.mes;
            datos.fecha.anio=fecha.anio;
            fwrite(&datos, sizeof(datos), 1, arch);
            fflush(arch);

        }else{
            printf("Desea ingresar un nuevo alumno?(1-SI, 0-NO): ");
            vf=leeyvalIntE2CF(0,1,1);
            if (vf==1)
            {
                printf("Ingrese la fecha de pago(dd/mm/aaaa): ");
                scanf("%d/%d/%d", &fecha.dia, &fecha.mes, &fecha.anio);
                while (!validarFecha(fecha.dia, fecha.mes, fecha.anio))
                {
                    printf("Fecha invalida. Reingrese:");
                    scanf("%d/%d/%d", &fecha.dia, &fecha.mes, &fecha.anio);
                }
                fseek(arch, 0, SEEK_END);
                datos.dni=dniAux;
                datos.fecha.dia=fecha.dia;
                datos.fecha.mes=fecha.mes;
                datos.fecha.anio=fecha.anio;
                fwrite(&datos, sizeof(datos), 1, arch);
                fflush(arch);
                info.dni=datos.dni;
                printf("Ingrese nombre del alumno:");
                leerTexto(info.nomb, 41);
                valVacio(info.nomb, 41);
                fseek(archalu, 0, SEEK_END);
                fwrite(&info, sizeof(info), 1, archalu);
                fflush(archalu);
            }
            
        }
        printf("Ingrese DNI del alumno: ");
        dniAux=leeyvalIntE2CF(1000000,99999999,0);
    }
    mostrar(arch, archalu);
    fclose(arch);
    fclose(archalu);


    return 0;
}

void mostrar(FILE *arch, FILE *archalu){
    pagos datos;
    Alu info;
    Alu *pinfo=&info;
    long pos;
    rewind(arch);
    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch))
    {
        if (datos.fecha.anio<2026)
        {   
            
            pos=busqueda2(archalu,datos.dni, pinfo);
            if (pos!=-1)
            {
                printf("El alumno %s con DNI - %d adeuda la ultima cuota\n", info.nomb, info.dni);
            }
        }else{
                if (datos.fecha.mes<5)
                {
                    pos=busqueda2(archalu,datos.dni, pinfo);
                    if (pos!=-1)
                    {
                        printf("El alumno %s con DNI -%d adeuda la ultima cuota\n", info.nomb, info.dni);
                    }
                }
                
        }
        fread(&datos, sizeof(datos), 1, arch);
    }
    
}

long busqueda2(FILE *arch, int dato, Alu *pdatos){
    int flag=0;
    long pos=-1;
    Alu datos;
    rewind(arch);
    fread(&datos, sizeof(datos), 1, arch);
    while (flag==0 && !feof(arch))
    {
        if (datos.dni==dato)
        {
            pos=ftell(arch)-sizeof(datos);
            flag=1;
            *pdatos=datos;
        }
        fread(&datos, sizeof(datos),1, arch);
    }
    return pos;
}

long busqueda(FILE *arch, int dato, pagos *pdatos){
    int flag=0;
    long pos=-1;
    pagos datos;
    rewind(arch);
    fread(&datos, sizeof(datos), 1, arch);
    while (flag==0 && !feof(arch))
    {
        if (datos.dni==dato)
        {
            pos=ftell(arch)-sizeof(datos);
            flag=1;
            *pdatos=datos;
        }
        fread(&datos, sizeof(datos),1, arch);
    }
    return pos;
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

int leeyvalIntE2CF(int min, int max, int cf){
    int dato;
    scanf("%d", &dato);
    while ((dato<min || dato>max) && dato!=cf)
    {
        printf("Error. Reingrese: ");
        scanf("%d", &dato);
    }
    return dato;
}

bool validarFecha(int dia, int mes, int anio){
    bool fechaValida = false;
    if (anio> 1900){
        if (mes >=1 && mes <=12){
            if (dia>=1 && dia <= cantDiasMes(mes, anio)){
                fechaValida = true;
            }
        }
    } return fechaValida;
}
int cantDiasMes(int mes, int anio){
    int cantDias =31;
    if(mes == 4 || mes == 6 || mes == 9 || mes == 11){
        cantDias = 30;
    }else{
        if(mes==2){
            cantDias= 28 + esBisiesto(anio);
        }
    }
        
    return cantDias;
}
int esBisiesto(int anio){
    int bisiesto =0;
    if ((anio%4==0 && anio%100!=0)||(anio%400==0))
        bisiesto = 1;
    return bisiesto;
}