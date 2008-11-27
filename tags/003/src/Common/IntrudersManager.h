#ifndef __INTRUDERSMANAGER_H_
#define __INTRUDERSMANAGER_H_

#include <string>
#include <vector>
#include "Intruder.h"
#include "StrToken.h"

typedef std::vector<Intruder> tVecinstrud;
class IntrudersManager {
public:
	IntrudersManager();
	virtual ~IntrudersManager();
	static tVecinstrud getIntruders();
	static bool ExistNewIntruder();
	static void writeIntruder(tVecStr vStr);
};

#endif /* __INTRUDERSMANAGER_H_ */
