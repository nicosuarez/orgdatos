#ifndef __ITERATOR_OUT_OF_RANGE_H__
#define __ITERATOR_OUT_OF_RANGE_H__

#include "../../Exception/storageException.h"

class IteratorOutOfRange : public StorageException{
    public:
        IteratorOutOfRange(const std::string& amessage) : StorageException(amessage) {
        }
};

#endif /* __ITERATOR_OUT_OF_RANGE__ */

