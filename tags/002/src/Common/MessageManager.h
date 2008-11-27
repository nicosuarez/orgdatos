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
#include "Exception/eNotExist.h"
#include "Exception/eExist.h"
#include "../Steganographic/ImageFactory.h"
#include "../DataAccess/Organizations/OrgExtensibleRelative.h"
#include "../DataAccess/Organizations/OrgList.h"
#include "../DataAccess/Organizations/OrgText.h"
#include "../DataAccess/Registries/MsgRegistry.h"
#include "../DataAccess/Registries/ListImgRegistry.h"
#include "../DataAccess/Registries/ListFreeSpaceRegistry.h"
#include "../Tree/BppTree/bpptree.h"
#include "../Tree/factory.h"
#include "../Tree/BppTree/treeIterator.h"
#include "Resource.h"

typedef std::list<Space*> tListSpaces;
typedef std::list<Space*>::iterator itListSpaces;
typedef std::vector< Space* > tVecFreeSpace;

/**
 * Clase que maneja el comportamiento de los mensajes, ocultandolos y extrayendolos
 */
class MessageManager
{

public:

	/*Devuelve la unica instancia de MessageManager (clase singleton)*/
	static MessageManager* GetInstance();

	/*Extrae el mensaje oculto y lo devuelve como un nuevo mensaje*/
	void Extract(std::string nameMsg, std::string pathMsg, Message msgTar=Message(PATH_TARGET_DESCOMPRESS_CM));

	/*Oculta un mensaje*/
	void Hide(Message msg,Message msgTar=Message(PATH_TARGET_ENCRYPT_EM));

	/*Elimina un mensaje oculto*/
	void DeleteMessage(ID_type idMsg, bool addFreeSpace, tVecStr* imgErasedList=NULL);
	
	void DeleteMessage(std::string nameMessage, bool addFreeSpace, tVecStr* imgErasedList=NULL);
	
	void DeleteMessages(list<ID_type> *listImg);

	void ShowMessage();

	/*Destructor*/
	virtual ~MessageManager();

private:

	/*Puntero a la unica instancia del MessageManager*/
	static MessageManager* instance;

	OrgExtensibleRelative orgMsg;
	OrgList orgListImages;
	OrgText orgNames;

	/*Arbol de Mensajes*/
	BppTree treeMsg;

	/*Constructor privado*/
	MessageManager();

	ID_type HideMessage(tListSpaces *spaces, Message &msgTarget);
	
	void UpdateListMessage(MsgRegistry &regMsg);
	
	void ExtractMessage(ID_type idFirstList, Message &msgTarget);
	
	void AddFreeSpaces(tRegisterList *listImg);
	
	tRegisterList* FilterErasedImages(tRegisterList* imgList,tVecStr* imgErasedList);
	
	/*Constructor de copia y operador = privados para evitar errores*/
    MessageManager(const MessageManager &manager);
    MessageManager& operator=(const MessageManager &manager);
};
#endif // __MESSAGEMANAGER_H__
