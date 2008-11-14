#ifndef __TREE_ITERATOR_H__
#define __TREE_ITERATOR_H__

#include "register_pack.h"

class TreeIterator{
	public:
		TreeIterator(){}
		virtual ~TreeIterator(){}

		virtual bool EndOfFile()=0;
		virtual bool BeginOfFile()=0;
		virtual TreeIterator* sig()=0;
		virtual TreeIterator* ant()=0;		
		virtual Register* getRegister()=0;
};

#endif /* __TREE_ITERATOR_H__ */
