Introducción :
==============

DataSafe es un programa esteganografico capaz de ocultar datos en diversos 
tipos de imágenes, sin cambios perceptibles al ojo humano.

La versión actual de datasafe es 1.0

Características:
*) compresión de datos ocultos
*) encriptación de los datos ocultos
*) interfaz de usuario sencilla e intuitiva
*) soporta archivos JPEG, BMP, PNG y GIF

Esteganografía :
===============

Esteganografía significa literalmente escritura cubierta u oculta. Su 
objetivo es ocultar el hecho de que una comunicación se está llevando
a cabo. Esto se realiza generalmente mediante el uso de un archivo
(bastante grande) en donde un mensaje secreto (más corto) es ocultado.
Como resultado se tiene un archivo inocuo que contiene el mensaje secreto.


Compilación e instalación :
==============================

Dependencias :
--------------
Librerías que se deben tener instaladas para el correcto uso de DataSafe.	

* cImg 
  Librería en C++ que proporciona herramientas en forma de clases y métodos
  que permiten la manipulación de distintos formatos de imágenes, mediante
  código C++.
  Disponible en: http://cimg.sourceforge.net/

* ImageMagick
  Librería que permite la manipulación de varios formatos de imágenes
  (JPEG, TIFF, PhotoCD, PBM, XPM, etc...) dando ademas, la posibilidad
  de poder aplicar efectos sobre las imágnes.
  Disponible en: http://www.imagemagick.org/script/index.php

* readline-dev o libreadline5-dev
  Librería GNU que proporciona una interfaz de usuario para recordar 
  las líneas de entrada previamente escritas.
  Disponible en: http://cnswww.cns.cwru.edu/php/chet/readline/rltop.html

* libpng12-dev
  libpng es una librería que implementa una interfaz para lectura y 
  escritura de archivos PNG (Portable Network Graphics).
  Disponible en: http://www.libpng.org/pub/png/libpng.html
  
Nota:
En el caso de utilizar plataforma Ubuntu, las librerías se pueden instalar 
desde repositorio.
Se pueden instalar las librerias desde la carpeta Libraries.

Linux / Unix :
--------------
Finalizada la descompresión del código fuente, introduzca los siguientes 
comandos:

1) Desde consola entrar al directorio DataSafe_Installer
2) Ejecutar ./install
3) Si las librerias estan bien instaladas, se tuvo que haber generado la 
   carpeta DataSafe
4) Para correr el programa hay que ejecutar dentro del directorio DataSafe
   ./DataSafe.

Olvido de Password: En el caso de que se haya olvidado el password la unica 
forma de volver acceder al sistema es eliminado la carpeta Files o
reinstalandolo. Obviamente por seguridad no se podra recuperar los datos 
almacenados.

Si alguno de los comandos falla, por favor envie un mail describiendo en
problema a algunos de los mails que aparecen al final.

Contactos : GRUPO 1
=========
Email Grupo 		grupo-datos@googlegroups.com
Sebastian Camjayi 	scamjayi@gmail.com
Leandro Oscar Mencias   leandromencias@gmail.com
Nicolas Suarez		nicolas.suarez@gmail.com
Diego Malchinsky	malcha@gmail.com
Nicolas Ige		igenico@gmail.com
