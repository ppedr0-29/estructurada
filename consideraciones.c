
/* 
CONSIDERACIONES
ctype solo si usas tolower
stdlib tiene la de system("pause")
#define name dato constantes
octal 045
hexa 0x4567
todas las variables al inicio

getchar()limpia el buffer del eneter dsp de scanf
fflush(sdtin)funciona pero no en todos los compiladores

if de una sola instruccion:
        expresión? Instruccion1 (true): Instruccion2 (false);
        ej: (n%2==0)?printf("\nPar"):printf("\nImpar");

En operadores logicos siempre lee en orden, ejemplo si hay una cond falsa en un producto, deja de evaluar
y ya da un false como resultado

False = 0
True = !0

Switch (char o entero){
    case 1:
        break; si o si sino sigue leyendo
    default: (opcional)}
    
b=5++=5 
b=++5 = 6

while(cond) si es verdadera entra en el bucle, si es falsa sale. puede no ejecutarse nunk
    True
False

do{
}while(cond) se ejecuta minimo una ves y si la cond es verdadera vuelve a hacerse, si es falsa sigue su camino
Si un programa falla cuando el primer dato ingresado es la condición de fin, el programa está MAL diseñado
(no uso dowhile para ingreso de datos si corto con un dato de los de ingreso, porque operaria con ese dato antes de analizarlo)

for(cond inicial; cond; incremento){} se sabe exactamente la cantidad de veces que se va a ejecutar.

funciones:
prototipo dsp de los define
tipo de dato nombre de la funcion (tipos de datos a recibir, sin nombre);
primero va el main y dsp las funciones.

no poner mas de un return por funcion. utilizar una variable y que luego devuelva esa variable
Los datos de los argumentos se pasan por copia. main a fun: te paso un marcador, fun: listo, creo otro 
marcador.

Vectores:
siempre señalan la primera direccion de memoria. con el indice en 0. las demas direcciones se calculan de
 acuerdo al indice
tipo_de_dato_base nombre_del_vector [cantidad de elementos];

C no chequea hasta donde llega el vector. esa es responsabilidad del programador cuidar que el programa 
se mantenga entre los limites definidos
Cuando se conoce la cant exacta de elementos a ingresar se utiliza un ciclo for, pero cuando no se conoce 
exactamente la cantidad, si van a ser 
todos, la mitad o ninguno, se hace una carga parcial. 

Carga parcial:
para eso se tiene que tener una variable que diga cuantos elementos hay guardados en el vector, pasa a 
ser el tamaño del vector
para agregar otro dato se guarda en una variable aux para primero verificar si hay espacio y si hay ahi 
guardarlo.

Incializar un vector:
int vec[2]={1,2}  |1|2|         se pone entre llaves cada elemento
int vec[5]={1,2}  |1|2|0|0|0|   si no se ponen todos, rellena con ceros
int vec[]={1,2}   |1|2|         si no se pone el tamaño, el compilador lo estima de acuerdo a la cantidad de elementos
int vec[2]={0}    |0|0|         inicializacion en 0 para todo
int vec[2]={1}    |1|0|         No se inicializa con otro valor, solo lo pondria en el primer lugar y despues rellena con ceros
int vec[2]={1,1}  |1|1|         para incializar en un valor distinto de 0 hay que poner eso a inciializar en todas las posiciones

solo cuando estoy declarandolo, una vez hecho si o si se hace en un bucle.

AL pasar un vector como parametro se pasa la direccion de memoria osea que se modifica el vector, no se duplica
al pasarlo solo se escribe el nombre pero al parametrizar la funcion se pone con corchetes. 

Busqueda de algo en un vector
hay que hacer un ciclo y retornar la posicion donde lo encontro, sino lo encontro devolver -1

Tipo de formas de eencontrar valor maximo o minimo
opcion 1: tomar el primer valor como maximo o como minimo y comparar todos los demas contra ese 
opcion 2: (menos recomendable) tomar un valor imposible dependiendo del contexto
opcion 3: Bandera, sabes si ya se cargo el primer elemento o no.

PUNTEROS Y MEMORIA DINAMICA-----------------------------------------------
si tengo un puntero ej:
int *vec;
y dspues quiero usarlo como vector, si uso scanf puedo usar o v+i directo porque el puntero es una direccion 
de memoria o tambien *v[i], aunque no lo defina como vector al ser un puntero puedo usar subindices

Malloc y Calloc(pone toda la memoria en 0) para asignacion y Realloc para reasignacion (y copia datos 
ya cargados)

para usar un puntero de struct. hay dos formas : 1. (*pt).codigo 2. pt->codigo
realloc tiene que ir en el main 

ARCHIVOS-----------------------------------------------------------------------
Comando / Tipo    Descripción
FILE *    Puntero a la estructura de control del flujo para comunicarnos con el archivo
fopen    Crea el flujo y retorna el puntero
fclose    Cierra el flujo y libera la memoria
fread    Lectura de Archivos Binarios
fwrite    Escritura de Archivos Binarios
feof    Detección del fin de archivo
fprintf    Escritura con formato en archivos de texto


de fread a fwrite va un fseek
de fwrite a fread va o fseek o fflush
*/

/*#include <stdio.h>
#define ARCHIVO "ventas.dat"

typedef struct
{
    int codigo;
    int cantVendida;
    int dia;
} Venta;

int main()
{
    Venta vec[] = {
        {101, 5, 3},
        {101, 2, 7},
        {101, 8, 15},
        {205, 3, 1},
        {205, 6, 12},
        {310, 1, 5},
        {310, 4, 20},
        {310, 2, 28}
    };

    int cant = sizeof(vec) / sizeof(Venta);
    FILE *arch = fopen(ARCHIVO, "wb");
    if (arch == NULL)
    {
        printf("Error al crear el archivo");
        return 1;
    }
    for (int i = 0; i < cant; i++)
        fwrite(&vec[i], sizeof(Venta), 1, arch);

    fclose(arch);
    return 0;
}*/