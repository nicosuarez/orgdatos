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

class ImgRegistry:public ExtensibleRelativeRegistry{
	public:
		ImgRegistry();
		~ImgRegistry();

		static ExtensibleRelativeRegistry* RegCreate();

		ID_type getIDFirstFreeSpace() const;
		void setIDFirstFreeSpace(ID_type idFirstFreeSpace);

		ID_type getIDLastFreeSpace() const;
		void setIDLastFreeSpace(ID_type idLastFreeSpace);

		ID_type getPtrMsgList() const;

		void setPtrMsgList(ID_type ptrMsgList);

		unsigned long getSizeMaxFreeSpace() const;

		void setSizeMaxFreeSpace(unsigned long  sizeMaxFreeSpace);

		Date getDate() const;
		
		unsigned long getTotalFreeSpace() const;
		
		void setTotalFreeSpace(unsigned long totalFreeSapce);
		
		void setDate(Date& date);

		unsigned int GetSize() const;

		char* Serialize() const;

		void Deserialize(const char* buffer, unsigned int length);

  private:

    ID_type idFirstFreeSpace;
    ID_type idLastFreeSpace;
    ID_type ptrMsgList;
    unsigned long sizeMaxFreeSpace;
    unsigned long totalFreeSpace;
    Date date;
};


#endif /* IMGREGISTRY_H_ */
