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
#include <string>
#include "../DataAccess/Organizations/OrgExtensibleRelative.h"
#include "../DataAccess/Organizations/OrgList.h"
#include "../DataAccess/Organizations/OrgText.h"
#include "../DataAccess/Registries/ImgRegistry.h"
#include "../DataAccess/Registries/ListImgRegistry.h"
#include "../DataAccess/Registries/ListMsgRegistry.h"
#include "Constant.h"
#include "../Tree/factory.h"
#include "../Tree/BppTree/bpptree.h"
#include "FileSystem.h"
#include "FreeSpaceManager.h"
#include "MessageManager.h"
#include "../Steganographic/ImageFactory.h"

typedef enum IMMode {Erased=0 , Added=1 } IMMode;
typedef std::pair<tVecStr*,tVecStr*> pListUpdate;
/**
 * Clase que se encarga de eliminar/agregar una imagen al ocultador.
 * Implementa el patron Singleton
 */
class ImageManager
{

	public:

	/* Actualiza las imagenes nuevas y viejas */	
	pListUpdate UpdateImages();
		
	/* Devuelve la unica instancia de ImageManager (clase singleton)*/
	static ImageManager* GetInstance();

	/* Devuelve el path de la imagen */
	std::string GetPathImage(ID_type idImg);

	/**
	 * Cargar el imgtree y el dirTree con todos los subdirectorios
	 * y los archivos aceptados por el programa
	 */
	tVecStr	AddDirectory(const char* dirPath);

	/**
	 * da de baja en el imgtree y el dirTree de todos los subdirectorios
	 * y los archivos aceptados por el programa
	 */
	tVecStr DeleteDirectory(const char* dirPath);

	/* Elimina una imagen de la organizacion de archivos*/
	void DeleteImage(std::string path, tVecStr* imgErasedList=NULL,bool filterAll=false);

	/* Almacena una imagen en la organizacion de archivos*/
	ID_type AddImage(const char* imagePath);

	/* Devuelve una lista con los IDs de los mensajes que estan
	 * ocultos en la imagen parámetro */
	list<int> GetMessages(Image* image);

	/* Devuelve una lista con los espacios libres que tiene
	 * la imagen parámetro */
	list<Space> GetFreeSpaces(Image* image);

	/*Dado el tamaño de un mensaje, devuelve una lista de espacios
	 * libres para almacenarlo*/
	list<Space> GetSpacesToStore(unsigned long sizeMsg);

	/**
	 * Devuelve el IdImage del archivo pasado como parametro
	 * Devuelve 0 si no existe ese path en el imgTree
	 */
	ID_type GetIDImage(const char* path);

	/*Devuelve el espacio libre total en toda la organizacion*/
	unsigned long GetTotalFreeSize() const;

	/*
	 *  Returns a list of image files stored in the BppTree that
	 *  have been recently removed from a specific directory.
	 *
	 *  path: path of the directory, without '/' as the last character.
	 */
	tVecStr GetImageErasedList ( const std::string & path );

	/*
	 *  Returns a list of image files stored in the BppTree that
	 *  have been recently removed from all the directories.
	 */
	tVecStr GetImageErasedFromDirectories();

	/* Agrega un mensaje a la imagen */
	void AddMessageToImage( ID_type idImage, ID_type idMessage);

	/* Obtiene un registro imagen */
	ImgRegistry* GetImageRegistry( ID_type idImage);

	/* Actualiza un registro imagen */
	void UpdateImageRegistry(ImgRegistry* modifiedImgReg);

	/* Destructor*/
	virtual ~ImageManager();

	void RecorreElArbol();

	void RecorreElArbolDir();

	void TestDirectory(const char* dirPath);
	
	unsigned int GetBitsLsb(const char* filePath);

	/*
	* devuelve la lista de todos los directorios
	*/
	tVecStr GetAllDirectories();

	/*
	 * Devuelve una lista de imagenes borradas o nuevas de
	 * los directorios.
	 */
	tVecStr* GetUpdatedList( IMMode );
	
	/**
	 * Elimina el mensaje de la imagen.
	 */
	void RemoveMessageToImage( ID_type idImage, ID_type idMessage);

private:
	//Borra la imagen y sus mensajes
	void DeleteImage(ID_type id, tVecStr* imgErasedList=NULL, bool filterAll=false);

	//Le quita al string lo que la identica como directorio
	void TransformKeyImgToKeyDir(std::string& str);

	//devuelve true si el unknow es un archivo dentro del directorio o una subcarpeta dentro del mismo
	bool isSubDirectoryOrSubFile(tVecStr* dir,tVecStr* unknow);

	/*Espacio libre total para almacenar mensajes*/
	static unsigned long totalFreeSize;

	/*Puntero a la unica instancia del ImageManager*/
	static ImageManager *instance;

	OrgExtensibleRelative orgImages;
	OrgList orgListMsgs;
	OrgText orgNamesImages;//, orgNamesDir;

	BppTree imgTree;
	BppTree dirTree;
	/*Constructor privado*/
	ImageManager();

	/*Constructor de copia y operador = privados para evitar errores*/
    ImageManager(const ImageManager &manager);
    ImageManager& operator=(const ImageManager &manager);

    /*
	 * Devuelve una lista con las imagenes que no figuran
	 * en 2 Trees (compara solo por nombre).
	 */
	tVecStr GetMergedList( BppTree & , BppTree &);

	/*
	 * Filtra la lista obtenida por GetMergedList por date
	 */
	tVecStr filterByDate ( tVecStr list , BppTree & tree );

};
#endif /* IMAGEMANAGER_H */
