	#include "ImgRegistry.h"

	ImgRegistry::~ImgRegistry(){}
	ImgRegistry::ImgRegistry():ExtensibleRelativeRegistry(){};

	ExtensibleRelativeRegistry* ImgRegistry::RegCreate(){
		return new ImgRegistry();
	}

    ID_type ImgRegistry::getIDDir() const
    {
        return idDir;
    }

    void ImgRegistry::setIDDir(ID_type idDir)
    {
        this->idDir = idDir;
    }

    ID_type ImgRegistry::getIDName() const
    {
        return idName;
    }

    void ImgRegistry::setIDName(ID_type idName)
    {
        this->idName = idName;
    }

    ID_type ImgRegistry::getIDFirstFreeSpace() const
    {
        return idFirstFreeSpace;
    }

    void ImgRegistry::setIDFirstFreeSpace(ID_type idFirstFreeSpace)
    {
        this->idFirstFreeSpace = idFirstFreeSpace;
    }

    ID_type ImgRegistry::getIDLastFreeSpace() const
    {
        return idLastFreeSpace;
    }

    void ImgRegistry::setIDLastFreeSpace(ID_type idLastFreeSpace)
    {
        this->idLastFreeSpace = idLastFreeSpace;
    }

    ID_type ImgRegistry::getPtrMsgList() const
    {
        return ptrMsgList;
    }

    void ImgRegistry::setPtrMsgList(ID_type ptrMsgList)
    {
        this->ptrMsgList = ptrMsgList;
    }

    unsigned long ImgRegistry::getSizeMaxFreeSpace() const
    {
        return sizeMaxFreeSpace;
    }

    void ImgRegistry::setSizeMaxFreeSpace(unsigned long  sizeMaxFreeSpace)
    {
        this->sizeMaxFreeSpace = sizeMaxFreeSpace;
    }

    Date ImgRegistry::getDate() const
    {
        return date;
    }

    void ImgRegistry::setDate(Date& date)
    {
        this->date = date;
    }

    unsigned int ImgRegistry::GetSize() const
    {
    	size_t extRel=ExtensibleRelativeRegistry::GetSize();
    	return (extRel+ sizeof(idDir) + sizeof(idFirstFreeSpace)+sizeof(idLastFreeSpace)+
    			sizeof(idName)+ sizeof(ptrMsgList) + sizeof(sizeMaxFreeSpace)+date.getSize());
    }

    char* ImgRegistry::Serialize() const
    {
    	char *buffer=ExtensibleRelativeRegistry::Serialize();
    	buffer = (char*)realloc(buffer,GetSize());
    	unsigned int pos = ExtensibleRelativeRegistry::GetSize();
    	AddToSerialization(buffer, &idDir, pos, sizeof(this->idDir));
		pos += sizeof(this->idDir);
		AddToSerialization(buffer, &idName, pos, sizeof(idName));
		pos += sizeof(this->idName);
		AddToSerialization(buffer, &idFirstFreeSpace, pos, sizeof(this->idFirstFreeSpace));
		pos += sizeof(this->idFirstFreeSpace);
		AddToSerialization(buffer, &idLastFreeSpace, pos, sizeof(idLastFreeSpace));
		pos += sizeof(this->idLastFreeSpace);
		AddToSerialization(buffer, &ptrMsgList, pos, sizeof(ptrMsgList));
		pos+=sizeof(this->ptrMsgList);
		unsigned int year=date.getYear();
		unsigned int month=date.getMonth();
		unsigned int day=date.getDay();
		unsigned int hour=date.getHour();
		unsigned int min=date.getMin();
		unsigned int seg=date.getSeg();
		AddToSerialization(buffer, &year, pos, sizeof(date.getYear()));
		pos += sizeof(this->date.getYear());
		AddToSerialization(buffer, &month, pos, sizeof(date.getMonth()));
		pos += sizeof(this->date.getMonth());
		AddToSerialization(buffer, &day, pos, sizeof(date.getDay()));
		pos+=sizeof(this->date.getDay());
		AddToSerialization(buffer, &hour, pos, sizeof(this->date.getHour()));
		pos += sizeof(this->date.getHour());
		AddToSerialization(buffer, &min, pos, sizeof(date.getMin()));
		pos+=sizeof(this->date.getMin());
		AddToSerialization(buffer, &seg, pos, sizeof(this->date.getSeg()));
		pos += sizeof(this->date.getSeg());
		return buffer;
    }
