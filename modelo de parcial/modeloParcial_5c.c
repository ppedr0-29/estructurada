/*La empresa VoiYa de la comuna 1 de CABA desea contabilizar la facturación de los viajes realizados por sus 100 choferes en el día de la fecha. 
Para cada chofer se ingresa la siguiente información:
Código de chofer (entero, 4 dígitos)
Apellido y Nombre (50 caracteres)
Antigüedad (entero, mayor o igual a cero)
Importe por km (float, mayor o igual a 2150)
Luego, se procesan los viajes realizados en el día. La carga finaliza con código de chofer igual a 999, y los datos vienen desordenados.
Código de chofer (entero, 4 dígitos)
Kms recorridos (entero, mayor a cero)
Zona recorrida (L – La Boca, B – Barracas, P – Parque Patricios, N – Nueva Pompeya)
Se pide realizar un programa en lenguaje C que realice los siguientes informes:
Informar el importe recaudado para cada chofer indicando apellido y nombre, total kms recorridos, importe recaudado.
Informar los kms recorridos y el importe recaudado por zona.
Informar la/las zonas que menos han facturado en el día.*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define TAM 2

typedef struct
{
    int codC;
    char AyN[50];
    int ant;
    float impkm;

} CHOFER;

typedef struct
{
    int codC;
    int kmr;
    char zr;

} VIAJES;

void ingreso(CHOFER [], int);
int leeryvalE2(int, int);
int leeryvalInt(int);
float leeryvalFloat(float);
int busqueda(CHOFER [], int, int);
//void ponerencero(VIAJES [], int);
int leeryvalE2CF(int, int, int);
void leertexto(char [], int);
void valVacio(char [], int);
char zonaVal();
int viajesDia(VIAJES [], int ,CHOFER []);
void listado(VIAJES [], CHOFER [], int, int);
float minimo(float [], int);
void puntoB(VIAJES [], CHOFER [], int , int , int [], float []);
void puntoC(float [], int );

int main()
{
    CHOFER datos[TAM];
    VIAJES datosB[TAM];
    int kmxz[4]={0};
    float impxz[4]={0};
    ingreso(datos, TAM);
    //ponerencero(datosB, TAM);
    int cantV=viajesDia(datosB, TAM,datos);
    listado(datosB, datos, TAM, cantV);
    puntoB(datosB, datos, TAM, cantV, kmxz, impxz);
    puntoC(impxz, 4);

    return 0;
}

void ingreso(CHOFER datos[], int cc){
    CHOFER info;
    printf("--INGRESO DATOS CHOFERES--\n");
    for(int i = 0; i < cc; i++){
        printf("Ingrese cod chofer: ");
        info.codC = leeryvalE2(1000, 9999);
        while(busqueda(datos, i, info.codC) != -1){
            printf("El cod se repite. Reingrese: ");
            info.codC = leeryvalE2(1000, 9999);
        }
        printf("Ingrese apellido y nombre: ");
        leertexto(info.AyN, 50);
        valVacio(info.AyN, 50);
        printf("Ingrese antiguedad: ");
        info.ant = leeryvalInt(0);
        printf("Ingrese imp/km: ");
        info.impkm = leeryvalFloat(2150);
        datos[i] = info;
    }
}

/*void ponerencero(VIAJES datosB[], int cc){
    for(int i = 0; i < cc; i++){
        datosB[i].kmr = 0;
    }
}*/

int viajesDia(VIAJES datosB[], int cc,  CHOFER datos[]){
    VIAJES aux;
    int i = 0;
    int pos;
    printf("--VIAJES X DIA--:\n");
    printf("Ingrese cod chofer: ");
    aux.codC = leeryvalE2CF(1000, 9999, 999);
    while(aux.codC != 999){
        pos = busqueda(datos, cc, aux.codC);
        if(pos != -1){
            printf("Ingrese kms recorridos: ");
            aux.kmr = leeryvalInt(1);
            printf("Ingrese la zona (L-B-P-N): ");
            aux.zr = zonaVal();
            printf("Viaje guardado\n");
            datosB[i]=aux;
            i++;
            printf("Ingrese cod del chofer: ");
        }
        else{
            printf("No se encontro. Reingrese");
        }
        aux.codC = leeryvalE2CF(1000, 9999, 999);
    }
    return i;
}

int leeryvalE2(int min, int max){
    int dato;
    scanf("%d", &dato);
    while(dato < min || dato > max){
        printf("Dato invalido. Reingrese: ");
        scanf("%d", &dato);
    }
    return dato;
}

