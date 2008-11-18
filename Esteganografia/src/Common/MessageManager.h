#ifndef __MESSAGEMANAGER_H__
#define __MESSAGEMANAGER_H__

#include <list>
#include "Message.h"
#include "Space.h"
#include "EncriptationManager.h"
#include "CompressionManager.h"
#include "ImageManager.h"
#include "FreeSpaceManager.h"
#include "Constant.h"
#include "StrToken.h"
#include "Exception/eFile.h"
#include "../Steganographic/ImageFactory.h"
#include "../DataAccess/Organizations/OrgExtensibleRelative.h"
#include "../DataAccess/Organizations/OrgList.h"
#include "../DataAccess/Registries/MsgRegistry.h"
#include "../DataAccess/Registries/ListImgRegistry.h"
#include "../DataAccess/Registries/ListFreeSpaceRegistry.h"
#include "../Tree/BppTree/bpptree.h"
#include "../Tree/factory.h"

/**
 * Clase que maneja el comportamiento de los mensajes, ocultandolos y extrayendolos
 */
class MessageManager
{

public:

	/*Devuelve la unica instancia de MessageManager (clase singleton)*/
	static MessageManager* GetInstance();

	/*Extrae el mensaje oculto y lo devuelve como un nuevo mensaje*/
	void Extract(Message msg,Message msgTar=Message(PATH_TARGET_DESCOMPRESS_CM));

	/*Oculta un mensaje*/
	void Hide(Message msg,Message msgTar=Message(PATH_TARGET_ENCRYPT_EM));

	/*Elimina un mensaje oculto*/
	void DeleteMessage(unsigned long messageId);

	/*Devuelve una lista con los distintos espacios en los
	 * cuales el mensaje esta oculto */
	list<Space> GetFullSpaces(unsigned long messageId);

	/*Destructor*/
	virtual ~MessageManager();

private:

	/*Puntero a la unica instancia del MessageManager*/
	static MessageManager* instance;

	OrgExtensibleRelative orgMsg;
	OrgList orgListImages;

	/*Arbol de Mensajes*/
	BppTree treeMsg;
	
	/*Constructor privado*/
	MessageManager();

	/*Constructor de copia y operador = privados para evitar errores*/
    MessageManager(const MessageManager &manager);
    MessageManager& operator=(const MessageManager &manager);
};
#endif // __MESSAGEMANAGER_H__
