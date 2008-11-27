#ifndef INTRUDER_H_
#define INTRUDER_H_

#include "Date.h"
#include <string>
#include <vector>

class Intruder: public Date {
public:
	Intruder();
	virtual ~Intruder();
	void SetDate(Date date);
	void AddStr(std::string str);
	void Deserialize(std::string str);
	virtual void /*std::ostream&*/ toOstream(/*std::ostream& out*/)const;

private:
	Date date;
	std::vector<std::string> strings;
};

#endif /* INTRUDER_H_ */