int leeryvalInt(int lim){
    int dato;
    scanf("%d", &dato);
    while(dato < lim){
        printf("Dato invalido. Reingrese: ");
        scanf("%d", &dato);
    }
    return dato;
}

float leeryvalFloat(float lim){
    float dato;
    scanf("%f", &dato);
    while(dato < lim){
        printf("Dato invalido. Reingrese: ");
        scanf("%f", &dato);
    }
    return dato;
}

int busqueda(CHOFER datos[], int cc, int cod){
    int pos = -1;
    int i = 0;
    while(pos == -1 && i < cc){
        if(datos[i].codC == cod){
            pos = i;
        }
        else{
            i++;
        }
    }
    return pos;
}

int leeryvalE2CF(int min, int max, int cf){
    int dato;
    scanf("%d", &dato);
    while((dato < min || dato > max) && dato != cf){
        printf("Dato invalido. Reingrese:");
        scanf("%d", &dato);
    }
    return dato;
}

void leertexto(char texto[], int max){
    fflush(stdin);
    int i = 0;
    fgets(texto, max, stdin);
    while(texto[i] != '\0'){
        if(texto[i] == '\n'){
            texto[i] = '\0';
        }
        else{
            i++;
        }
    }
}

void valVacio(char texto[], int max){
    while(strlen(texto) == 0){
        printf("Texto vacio. Reingrese: ");
        leertexto(texto, max);
    }
}

char zonaVal(){
    char dato;
    fflush(stdin);
    scanf("%c", &dato);
    dato = toupper(dato);
    while(dato != 'L' && dato != 'B' && dato != 'P' && dato != 'N'){
        printf("Zona invalida. Reingrese: ");
        fflush(stdin);
        scanf("%c", &dato);
        dato = toupper(dato);
    }
    return dato;
}



void listado(VIAJES datosB[], CHOFER datos[], int cc, int cv){
    int kms;
    for(int i = 0; i < cc; i++){
        kms=0;
        for (int j = 0; j < cv; j++)
        {
            if (datosB[j].codC==datos[i].codC)
            {
                kms+=datosB[j].kmr;
            }
        }
        printf("%s Km:%d imp:$%.2f\n",datos[i].AyN,kms,(kms*datos[i].impkm));
    }
}

float minimo(float impxz[], int cz)
{
    float min = impxz[0];
    for(int i = 0; i < cz; i++){
        if(impxz[i] < min){
            min = impxz[i];
        }
    }
    return min;
}

void puntoB(VIAJES datosB[], CHOFER datos[], int cc, int cv, int kmxz[], float impxz[]){
    int pos;
        for (int j = 0; j < cv; j++)
        {   
            pos=busqueda(datos, cc, datosB[j].codC);
            switch(datosB[j].zr){
                case 'L':
                    kmxz[0]+=datosB[j].kmr;
                    impxz[0]+=(datos[pos].impkm*datosB[j].kmr);
                break;
                case 'B':
                    kmxz[1]+=datosB[j].kmr;
                    impxz[1]+=(datos[pos].impkm*datosB[j].kmr);
                break;
                case 'P':
                    kmxz[2]+=datosB[j].kmr;
                    impxz[2]+=(datos[pos].impkm*datosB[j].kmr);
                break;
                case 'N':
                    kmxz[3]+=datosB[j].kmr;
                    impxz[3]+=(datos[pos].impkm*datosB[j].kmr);
                break;
            }
        }
        printf("En La Boca se recorrieron %d kms con un total de $%.2f\n", kmxz[0], impxz[0]);
        printf("En Barracas se recorrieron %d kms con un total de $%.2f\n", kmxz[1], impxz[1]);
        printf("En Parque Patricios se recorrieron %d kms con un total de $%.2f\n", kmxz[2], impxz[2]);
        printf("En Nueva Pompeya se recorrieron %d kms con un total de $%.2f\n", kmxz[3], impxz[3]);
}

void puntoC(float impxz[], int cz){
    float min=minimo(impxz, cz);
    for (int i = 0; i < cz; i++)
    {
        if (impxz[i]==min)
        {
            if (i==0)
            {
                printf("La boca fue la zona que menos facturo.\n");
            }
            if (i==1)
            {
                printf("Barracas fue la zona que menos facturo.\n");
            }
            if (i==2)
            {
                printf("Parque patricios fue la zona que menos facturo.\n");
            }
            if (i==3)
            {
                printf("Pompeya fue la zona que menos facturo\n");
            }
        }
    }
}