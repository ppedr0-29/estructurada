/*Una agencia necesita liquidar las comisiones de sus vendedores y para ello dispone del archivo ventas.dat 
con la siguiente estructura:
Vendedor (string de 4 caracteres)
Nombre Vendedor (string de 30 caracteres)
Sector (H – Hogar, E – Electrodomésticos, B – Bazar, T – Telefonía)
Porcentaje de comisión (entero entre 5 y 30)
Comisión a cobrar (real)
Luego por cada vendedor se ingresa por teclado el Vendedor, Sector y el importe vendido en el mes (real positivo). 
En base al porcentaje de comisión y el importe vendido se debe actualizar la comisión a cobrar en el archivo. 
En caso de no encontrar el Vendedor en el archivo debe guardarse el error en un archivo llamado Errores.dat con 
la siguiente estructura 
(Vendedor, Sector y el importe vendido) .
El ingreso de las ventas termina con el ingreso de un vendedor igual a "FFFF".
Además, se necesita determinar e informar:
El nombre del vendedor que cobra la mínima comisión actualizada, en caso de ser más de uno mostrar a todos.
El porcentaje de comisiones a pagar por cada sector respecto del total vendido (resolver en una función).
Validar todos los datos que ingresan por teclado según lo indicado.
El código debe estar correctamente identado.*/

/*abrir ventas.dat ("r+b"), abrir Errores.dat ("wb")
impSector[4] = {0,0,0,0}   // H, E, B, T -> índices 0..3
comSector[4] = {0,0,0,0}

ingreso vendedor, sector, importe (con validación: sector debe ser H/E/B/T, importe>0)

while(vendedor != "FFFF")
    pos = busqueda(archVentas, vendedor, &reg)   // rewind interno, devuelve pos o -1

    si pos != -1{
        reg.comision += (importe * reg.porcentaje) / 100
        fseek(archVentas, pos, SEEK_SET)
        fwrite(&reg, sizeof(reg), 1, archVentas)
        fflush(archVentas)

        i = indiceSector(sector)        // mapea 'H','E','B','T' -> 0,1,2,3
        impSector[i] += importe
        comSector[i] += (importe * reg.porcentaje) / 100
    }
    si no{
        error.vendedor = vendedor
        error.sector = sector
        error.importe = importe
        fwrite(&error, sizeof(error), 1, archErrores)
    }

    ingreso vendedor, sector, importe (validado)
fin while

cerrar archVentas, archErrores

// recién ACÁ, fuera del while:
minimo = buscarMinimo(archVentas)        // recorre TODO el archivo, primero/flag, sin tocar impSector ni comSector
int primero=1
if(primero==1)
min=com
primero=0;
else
if com<min
min=com
mostrarMinimo(archVentas, minimo)        // recorre de nuevo, imprime nombre de cada uno con comision==minimo

porcentajePorSector(impSector, comSector)   // NO recibe el archivo, ya tiene todo acumulado
    for i = 0 hasta 3
        si impSector[i] > 0
            porcentaje = (comSector[i] / impSector[i]) * 100
            mostrar sector i, porcentaje
        si no
            mostrar "sector sin ventas este mes"*/