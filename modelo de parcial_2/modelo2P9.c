/*La universidad Argentina de la Empresa (U.A.D.E.) desea realizar un control de los docentes investigadores asociados a los proyectos del año 2025. Un docente puede estar vinculado a uno o varios proyectos de investigación. Dentro del mismo, puede cumplir el rol de Director o Co-Director o investigador de categoría (1 - 5). Se dispone del archivo proyectosinvestigacion2025.dat que contiene los datos de los casi 200 proyectos de investigación, que al día de la fecha se encuentran activos. El diseño del registro es: Nro. de Proyecto (int 1000 - 5500), Nombre del proyecto (Texto de 80 caracteres máximo), Nro. de matrícula de cada uno de los 5 investigadores con categoría (cada nro. de matrícula es un int 111111 - 777777), Nombre y apellido del Director del proyecto (Texto de 40 caracteres máximo).

Por otra parte, se dispone del archivo docentesinvestigadores.dat con el siguiente diseño de registro: Nro. de matrícula (int 111111 - 777777), Nombre y apellido (Texto de 40 caracteres máximo), Cantidad de proyectos asociados (int, inicialmente se encuentra en cero).

Nota: Si un docente no se encuentra el proceso se debe realizar igualmente. No se debe contabilizar el proyecto a los directores, ni tampoco forman parte de la cantidad total de docentes investigadores.

Se solicita

Generar el proceso correspondiente para actualizar el campo Cantidad de proyectos asociados por cada docente del archivo docentesinvestigadores.dat

Generar el archivo directoreproyectos.dat con el siguiente diseño de registro: Nro. de matrícula | Nombre y apellido del director | Nombre del proyecto. (Nota: Como un docente puede oficiar de director en múltiples proyectos, el mismo se puede repetir en este archivo).

Generar el archivo resumenproyectos.dat con el siguiente diseño de registro: Cantidad total de proyectos | Cantidad total de docentes investigadores.*/