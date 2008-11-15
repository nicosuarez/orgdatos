///////////////////////////////////////////////////////////
//  ImageManager.h
//  Implementation of the Class ImageManager
//  Created on:      13-Oct-2008 2:49:32 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include "CImg.h"
#include "../Steganographic/Image.h"
#include <list>
#include "../DataAccess/Organizations/OrgExtensibleRelative.h"
#include "../DataAccess/Organizations/OrgList.h"
#include "../DataAccess/Organizations/OrgText.h"
#include "../DataAccess/Registries/ImgRegistry.h"
#include "../DataAccess/Registries/ListImgRegistry.h"
#include "../DataAccess/Registries/ListMsgRegistry.h"
#include "../DataAccess/Registries/ListFreeSpaceRegistry.h"
#include "Constant.h"

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
	
	/*Dado el tamaño de un mensaje, devuelve una lista de espacios 
	 * libres para almacenarlo*/
	list<Space> GetSpacesToStore(unsigned long sizeMsg);
	
	/*Devuelve el espacio libre total en toda la organizacion*/
	unsigned long GetTotalFreeSize() const;
	
	/* Destructor*/
	virtual ~ImageManager();
	
private:
	
	/*Espacio libre total para almacenar mensajes*/
	static unsigned long totalFreeSize;

	/*Puntero a la unica instancia del ImageManager*/
	static ImageManager *instance;

	OrgExtensibleRelative orgImages;
	OrgList orgListFreeSpaces, orgListMsgs;
	OrgText orgNamesImages, orgNamesDir;
	
	/*Constructor privado*/ 
	ImageManager();
	
	/*Constructor de copia y operador = privados para evitar errores*/
    ImageManager(const ImageManager &manager);
    ImageManager& operator=(const ImageManager &manager);

};
#endif /* IMAGEMANAGER_H */
