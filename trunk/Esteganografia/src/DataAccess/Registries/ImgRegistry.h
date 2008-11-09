/*
 * ImgRegistry.h
 *
 *  Created on: 08/11/2008
 *      Author: malcha
 */

#ifndef IMGREGISTRY_H_
#define IMGREGISTRY_H_

#include "ExtensibleRelativeRegistry.h"
#include "../../Common/Date.h"

class ImgRegistry:ExtensibleRelativeRegistry{

	ImgRegistry();
	~ImgRegistry();

    ID_type getIDDir() const;

    void setIDDir(ID_type idDir);

    ID_type getIDName() const;

    void setIDName(ID_type idName);

    ID_type getIDFirstFreeSpace() const;
    void setIDFirstFreeSpace(ID_type idFirstFreeSpace);

    ID_type getIDLastFreeSpace() const;
    void setIDLastFreeSpace(ID_type idLastFreeSpace);

    ID_type getPtrMsgList() const;

    void setPtrMsgList(ID_type ptrMsgList);

    unsigned long getSizeMaxFreeSpace() const;

    void setSizeMaxFreeSpace(unsigned long  sizeMaxFreeSpace);

    Date getDate() const;

    void setDate(Date& date);

    unsigned int GetSize() const;

    char* Serialize() const;

  private:
    ID_type idDir;
    ID_type idName;
    ID_type idFirstFreeSpace;
    ID_type idLastFreeSpace;
    ID_type ptrMsgList;
    unsigned long sizeMaxFreeSpace;
    Date date;
};


#endif /* IMGREGISTRY_H_ */
