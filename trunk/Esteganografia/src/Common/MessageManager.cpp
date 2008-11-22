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

bool MessageManager::Extract(Message msg,Message msgTarget){

	//Busco en el arbol el id del mensaje.
	if( this->treeMsg.empty() )
	{
		//std::cout << ERR_MSG_NOT_EXIST << std::endl;
		return false;
	}
	ID_type idMsg;
	KeyStr key(msg.GetName());
	if(!treeMsg.exists(key)){
		//cout <<ERR_MSG_NOT_EXIST;
		return false;
	}
	TreeIterator& itTree = this->treeMsg.iterator(key);
	if( itTree.end() )
	{
		//perror( ERR_MSG_NOT_EXIST);
		return false;
	}
	std::cout << PROCESS_COMMAND;
	ValueInt* vInt=dynamic_cast<ValueInt*>(itTree.getValue());
	idMsg = vInt->getValue();
	delete vInt;

	MsgRegistry *msgRegistry = dynamic_cast<MsgRegistry*>(this->orgMsg.GetRegistry( idMsg));
	if( msgRegistry == NULL)
	{
		//cout << "ERROR, NO SE PUDO LEVANTAR EL REGISTRO" << endl;
		return false;
	}
	ID_type idFirstList = msgRegistry->GetPtrImgList();

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
		string pathImg = imageManager->GetPathImage(idImg);
		space = new Space(pathImg, offsetImg, sizePartitionMsg);
		image = ImageFactory::GetImage(pathImg.c_str());
		image->Extract(space, &msgTarget);
//		cout<<"listaaaaa"<<endl<<idImg<<"  "<<offsetImg<<"  "<<sizePartitionMsg<<"  "<<sizePartitionMsg<<endl;
		delete image;
		delete (*it);
	}
	delete listSpacesImg;
	Message m1=EncriptationManager::Decrypt(msgTarget);
	CompressionManager::Decompress(m1,msg);
	m1.Delete();
	msgTarget.Delete();
	return true;
}
/* -------------------------------------------------------------------------- */

void MessageManager::Hide(Message msg,Message msgTarget){

	KeyStr k( msg.GetName());
	if( !this->treeMsg.empty() )
		if( this->treeMsg.exists(k) )
		{
			std::cout <<  ERR_ALREADY_EXIST;
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
			std::cout <<  ERR_NOT_SPACE;
			return;
		}
		
		std::cout << PROCESS_COMMAND;
		
		//Encripto el mensaje
		EncriptationManager::Encrypt(m1, msgTarget);


		ImageManager *imageManager = ImageManager::GetInstance();
		Space *space;
		Image *image;
		ID_type idImage=0, idFirstList=0;
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
				ListImgRegistry regList( idImage, space->GetInitialPosition(), msgTarget.GetHiddenSize() );
				this->orgListImages.CreateList(regList);
				idFirstList = regList.GetID();
				it++;
			}
			else
			{

				/*Verifico si el ultimo space de la lista fue ocupado por completo.
				 * Si no se ocupo por completo, calculo el espacio usado*/
				it++;
				if( (it == spaces->end()) && (sizeHidden > msgTarget.GetSize()) )
				{
					sizeSpace = space->GetSize() - (sizeHidden - msgTarget.GetSize());
				}

				//Guardo el registro en la orgListImages
				ListImgRegistry regList( idImage, space->GetInitialPosition(), sizeSpace );
				this->orgListImages.AddToListLast(regList,idFirstList);
			}
			//it++;
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
			imageManager->AddMessageToImage( reg->GetIDImage(), regMsg.GetID());
			delete reg;
		}


		delete listImages;

		//Elimino la lista de espacios libres para liberar memoria
		for(it = spaces->begin(); it != spaces->end(); it++)
		{
			delete *it;
		}
		delete spaces;

		//Elimino los archivos de mensajes
		m1.Delete();
		msgTarget.Delete();
		std::cout << MSG_HIDE_SUCCESS;
		msg.Delete();
	}
	catch( eFile &e)
	{
		cout << e.what() << endl;
	}
//	cout << this->treeMsg;
}
/* -------------------------------------------------------------------------- */

void MessageManager::DeleteMessage(std::string nameMessage)
{
	KeyStr k(nameMessage);
	ValueInt *regTree = dynamic_cast<ValueInt*>(treeMsg.find(k));
	if( regTree == NULL )
	{
		std::cout << ERR_MSG_NOT_EXIST << ": " << nameMessage << std::endl;
		return;
	}
	ID_type messageId = regTree->getValue();
	delete regTree;
	MsgRegistry *msgRegistry = dynamic_cast<MsgRegistry*>(orgMsg.GetRegistry(messageId));
	if( msgRegistry == NULL )
	{
		std::cout << ERR_MSG_NOT_EXIST << ": " << messageId << std::endl;
		return;
	}
	//obtengo la lista de imagenes
	ID_type idFirstList = msgRegistry->GetPtrImgList();
	std::list<ListRegistry*> *listImg = orgListImages.GetList(idFirstList);
	std::list<ListRegistry*>::iterator it;
	ListImgRegistry* listImgRegistry;
	tListSpaces* listSpaces = new tListSpaces;
	for( it=listImg->begin(); it != listImg->end(); it++)
	{
		listImgRegistry = dynamic_cast<ListImgRegistry*>(*it);
		ID_type idImg = listImgRegistry->GetIDImage();
		unsigned long offsetImg = listImgRegistry->GetOffsetImg();
		unsigned long size = listImgRegistry->GetSizePartitionMsg();
		listSpaces->push_back(new Space(idImg, offsetImg, size));
		delete (*it);
	}
	//Elimino los registros
	orgListImages.DeleteList(idFirstList);
	orgMsg.DeleteRegistry(messageId);
	treeMsg.remove(k);
//	cout << treeMsg << endl;
	//Doy de alta los nuevos espacios libres
	FreeSpaceManager::GetInstance()->AddFreeSpaces(listSpaces);

	delete msgRegistry;
	delete listImg;
}
/* -------------------------------------------------------------------------- */

list<Space> MessageManager::GetFullSpaces(unsigned long messageId)
{
	list<Space> lista;
	return lista;
}
/* -------------------------------------------------------------------------- */

void MessageManager::ShowMessage()
{
	int hiddenSize = 0;
	if(treeMsg.empty())
	{
		std::cout << std::endl << ERR_MSG_EMPTY;
		return;
	}
	TreeIterator &it = treeMsg.first();
	
	std::cout << std::endl; 
	while( !it.end() )
	{
		std::pair<Register*,Register*>keyval= *it;
		KeyStr* key = dynamic_cast<KeyStr*>(keyval.first);
		std::cout << CIRCLE << " " << key->getKey() << std::endl;
		delete key;
		++it;
		hiddenSize++;
	}
	std::cout << std::endl;
	std::cout << LBL_HIDDEN_MSG_SIZE << hiddenSize << std::endl;
	treeMsg.deleteIterator(it);
}
