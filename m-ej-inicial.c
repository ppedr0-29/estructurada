/*
Una cadena de supermercados tiene 5 sucursales y comercializa 12 rubros distintos
de mercadería.  A diario se recibe las notas de pedido de mercadería originadas
por sus sucursales.  Estos datos son:
    Número de sucursal (entero, de 1 a 5)
    Código de rubro (entero, de 1 a 12)
    Cantidad pedida (entero, mayor que cero)
El ingreso de datos termina con número de sucursal igual a cero, los datos vienen
desordenados y puede venir para la misma sucursal y rubro más de una información.
Informar con títulos aclaratorios:
Cantidad pedida por sucursal en cada rubro.
Cantidad pedida por sucursal.
Cantidad pedida por rubro.
Rubro de mayor cantidad pedida (en total – Suponemos único).
Cantidad pedidas del rubro 7 para todas las sucursales.
Qué sucursal pidió la menor cantidad en total (puede haber más de una sucursal).
Cantidad de rubros NO pedidos por ninguna sucursal.

*/
#include <stdio.h>

void PonerEnCeroM(int[][12], int, int);
void PonerEnCero(int[], int);
int IngrDatoValRango(int,int );
int ingrDatoVal(int);
void CargaMat(int [][12],int , int);
void MostrarMatFila(int [][12], int, int);
void SumarFilaMatEnV(int [][12], int, int , int[]);
void MostrarVec(int[],int);
void SumarColMatAVec(int [][12], int, int , int[]);
int PosicionMax(int[],int );
void MostrarVecM(int [][12],int,int );
int Minimo(int [],int );
void MostrarIgualA(int [],int , int );
int ContarIgualA(int [],int, int );

int main()
{
    int Mat [5][12];
    int vSuc [5];
    int vRub [12];
    int posMay,min,Sinvta;
    PonerEnCeroM(Mat, 5, 12);
    PonerEnCero(vSuc,5);
    CargaMat(Mat, 5, 12);
    MostrarMatFila(Mat, 5, 12);
    SumarFilaMatEnV(Mat, 5, 12, vSuc);
    printf("\n Cantidad pedida por sucursal");
    MostrarVec(vSuc, 5);
    SumarColMatAVec(Mat, 5, 12 , vRub);
    printf("\n Cantidad pedida por rubro");
    MostrarVec(vRub, 12);
    posMay=PosicionMax(vRub,12);
    printf("\n Rubro mas vendido es el rubro %d \t",posMay+1);
    printf("\n Cantidad pedidas del rubro 7 para todas las sucursales");
    MostrarVecM(Mat,5,7);
    min=Minimo(vSuc,5);
    //printf ("\n minimo %d ", min);
    printf("\n Sucursal que pidio la menor cantidad en total (puede haber mas de una sucursal)");
    MostrarIgualA(vSuc,5,min);
    Sinvta=ContarIgualA(vRub,12,0);
    printf("\n Rubros sin ventas %d",Sinvta);
    return 0;
}
/////////////////////////FUNCIONES/////////////////////////////////////

void PonerEnCeroM(int m[][12], int f, int c){
    for(int i=0; i<f; i++){
        for(int j=0; j<c; j++){
            m[i][j]=0;
        }
    }
}

void PonerEnCero(int v[], int ce){
    for(int i=0; i<ce; i++){
        v[i]=0;
    }
}

int IngrDatoValRango(int min, int max ){
    int dato;
    scanf("%d", &dato);
    while(dato<min || dato>max){
        printf("Error. Ingrese un dato valido entre %d y %d:", min, max);
        scanf("%d", &dato);
    }
    return dato;
}

int ingrDatoVal(int lim){
    int dato;
    scanf("%d", &dato);
    while(dato<=lim){
        printf("Error. Ingrese un dato mayor a %d:", lim);
        scanf("%d", &dato);
    }
    return dato;
}

void CargaMat(int m[][12],int f, int c){
    printf("Ingrese numero de sucursal entre 1 y 5 (0 finaliza):");
    int suc= IngrDatoValRango(0,f);
    int rub;
    int cant;

    while(suc!=0){
            printf("Ingrese codigo de rubro entre 1 y 12:");
            rub= IngrDatoValRango(1,c);
            printf("Ingrese cantidad pedida:");
            cant= ingrDatoVal(0);
            m [suc][rub]+= cant;
            printf("Ingrese numero de sucursal entre 1 y 5 (0 finaliza):");
            int suc= IngrDatoValRango(0,f);
    }
    printf("Ingreso de datos finalizado.");
}

void MostrarMatFila(int m[][12], int f, int c){
    printf("\n--TABLA SUCURSAL POR RUBRO--\n");
    printf("Rubro:\t\t1\t2\t3\t4\t5\t6\t7\t8\t9\t10\t11\t12");
    for(int i=0; i<f; i++){
            printf("Sucursal %d\t", i+1);
        for(int j=0; j<c; j++ ){
            printf("%4d", m[i][j]);
        }
        printf("\n");
    }

}
void SumarFilaMatEnV(int m [][12], int f, int c, int v[]){
        int suma;
        for (int i=0; i<f;i++){
                suma=0;
            for (int j=0;j<c;j++){
                suma += m[i] [j] ;
            }
            v[i] = suma;

        }


}

    void MostrarVec(int v[],int ce){
        for(int i=0;i<ce;i++){
            printf("\n %d",v[i]);

        }
    }
void SumarColMatAVec(int m [][12], int f, int c , int v[]){
            int suma;
        for (int i=0; i<c;i++){
                suma=0;
            for (int j=0;j<f;j++){
                suma += m[j] [i] ;
            }
            v[i] = suma;

        }

        }
        int PosicionMax(int v[],int ce ){
        int max=v[0];
        int pos;
        for(int i=1; i<ce; i++){
            if(v[i]>max){
                max=v[i];
            }
        }
        for(int i=0; i<ce; i++){
            if(v[i]==max){
                pos=i;

            }
        }
        return pos;

        }
    void MostrarVecM(int m [][12],int f,int rubro ){

    int suma=0;

        for(int i=0; i<f; i++){
            suma+= m [i] [rubro];

        }
            printf("%d", suma);


    }

int Minimo(int v [],int ce ){
    int min=v[0];
    for(int i=1;i<ce; i++ ){
    if(v[i]<min){
        min=v[i];
    }
    }
return min;

}

void MostrarIgualA(int v[],int ce, int dato){
    for(int i=0; i<ce; i++){
        if(v[i]==dato){
            printf("%d", i+1);
        }
    }

}

int ContarIgualA(int v[], int ce, int dato ){
    int suma=0;
    for(int i=0; i<ce; i++){
        if(v[i]==dato){
                suma++;
        }
    }
    return suma;
}