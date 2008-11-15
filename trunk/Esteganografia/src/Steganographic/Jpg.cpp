///////////////////////////////////////////////////////////
//  Jpg.cpp
//  Implementation of the Class Jpg
//  Created on:      13-Oct-2008 2:49:34 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#include "Jpg.h"

using namespace std;

Jpg::Jpg(const char* filePath){
	this->filePath = filePath;
}
/* -------------------------------------------------------------------------- */

Jpg::~Jpg(){

}
/* -------------------------------------------------------------------------- */

/**
 * Implementar el comportamiento para extraer la informacion en un lugar
 * determinado.
 */
void Jpg::Extract(Space* space, Message* msg)
{
	long spaceSize = space->GetSize(); 
	ifstream fin(space->GetFilePath(), ios::in | ios::binary);
	ofstream fdata(msg->GetFilePath(), ios::out | ios::app);
	long extractBytes = 0;
	UBYTE dataByte;

	fin.seekg(space->GetInitialPosition());
	
	while(extractBytes < spaceSize)
	{
		fin.read(&dataByte,sizeof(UBYTE));
		fdata.write(&dataByte,sizeof(UBYTE));
		extractBytes ++;
	}
	
	fin.close();
	fdata.close();
}
/* -------------------------------------------------------------------------- */

/**
 * Implementa el comportamiento para ocultar unn mensaje en el espacio indicado
 * por el parametro space.
 */
void Jpg::Hide(Space* space, Message* msg)
{
	long spaceSize = space->GetSize(); 
	fstream fin(space->GetFilePath(), ios::in | ios::out | ios::binary);
	ifstream fdata(msg->GetFilePath(),ios::in | ios::binary);
	UBYTE dataByte;
	long hideBytes = -1;
	
	fdata.seekg(msg->GetHiddenSize());
	fin.seekp(space->GetInitialPosition());
	
	while(!fdata.eof() && (hideBytes < spaceSize))
	{
		fdata.read(&dataByte,sizeof(UBYTE));
		fin.write(&dataByte,sizeof(UBYTE));
		hideBytes++;
	}
	msg->IncHiddenSize(hideBytes);
	
	fin.close();
	fdata.close();
}
/* -------------------------------------------------------------------------- */

bool Jpg::ValidateFormat(const char *filePath)
{
	
	fstream fin(filePath);
	fin.seekg(6);
	string format;
	string header(JpgFileType);
	bool isValid = false;
    
	if(fin.good())
	{
		fin >> format;
		cout << format << "\n";
		cout << header << "\n";
		if(format.compare(0,4,header) == 0)
		{
			cout << "Formato JPG/JPEG Correcto.\n";
			isValid = true;
		}
		fin.close();
	}
	else
	{
		cerr << ERR_FILE_OPEN << filePath <<"\n";
	}
	return isValid;
}
/* -------------------------------------------------------------------------- */
int Jpg::GetQualityForMinSizeCompressionFound(tVecLong imageSizeList,
												tVecLong imageQualityList)
{
	int posMin = -1;
	if(!imageSizeList.empty())
	{
		long min = imageSizeList[0];
		int posMin = 0;
		for(size_t i=0; i<imageSizeList.size(); i++)
		{
			if(imageSizeList[i] < min)
			{
				min=imageSizeList[i];
				posMin=i;
			}
		}
		return imageQualityList[posMin];
	}
	
	return posMin;
}
/* -------------------------------------------------------------------------- */
int Jpg::SearchBestCompression(){
	
	tVecLong imageSizeList;
	tVecLong imageQualityList;
	double sizeOrig = this->GetTotalSize();
	double sizeComp = 0;
	double compressionPct = 0;
	
	for(int quality=0; quality <=90; quality+=20)
	{
		sizeComp = this->CompressImage(quality, PATH_COMPRESS_IMAGE_TEMP);
		compressionPct = (sizeComp / sizeOrig)*100;
		if((compressionPct >= CompressionPercentage) && (compressionPct < 100))
		{
			imageSizeList.push_back(sizeComp);
			imageQualityList.push_back(quality);
		}
	}
	
	if( remove(PATH_COMPRESS_IMAGE_TEMP) != 0 )
		perror( "Error deleting file" );
	
	return GetQualityForMinSizeCompressionFound(imageSizeList, imageQualityList);
}
/* -------------------------------------------------------------------------- */
Space* Jpg::Load()
{
	long sizeComp=0, freeSpace=0;
	Space *space;
	long sizeOrig = this->GetTotalSize();

	//Se busca la mejor compresion.
	int quality = SearchBestCompression();
	
	//Si se puede comprimir.
	if(quality != -1)
	{
		sizeComp = this->CompressImage(quality, this->GetFilePath());
		freeSpace = sizeOrig - sizeComp;
		this->spaceTotal = freeSpace;
		this->freeSpaceTotal = freeSpace;	
		this->FillImage(freeSpace);
		this->SetInitPosFreeSpace(sizeComp);
		space = new Space(this->filePath, JpgFileType, sizeComp, spaceTotal);
	}
	else
	{
		std::cout << "La imagen no se puede comprimir mas.\n";
	}
	return space;
}
/* -------------------------------------------------------------------------- */
void Jpg::FillImage(long freeSpace)
{
	ofstream fout(this->GetFilePath(), ios::out | ios::binary | ios::app);
	srand( (unsigned int) time(NULL));
	while(freeSpace)
	{
		char rdmChar = (rand() % 26) + 'a';
		fout.write(&rdmChar,sizeof(UBYTE));
		freeSpace--;
	}
	fout.close();
}
/* -------------------------------------------------------------------------- */
long Jpg::CompressImage(int quality, const char* outFile)
{
	Jpg jpg(outFile);
	long sizeOrig = this->GetTotalSize();
	cout << "Load Path: "<< this->GetFilePath() << " SizeOrig: " << sizeOrig << "\n";
	cimg_library::CImg<unsigned char> image(this->GetFilePath());
	image.save_jpeg(outFile, quality);
	cout << "Se comprime: "<< this->GetFilePath() << ", en un factor de " << quality <<  "\n";
	long sizeComp = jpg.GetTotalSize();
	cout << "Load Path: "<< jpg.GetTotalSize() << " SizeComp: " << sizeComp << "\n";
	return sizeComp;
}
/* -------------------------------------------------------------------------- */

