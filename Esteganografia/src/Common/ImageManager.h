///////////////////////////////////////////////////////////
//  ImageManager.h
//  Implementation of the Class ImageManager
//  Created on:      13-Oct-2008 2:49:32 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#if !defined(EA_B58FBDCC_98EA_11dd_B49B_001B2425640C__INCLUDED_)
#define EA_B58FBDCC_98EA_11dd_B49B_001B2425640C__INCLUDED_

#include "CImg.h"
#include "../Steganographic/Image.h"
#include <list>

/**
 * Clase que se encarga de eliminar/agregar una imagen al ocultador.
 * Implementa el patron Singleton
 */
class ImageManager
{
public:

	/* Devuelve la unica instancia de ImageManager (clase singleton)*/
	static ImageManager* GetInstance();
	
	/* Elimina una imagen de la organizacion de archivos*/
	static void DeleteImage(Image* image);
	
	/* Almacena una imagen en la organizacion de archivos*/
	static void AddImage(Image* image);
	
	/* Devuelve una lista con los IDs de los mensajes que estan 
	 * ocultos en la imagen parámetro */
	list<int> GetMessages(Image* image);
	
	/* Devuelve una lista con los espacios libres que tiene 
	 * la imagen parámetro */
	list<Space> GetFreeSpaces(Image* image);
	
	/* Destructor*/
	virtual ~ImageManager();
	
private:
	
	/*Espacio libre total para almacenar mensajes*/
	static unsigned long freeTotalSize;

	/*Puntero a la unica instancia del ImageManager*/
	static ImageManager *instace;

	/*Constructor privado*/ 
	ImageManager();
	
	/*Constructor de copia y operador = privados para evitar errores*/
    ImageManager(const ImageManager &manager);
    ImageManager& operator=(const ImageManager &manager);

};
#endif // !defined(EA_B58FBDCC_98EA_11dd_B49B_001B2425640C__INCLUDED_)
