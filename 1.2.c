/*1° Ingreso CodPro (4 cifras y 0)
2° while (codPro !=0)
2.1° Buscar en vProd
Si Existe ingresa cant >0 y acumulas en vCant
Si no Existe mensaje aclaratorio
2.2° Ingresar codPro (4 cifras y cero)
3° Informes
*/

/*1.2 Una empresa debe registrar los pedidos recibidos de cada uno sus 10 productos a lo largo del día. Cada
producto está identificado por un código de 4 cifras. Los códigos deben ingresarse al inicio del programa
mediante la función IngresaCódigos y no pueden repetirse.
Por cada pedido se recibe:
• Código de producto
• Cantidad de unidades solicitadas
Se puede recibir más de un pedido por producto.
La carga de pedidos finaliza cuando se ingresa un producto igual a 0*/

#include <stdio.h>
#define TAM 10

void ingresaCodigos(int [], int []);
int leeyvalida (int , int);
void norepite(int [], int);
void pedidos(int [], int []);
int valCant (int);
int validaCodigo (int , int []);
void informeA (int [], int []);
int maximo (int [], int []);
void informeB (int [], int, int []);
int minimo (int [], int []);
void informeC(int [], int, int []);

int main (){
    int vCod [TAM], vProd[TAM]={0};
    ingresaCodigos(vCod, vProd);
    pedidos(vCod, vProd);
    informeA(vCod, vProd);
    int max= maximo(vCod, vProd);
    informeB(vCod, max, vProd);
    int min= minimo(vCod, vProd);
    informeC(vCod, min, vProd);

    return 0;
}

void ingresaCodigos (int vCod[], int vProd[]){
    int i;

    for (i=0; i<TAM; i++)
    {
        printf("Ingrese codigo de producto %d (4 cifras):", i+1);
        vCod[i]= leeyvalida(1000, 9999);
        norepite(vCod, i);
    }
}

int leeyvalida (int li, int ls){ // valida entre 2 numeros
    int dato;
    scanf("%d", &dato);
    while (dato<li || dato>ls)
    {
        printf("El codigo es invalido. Ingrese nuevamente\n");
        scanf("%d", &dato);
    }
    return dato;
}

void norepite (int vCod[], int i){
    int flag=0, j;
    for(j=0; j<i; j++){ // se busca hasta i-1, para que no arroje el mismo valor
        if (vCod[j]==vCod[i])
            flag=1;
    }
    while (flag==1){
        printf("Codigo repetido. Ingrese nuevamente:\n");
        scanf("%d", &vCod[i]);
        flag=0;
        for(j=0; j<i; j++){
            if (vCod[j]==vCod[i]){
                flag=1;
            }
        }
    }
}

void pedidos(int vCod[], int vProd[]){
    int codPedido, pos, cant;
    printf("Ingresar codigo para realizar pedido (0 para finalizar):");
    scanf("%d", &codPedido);
    while (codPedido!=0){
    pos= validaCodigo(codPedido, vCod);
    if (pos==-1){
        printf("El codigo no existe.\n");
        }else{
        printf("Ingrese la cantidad del producto(%d):", codPedido);
        cant = valCant(0);
        vProd[pos]= vProd[pos] + cant;
        }
    printf("Ingresar codigo para realizar pedido (0 para finalizar):");
    scanf("%d", &codPedido);
    }
    printf("Carga de productos finalizada.");
}

int valCant (int lim){
    int dato;
    scanf("%d", &dato);
    while (dato<=0)
    {
        printf("Cantidad invalida. Ingrese nuevamente:");
        scanf("%d", &dato);
    }
    return dato;
}

int validaCodigo (int codPedido, int vCod []){
    int flag=0, j;
    int rt=-1;

    for (j=0; j<TAM && flag==0; j++)
    {
        if (codPedido==vCod[j])
        {
            flag=1;
            rt=j;
        }
    }
    return rt;
}

void informeA(int vCod[], int vProd[]){
    int i;
    for(i=0; i<TAM; i++){
        printf("\n%d unidades del producto %d", vProd[i], vCod[i]);
    }
}

int maximo(int vCod[], int vProd[]){
    int max= vProd[0], i;
    for (i = 1; i < TAM; i++)
    {
        if (vProd[i]>max)
        {
            max=vProd[i];
        }
    }
    return max;
}

void informeB(int vCod[], int max, int vProd []){
    for (int i = 0; i < TAM; i++)
    {
        if (vProd[i]==max)
        {
            printf("\nEl producto %d alcanzo la mayor cantidad de pedidos", vCod[i]);
        }
    }
    
}

int minimo(int vCod[], int vProd[]){
    int i=0;
    int min;
    
    while (vProd[i]==0)
    {
        i++;
    }
    min= vProd[i];
    for (i=i+1; i < TAM; i++)
    {
        if (vProd[i]<min)
        {
            min=vProd[i];
        }
        
    }
    return min;
}

void informeC(int vCod[], int min, int vProd []){
    for (int i = 0; i < TAM; i++)
    {
        if (vProd[i]==min && vProd[i]>0)
        {
            printf("\nEl producto %d alcanzo la menor cantidad de pedidos", vCod[i]);
        }
    }
    
}
