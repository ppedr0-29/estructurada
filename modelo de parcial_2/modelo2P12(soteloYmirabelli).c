/*La empresa SALES dispone de un archivo llamado Stock.dat que contiene la información de los productos que vende.
El archivo contiene la siguiente información:
Código de artículo (string de 4 caracteres)
Descripción (50 caracteres máximo)
Stock (entero)
Luego se ingresan por teclado las compras realizadas indicando:
Código de artículo (string de 4 caracteres)
Cantidad vendida (entero mayor a cero)
La carga por teclado de las ventas finaliza con un código de artículo "SALE".
Por cada venta se debe controlar si existe el artículo (resolver en una Función llamada BUSCAR) si no existe solicitar nuevamente y si existe, 
actualizar el stock de dicho producto, sino hay stock suficiente grabar un registro en un archivo Errores.dat con la cantidad que no pudo vender, 
dicho registro debe contener:
Código de artículo
Cantidad
Si ya hay un registro previo en dicho archivo de errores con el mismo artículo debe incrementarse la cantidad. Informar al final la cantidad de 
ventas realizadas y la cantidad de ventas no realizadas utilizando la función INFORME.
Validar todos los datos que ingresan por teclado según lo indicado.
El código debe estar correctamente identado.*/