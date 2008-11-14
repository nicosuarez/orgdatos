#include "bpptree.h"
#include "leaf_register.h"
#include "level_register.h"

using namespace bpptree;

std::ostream& bpptree::operator <<(std::ostream& out,BppTree& tree){

	Node* node = tree.manager.readNode(BppTree::OFFSET_ROOT);
	std::queue<unsigned int> offsets;
	out << "*------Comienzo Arbol B+----------*" << std::endl;
	node->toOstream(out,offsets);
	while(!offsets.empty()){		
		unsigned int off = offsets.front();
		offsets.pop();
		Node* temp = tree.manager.readNode(off);
		temp->toOstream(out,offsets); /* suma al queue offsets */
		delete temp;
	}
	out << "*------Fin Arbol B+----------*" << std::endl;
	delete node;
	return out;
}

std::ostream& BppTree::toOstream(std::ostream& out){
	BppTree& tree = dynamic_cast<BppTree&>(*this);
	out << tree;
	return out;
}

BppTree::BppTree(unsigned int nodeSize,const RegisterFactory& factory,const RegisterFactory& factoryNivel,const std::string& nodesFilename) :
manager(nodesFilename,nodeSize,factory,factoryNivel){
	this->root = manager.readNode(OFFSET_ROOT);
}

BppTree::~BppTree(){
	/* No hace falta escribirlo ya que la raiz siempre se mantiene 
       actualizada en disco<->memoria */
	delete this->root;
}

bool BppTree::insert(const Register& reg){
	return nodeInsert(OFFSET_ROOT,NULL,reg);
}

bool BppTree::nodeInsert(unsigned int nodeOffset,LevelNode* root,const Register& reg){
	Node* node=NULL;
	bool ret = false;
	/* A partir de los hijos de la raiz empiezo a levantar nodos */
	if(nodeOffset!=OFFSET_ROOT)
		node = manager.readNode(nodeOffset);
	else
		node = this->root;
	
	if(node->getLevel()==Node::LEAF_LEVEL){
		LeafNode* leafNode = dynamic_cast<LeafNode*>(node);
		
		ret = leafNode->insert(LeafRegister(reg));

		if(leafNode->overflow()){
			/* Se debe resolver el overflow */
			handleLeafOverflow(leafNode,root);
		}else if(leafNode->modified()){
			/* Caso mas simple, agregado sin overflow */
			manager.writeNode(*leafNode);
		}/* else -> el registro ya existe */
	}else{
		LevelNode* levelNode = dynamic_cast<LevelNode*>(node);
		/* Busco la rama de bifuracion */
		Register* regNiv = reg.getKeyRegister();
		std::pair<bool,unsigned int> nodeOffset = levelNode->getSubTree(*regNiv);
		delete regNiv;
		/* El registro podria ya existir y estar en este nodo*/
	
		if(nodeOffset.first){
			/* Inserto en la rama obtenida */
			ret = nodeInsert(nodeOffset.second,levelNode,reg);
		}

		if(levelNode->overflow()){
			/* Desde la insercion en alguna hoja se desencadeno un overflow que debe resolverse
               y tal vez propagarse hacia arriba */
			handleLevelOverflow(levelNode,root);
		}else if(levelNode->modified()){
			/* Hubo propagacion de desbordes hasta este nivel pero aqui termino*/
			manager.writeNode(*levelNode);
		}/* else -> el registro ya existe */
	}

	if(node!=this->root)delete node;
	return ret;
}

