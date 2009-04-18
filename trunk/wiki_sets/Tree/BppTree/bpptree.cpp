#include "bpptree.h"
#include "leaf_register.h"
#include "level_register.h"
#include "bppIterator.h"
#include "control_register.h"

std::ostream& operator <<(std::ostream& out,BppTree& tree){

	Node* node = tree.manager.readNode(BppTree::OFFSET_ROOT);
	std::queue<unsigned int> offsets;
	out << "*------Comienzo Arbol B+----------*\n";
	node->toOstream(out,offsets);
	while(!offsets.empty()){
		unsigned int off = offsets.front();
		offsets.pop();
		if(off!=NodeManager::NO_OFFSET){
			Node* temp = tree.manager.readNode(off);
			temp->toOstream(out,offsets); /* suma al queue offsets */
			delete temp;
		}
	}
	out << "*------Fin Arbol B+----------*\n";
	delete node;
	return out;
}

BppTree::BppTree(unsigned int nodeSize,const RegisterFactory& keyFactory,const RegisterFactory& valFactory,const std::string& nodesFilename) :
manager(nodesFilename,nodeSize,keyFactory,valFactory){
	this->root = manager.readNode(OFFSET_ROOT);
}

BppTree::~BppTree(){
	/* No hace falta escribirlo ya que la raiz siempre se mantiene
       actualizada en disco<->memoria */
	delete this->root;

	while(!iterators.empty()){
		TreeIterator* toDelete = *this->iterators.begin();
		delete toDelete;
		this->iterators.erase(this->iterators.begin());
	}
}

bool BppTree::empty(){
	if(!this->root)
		return true;

	if(!this->root->getRegisterCount())
		return true;

	return false;
}

bool BppTree::exists(const Register& key){
	if(this->empty())
		return false;
	TreeIterator& it = this->iterator(key);
	// si !a<b y !b<a => b=a
	bool ret = ( !(it.peekKey()<key) && !(key<it.peekKey()) );
	this->deleteIterator(it);
	return ret;
}

Register* BppTree::find(const Register& key){
	if(this->empty())
			return NULL;
	LevelRegister lr(ControlRegister(key,-1,0),NodeManager::NO_OFFSET);
	return nodeFind(NULL,lr);
}

Register* BppTree::nodeFind(Node* root,NodeRegister& key){
	Register* ret = NULL;

	if(!root)
		root = this->root;

	if(root->getLevel()==Node::LEAF_LEVEL){
		std::pair<bool,Node::Registers::iterator> p = root->search(key);
		if(p.first)
			ret = dynamic_cast<ControlRegister&>(static_cast<LeafRegister*>((*p.second))->getValue()).getRegister().duplicate();
	}else{
		unsigned int offset = dynamic_cast<LevelNode*>(root)->getSubTree(key);
		Node* node =  manager.readNode(offset);
		ret = nodeFind(node,key);
		delete node;
	}
	return ret;
}

TreeIterator& BppTree::iterator(const Register& key){
	LevelRegister lr(ControlRegister(key,-1,0),NodeManager::NO_OFFSET);
	TreeIterator* it = getNodeIterator(NULL,lr);
	iterators.insert(it);
	return *it;
}

TreeIterator& BppTree::last(){
	TreeIterator* it = getLastNodeIterator(NULL);
	iterators.insert(it);
	return *it;
}

TreeIterator& BppTree::first(){
	TreeIterator* it = getFirstNodeIterator(NULL);
	iterators.insert(it);
	return *it;
}

TreeIterator* BppTree::getFirstNodeIterator(Node* root){
	if(!root)
		root = this->root;

	if(root->getLevel()==Node::LEAF_LEVEL){
		return new BppIterator(root->getOffset(),root->getFirst(),this->manager);
	}


	Node* node = manager.readNode(dynamic_cast<LevelNode*>(root)->getLeftChild());
	TreeIterator* ret = getFirstNodeIterator(node);
	delete node;
	return ret;
}

