/* Clase StrToken
* Descripcion:
* Clase encargada de realizar el parseo de cadenas por tokens
*/

/* Metodos principales
* tVecStr getStrTokens():Restorna un vector de cadenas,partiendo la cadena 
* pasada dividida por el delimitador.
*
* bool stringTo()<Tipo>: parsea una cadena al tipo del template.
*
* void setTokensParams():Carga los parametros pasados, con los valores del
* vector de string dependiendo del formato.
* ej: setTokensParams(getStrTokens("1;Pablo;Perez;20;M", ";"),"*ssic",
&nombre,&apellido,&edad,&sexo)

Formato: (*)ignora el valor del string.
(s)valor tipo string.
(i)valor tipo entero.
(c)valor tipo caracter.

resultado: nombre="Pablo"
apellido="Perez"
edad=20
sexo='M'
*/

#ifndef __STR_TOKEN_H__
#define __STR_TOKEN_H__

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <stdarg.h>

using std::string;
using std::vector;

typedef std::vector<std::string> tVecStr;

class StrToken
{
public:
    //Metodos
    static tVecStr getStrTokens(string cadena,string delimeter,bool ignoreSpaces=true);
    template <class Type> 
    static bool stringTo(Type& tipo,const std::string& s);
    static void setTokensParams(tVecStr strTok,char *formato,...);
    static void toUpperString(std::string& str);
    static void toLowerString(std::string& str);
    static string intToString( int entero );
    static void Trim(std::string& str);
};

#endif