void BppTree::handleLeafOverflow(LeafNode* leafNode,LevelNode* root){

	NodeRegister* overflowRegister = leafNode->getOverflowRegister();
	Node* newNode = leafNode->getNewNode();
		
	/* La raiz desbordo por PRIMERA vez */
	if(leafNode->getOffset()==OFFSET_ROOT){
		/* Debe resguardarse la posicion de la raiz */
		leafNode->setOffset(NodeManager::NO_OFFSET);
		manager.writeNode(*leafNode);
	}	


	dynamic_cast<LeafNode*>(newNode)->setPreviousNode(leafNode->getOffset());
	dynamic_cast<LeafNode*>(newNode)->setNextNode(leafNode->getNextNode());
	manager.writeNode(*newNode);
	dynamic_cast<LeafNode*>(leafNode)->setNextNode(newNode->getOffset());
	manager.writeNode(*leafNode);
	if(dynamic_cast<LeafNode*>(newNode)->getNextNode()!=0){
		LeafNode* nodeSigAux = dynamic_cast<LeafNode*>(manager.readNode((dynamic_cast<LeafNode*>(newNode))->getNextNode()));
		nodeSigAux->setPreviousNode(newNode->getOffset());
		manager.writeNode(*nodeSigAux);
		delete nodeSigAux;
	}

	/* Grabados ambos hijos solo queda actualizar al padre */
	if(root==NULL){
		/* Caso especial, desbordo por primera vez y no hay padre */
		unsigned int level = leafNode->getLevel()+1;
		LevelNode* root2 = new LevelNode(level,leafNode->getOffset(),OFFSET_ROOT,manager.getNodeSize());
		Register* ovReg = (overflowRegister->getRegister()).duplicate();
		LevelRegister overflow(*ovReg,newNode->getOffset());
		root2->insert(overflow);
		
		/* solo para apagar el flag modified*/		
		root2->modified();
		manager.writeNode(*root2);
		/* Aparecio una nueva raiz */
		//if(this->root!=NULL)
		//	delete this->root;
		this->root = root2;
		delete ovReg;
	}else{
		/* Simplemente se agrega un nuevo registro al nodo  */
		LevelRegister overflow = LevelRegister(overflowRegister->getRegister(), newNode->getOffset()) ;
		root->insert(overflow);
		/* En el caso de que sea el primero de la cadena debe modificarse 
           tambien la referncia al hijo izquierdo*/
		if(root->isFirst(*overflowRegister)){
			root->setLeftChild(leafNode->getOffset());
		}
		/* en caso de overflow se activara el flag y este se resolvera mas adelante */
	}

	delete overflowRegister;
	delete newNode;
}

void BppTree::handleLevelOverflow(LevelNode* levelNode,LevelNode* root){
	LevelRegister* overflowRegister = dynamic_cast<LevelRegister*>(levelNode->getOverflowRegister()); 
	Node* newNode = levelNode->getNewNode();
	/* Caso especial ,desbordo la raiz */
	if(levelNode->getOffset()==OFFSET_ROOT){
		/* Debe resuardarse la posicion de la raiz */
		levelNode->setOffset(NodeManager::NO_OFFSET);
	}
	manager.writeNode(*levelNode);
	manager.writeNode(*newNode);
	/* Grabados ambos hijos solo resta grabar al padre */
	if(root==NULL){
		/* Caso especial, un desborde provoca nueva raiz general del arbol */
		unsigned int level = levelNode->getLevel()+1;
		LevelNode* root = new LevelNode(level,levelNode->getOffset(),OFFSET_ROOT,manager.getNodeSize());
		overflowRegister->setRightChild(newNode->getOffset());
		root->insert(*overflowRegister);
		/* solo para apagar el flag modified*/
		root->modified();
		manager.writeNode(*root);
		/* Aparecio una nueva raiz */
		this->root = root;
	}else{
		/* Simplemente se agrega un nuevo registro al nodo  */
		overflowRegister->setRightChild(newNode->getOffset());
		root->insert(*overflowRegister);
		/* En el caso de que sea el primero de la cadena debe modificarse 
           tambien la referncia al hijo izquierdo*/
		if(root->isFirst(*overflowRegister)){
			root->setLeftChild(levelNode->getOffset());
		}
		/* en caso de overflow se activara el flag y este se resolvera mas adelante */
	}
	delete overflowRegister;
	delete newNode;
}

bool BppTree::remove(const Register& reg){ 
	return nodeRemove(OFFSET_ROOT,NULL,reg);
}

bool BppTree::nodeRemove(unsigned int nodeOffset,LevelNode* root,const Register& reg){
	Node* node = NULL;
	bool ret = false;
	/* A partir de los hijos de la raiz empiezo a levantar nodos */
	if(nodeOffset!=OFFSET_ROOT)
		node = manager.readNode(nodeOffset);
	else
		node = this->root;
	
	if(node->getLevel()==Node::LEAF_LEVEL){
		LeafNode* leafNode = dynamic_cast<LeafNode*>(node);
		LeafRegister* lfR = new LeafRegister(reg);
		ret = leafNode->remove(*lfR);
		delete lfR;

		if(leafNode->underflow()){
			/* Se debe resolver el overflow */
			handleLeafUnderflow(leafNode,root,reg);
			
		}else if(leafNode->modified()){
			/* Caso mas simple, agregado sin overflow */
			manager.writeNode(*leafNode);
		}/* else -> el registro ya existe */
	}else{
		LevelNode* levelNode = dynamic_cast<LevelNode*>(node);
		/* Busco la rama de bifuracion */
		Register* regNiv = reg.getKeyRegister();
		std::pair<bool,unsigned int> nodeOffset = levelNode->getSubTree(*regNiv);
		delete regNiv;
		/* El registro podria ya existir y estar en este nodo*/
	
		if(nodeOffset.first){
			/* Inserto en la rama obtenida */
			ret = nodeRemove(nodeOffset.second,levelNode,reg);
		}
		if(levelNode->underflow()){
			/* Desde la insercion en alguna hoja se desencadeno un overflow que debe resolverse
               y tal vez propagarse hacia arriba */
			handleLevelUnderflow(levelNode,root,reg);
		}else if(levelNode->modified()){
			/* Hubo propagacion de desbordes hasta este nivel pero aqui termino*/
			manager.writeNode(*levelNode);
		}/* else -> el registro ya existe */
	}

	if(node!=this->root)delete node;
	return ret;
}

