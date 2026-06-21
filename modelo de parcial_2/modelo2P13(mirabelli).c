/*La empresa TRASH dispone de un archivo llamado Stock.dat que contiene la información de los productos 
que comercializa.
El archivo contiene la siguiente información:
Código de artículo (string de 3 caracteres)
Descripción (50 caracteres máximo)
Stock (entero)
Luego se ingresan por teclado las compras realizadas indicando:
Código de artículo (string de 3 caracteres)
Cantidad (entero mayor a cero)
La carga por teclado de las compras finaliza con un código de artículo "FIN".
Por cada compra se debe controlar si existe el articulo (resolver en una Función llamada BUSCAR) y si existe, 
actualizar el stock de dicho producto, sino existe el articulo grabar un registro en un archivo Errores.dat 
con la cantidad que no pudo registrar, dicho registro debe contener:
Código de artículo
Cantidad
Si ya hay un registro previo en dicho archivo de errores con el mismo artículo debe incrementarse la cantidad. 
Informar al final la cantidad de artículos actualizados y la cantidad de errores utilizando la función INFORME.
Validar todos los datos que ingresan por teclado según lo indicado.*/