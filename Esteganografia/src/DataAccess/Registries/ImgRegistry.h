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

		ID_type GetIDImagePath() const;
		void SetIDImagePath(ID_type idImgPath);

		ID_type GetPtrMsgList() const;

		void SetPtrMsgList(ID_type ptrMsgList);

		Date GetDate() const;
		
		void SetDate(Date& date);

		unsigned int GetSize() const;

		char* Serialize() const;

		void Deserialize(const char* buffer, unsigned int length);

  private:
	    ID_type idImgPath;
	    ID_type ptrMsgList;
	    Date date;
};


#endif /* IMGREGISTRY_H_ */