void BppTree::handleLeafUnderflow(LeafNode* leafNode,LevelNode* root,const Register& reg){

	std::pair<int, std::pair<LevelRegister*,unsigned int> > sibling;
	Node* nodeSibling = NULL;
	LevelRegister* levelRegister = NULL;
	NodeRegister* siblingsRegister = NULL;
	/* Grabados ambos hijos solo queda actualizar al padre */
	if(root==NULL){
		leafNode->modified();
		leafNode->underflow();
		manager.writeNode(*leafNode);
	}else{
		/*Pido un sibling al root*/
		LeafRegister* leafReg1 = (dynamic_cast<LeafRegister*>(leafNode->getFirstRegister()));
		Register* regAux = leafReg1->getKeyRegister();
		levelRegister = new LevelRegister(*(regAux),NodeManager::NO_OFFSET);
		sibling = root->getSibling(levelRegister);
		delete leafReg1;
		delete regAux;
		delete levelRegister;
		nodeSibling = manager.readNode(sibling.second.second);
		if(sibling.first>0){
			
			/*Saco primero*/
			siblingsRegister=nodeSibling->extractFirstRegister();
			/*Si underflow en sibling junto nodos*/
			if(nodeSibling->underflow()){
				
				/*JuntarNodos la funcion no elimina el segundo sibling*/
				NodeRegister* lr = leafNode->joinNodes(nodeSibling);
				/*agrego el registro del sibling al primer nodo*/
				leafNode->insert(*siblingsRegister);
				/*Elimino del disco el sibling*/
				manager.freeNodeBlock(*nodeSibling);
				/*Elimino de root el que saque y dio overflow*/ 
				Register* rr = (dynamic_cast<LeafRegister*>(siblingsRegister))->getKeyRegister();
				LevelRegister* lRAux= new LevelRegister(*rr, NodeManager::NO_OFFSET); 
				delete rr;

				root->remove(*lRAux);
				
				/*Elimino el nodo sibling*/

				/*Actualizo siguiente nodo*/
				if(leafNode->getNextNode()!=0){
					LeafNode* nodeLAux = (LeafNode*)manager.readNode(leafNode->getNextNode());
					nodeLAux->setPreviousNode(leafNode->getOffset());
					manager.writeNode(*nodeLAux);
					delete nodeLAux;
				}
			
				delete lRAux;
				delete lr;
				manager.writeNode(*leafNode);
			}else{
				
				nodeSibling->modified();
				leafNode->insert(*siblingsRegister);
				/*Cambio en padre de clave*/
				Register* r1 =  (dynamic_cast<LeafRegister*>(siblingsRegister))->getKeyRegister();
				LevelRegister* lRAux1= new LevelRegister(*r1, NodeManager::NO_OFFSET); 
				/**/
				LeafRegister* leafReg2 = (dynamic_cast<LeafRegister*>(nodeSibling->getFirstRegister()));
				Register* r2 = leafReg2->getKeyRegister();
				LevelRegister* lRAux2= new LevelRegister(*r2, NodeManager::NO_OFFSET); 
				/**/
				NodeRegister* raux = root->modify(*lRAux1 ,*lRAux2);
				manager.writeNode(*leafNode);
				manager.writeNode(*nodeSibling);
				delete leafReg2;
				delete lRAux1;
				delete lRAux2;
				delete r1;
				delete r2;
				delete raux;
			}
			delete siblingsRegister;
		}else{
			/*Saco ultimo*/
			siblingsRegister=nodeSibling->extractLastRegister();
			
			/*Si underflow en sibling junto nodos*/
			if(nodeSibling->underflow()){
				
				/*JuntarNodos la funcion no elimina el nodo*/
				NodeRegister* lr = (dynamic_cast<LeafNode*>(nodeSibling))->joinNodes(leafNode);
				/*agrego el registro del sibling al segundo nodo*/
				nodeSibling->insert(*siblingsRegister);
				/*Elimino del disco el sibling*/
				manager.freeNodeBlock(*leafNode);
				/*Elimino de root el que saque y dio overflow*/ 
				Register* reg2 = reg.getKeyRegister();
				
				LevelRegister* lRAux=NULL;

				if(lr!=NULL){
					Register* reg1 = ((lr->getRegister()).duplicate());	
					
					if((*reg1)<*reg2)
						lRAux= new LevelRegister(*reg1, NodeManager::NO_OFFSET); 
					else
						lRAux= new LevelRegister(*reg2, NodeManager::NO_OFFSET);
					delete reg1;
				}
				else
					lRAux= new LevelRegister(*reg2, NodeManager::NO_OFFSET);

				
				if((dynamic_cast<LeafNode*>(nodeSibling))->getNextNode()!=0){
					LeafNode* nodeLAux = (LeafNode*)manager.readNode((dynamic_cast<LeafNode*>(nodeSibling))->getNextNode());
					nodeLAux->setPreviousNode((dynamic_cast<LeafNode*>(nodeSibling))->getOffset());
					manager.writeNode(*nodeLAux);
					delete nodeLAux;
				}				
				
				root->remove(*lRAux);
				
				/*Elimino el nodo sibling*/
				manager.writeNode(*nodeSibling);
				//delete leafNode;
				delete lr;
				delete lRAux;
				delete reg2;

			}else{
				
				/*Cambio en padre de clave*/
				
				Register* r1= (dynamic_cast<LeafRegister*>(siblingsRegister))->getKeyRegister();
				LevelRegister* lRAux1= new LevelRegister(*(r1), NodeManager::NO_OFFSET); 
				/**/
				LeafRegister* lfR2=dynamic_cast<LeafRegister*>(leafNode->getFirstRegister());
				Register* r2 = lfR2->getKeyRegister();
				LevelRegister* lRAux2= new LevelRegister(*r2, NodeManager::NO_OFFSET); 
				delete lfR2;
				/**/
				NodeRegister* nr = root->modify(*lRAux2 ,*lRAux1);
				
				/*Agrego registro*/
				leafNode->insert(*siblingsRegister);
				manager.writeNode(*leafNode);
				manager.writeNode(*nodeSibling);
				nodeSibling->modified();
				leafNode->modified();
				delete lRAux1;
				delete lRAux2;
				delete r1;
				delete r2;
				delete nr;
			}
			delete siblingsRegister;
		}
		delete nodeSibling;	
		delete sibling.second.first;
	}

}

