/*Una empresa necesita actualizar el stock de sus productos con las compras y para ello dispone del 
archivo stock.dat con la siguiente estructura:
Código de Producto (string de 3 caracteres)
Descripción (string de 30 caracteres)
Rubro (C – Construcción, E – Electricidad, P – Plomería, F – Fijaciones)
Stock Máximo (entero)
Stock (entero)
Luego por cada producto se ingresarán por teclado el Código de Producto y la cantidad comprada 
(entero positivo) en el mes. En base a la cantidad comprada se debe actualizar el stock en el archivo. 
En caso de no encontrar el Código de Producto en el archivo debe guardarse el error en un archivo 
llamado Errores.dat con la siguiente estructura (Código de Producto y Cantidad Comprada) .
La actualización de compras termina con el ingreso de un Código de Producto igual a "FIN".
Además, se necesita determinar e informar:
La descripción de los productos cuyo stock actualizado supera el stock máximo. (resolver en una función).
El rubro del que se compró la menor cantidad en total (resolver en una función).
Validar los datos que ingresan por teclado según lo indicado.
El código debe estar correctamente identado.
*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef struct 
{
    char codigo[4];
    char descripcion[31];
    char rubro;
    int maxStock;
    int stock;
}STOCK;

typedef struct 
{
    char codigo[4];
    int stock;
}COMPRA;

void generarArchivoInicial();
void procesarArchivos(int*);
FILE* abrirArchivo(char [], char []);
void leertexto(char[], int);
void valVacio(char[], int);
void leeyvalidaInt(int*,int );
long busqueda(FILE*, char[], STOCK*);
int indice(char);
void mostrarStockMax();
void minimo(int*);
void mostrarMinimo(int, int*);

int main(){
    generarArchivoInicial();
    int cantTotal[4]={0};
    procesarArchivos(cantTotal);//saber si se pasa asi o con el &
    mostrarStockMax();
    minimo(cantTotal);
    return 0;
}

void procesarArchivos(int*cantTotal){
    FILE *archS;
    FILE *archE;
    COMPRA compras;
    STOCK datos, *pdatos=&datos;
    long pos;
    int i;
    archS=abrirArchivo("stock.dat", "r+b");
    archE=abrirArchivo("errores.dat", "wb");
    printf("Ingrese el codigo de producto: ");
    leertexto(compras.codigo, 4);
    valVacio(compras.codigo, 4);
    while(strcmpi(compras.codigo, "FIN")!=0){
        printf("Ingrese la cantidad comprada: ");
        leeyvalidaInt(&compras.stock, 1);
        pos=busqueda(archS, compras.codigo, pdatos);
        if(pos!=-1){
            datos.stock+=compras.stock;
            fseek(archS, pos, SEEK_SET);
            fwrite(&datos, sizeof(datos), 1, archS);
            fflush(archS);
            i=indice(datos.rubro);
            cantTotal[i]+=compras.stock;//fijarse si esto es asi o con *
        }else{
            fwrite(&compras, sizeof(compras), 1, archE);
        }
        printf("Ingrese el codigo de producto: ");
        leertexto(compras.codigo, 4);   
        valVacio(compras.codigo, 4);
    }
    fclose(archE);
    fclose(archS);
}


void minimo(int *cantTotal){//devuelta verificar como manerar el puntero aca, si con o sin *
    int minimo=cantTotal[0];
    int pos=0;
    for(int i=1;i<4;i++){//inicializo en uno porque en cero ya setee el minimo
        if(cantTotal[i]<minimo){
            minimo=cantTotal[i];
            pos=i;
        }
    }
    mostrarMinimo(pos, cantTotal);
}

void mostrarMinimo(int pos, int*cantTotal){
    switch(pos){
        case 0:
            printf("el rubro que menos compro fue construccion con una compra de %d\n", cantTotal[pos]);
            break;
        case 1:
            printf("el rubro que menos compro fue electricidad con una compra de %d\n", cantTotal[pos]);
            break;
        case 2:
            printf("el rubro que menos compro fue plomeria con una compra de %d\n", cantTotal[pos]);
            break;
        case 3:
            printf("el rubro que menos compro fue fijaciones con una compra de %d\n", cantTotal[pos]);
            break;
        
    }
}

void mostrarStockMax(){
    STOCK datos;
    FILE*arch;
    arch=abrirArchivo("stock.dat", "rb");
    fread(&datos, sizeof(datos), 1, arch);
    printf("---productos que superan el stock maximo---\n");
    while(!feof(arch)){
        if(datos.stock>datos.maxStock){
            printf("-%s\n", datos.descripcion);
        }
        fread(&datos, sizeof(datos), 1, arch);
    }
    fclose(arch);
}

int indice(char dato){
    int indice;
    switch (dato)
    {
    case 'C':
        indice=0;
        break;
    case 'E':
        indice=1;
        break;
    case 'P':
        indice=2;
        break;
    case 'F':
        indice=3;
        break;
    }
    return indice;
}

long busqueda(FILE*arch, char codigo[], STOCK*pdatos){
    long pos=-1;
    STOCK datos;
    int flag =0;
    rewind(arch);
    fread(&datos, sizeof(datos), 1, arch);
    while(!feof(arch)&&flag==0){
        if(strcmpi(datos.codigo, codigo)==0){
            pos=ftell(arch)-sizeof(datos);
            *pdatos=datos;
            flag=1;
        }else
            fread(&datos, sizeof(datos), 1, arch);
    }
    return pos;
}
void leeyvalidaInt(int *dato, int lim){
    scanf("%d", dato);
    while(*dato<lim){
        printf("Error. reingrese: ");
        scanf("%d", dato);
    }
}


void leertexto(char texto[], int largo){
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
        printf("Error, el texto no puede ser vacio. Reingrese: ");
        leertexto(texto, largo);
    }
}


FILE* abrirArchivo(char nombre[], char tipo[]){
    FILE *arch;
    arch=fopen(nombre, tipo);
    if(arch == NULL){
        printf("ERROR");
        getch();
        exit(1);
    }
    return arch;
}
void generarArchivoInicial() {
    FILE *arch = fopen("stock.dat", "wb");
    if (arch == NULL) {
        printf("ERROR: No se pudo crear el archivo de prueba stock.dat\n");
        exit(1);
    }

    STOCK productos[20] = {
        // --- CONSTRUCCIÓN (C) ---
        {"C01", "Cemento Avellaneda x 50kg", 'C', 150, 120},
        {"C02", "Cal Hidratada Milagro 25kg", 'C', 100, 95}, 
        {"C03", "Arena Lavada por Bolsón",    'C', 50,  30},
        {"C04", "Ladrillo Hueco 12x18x33 xU", 'C', 500, 400},
        {"C05", "Hierro del 8 AcelorMittal",  'C', 80,  45},

        // --- ELECTRICIDAD (E) ---
        {"E01", "Cable Unipolar 2.5mm 100m", 'E', 60,  55},  
        {"E02", "Llave Termica Sica 2x20A",  'E', 40,  15},
        {"E03", "Caja Otogonal Chapa Sica",  'E', 200, 180},
        {"E04", "Cinta Aisladora 3M Negra",  'E', 150, 80},
        {"E05", "Disyuntor Diferencial 2x40", 'E', 25,  10},

        // --- PLOMERÍA (P) ---
        {"P01", "Codo Fusion Verde 20mm",    'P', 200, 195}, 
        {"P02", "Caño AquaSystem 20mm x 4m", 'P', 80,  60},
        {"P03", "Teflon Alta Densidad 3/4",  'P', 120, 100},
        {"P04", "Adhesivo PVC Tigre 250cc",  'P', 35,  30},
        {"P05", "Flexible Mallado Inox 1/2", 'P', 50,  12},

        // --- FIJACIONES (F) ---
        {"F01", "Tornillo Fix 4x16 x100 u",  'F', 300, 150},
        {"F02", "Tarugo Fischer c/Tope N8",  'F', 500, 480}, 
        {"F03", "Clavo Punta Paris 2 pulg",  'F', 100, 40},
        {"F04", "Remache Aluminio 4x10 x100", 'F', 150, 90},
        {"F05", "Anclaje Espiga 3/8 x 3",    'F', 60,  55}   
    };

    fwrite(productos, sizeof(STOCK), 20, arch);
    fclose(arch);
    printf(">> Archivo 'stock.dat' inicializado con 20 productos.\n\n");
}