#ifndef __TREE_H__
#define __TREE_H__

#include <iostream>
#include "tree_iterator.h"

class Tree{
	public:
		Tree(){}
		virtual ~Tree(){}

		virtual bool insert(const Register& reg)=0;
		virtual bool remove(const Register& reg)=0;
		virtual bool search(Register& reg)=0;
		virtual bool modify(const Register& reg)=0;
		virtual TreeIterator* getIterator(const Register& reg)=0;
		virtual TreeIterator* getFirst()=0;
		virtual TreeIterator* getLast()=0;
		virtual std::ostream& toOstream(std::ostream& out)=0;
};

#endif /* __TREE_H__ */
