#ifndef __ITERATOR_H__
#define __ITERATOR_H__

template <typename T>
class Iterator{
	public:
		Iterator(){}
		virtual ~Iterator(){}

		virtual bool begin()=0;
		virtual bool end()=0;

		virtual Iterator& operator++()=0;
		virtual Iterator& operator--()=0;

		virtual T operator*()=0;
};

#endif /* __ITERATOR_H__ */
