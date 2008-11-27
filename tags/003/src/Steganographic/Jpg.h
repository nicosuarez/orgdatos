///////////////////////////////////////////////////////////
//  Jpg.h
//  Implementation of the Class Jpg
//  Created on:      13-Oct-2008 2:49:33 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#if !defined(EA_B637FB36_98EA_11dd_B49B_001B2425640C__INCLUDED_)
#define EA_B637FB36_98EA_11dd_B49B_001B2425640C__INCLUDED_

#include "Image.h"
#include "../Common/CImg.h"
#include "../Common/Constant.h"
#include <vector>
#include <stdlib.h>
#include <time.h>

using std::fstream;
using std::ifstream;
using std::ofstream;
using std::ios;

typedef  std::vector<long> tVecLong;

#define JpgFileType "JFIF"

/**
 * Formato comprimido jpg,jpge
 */
class Jpg : public Image
{

public:
	Jpg(const char* filePath);
	virtual ~Jpg();

	static bool ValidateFormat(const char *filePath);
	virtual void Extract(Space* space, Message* msg);
	virtual void Hide(Space* space, Message* msg);
	Space* Load();
	
	long GetInitPosFreeSpace() const{
		return initPosFreeSpace;
	}
	
	void SetInitPosFreeSpace(long position){
		this->initPosFreeSpace = position;
	}
	
	//Relleno la imagen para mantener el tamano original.
	void FillImage(long freeSpace);
	
	//Comprime la imagen.
	long CompressImage(int quality, const char* outFile);
	
	//Obtiene la mejor calidad con la que hay que comprimir la imagen.
	int GetQualityForMinSizeCompressionFound(tVecLong imageSizeList,
												tVecLong imageQualityList);
	
private:
	long initPosFreeSpace;
	int SearchBestCompression();
	static const double CompressionPercentage = 30;

};
#endif // !defined(EA_B637FB36_98EA_11dd_B49B_001B2425640C__INCLUDED_)