TreeIterator* BppTree::getLastNodeIterator(Node* root){
	if(!root)
		root = this->root;

	if(root->getLevel()==Node::LEAF_LEVEL){
		return new BppIterator(root->getOffset(),root->getLast(),this->manager);
	}

	unsigned int offset = dynamic_cast<LevelRegister&>(dynamic_cast<LevelNode*>(root)->getLast()).getRightChild();
	Node* node =  manager.readNode(offset);
	TreeIterator* ret = getLastNodeIterator(node);
	delete node;
	return ret;
}

TreeIterator* BppTree::getNodeIterator(Node* root,NodeRegister& key){
	if(!root)
		root = this->root;

	if(root->getLevel()==Node::LEAF_LEVEL){
		return new BppIterator(root->getOffset(),key,this->manager);
	}


	unsigned int offset = dynamic_cast<LevelNode*>(root)->getSubTree(key);
	Node* node =  manager.readNode(offset);
	TreeIterator* ret = getNodeIterator(node,key);
	delete node;
	return ret;
}

void BppTree::updateIterators(unsigned int srcOffset,Node* modified,Node* neighbor){
	/* Busco todos los iteradores que apunten a src */
	bool located=false;
	for(Iterators::iterator it=iterators.begin();it!=iterators.end();++it){
		BppIterator& bppIt = dynamic_cast<BppIterator&>(**it);
		if(bppIt.getOffset()==srcOffset){
			/* Solo resta ver si el puntero esta en modified o en el vecino  */
			if(modified)
				if( located=modified->search(*bppIt.getPointer()).first)
					bppIt.setOffset(modified->getOffset());
			if(neighbor)
				if( located=neighbor->search(*bppIt.getPointer()).first)
					bppIt.setOffset(neighbor->getOffset());

			/* Se borro justo el apuntando */
			if(!located){
				/* Por defecto trato de dejarlo en el nodo donde estaba
				 * salvo que haya unido con el vecino */
				if(modified->getRegisterCount())
					bppIt.setOffset(modified->getOffset());
				else
					bppIt.setOffset(modified->getOffset());
			}
		}
	}
}

void BppTree::deleteIterator(TreeIterator& it){
	Iterators::iterator eit = iterators.find(&it);
	if(eit!=iterators.end()){
		delete *eit;
		if(iterators.erase(&it));
	}
}

bool BppTree::update(const Register& key,const Register& value){
	unsigned int keyControlSize = (LevelRegister(key,0).getSize()-key.getSize())+(LevelNode(Node::NO_LEVEL,NodeManager::NO_OFFSET,NodeManager::NO_OFFSET,manager.getNodeSize()).getHeaderSize());
	unsigned int valueControlSize = LeafNode(Node::NO_LEVEL,NodeManager::NO_OFFSET,manager.getNodeSize()).getHeaderSize();
	ControlRegister ctrlKey(key,ControlRegister::getThreshold(value,manager.getNodeSize(),keyControlSize) ,ControlRegister::KEY_TYPE);
	ControlRegister ctrlVal(value,ControlRegister::getThreshold(ctrlKey,manager.getNodeSize(),valueControlSize),0);
	LeafRegister temp(ctrlKey,ctrlVal);

	return nodeInsert(OFFSET_ROOT,NULL,temp,true);
}

bool BppTree::insert(const Register& key,const Register& value){
	unsigned int keyControlSize = (LevelRegister(key,0).getSize()-key.getSize())+(LevelNode(Node::NO_LEVEL,NodeManager::NO_OFFSET,NodeManager::NO_OFFSET,manager.getNodeSize()).getHeaderSize());
	unsigned int valueControlSize = LeafNode(Node::NO_LEVEL,NodeManager::NO_OFFSET,manager.getNodeSize()).getHeaderSize();
	ControlRegister ctrlKey(key,ControlRegister::getThreshold(value,manager.getNodeSize(),keyControlSize) ,ControlRegister::KEY_TYPE);
	ControlRegister ctrlVal(value,ControlRegister::getThreshold(ctrlKey,manager.getNodeSize(),valueControlSize),0);
	LeafRegister temp(ctrlKey,ctrlVal);

	return nodeInsert(OFFSET_ROOT,NULL,temp);
}

