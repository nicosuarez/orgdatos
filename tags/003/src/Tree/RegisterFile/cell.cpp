#include "cell.h"
#include <cstring>
#include <cmath>

Cell::Cell(unsigned int offset){
	this->offset = offset;
	this->nextCell = -1;
	this->data=NULL;
	this->size=0;
	this->flags=0;
}

Cell::~Cell(){
	if(this->data)
		delete[] this->data;
}


void Cell::readHeader(char* data){
	memcpy(&this->flags,data,sizeof(flags));
	data+=sizeof(flags);
	memcpy(&this->size,data,sizeof(size));
	data+=sizeof(size);
	memcpy(&this->nextCell,data,sizeof(nextCell));
}

void Cell::writeHeader(char* data)const{
	memcpy(data,&this->flags,sizeof(flags));
	data+=sizeof(flags);
	memcpy(data,&this->size,sizeof(size));
	data+=sizeof(size);
	memcpy(data,&this->nextCell,sizeof(nextCell));
}

char* Cell::toBytes(char* data)const{
	writeHeader(data);
	data += Cell::getHeaderSize();

	if(this->data){
		memcpy(data,this->data,this->size);
		data += size;
	}

	return data;
}

void Cell::setData(char* data,unsigned int size){
	if(this->data)
		delete[] this->data;
	this->data=data;
	this->size = size;
	this->flags |= USED;
}

void Cell::split(std::list<Cell*>& cells,unsigned int cellSize){
	char* ptr = data;
	unsigned int chunkSize = cellSize-Cell::getHeaderSize();
	unsigned int cellNum = this->size/(cellSize-Cell::getHeaderSize());
	if(this->size%(cellSize-Cell::getHeaderSize()))
		cellNum++;

	for(unsigned int c=0;c<cellNum;c++){
		char* chunk = new char[chunkSize];
		memset(chunk,0,chunkSize);
		if(c<cellNum-1)
			memcpy(chunk,ptr,chunkSize);
		else
			memcpy(chunk,ptr,this->size-(chunkSize*c));


		Cell* newCell = new Cell(this->offset);
		newCell->setData(chunk,chunkSize);
		newCell->setChained(true);

		if(c==0)
			newCell->setChainBegin(true);
		else if(c==cellNum-1)
			newCell->setChainEnd(true);

		ptr+=chunkSize;
		cells.push_back(newCell);
	}
}

void Cell::setDeleted(bool state){
	if(state)
		this->flags |= Cell::IS_DELETED;
	else
		this->flags &= (~Cell::IS_DELETED);
}

void Cell::setChained(bool state){
	if(state)
		this->flags |= Cell::IS_CHAINED;
	else
		this->flags &= (~Cell::IS_CHAINED);
}

void Cell::setChainBegin(bool state){
	if(state)
		this->flags |= Cell::IS_CHAIN_BEGIN;
	else
		this->flags &= (~Cell::IS_CHAIN_BEGIN);
}

void Cell::setChainEnd(bool state){
	if(state)
		this->flags |= Cell::IS_CHAIN_END;
	else
		this->flags &= (~Cell::IS_CHAIN_END);
}

std::ostream& Cell::toOstream(std::ostream& out){
	out << "\t--Header Data--" << "\n";

	out << "\tFlags: UD|DL|IC|CB|CE|R|R|R " << "\n";
	out << "\t       ";
	for(char c=0;c<8;c++){
		char mask=0x00 + (char)pow(2,c);
		if(flags&mask)
			out << "ON";
		else
			out << "OFF";

		if(c<7)
			out << "|";
	}
	out << "\n";

	out << "\tData Size: " << size << "\n";
	out << "\tNext Cell: " << nextCell << "\n";
	out << "\t--Fin Header Data--" << "\n";
	return out;
}
