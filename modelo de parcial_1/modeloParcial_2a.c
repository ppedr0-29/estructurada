/*Una fábrica de empanadas necesita controlar la venta de sus casi 20 gustos de empanada y 
para ello deben registrar y almacenar con la estructura adecuada:

Código de empanada (entero de 3 cifras no correlativo y sin repetidos)
Nombre Gusto (string de 25 caracteres)
Cocción (H – Horno, F – Fritas, S – Sin Cocción)
Cantidad Vendida (entero mayor a 0)
Precio (real mayor que cero)

La registración de gustos termina con el ingreso de un código de empanada igual a cero.

Luego por cada código de empanada se ingresará la venta que hizo por cada día de la semana 
(real mayor o igual que 0) en los 7 días de la semana y debe actualizar la cantidad vendida. 
La carga de las ventas finaliza con un código de empanada igual a cero.

Se necesita determinar e informar:

Listado de importe total vendido por día y código de empanada mostrando su nombre 
(resolver en una función).
El nombre del gusto que tuvo la mayor venta, en caso de ser más de uno mostrarlos a todos.
La cantidad total vendida por Cocción (resolver en una función).

Validar todos los datos que ingresan por teclado según lo indicado.
El código debe estar correctamente indentado.   10:05 11.06 11.16*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define TAM 25
#define CANT 20

typedef struct 
{
    int cod;
    char gusto[TAM];
    char cat;
    int cant;
    float precio;
}emp;

int ingreso(emp[], int);
emp ingresoStruct(emp[], int);
void ventas(emp[], int, float[][7]);
void listado(emp[], int, float[][7]);
void mostrarMayor(emp[], int, float[][7]);
void mostrarCat(emp[], int);
float mayor(float [][7], int);
void categorias(emp [], int , int []);
int busqueda(emp [], int , int );
int norepite(emp [], int , int);
float leeyvalidaFloat(int );
int leeyvalidaInt(int );
char leeyvalidaChar();
void leerTexto(char [], int );
void validarVacio(char [], int );
int leeyvalidaEntre2CF(int , int , int );


int main(){
    emp datos[CANT];
    float ventaxSem[CANT][7]={{0}};
    int cantEmp=ingreso(datos, CANT);
    ventas(datos, cantEmp, ventaxSem);
    listado(datos, cantEmp, ventaxSem);
    mostrarMayor(datos, cantEmp, ventaxSem);
    mostrarCat(datos, cantEmp);
    return 0;
}
int ingreso(emp datos[], int ce){
    printf("--INGRESO DE GUSTOS--\n");
    emp aux;
    int flag=0;
    int i=0;
    while(flag==0 && i<ce){
        aux=ingresoStruct(datos, i);
        if(aux.cod!=0){
            datos[i]=aux;
            i++;
        }else{
            flag=1;
        }
    }
    printf("INGRESO FINALIZADO\n");
    return i;
}

emp ingresoStruct(emp datos[], int i){
    emp aux;
    printf("Ingrese el cod de empanada: ");
    aux.cod=leeyvalidaEntre2CF(100,999,0);
    while(norepite(datos, i, aux.cod)==1){
        printf("El codigo ya existe. Ingrese otro:");
        aux.cod=leeyvalidaEntre2CF(100,999,0);
    }
    if(aux.cod!=0){
        printf("ingrese el gusto: ");
        leerTexto(aux.gusto, TAM);
        validarVacio(aux.gusto, TAM);
        printf("Ingrese el tipo de coccion: (H-horno, F-frita, S-Sin coccion): ");
        aux.cat=leeyvalidaChar();
        printf("Ingrese cantidad vendida: ");
        aux.cant=leeyvalidaInt(0);
        printf("Ingrese el precio: ");
        aux.precio=leeyvalidaFloat(0);
        printf("EMPANADA GUARDADA\n");

    }
    return aux;
}

void ventas(emp datos[], int ce, float m[][7]){
    int cod, pos;
    float totVenta;
    printf("--INGRESO DE VENTAS X SEMANA--\n");
    printf("Ingrese el codigo de empanada: ");
    cod=leeyvalidaEntre2CF(100,999,0);
    while(cod!=0){
        pos=busqueda(datos, ce, cod);
        if(pos!=-1){
            for(int i=0; i<7; i++){
                printf("Ingrese las ventas del dia %d: ", i+1);
                totVenta=leeyvalidaFloat(0);
                m[pos][i]=totVenta;
                datos[pos].cant+=(int)(totVenta/datos[pos].precio);
            }
            printf("venta registrada\n");
            printf("Ingrese el codigo de empanada: ");
        }else{
            printf("El codigo no existe. Reingrese: ");
        }
        cod=leeyvalidaEntre2CF(100,999,0);
    }
    printf("VENTAS FINALIZADAS\n");

}

void listado(emp datos[], int ce, float m[][7]){
    printf("--LISTADO VENTAS X DIA--\n");
    for (int i = 0; i < 7; i++){
        printf("DIA %d\n", i+1);
        for(int j=0;j<ce;j++){
            printf("%d. importe $%.2f codigo: %d gusto: %s\n", j+1, m[j][i], datos[j].cod, datos[j].gusto);
        }
    }
    
}

void mostrarMayor(emp datos[], int ce, float m[][7]){
    float max=mayor(m, ce);
    for(int i=0;i<7;i++){
        for(int j=0;j<ce;j++){
            if(m[j][i]==max){
                printf("%s es el gusto/s que mas facturo con un importe de $%.2f\n", datos[j].gusto, m[j][i]);
            }
        }
    }
}
float mayor(float m[][7], int ce){
    float max = m[0][0];
    for(int i=0;i<ce;i++){
        for(int j=0;j<7;j++){
            if(m[i][j]>max)
                max=m[i][j];
        }
    }
    return max;
}

void mostrarCat(emp datos[], int ce){
    int cantxCat[3]={0};
    categorias(datos,ce,cantxCat);
    printf("Se vendieron %d empanadas horneadas\n", cantxCat[0]);
    printf("Se vendieron %d empanadas fritas\n", cantxCat[1]);
    printf("Se vendieron %d empanadas sin cocinar\n", cantxCat[2]);
}

void categorias(emp datos[], int ce, int vec[]){
    for(int i =0; i<ce; i++){
        switch (datos[i].cat)
        {
        case 'H':
            vec[0]+=datos[i].cant;
            break;
        case 'F':
            vec[1]+=datos[i].cant;
            break;
        case 'S':
            vec[2]+=datos[i].cant;
            break;
        }
    }
}

int busqueda(emp datos[], int ce, int num){
    int pos=-1;
    int j=0;
    while(pos==-1 && j<ce){
        if(datos[j].cod==num){
            pos=j;
        }else{
            j++;
        }
    }
    return pos;
}

int norepite(emp datos[], int i, int num){
    int j=0;
    int flag=0;
    while(flag==0&&j<i){
        if(datos[j].cod==num){
            flag=1;
        }else{
            j++;
        }
    }
    return flag;
}

float leeyvalidaFloat(int lim){
    float dato;
    scanf("%f", &dato);
    while(dato<=lim){
        printf("Numero invalido. Reingrese: ");
        scanf("%f", &dato);
    }
    return dato;
}

int leeyvalidaInt(int lim){
    int dato;
    scanf("%d", &dato);
    while(dato<=lim){
        printf("Numero invalido. Reingrese: ");
        scanf("%d", &dato);
    }
    return dato;
}
char leeyvalidaChar(){
    char dato;
    scanf("%c", &dato);
    dato=toupper(dato);
    fflush(stdin);
    while(dato!='H'&&dato!='F'&&dato!='S'){
        printf("Categoria invalida. Reingrese: ");
        scanf("%c", &dato);
        dato=toupper(dato);
        fflush(stdin);
    }
    return dato;
}

void leerTexto(char texto[], int largo){
    fflush(stdin);
    fgets(texto, largo, stdin);
    int i=0; 
    while(texto[i]!='\0'){
        if(texto[i]=='\n'){
            texto[i]='\0';
        }else
            i++;
    }
}
void validarVacio(char texto[], int largo){
    while(strlen(texto)==0){
        printf("El texto no puede ser vacio. Reingrese: ");
        leerTexto(texto, largo);
    }
}

int leeyvalidaEntre2CF(int min, int max, int cf){
    int dato;
    scanf("%d", &dato);
    while(dato!=cf &&(dato<min || dato>max)){
        printf("El numero invalido. reingrese: ");
        scanf("%d", &dato);
    }
    return dato;
}