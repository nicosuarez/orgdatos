#include "ListImgRegistry.h"

ListImgRegistry::ListImgRegistry():ListRegistry()
{
	this->idImage = 0;
	this->offsetImg = 0;
	this->sizePartitionMsg = 0;
}

ListImgRegistry:: ListImgRegistry( ID_type idImage, unsigned long offsetImg, 
								   unsigned long sizePartitionMsg) : ListRegistry()
{
	this->idImage = idImage;
	this->offsetImg = offsetImg;
	this->sizePartitionMsg = sizePartitionMsg;
}

ListImgRegistry::~ListImgRegistry()
{
}


ExtensibleRelativeRegistry* ListImgRegistry::Create()
{
	return new ListImgRegistry();
}

ID_type ListImgRegistry::GetIDImage() const
{
	return idImage;
}
	
unsigned long ListImgRegistry::GetOffsetImg() const
{
	return offsetImg;
}

unsigned long ListImgRegistry::GetSizePartitionMsg() const
{
	return sizePartitionMsg;
}

void ListImgRegistry::SetIDImage(ID_type idImage)
{
	this->idImage = idImage;
}

void ListImgRegistry::SetOffsetImg(unsigned long offsetImg)
{
	this->offsetImg = offsetImg;
}

void ListImgRegistry::SetSizePartitionMsg(unsigned long sizePartitionMsg)
{
	this->sizePartitionMsg = sizePartitionMsg;
}

unsigned int ListImgRegistry::GetSize() const
{
	return (ListRegistry::GetSize() + sizeof(idImage) + sizeof(offsetImg) + sizeof(sizePartitionMsg));
}

char* ListImgRegistry::Serialize() const
{
	char *buffer = ListRegistry::Serialize();
	unsigned int pos = ListRegistry::GetSize();
	
	AddToSerialization(buffer, &idImage, pos, sizeof(idImage));
	pos += sizeof(idImage);
	AddToSerialization(buffer, &offsetImg, pos, sizeof(offsetImg));
	pos += sizeof(offsetImg);
	AddToSerialization(buffer, &sizePartitionMsg, pos, sizeof(sizePartitionMsg));
	
	return buffer;
}

void ListImgRegistry::Deserialize(const char* buffer, unsigned int length)
{
	ListRegistry::Deserialize(buffer, length);
	unsigned int pos = ListRegistry::GetSize();
	
	GetFromSerialization(buffer, &idImage, pos, sizeof(idImage));
	pos += sizeof(idImage);
	GetFromSerialization(buffer, &offsetImg, pos, sizeof(offsetImg));
	pos += sizeof(offsetImg);
	GetFromSerialization(buffer, &sizePartitionMsg, pos, sizeof(sizePartitionMsg));
}

