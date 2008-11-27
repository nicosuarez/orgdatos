#ifndef __TREE_ITERATOR_H__
#define __TREE_ITERATOR_H__

#include "../Common/register.h"
#include "../Index/iterator.h"
#include <utility>

typedef std::pair<Register*,Register*> key_val;

class TreeIterator : public Iterator<key_val>{
	public:
		TreeIterator(){}
		TreeIterator(const TreeIterator& it){}
		virtual ~TreeIterator(){}

		virtual bool begin()=0;
		virtual bool end()=0;

		virtual Iterator<key_val>& operator++()=0;
		virtual Iterator<key_val>& operator--()=0;

		virtual key_val operator*()=0;

		virtual const Register& peekKey()=0;
		virtual const Register& peekValue()=0;

		virtual Register* getKey()=0;
		virtual Register* getValue()=0;

		virtual bool operator==(const TreeIterator& it)=0;
};

#endif /* __TREE_ITERATOR_H__ */
