	#include "ImgRegistry.h"

	ImgRegistry::~ImgRegistry()
	{
		this->idImgPath = 0;
	    this->ptrMsgList = NULL;
	    this->ptrFreeSpaceList = NULL;
	}
	
	ImgRegistry::ImgRegistry():ExtensibleRelativeRegistry(){};

	ExtensibleRelativeRegistry* ImgRegistry::Create()
	{
		return new ImgRegistry();
	}

    ID_type ImgRegistry::GetIDImagePath() const
    {
        return idImgPath;
    }

    void ImgRegistry::SetIDImagePath(ID_type idImgPath)
    {
        this->idImgPath = idImgPath;
    }

    ID_type ImgRegistry::GetPtrFreeSpaceList() const
    {
        return ptrFreeSpaceList;
    }

    void ImgRegistry::SetPtrFreeSpaceList(ID_type ptrFreeSpaceList)
    {
        this->ptrFreeSpaceList = ptrFreeSpaceList;
    }
    
    ID_type ImgRegistry::GetPtrMsgList() const
    {
        return ptrMsgList;
    }

    void ImgRegistry::SetPtrMsgList(ID_type ptrMsgList)
    {
        this->ptrMsgList = ptrMsgList;
    }

    Date ImgRegistry::GetDate() const
    {
        return date;
    }

    void ImgRegistry::SetDate(Date& date)
    {
        this->date = date;
    }

    unsigned int ImgRegistry::GetSize() const
    {
    	size_t extRel=ExtensibleRelativeRegistry::GetSize();
    	return (extRel + sizeof(idImgPath) + sizeof(ptrMsgList) +
    			sizeof(ptrFreeSpaceList) + date.getSize());
    }

    char* ImgRegistry::Serialize() const
    {
    	char *buffer=ExtensibleRelativeRegistry::Serialize();
    	unsigned int pos = ExtensibleRelativeRegistry::GetSize();
    	AddToSerialization(buffer, &idImgPath, pos, sizeof(this->idImgPath));
		pos += sizeof(this->idImgPath);
		AddToSerialization(buffer, &ptrMsgList, pos, sizeof(ptrMsgList));
		pos+=sizeof(this->ptrMsgList);
		AddToSerialization(buffer, &ptrFreeSpaceList, pos, sizeof(ptrFreeSpaceList));
		pos+=sizeof(this->ptrFreeSpaceList);
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

    void ImgRegistry::Deserialize(const char* buffer, unsigned int length){
          ExtensibleRelativeRegistry::Deserialize(buffer, length);

          unsigned int pos = ExtensibleRelativeRegistry::GetSize();
          GetFromSerialization(buffer, &idImgPath, pos, sizeof(idImgPath));
          pos += sizeof(this->idImgPath);
          GetFromSerialization(buffer, &ptrMsgList, pos, sizeof(ptrMsgList));
          pos+=sizeof(this->ptrMsgList);
          GetFromSerialization(buffer, &ptrFreeSpaceList, pos, sizeof(ptrFreeSpaceList));
          pos+=sizeof(this->ptrFreeSpaceList);
          unsigned int year=date.getYear();
          unsigned int month=date.getMonth();
          unsigned int day=date.getDay();
          unsigned int hour=date.getHour();
          unsigned int min=date.getMin();
          unsigned int seg=date.getSeg();
          GetFromSerialization(buffer, &year, pos, sizeof(date.getYear()));
          pos += sizeof(this->date.getYear());
          GetFromSerialization(buffer, &month, pos, sizeof(date.getMonth()));
          pos += sizeof(this->date.getMonth());
          GetFromSerialization(buffer, &day, pos, sizeof(date.getDay()));
          pos+=sizeof(this->date.getDay());
          GetFromSerialization(buffer, &hour, pos, sizeof(this->date.getHour()));
          pos += sizeof(this->date.getHour());
          GetFromSerialization(buffer, &min, pos, sizeof(date.getMin()));
          pos+=sizeof(this->date.getMin());
          GetFromSerialization(buffer, &seg, pos, sizeof(this->date.getSeg()));
          Date d(year,month,day,hour,min,seg);
          this->date=d;
          pos += sizeof(this->date.getSeg());
          
    }

