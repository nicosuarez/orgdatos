#include "MessageManager.h"
#include "EncriptationManager.h"
#include "CompressionManager.h"
MessageManager* MessageManager:: instance = NULL;
/* -------------------------------------------------------------------------- */

MessageManager::MessageManager(): orgMsg(PATH_MESSAGE_FILE, MsgRegistry::Create),
								  orgListImages(PATH_IMG_LIST_FILE, ListImgRegistry::Create),
								  treeMsg(512, KeyStrFactory(), ValueIntFactory(), PATH_TREE_MSG)
{

}
/* -------------------------------------------------------------------------- */

MessageManager* MessageManager::GetInstance()
{
	if(instance == NULL)
		instance = new MessageManager();
	return instance;
}
/* -------------------------------------------------------------------------- */

MessageManager::~MessageManager(){
	delete instance;

}
/* -------------------------------------------------------------------------- */

void MessageManager::Extract(Message msg,Message msgTarget){
	
	//Busco en el arbol el id del mensaje.
	ID_type idMsg;
	KeyStr key(msg.GetName());
	TreeIterator& itTree = this->treeMsg.iterator(key);
	if( itTree.end() )
	{
		perror( ERR_NOT_EXIST);
		return;
	}
	ValueInt* vInt=dynamic_cast<ValueInt*>(itTree.getValue());
	idMsg = vInt->getValue();
	delete vInt;
	
	ImgRegistry *imgRegistry = dynamic_cast<ImgRegistry*>(this->orgMsg.GetRegistry( idMsg));
	ID_type idFirstList = imgRegistry->GetPtrMsgList();
	
	//Obtengo la lista de espacios de las imagenes en donde esta oculto el mensaje
	std::list<ListRegistry*> *listSpacesImg = this->orgListImages.GetList(idFirstList);
	std::list<ListRegistry*>::iterator it;
	
	ListImgRegistry* listImgRegistry;
	Space *space;
	Image *image;
	ImageManager *imageManager = ImageManager::GetInstance();
	
	//Por cada elemento de la lista, instancio un Space, una imagen y extraigo la particion del mensaje
	for( it = listSpacesImg->begin(); it != listSpacesImg->end(); it++ )
	{
		listImgRegistry = dynamic_cast<ListImgRegistry*>(*it);
		ID_type idImg = listImgRegistry->GetIDImage();
		unsigned long offsetImg = listImgRegistry->GetOffsetImg();
		unsigned long sizePartitionMsg = listImgRegistry->GetSizePartitionMsg();
		const char *pathImg = imageManager->GetPathImage(idImg);
		space = new Space(pathImg, offsetImg, sizePartitionMsg);
		image = ImageFactory::GetImage(pathImg);
		image->Extract(space, &msgTarget);
		delete image;
		delete (*it);
	}
	delete listSpacesImg;
	Message m1=EncriptationManager::Decrypt(msg);
	CompressionManager::Decompress(m1,msgTarget);
	if( remove( m1.GetFilePath()) != 0 )
		perror( ERR_FILE_DELETE );
}
/* -------------------------------------------------------------------------- */

void MessageManager::Hide(Message msg,Message msgTarget){
	
	KeyStr k( msgTarget.GetName());
	if( !this->treeMsg.empty() )
		if( this->treeMsg.exists(k) )
		{
			perror( ERR_ALREADY_EXIST ); 
			return;	
		}
	
	try
	{
		//Comprimo el mensaje
		Message m1=CompressionManager::Compress(msg);
	
		//Obtengo la lista de espacios libres en donde voy a almacenar el mensaje
		FreeSpaceManager *freeSpaceManager = FreeSpaceManager::GetInstance();
		tListSpaces *spaces = freeSpaceManager->GetFreeSpaces(m1.GetSize());
		
		//Si la lista es NULL, no hay espacio disponible
		if( spaces == NULL )
		{
			perror( ERR_NOT_SPACE );
			return;
		}
		
		//Encripto el mensaje
		EncriptationManager::Encrypt(m1, msgTarget);
		
		
		ImageManager *imageManager = ImageManager::GetInstance();
		Space *space;
		Image *image;
		ID_type idImage, idFirstList;
		unsigned long sizeHidden = 0, sizeSpace;
		tListSpaces::iterator it = spaces->begin();
		
		while( it != spaces->end())
		{
			space = dynamic_cast<Space*>(*it);
			
			//Oculto el mensaje en el esapcio libre
			image = ImageFactory::GetImage( space->GetFilePath());
			image->Hide(space, &msgTarget);
			
			//Obtengo los datos para alamcenar el registro
			sizeSpace = space->GetSize();
			sizeHidden += sizeSpace;
			idImage = imageManager->GetIDImage(space->GetFilePath());
			
			//Si el space es el primero de la lista, debo crear una lista en la organizacion lista
			if( it == spaces->begin() )
			{
				ListImgRegistry regList( idImage, space->GetInitialPosition(), sizeSpace );
				this->orgListImages.CreateList(regList);
				idFirstList = regList.GetID();
				it++;
			}
			else 
			{
				it++;
				/*Verifico si el ultimo space de la lista fue ocupado por completo.
				 * Si no se ocupo por completo, calculo el espacio usado*/
				if( (it == spaces->end()) && (sizeHidden > msgTarget.GetSize()) )
				{
					sizeSpace = space->GetSize() - (sizeHidden - msgTarget.GetSize());
				}
				
				//Guardo el registro en la orgListImages
				ListImgRegistry regList( idImage, space->GetInitialPosition(), sizeSpace );
				this->orgListImages.AddToListLast(regList,idFirstList);
			}
			delete image;
		}
		
		//Guardo el registro en la orgMsg
		MsgRegistry regMsg(idFirstList);
		this->orgMsg.WriteRegistry(regMsg);
		
		//Guardo el registro en el arbol
		ValueInt v(regMsg.GetID());
		this->treeMsg.insert(k,v);
		
		//Actualizo la lista de mensajes que tiene cada registro en el archivo de imagenes
		std::list<ListRegistry*> *listImages = this->orgListImages.GetList( regMsg.GetPtrImgList());
		std::list<ListRegistry*>::iterator itListImg;
		for( itListImg=listImages->begin(); itListImg != listImages->end(); itListImg++ )
		{
			ListImgRegistry* reg = dynamic_cast<ListImgRegistry*>(*itListImg);
			imageManager->AddMessageToImage( idImage, reg->GetIDImage());
			delete reg;
			delete *itListImg;
		}
		delete listImages;
		
		//Elimino la lista de espacios libres para liberar memoria
		for(it = spaces->begin(); it != spaces->end(); it++)
		{
			delete *it;
		}
		delete spaces;
		
		//Elimino los archivos de mensajes
		if( remove( m1.GetFilePath()) != 0 )
				perror( "Error deleting file" );
		if( remove( msgTarget.GetFilePath()) != 0)
				perror( "Error deleting file" );
		if( remove( msg.GetFilePath()) != 0)
					perror( "Error deleting file" );
	}
	catch( eFile &e)
	{
		cout << e.what() << endl;
	}
	
}
/* -------------------------------------------------------------------------- */

void MessageManager::DeleteMessage(unsigned long messageId)
{

}
/* -------------------------------------------------------------------------- */

list<Space> MessageManager::GetFullSpaces(unsigned long messageId)
{
	list<Space> lista;
	return lista;
}
/* -------------------------------------------------------------------------- */