bool BppTree::nodeInsert(unsigned int nodeOffset,LevelNode* root,const NodeRegister& reg,bool update){
	Node* node=NULL;
	bool ret = false;
	/* A partir de los hijos de la raiz empiezo a levantar nodos */

	if(nodeOffset!=OFFSET_ROOT)
		node = manager.readNode(nodeOffset);
	else
		node = this->root;

	if(node->isLeaf()){
		LeafNode* leafNode = dynamic_cast<LeafNode*>(node);

		if( !(ret=leafNode->insert(reg)) && update ){
			/* El registro ya existe y se lo desea actualizar */
			leafNode->remove(reg);
			leafNode->insert(reg);
			ret = true;
		}else if(update){
			/* Es una actualizacion no debe insertarse nada si no existe */
			leafNode->remove(reg);
			leafNode->offModified();
			ret = false;
		}

		if(leafNode->overflow()){
			/* Se debe resolver el overflow */
			handleLeafOverflow(leafNode,root);
		}else if(leafNode->modified()){
			/* Caso mas simple, agregado sin overflow */
			manager.writeNode(*leafNode);
			updateIterators(leafNode->getOffset(),leafNode,NULL);
		}else if(leafNode->underflow()){
			/* Un update pudo haber provocado un underflow */
			handleLeafUnderflow(leafNode,root);
		}
	}else{
		LevelNode* levelNode = dynamic_cast<LevelNode*>(node);
		/* Busco la rama de bifuracion */
		LevelRegister levelReg(reg.getKey(),NodeManager::NO_OFFSET);
		unsigned int nodeOffset = levelNode->getSubTree(levelReg);

		ret = nodeInsert(nodeOffset,levelNode,reg,update);

		if(levelNode->overflow()){
			/* Desde la insercion en alguna hoja se desencadeno un overflow que debe resolverse
               y tal vez propagarse hacia arriba */
			handleLevelOverflow(levelNode,root);
		}else if(levelNode->modified()){
			/* Hubo propagacion de desbordes hasta este nivel pero aqui termino*/
			manager.writeNode(*levelNode);
		}
	}

	if(node!=this->root)
		delete node;
	return ret;
}

void BppTree::handleLeafOverflow(LeafNode* leafNode,LevelNode* root){
	std::pair<Node*,NodeRegister*> splitResult = leafNode->split();
	NodeRegister* overflowRegister = splitResult.second;
	LeafNode* newNode = dynamic_cast<LeafNode*>(splitResult.first);
	unsigned int leafNodeOffset = leafNode->getOffset();

	/* La raiz desbordo por PRIMERA vez */
	if(leafNodeOffset==OFFSET_ROOT){
		/* Debe resguardarse la posicion de la raiz */
		leafNode->setOffset(manager.fillNewNodeSize());
		/* Debe modificarse el puntero del nuevo nodo */
		newNode->setPreviousNode(leafNode->getOffset());
	}
	newNode->setOffset(manager.fillNewNodeSize());
	newNode->setPreviousNode(leafNode->getOffset());
	newNode->setNextNode(leafNode->getNextNode());

	leafNode->setNextNode(newNode->getOffset());
	manager.writeNode(*leafNode);

	/* Si es el primer overflow crea nuevamenta a la raiz como un nodo nivel */
	if(!root){
		this->root = new LevelNode(	leafNode->getLevel()+1,
									leafNode->getOffset(),
									OFFSET_ROOT,
									manager.getNodeSize());
		root = dynamic_cast<LevelNode*>(this->root);
	}

	/* Podria seguir con overflow el nuevo nodo */
	if(newNode->overflow())
		handleLeafOverflow(newNode,root);
	else
		manager.writeNode(*newNode);

	/* Actualizo los iteradores que apuntaban al nodo que desbordo */
	updateIterators(leafNodeOffset,leafNode,newNode);

	/* Actualizo el puntero nodo siguiente al de overflow si es que existe uno */
	if(newNode->getNextNode()!=NodeManager::NO_OFFSET){
		LeafNode* nextNode = dynamic_cast<LeafNode*>(manager.readNode(newNode->getNextNode()));
		nextNode->setPreviousNode(newNode->getOffset());
		manager.writeNode(*nextNode);
		delete nextNode;
	}

	/* Grabados ambos hijos solo queda actualizar al padre */
	LevelRegister overflow(overflowRegister->getKey(),newNode->getOffset());

	root->insert(overflow);

	/* En el caso de que sea el primero de la cadena debe modificarse
     * tambien la referncia al hijo izquierdo
     */
	if(root->isFirst(overflowRegister)){
		root->setLeftChild(leafNode->getOffset());
	}

	if(!root->overflow())
		manager.writeNode(*root);
	/* En caso de overflow se activara el flag y este se resolvera mas adelante */

	delete overflowRegister;
	delete newNode;
}