void BppTree::handleLevelUnderflow(LevelNode* levelNode,LevelNode* root,const Register& reg){
	
	std::pair<int, std::pair<LevelRegister*,unsigned int> > sibling;
	Node* nodeSibling=NULL;
	LevelRegister* levelRegister=NULL;
	NodeRegister* siblingsRegister=NULL;
	/* Grabados ambos hijos solo queda actualizar al padre */

	if(root==NULL){
		
		if(levelNode->getRegCount()==0){
			unsigned int offsetAux;
			Node* nuevaRaiz =  manager.readNode(levelNode->getLeftChild());
			offsetAux = nuevaRaiz->getOffset();
			nuevaRaiz->setOffset(BppTree::OFFSET_ROOT);
			manager.writeNode(*nuevaRaiz);
			nuevaRaiz->setOffset(offsetAux);
			manager.freeNodeBlock(*nuevaRaiz);
			nuevaRaiz->setOffset(BppTree::OFFSET_ROOT);
			//delete this->root;
			this->root = nuevaRaiz;
		}
		else
			manager.writeNode(*levelNode);
	}else{
		
		/*Pido un sibling al root*/
		levelRegister = dynamic_cast<LevelRegister*>(levelNode->getFirstRegister());
		sibling = root->getSibling(levelRegister);
		nodeSibling = manager.readNode(sibling.second.second);
		if(sibling.first>0){
			
			/*Saco primero*/
			siblingsRegister=nodeSibling->extractFirstRegister();

			/*Si underflow en sibling junto nodos*/
			if(nodeSibling->underflow()){
				
				/*JuntarNodos la funcion no elimina el segundo sibling*/
				NodeRegister* nrAux =levelNode->joinNodes(nodeSibling,sibling.second.first);
				/*agrego el registro del sibling al primer nodo*/
				levelNode->insert(*siblingsRegister);
				/*Elimino del disco el sibling*/
				manager.freeNodeBlock(*nodeSibling);
				/*Elimino de root el que saque y dio overflow*/ 
				root->remove(*dynamic_cast<LevelRegister*>(sibling.second.first));
				/*Elimino el nodo sibling*/
				//delete nodeSibling;
				levelNode->modified();
				levelNode->underflow();
				
				manager.writeNode(*levelNode);

				delete nrAux;

			}else{
				
				nodeSibling->modified();
				/*Guardo el nodo de la derecha del primer registro del siguiente nodo*/
				unsigned int auxNodo = (dynamic_cast<LevelRegister*>(siblingsRegister))->getRightChild();
				/*Guardo el primer registro del siguiente nodo en la raiz y le cambio clave*/

				/*NodeRegister* aux = root->modify(*levelRegister ,*(dynamic_cast<LevelRegister*>(siblingsRegister)));*/

				NodeRegister* aux = root->modify(*(dynamic_cast<LevelRegister*>(siblingsRegister)) ,*(dynamic_cast<LevelRegister*>(siblingsRegister)));

				/*Al registro de la raiz que habia antes le cambio el nodo de la derecha*/
				(dynamic_cast<LevelRegister*>(aux))->setRightChild((dynamic_cast<LevelNode*>(nodeSibling))->getLeftChild());
				/*Guardo el auxNodo como primer puntero del siguiente*/
				(dynamic_cast<LevelNode*>(nodeSibling))->setLeftChild(auxNodo);
				/*Agrego el registro que estaba en la raiz al primer bloque*/
				levelNode->insert(*aux);	
				/*Guardo los datos a disco*/
				levelNode->modified();
				manager.writeNode(*levelNode);
				manager.writeNode(*nodeSibling);

				delete aux;
			}

		}else{
			/*Saco primero*/
			siblingsRegister=nodeSibling->extractLastRegister();
			/*Si underflow en sibling junto nodos*/
			if(nodeSibling->underflow()){
				/*JuntarNodos la funcion no elimina el segundo sibling*/
					
				NodeRegister* nraux = (dynamic_cast<LevelNode*>(nodeSibling))->joinNodes(levelNode,sibling.second.first);
				
				
				/*agrego el registro del sibling al primer nodo*/
				nodeSibling->insert(*siblingsRegister);
				/*Elimino del disco el sibling*/
				manager.freeNodeBlock(*levelNode);

				/*Elimino de root el que saque y dio overflow*/ 
				root->remove(*dynamic_cast<LevelRegister*>(sibling.second.first));
				/*Elimino el nodo sibling*/
				nodeSibling->modified();
				nodeSibling->underflow();
				manager.writeNode(*nodeSibling);
				
				delete nraux;
				//nraux=NULL;
			}else{
				
				nodeSibling->modified();
				/*Guardo el child del ultmo del sibling anterior*/
				unsigned int auxNodo = (dynamic_cast<LevelRegister*>(siblingsRegister))->getRightChild();
				
				NodeRegister* aux = root->modify(*levelRegister ,*dynamic_cast<LevelRegister*>(siblingsRegister));
				
				/*(dynamic_cast<LevelRegister*>(aux))->setRightChild((dynamic_cast<LevelNode*>(nodeSibling))->getLeftChild());*/
				(dynamic_cast<LevelRegister*>(aux))->setRightChild((dynamic_cast<LevelNode*>(levelNode))->getLeftChild());
				/*Guardo como leafChild del nodo al rightChild del ultimo registro del hermano*/
				levelNode->setLeftChild(auxNodo);
				levelNode->insert(*aux);
				levelNode->modified();
				manager.writeNode(*levelNode);
				manager.writeNode(*nodeSibling);
				delete aux;
			}
		}
		delete sibling.second.first;
		delete levelRegister;	
		delete nodeSibling;	
		delete siblingsRegister;
	}
}

