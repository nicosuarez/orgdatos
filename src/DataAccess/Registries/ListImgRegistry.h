#ifndef LISTIMGREGISTRY_H_
#define LISTIMGREGISTRY_H_

#include "ListRegistry.h"

class ListImgRegistry : public ListRegistry
{
public:
	ListImgRegistry();
	
	ListImgRegistry( ID_type idImage, unsigned long offsetImg, unsigned long sizePartitionMsg);
	
	virtual ~ListImgRegistry();
	
	static ExtensibleRelativeRegistry* Create();
	
	ID_type GetIDImage() const;
	
	unsigned long GetOffsetImg() const;
	
	unsigned long GetSizePartitionMsg() const;
	
    unsigned int GetSize() const;
	
	void SetIDImage(ID_type idImage);
	
	void SetOffsetImg(unsigned long offsetImg);
	
	void SetSizePartitionMsg(unsigned long sizePartitionMsg);
	
	char* Serialize() const;
	
	void Deserialize(const char* buffer, unsigned int length);
	
private:
	ID_type idImage;
	unsigned long offsetImg;
	unsigned long sizePartitionMsg;
	
    /* Allocation and copy constructor are private to prevent errors. */
	ListImgRegistry(const ListImgRegistry &Reg);
	ListImgRegistry& operator=(const ListImgRegistry &reg);
};

#endif /*LISTIMGREGISTRY_H_*/
