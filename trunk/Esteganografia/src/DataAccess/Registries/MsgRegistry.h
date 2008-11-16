#ifndef MSGREGISTRY_H_
#define MSGREGISTRY_H_

#include "ExtensibleRelativeRegistry.h"

class MsgRegistry : public ExtensibleRelativeRegistry
{
public:
	MsgRegistry();
	
	MsgRegistry(ID_type ptrImgList);
	
	virtual ~MsgRegistry();
	
	static ExtensibleRelativeRegistry* Create();
	
	ID_type GetPtrImgList() const;
	
	void SetPtrImgList(ID_type ptrImgList);
	
	unsigned int GetSize() const;
	
	char* Serialize() const;

	void Deserialize(const char* buffer, unsigned int length);
	
private:
	ID_type ptrImgList;
	
    /* Allocation and copy constructor are private to prevent errors. */
    MsgRegistry(const MsgRegistry &Reg);
    MsgRegistry& operator=(const MsgRegistry &reg);
	
};

#endif /*MSGREGISTRY_H_*/