bool BppTree::search(Register& reg){ 
	LeafNode* leafNode;
	LevelNode* levelNode;
	Node* node;
	bool ret = false;
	/*Encuentro hoja*/
	node = this->root;
	while(node->getLevel()!=Node::LEAF_LEVEL){
		levelNode = dynamic_cast<LevelNode*>(node);
		Register* regNiv = reg.getKeyRegister();
		std::pair<bool,unsigned int> nodeOffset = levelNode->getSubTree(*regNiv);
		delete regNiv;
		if(nodeOffset.first){
			if(node!=this->root)delete node;
			node = manager.readNode(nodeOffset.second);					
		}
	}
	leafNode=dynamic_cast<LeafNode*>(node);
	/*Encuentro Registro*/
	LeafRegister* leafReg = new LeafRegister(reg);
	if(leafNode->search(*leafReg)){
		reg.setFields(leafReg->getRegister());
		ret = true;
	}
	
	if(leafNode!=this->root)delete leafNode;
	delete leafReg;
	return ret;
}

bool BppTree::modify(const Register& reg){ 
	LeafNode* leafNode;
	LevelNode* levelNode;
	Node* node;
	bool ret = false;
	/*Encuentro hoja*/
	node = this->root;
	while(node->getLevel()!=Node::LEAF_LEVEL){
		levelNode = dynamic_cast<LevelNode*>(node);
		Register* regNiv = reg.getKeyRegister();
		std::pair<bool,unsigned int> nodeOffset = levelNode->getSubTree(*regNiv);
		delete regNiv;
		if(nodeOffset.first){
			if(node!=this->root)delete node;
			node = manager.readNode(nodeOffset.second);					
		}
	}
	leafNode=dynamic_cast<LeafNode*>(node);
	/*Encuentro Registro*/
	LeafRegister* leafReg = new LeafRegister(reg);
	if(leafNode->modify(*leafReg)){
		ret = true;
		manager.writeNode(*leafNode);
	}
	if(leafNode!=this->root)delete leafNode;
	delete leafReg;
	return ret;
}

