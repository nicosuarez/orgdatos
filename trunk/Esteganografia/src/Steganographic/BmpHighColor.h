///////////////////////////////////////////////////////////
//  BmpHighColor.h
//  Implementation of the Class BmpHighColor
//  Created on:      17-Oct-2008 3:48:09 PM
//  Original author: zebas
///////////////////////////////////////////////////////////

#if !defined(EA_24C1EC30_9C7C_11dd_B49B_001B2425640C__INCLUDED_)
#define EA_24C1EC30_9C7C_11dd_B49B_001B2425640C__INCLUDED_

#include "Bmp.h"

/**
 * Para los bmp con profundidad de color alta como por ej, 24 bits, se utiliza LSB
 * de 2 bits.
 */
class BmpHighColor : public Bmp
{
private:
	static const unsigned int BitsLsb = 2;
	
public:
	BmpHighColor(const char* filePath);
	virtual ~BmpHighColor();

	virtual long LsbExtract(fstream& fin, fstream& fdata);
	virtual void LsbHide(UBYTE dataByte,fstream& fin);
	
	/* Cantidad de informacion (bits) que se pueden ocultar por cada bytes 
	 * de la imagen */
	unsigned int GetBitsLsb() const{
		return BitsLsb;
	}
};
#endif // !defined(EA_24C1EC30_9C7C_11dd_B49B_001B2425640C__INCLUDED_)
