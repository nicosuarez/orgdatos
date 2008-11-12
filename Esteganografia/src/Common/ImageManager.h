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

/**
 * Clase que se encarga de eliminar/agregar una imagen al ocultador.
 */
class ImageManager
{
private:
	static unsigned long freeTotalSize;
public:
	ImageManager();
	virtual ~ImageManager();

	static void DeleteImage(Image* image);
	static void AddImage(Image* image);

};
#endif // !defined(EA_B58FBDCC_98EA_11dd_B49B_001B2425640C__INCLUDED_)
