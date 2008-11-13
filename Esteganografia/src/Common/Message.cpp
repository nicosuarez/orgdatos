#include "Message.h"

using namespace std;

Message::Message(){
	this->hiddenSize = 0;
	this->messageID = 0;
}

Message::Message(string filePath)
{
	this->filePath = filePath;
	this->hiddenSize = 0;
	this->messageID = 0;
}
/* -------------------------------------------------------------------------- */
Message::~Message(){

}
/* -------------------------------------------------------------------------- */


long Message::GetHiddenSize() const
{
	return this->hiddenSize;
}
/* -------------------------------------------------------------------------- */


void Message::SetHiddenSize(long size)
{
	this->hiddenSize = size;
}
/* -------------------------------------------------------------------------- */


long Message::IncHiddenSize(long size)
{
	this->SetHiddenSize(this->hiddenSize + size);
	return this->hiddenSize;
}
/* -------------------------------------------------------------------------- */


const char* Message::GetFilePath() const{

	return  this->filePath.c_str();
}
/* -------------------------------------------------------------------------- */

void Message::SetFilePath(std::string st){
	this->filePath=st;
}
/* -------------------------------------------------------------------------- */

long Message::GetSize() const
{
	long pos = 0;
	ifstream fin(this->filePath.c_str());
	if(fin)
	{
	   fin.seekg(0, ios::end);
	   pos = fin.tellg();
	}
	fin.close();
	return pos;
}
/* -------------------------------------------------------------------------- */


void Message::SetId(unsigned long newId)
{
	this->messageID = newId;
}

/* -------------------------------------------------------------------------- */
unsigned long Message::GetId() const
{
	return this->messageID;
}