void BppTree::handleLevelOverflow(LevelNode* levelNode,LevelNode* root){
	std::pair<Node*,NodeRegister*> splitResult = levelNode->split();
	LevelRegister* overflowRegister = dynamic_cast<LevelRegister*>(splitResult.second);
	LevelNode* newNode = dynamic_cast<LevelNode*>(splitResult.first);

	/* Caso especial ,desbordo la raiz */
	if(levelNode->getOffset()==OFFSET_ROOT){
		/* Debe resuardarse la posicion de la raiz */
		levelNode->setOffset(manager.fillNewNodeSize());
	}

	if(!root){
		this->root = new LevelNode(	levelNode->getLevel()+1,
									levelNode->getOffset(),
									OFFSET_ROOT,
									manager.getNodeSize());
		root = dynamic_cast<LevelNode*>(this->root);
	}

	manager.writeNode(*levelNode);


	if(newNode->overflow())
		handleLevelOverflow(newNode,root);
	else
		manager.writeNode(*newNode);

	/* Grabados ambos hijos solo resta grabar al padre */

	overflowRegister->setRightChild(newNode->getOffset());
	root->insert(*overflowRegister);
	/* En el caso de que sea el primero de la cadena debe modificarse
       tambien la referencia al hijo izquierdo*/
	if(root->isFirst(dynamic_cast<NodeRegister*>(overflowRegister))){
		root->setLeftChild(levelNode->getOffset());
	}

	if(!root->overflow())
		manager.writeNode(*root);
	/* En caso de overflow se activara el flag y este se resolvera mas adelante */

	delete overflowRegister;
	delete newNode;
}

bool BppTree::remove(const Register& key){
	return nodeRemove(BppTree::OFFSET_ROOT,NULL,ControlRegister(key,-1,0));
}


bool BppTree::nodeRemove(unsigned int nodeOffset,LevelNode* root,const Register& key){
	Node* node=NULL;
	bool ret = false;
	// A partir de los hijos de la raiz empiezo a levantar nodos

	if(nodeOffset!=OFFSET_ROOT)
		node = manager.readNode(nodeOffset);
	else
		node = this->root;

	if(node->isLeaf()){
		LeafRegister lr(key,key);
		LeafNode* leafNode = dynamic_cast<LeafNode*>(node);

		ret=leafNode->remove(lr);

		if(leafNode->underflow() && leafNode->getOffset()!=OFFSET_ROOT){
			// Se debe resolver el underflow
			handleLeafUnderflow(leafNode,root);
		}else if(leafNode->modified()){
			// Caso mas simple, eliminacion sin underflow
			manager.writeNode(*leafNode);
			updateIterators(leafNode->getOffset(),leafNode,NULL);
		}
	}else{
		LevelNode* levelNode = dynamic_cast<LevelNode*>(node);
		// Busco la rama de bifuracion
		LevelRegister levelReg(key,NodeManager::NO_OFFSET);
		unsigned int nodeOffset = levelNode->getSubTree(levelReg);

		ret = nodeRemove(nodeOffset,levelNode,key);

		if(levelNode->underflow() && levelNode->getOffset()!=OFFSET_ROOT ){
			// Desde la insercion en alguna hoja se desencadeno un underflow que debe resolverse
            //   y tal vez propagarse hacia arriba
			handleLevelUnderflow(levelNode,root);
		}else if(levelNode->overflow()){
			// Puede que se haya reemplazado un registro pequeno por uno mayo y
			// provocado asi overflow
			handleLevelOverflow(levelNode,root);
		}else if(levelNode->modified()){
			// Hubo propagacion de underflow hasta este nivel pero aqui termino
			manager.writeNode(*levelNode);
		}
	}

	if(node!=this->root)
		delete node;
	return ret;
}