BppIterator* BppTree::getIterator(const Register& reg){
	LeafNode* leafNode;
	LevelNode* levelNode;
	Node* node;
	BppIterator* iter = NULL;
	/*Encuentro hoja*/
	node = this->root;
	while(node->getLevel()!=Node::LEAF_LEVEL){
		levelNode = dynamic_cast<LevelNode*>(node);
		Register* regNiv = reg.getKeyRegister();
		std::pair<bool,unsigned int> nodeOffset = levelNode->getSubTree(*regNiv);
		delete regNiv;
		if(nodeOffset.first){
			if(node!=this->root)delete node;
			node = manager.readNode(nodeOffset.second);					
		}
	}
	leafNode=dynamic_cast<LeafNode*>(node);
	/*Encuentro Registro*/
	LeafRegister* leafReg = new LeafRegister(reg);

	if(leafNode->search(*leafReg))
		iter = new BppIterator(leafNode->getOffset(), *leafReg, &manager);
	
	if(leafNode!=this->root)delete leafNode;
	delete leafReg;

	return iter;
}


BppIterator* BppTree::getFirst(){ 
	
	LeafNode* leafNode;
	LevelNode* levelNode;
	Node* node;
	BppIterator* iter = NULL;
	/*Encuentro hoja*/
	node = this->root;
	while(node->getLevel()!=Node::LEAF_LEVEL){
		levelNode = dynamic_cast<LevelNode*>(node);
		unsigned int nodeOffset = levelNode->getLeftChild();
		
		if(node!=this->root)delete node;
		node = manager.readNode(nodeOffset);					
		
	}
	leafNode=dynamic_cast<LeafNode*>(node);
	/*Encuentro Registro*/

	iter = new BppIterator(leafNode->getOffset(), false, &manager);
	
	if(leafNode!=this->root)delete leafNode;


	return iter;
}
		
BppIterator* BppTree::getLast(){ 
	LeafNode* leafNode;
	LevelNode* levelNode;
	Node* node;
	BppIterator* iter = NULL;
	/*Encuentro hoja*/
	node = this->root;
	while(node->getLevel()!=Node::LEAF_LEVEL){
		levelNode = dynamic_cast<LevelNode*>(node);
		LevelRegister* lr = dynamic_cast<LevelRegister*>(levelNode->getLastRegister());
		unsigned int nodeOffset = lr->getRightChild();
		delete lr;
		if(node!=this->root)delete node;
		node = manager.readNode(nodeOffset);					
		
	}
	leafNode=dynamic_cast<LeafNode*>(node);
	/*Encuentro Registro*/

	iter = new BppIterator(leafNode->getOffset(), true, &manager);
	
	if(leafNode!=this->root)delete leafNode;


	return iter;
}


