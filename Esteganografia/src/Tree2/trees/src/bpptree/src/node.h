#ifndef __BPP_NODE_H__
#define __BPP_NODE_H__

#include <set>
#include <cstring>
#include <queue>
#include "node_register.h"

/* forwarding */
class RegisterFactory;

namespace bpptree{

class Node{
	public:
		static const unsigned int LEAF_LEVEL = 0;
		static const unsigned int NO_LEVEL = -1;
	protected:
		unsigned int size;
		unsigned int level;
		unsigned int registerCount;
		unsigned int offset;
		bool foverflow;
		bool funderflow;
		bool fmodified;
		NodeRegister* overflowRegister;
		Node* newNode;
		
		typedef std::set<NodeRegister*,NodeRegisterOrder> Registers;
		Registers regs;

		NodeRegister* joinNodes(Node* nodo){	
			
			
			Registers::iterator it = nodo->sequenceBegin();
			NodeRegister* primerRegistrodelNodoEliminado=NULL;

			if(it!=nodo->sequenceEnd())
				primerRegistrodelNodoEliminado = /*dynamic_cast<NodeRegister*>*/(*it)->duplicate();
			
			while(it!=nodo->sequenceEnd()){	
				std::pair<Registers::iterator,bool> p = regs.insert((*it)->duplicate());
				registerCount++;
				it++;
			}
				
			return primerRegistrodelNodoEliminado;
		}

	public:
		Node(unsigned int level,unsigned int offset,unsigned int size){
			this->registerCount=0;
			overflowRegister = NULL;
			newNode=NULL;
			this->level = level;
			this->size = size;
			this->offset = offset;
			this->funderflow = false;
			this->foverflow = false;
			this->fmodified = false;
		}

		virtual ~Node(){
			for(Registers::iterator it=regs.begin();it!=regs.end();++it){
				delete(*it);
			}
			regs.clear();
		}
		
	
			
		/* Todos los flags se apagan luego de ser consultados 
		   lo que implica que luego de la consulta DEBE antenderse
           el problema en cuestion.
		*/
		bool modified(){
			bool retVal = this->fmodified;
			this->fmodified = false;
			return retVal;
		}

		bool overflow(){ 
			bool retVal = this->foverflow;
			this->foverflow = false;
			return retVal;
		}

		bool underflow(){ 
			bool retVal = this->funderflow;
			this->funderflow = false;
			return retVal;
		}

		virtual bool insert(const NodeRegister& reg){
			NodeRegister* temp = reg.duplicate();
			std::pair<Registers::iterator,bool> p = regs.insert(temp);
			if(p.second) registerCount++;
			else delete temp;
			return p.second;
		}

		virtual	bool remove(NodeRegister& reg){
			Registers::iterator it = regs.find(&reg);
			if(it!=regs.end()){
				delete (*it);
				regs.erase(it);
				registerCount--;
				return true;
			}
			return false;
		}

		virtual	bool search(NodeRegister& reg){
			Registers::iterator it = regs.find(&reg);
			if(it!=regs.end()){
				reg.getRegister().setFields((*it)->getRegister());
			}
			return(it!=regs.end());
		}
		
		/* TODO -> ver para que sirve esto ??? */
		Registers::const_iterator sequenceBegin(){ return regs.begin(); }
		Registers::const_iterator sequenceEnd(){ return regs.end(); }

		void setOffset(unsigned int offset){ this->offset = offset; }
		void setSize(unsigned int size){ this->size = size; }
		void setLevel(unsigned int level){ this->level = level; }		
		void setRegCount(unsigned int registerCount){ this->registerCount = registerCount; }

		unsigned int getOffset()const { return offset; }
		unsigned int getLevel()const { return level; }
		unsigned int getRegCount()const { return registerCount; }
		virtual unsigned int getSize()const { return (size); }		

		/* En caso de overflow el nodo separa un registro marcado como overflow
		   (overflowRegister) y crea un nuevo nodo con los registros particionados
		   AMBOS objectos creados deben ser obteneidos de la clase y utilizados luego
		   de un overflow dado que la clase NO los libera
		*/
		Node* getNewNode()const{ return newNode; }		
		NodeRegister* getOverflowRegister()const{ return overflowRegister; }

		virtual char* toNode(char* data,const RegisterFactory& factory){
			char* temp = data;
			memcpy((void*)&registerCount,temp,sizeof(unsigned int));
			temp+=sizeof(unsigned int);
			memcpy((void*)&level,temp,sizeof(unsigned int));
			temp+=sizeof(unsigned int);
			return temp;
		}
		
		virtual char* toBytes(char* data,const RegisterFactory& factory)const {
			char* temp = data;
			memcpy(temp,&registerCount,sizeof(unsigned int));
			temp += sizeof(unsigned int);
			memcpy(temp,&level,sizeof(unsigned int));
			temp += sizeof(unsigned int);
			return temp;
		}

		virtual NodeRegister* extractFirstRegister(){ 
			Registers::iterator it = regs.begin();
			NodeRegister* nr = dynamic_cast<NodeRegister*>(*it);
			regs.erase(it);
			registerCount--;	
			//Si menor que mitad hay underflow TODO	
			return nr; 
		}

		virtual NodeRegister* extractLastRegister(){ 
			Registers::iterator it = regs.begin();
			while(it!=regs.end())
				it++;
			it--;
			NodeRegister* nr = dynamic_cast<NodeRegister*>(*it);
			regs.erase(it);
			registerCount--;		
			//Si menor que mitad hay underflow TODO
			return nr; 
		}

		static unsigned int peekLevel(char* data){
			return (unsigned int)( *(data+sizeof(unsigned int)) );
		}

		NodeRegister* getFirstRegister(){
			Registers::iterator it = regs.begin();
			return (*it)->duplicate();
		}
		NodeRegister* getLastRegister(){
			Registers::iterator it = regs.end();
			it--;
			return (*it)->duplicate();
		}
		
		/* Inventada solo para poder aplicar polimorfismo con operator << que es friend */
		virtual std::ostream& toOstream(std::ostream& out,std::queue<unsigned int>& offsets)const = 0;
};

}

#endif /* __BPP_NODE_H__ */