void BppTree::handleLeafUnderflow(LeafNode* leafNode,LevelNode* root){
	bool lastNode=false;

	// la raiz nunca puede tener underflow
	if(!root)
		return;

	LeafNode* nextNode = NULL;
	unsigned int nextNodeOffset = root->getNextSibling(leafNode->getOffset());
	if( lastNode=(nextNodeOffset==NodeManager::NO_OFFSET))
		nextNodeOffset = root->getPreviousSibling(leafNode->getOffset());

	nextNode = static_cast<LeafNode*>(manager.readNode(nextNodeOffset));

	/* Se busca salvar el underflow pidiendole registros al vecino
	 * caso contrario se fusionan y se elimina el registro padre de la raiz. */
	getFromLeafSibling(leafNode,nextNode,root,lastNode);
	if(nextNode->underflow())
		joinLeafSibling(leafNode,nextNode,root,lastNode);

	if(!leafNode->freed())
			manager.writeNode(*leafNode);
	if(!nextNode->freed())
			manager.writeNode(*nextNode);

	updateIterators(leafNode->getOffset(),leafNode,nextNode);

	if(nextNode!=this->root)
		delete nextNode;
}

void BppTree::getFromLeafSibling(LeafNode* leafNode,LeafNode* nextNode,LevelNode* root,bool reverse){
	LeafRegister* toUpperLevel = NULL;

	/* Se pasan registros hasta que ya no este en underflow o el vecino no pueda dar mas(este en underflow)*/
	while(	(leafNode->underflow()) && (!nextNode->underflow()) ){
		if(toUpperLevel)
			delete toUpperLevel;

		toUpperLevel = static_cast<LeafRegister*>(nextNode->extract(nextNode->getFirst(reverse)));

		leafNode->insert(*toUpperLevel);
	}

	if(reverse)
		std::swap(leafNode,nextNode);

	/* Actualizo el registro que esta en la raiz que direcciona al vecino
	 * salvo que el join sea inevitable.
	 */
	if(nextNode->getRegisterCount()>0 && leafNode->getRegisterCount()>0){
		root->remove(*root->getRootRegister(nextNode->getOffset()));
		root->insert(LevelRegister(nextNode->getFirst().getKey(),nextNode->getOffset()));
	}

	delete toUpperLevel;
}

void BppTree::joinLeafSibling(LeafNode* leafNode,LeafNode* nextNode,LevelNode* root,bool reverse){
	if(reverse)
		std::swap(leafNode,nextNode);

	/* Elimino el registro que esta en la raiz que direcciona al vecino */
	root->remove(*root->getRootRegister(nextNode->getOffset()));

	/* Paso todos los registros */
	std::list<NodeRegister*> regs;
	nextNode->extractAll(regs);
	for(std::list<NodeRegister*>::iterator it=regs.begin();it!=regs.end();++it){
		leafNode->insert(**it);
		delete *it;
	}
	leafNode->setNextNode(nextNode->getNextNode());
	if(nextNode->getNextNode()!=NodeManager::NO_OFFSET){
		LeafNode* temp = static_cast<LeafNode*>(manager.readNode(nextNode->getNextNode()));
		temp->setPreviousNode(leafNode->getOffset());
		manager.writeNode(*temp);
		delete temp;
	}


	/* Caso particular la raiz cayo hasta una hoja nuevamente */
	if(root->getRegisterCount()==0 && root->getOffset()==OFFSET_ROOT){
		manager.freeNodeBlock(*leafNode);
		leafNode->setOffset(OFFSET_ROOT);
		leafNode->setFreed(false);
		root->offModified();
		this->root = leafNode;
	}

	manager.freeNodeBlock(*nextNode);
}

