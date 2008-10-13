#include <iostream>
#include <cstdlib>
#include <vector>
#include "Lzss/lzss.h"

using namespace std;

void testCompresion()
{
	Lzss lz;
	string postaPosta="ciudado con la ca";// bombachita";/*"hhachaLa Papa, Ciudado con la petiza que te tiza cuak, esto en realidad es muuuy pelotudo de hacer ya que seria mejor cortar un texto de lanacion.com y despues pegarlo aca pasa que este año estoy muy boludo y ademas, esta bueno, esto de ir probrando un poco este texto de mierda y ver si el lzss realmente puede comprimir algo";*/
	string st=lz.compress(postaPosta.c_str());//,l);
	/*TEST*/
	const unsigned char* aux =(unsigned char*) st.c_str();
	cout<<"ESTE ES EL ARCHIVO COMPRIMIDO  ";
	for(unsigned int i=0;i<st.length();i++)
		cout<<(unsigned int)aux[i]<<" ";
	cout<<endl;
	/*ESTO LO DEBE HACER AL LEER EL ARCHIVO*/
	string descomprimir;
	unsigned char* aux2=(unsigned char*)st.c_str();
	for(unsigned int i=0;i<(unsigned int)aux2[0];i++)
		descomprimir.append(1,aux2[i+1]);
	/*FIN DE ESTO*/
	string ans=lz.uncompress((unsigned char*)descomprimir.c_str(),st.size());
	
	const char * a=ans.c_str();
	cout<<"la verdadera resp deberia ser:  "<<postaPosta<<endl<<endl;
	cout<<"LA RESPUESTA ES: TA TAN TA TAN...  "<<a<<endl;
}

int main(int argc, char *argv[])
{
	testCompresion();
	return EXIT_SUCCESS;
}