void BppTree::handleLevelUnderflow(LevelNode* levelNode,LevelNode* root){
	bool lastNode=false;
	LevelNode* nextNode = NULL;

	unsigned int nextNodeOffset = root->getNextSibling(levelNode->getOffset());
	if( lastNode=(nextNodeOffset==NodeManager::NO_OFFSET))
		nextNodeOffset = root->getPreviousSibling(levelNode->getOffset());

	nextNode = static_cast<LevelNode*>(manager.readNode(nextNodeOffset));

	/* Se busca salvar el underflow pidiendole registros al vecino
	 * caso contrario se fusionan y se elimina el registro padre de la raiz. */
	getFromLevelSibling(levelNode,nextNode,root,lastNode);
	if(nextNode->underflow())
		joinLevelSibling(levelNode,nextNode,root,lastNode);

	if(!levelNode->freed())
			manager.writeNode(*levelNode);
	if(!nextNode->freed())
			manager.writeNode(*nextNode);

	if(nextNode!=this->root)
		delete nextNode;
}

void BppTree::getFromLevelSibling(LevelNode* levelNode,LevelNode* nextNode,LevelNode* root,bool reverse){
	/* Se pasan registros hasta que ya no este en underflow o el vecino no pueda dar mas(este en underflow)*/	NodeRegister* toExtract = NULL;
	LevelNode* swpLevelNode = levelNode;
	LevelNode* swpNextNode = nextNode;
	bool stop=false;

	if(reverse)
		std::swap(swpLevelNode,swpNextNode);

	toExtract = root->getRootRegister(swpNextNode->getOffset());

	while(	(levelNode->underflow()) && (!nextNode->underflow()) && !stop){
		LevelRegister* toLevelNode = static_cast<LevelRegister*>(root->extract(*toExtract));
		LevelRegister* toRootNode = static_cast<LevelRegister*>(nextNode->extract(nextNode->getFirst(reverse)));

		levelNode->insert(LevelRegister(toLevelNode->getKey(),swpNextNode->getLeftChild()));

		if(!nextNode->getRegisterCount()){
			// Detengo el pasaje de registros dado que sino el nextNode quedaria vacio,
			// en este caso el levelNode debe soportar el underflow hasta que pueda
			// joinearse con su vecino.
			if( stop=(!levelNode->joinable(*nextNode,*toRootNode)) ){
					nextNode->insert(*toRootNode);
					root->insert(*toLevelNode);
					levelNode->remove(LevelRegister(toLevelNode->getKey(),0));
			}
		}

		if(!stop){
			root->insert(LevelRegister(toRootNode->getKey(),toLevelNode->getRightChild()));
			swpNextNode->setLeftChild(toRootNode->getRightChild());
		}

		toExtract = root->getRootRegister(swpNextNode->getOffset());
		delete toLevelNode;
		delete toRootNode;
	}
}

void BppTree::joinLevelSibling(LevelNode* levelNode,LevelNode* nextNode,LevelNode* root,bool reverse){
	if(reverse)
		std::swap(levelNode,nextNode);

	NodeRegister* rootReg = root->getRootRegister(nextNode->getOffset());

	/* La union puede no ser posible, en ese caso nextNode quedara en underflow inevitablemente */
	if(!levelNode->joinable(*nextNode,*rootReg))
		return;

	rootReg = root->extract(*rootReg);

	/* Paso todos los registros */
	std::list<NodeRegister*> regs;
	nextNode->extractAll(regs);
	for(std::list<NodeRegister*>::iterator it=regs.begin();it!=regs.end();++it){
		levelNode->insert(**it);
		delete *it;
	}
	levelNode->insert(LevelRegister(rootReg->getKey(),nextNode->getLeftChild()));

	/* Caso particular la raiz cayo hasta una hoja nuevamente */
	if(root->getRegisterCount()==0 && root->getOffset()==OFFSET_ROOT){
		manager.freeNodeBlock(*levelNode);
		levelNode->setOffset(OFFSET_ROOT);
		levelNode->setFreed(false);
		root->offModified();
		this->root = levelNode;
	}

	manager.freeNodeBlock(*nextNode);

	delete rootReg;
}

