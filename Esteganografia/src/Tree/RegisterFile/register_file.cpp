#include "register_file.h"
#include <vector>

RegisterFile::RegisterFile(const std::string path,const RegisterFactory& factory,unsigned int cellSize)
	: file(path.c_str(),std::fstream::in | std::fstream::out | std::fstream::binary){
	if(!file){
		file.open(path.c_str(),std::fstream::in | std::fstream::out | std::fstream::binary | std::fstream::trunc);
	}

    this->factory = factory.duplicate();
    this->cellSize = cellSize;
}

RegisterFile::~ RegisterFile(){
	delete this->factory;
}

unsigned int RegisterFile::write(Register& reg,unsigned int offset){
	Cell* cell = new Cell(offset);

	char* data = new char[reg.getSize()];
	(*factory)(reg,data);
	cell->setData(data,reg.getSize());
	cell->setDeleted(false);

	if(reg.getSize()>this->cellSize-Cell::getHeaderSize())
		writeChainedCell(*cell);
	else
		writeCell(*cell);

	delete cell;
	return (offset);
}

unsigned int RegisterFile::write(Register& reg){
	unsigned int retOffset;
	Cell* cell = firstFit();
	cell->clearFlags();
	retOffset = write(reg,cell->getOffset());
	delete cell;
	return retOffset;
}

unsigned int RegisterFile::append(Register& data){
	unsigned int currPos = file.tellg();
	file.seekg(0,std::fstream::end);
	unsigned int offset = file.tellg();
	write(data,offset);
	file.seekg(currPos);
	return offset;
}

Cell* RegisterFile::firstFit(){
	bool found=false;
	unsigned int pos=0;
	Cell* cell= new Cell(0);

	/*Celda a celda busco uno donde entre*/
	file.clear();
	file.seekg(0);
	while(!file.eof() && !found){
		Cell* temp = readCellHeader(pos);
		pos += this->cellSize;
		if( (found=(temp->isFree()||temp->isDeleted())) )
			cell->setOffset(temp->getOffset());

		delete temp;
		file.seekg(pos);
	}

	if(!found){
		cell->setOffset(pos);
	}

	return cell;
}

Cell* RegisterFile::readCell(unsigned int offset){
	file.clear();
	file.seekg(offset);
	
	/*No existe la celda*/
	if(file.eof())
		return new Cell(offset);

	Cell* cell = readCellHeader(offset);

	if(!cell->isFree()){
		char* data = new char[cell->getDataSize()];
		file.read(data,cell->getDataSize());
		cell->setData(data,cell->getDataSize());
	}

	return cell;
}

Cell* RegisterFile::readCellHeader(unsigned int offset){
	/* Primero se lee el header */
	file.clear();
	file.seekg(offset);

	if(file.eof())
		return  new Cell(offset);

	char* data = new char[Cell::getHeaderSize()];
	file.read(data,Cell::getHeaderSize());

	Cell* ret = new Cell(offset);
	ret->readHeader(data);
	delete []data;
	return ret;
}

void RegisterFile::writeCell(const Cell& cell){
	file.clear();	
	file.seekp(cell.getOffset());

	char* data = new char[this->cellSize];
	memset(data,0,this->cellSize);
	cell.toBytes(data);
	file.write(data,this->cellSize);

	delete[] data;
}

void RegisterFile::writeCellHeader(const Cell& cell){
	file.seekp(cell.getOffset());

	char* data = new char[Cell::getHeaderSize()];
	cell.writeHeader(data);
	file.write(data,Cell::getHeaderSize());

	delete[] data;
}

Register* RegisterFile::readNext(unsigned int& offset){
	Register* ret=NULL;
	file.clear();
	//unsigned int currPos = file.tellg();
	file.seekg(0,std::fstream::end);
	unsigned int eofPos = file.tellg();
	
	if(offset>=eofPos){
		offset = RF_EOF;
		return ret;
	}

	Cell* cell = readCell(offset);
	if(cell->isChainBegin() && cell->isChained())
		ret = readChainedCell(cell);
	else if(!cell->isChained()){
		ret = (*factory)(cell->getData());
		delete cell;
	}

	offset += cellSize;
	bool correctOffset = false;
	/* La proxima celda no debe estar encadenada o ser el final del archivos */
	while(!correctOffset){
		Cell* next = readCell(offset);
		if(next->isFree() || next->isDeleted() || ( next->isChained() && !next->isChainBegin()))
			offset += cellSize;
		else
			correctOffset = true;

		if(offset>=eofPos){
			correctOffset = true;
			offset = RF_EOF;
		}
		delete next;
	}


	return ret;
}

Register* RegisterFile::read(unsigned int offset){
	Register* ret=NULL;
	Cell* cell = readCell(offset);
	if(cell->isChainBegin() && cell->isChained())
		return readChainedCell(cell);
	else if(!cell->isChained())
		ret = (*factory)(cell->getData());

	delete cell;
	return ret;
}

Register* RegisterFile::readChainedCell(Cell* cell){
	std::vector<Cell*> chunks;
	unsigned int dataSize=0;
	Cell* link = readCell(cell->getNextCell());
	chunks.push_back(cell);
	chunks.push_back(link);
	dataSize += cell->getDataSize() + link->getDataSize();

	while(!link->isChainEnd()){
		link = readCell(link->getNextCell());
		chunks.push_back(link);
		dataSize += link->getDataSize();
	}

	char* data = new char[dataSize];
	char* ptr = data;
	memset(data,0,dataSize);
	for(std::vector<Cell*>::iterator it=chunks.begin();it!=chunks.end();++it){
		memcpy(ptr,(*it)->getData(),(*it)->getDataSize());
		ptr += (*it)->getDataSize();
		delete *it;
	}
	Register* ret = (*factory)(data);
	delete[] data;
	return ret;
}

void RegisterFile::free(unsigned int offset){
	Cell* cell = readCellHeader(offset);
	if(!cell->isFree()){
		cell->setDeleted(true);
		writeCellHeader(*cell);
		if(cell->isChainBegin())
			freeChainedCell(*cell);
	}
	delete cell;
}

void RegisterFile::freeChainedCell(Cell& cell){
	Cell* link = readCell(cell.getNextCell());
	link->setDeleted(true);
	writeCellHeader(*link);

	while(!link->isChainEnd()){
		Cell* next = readCell(link->getNextCell());
		next->setDeleted(true);
		writeCellHeader(*next);
		delete link;
		link = next;
	}
	delete link;
}

void RegisterFile::writeChainedCell(Cell& cell){
	std::list<Cell*> cells;
	cell.split(cells,this->cellSize);
	std::list<Cell*>::iterator it = cells.begin();
	Cell* next=NULL;

	writeCell(**it);
	for(;it!=cells.end();++it){
		next = firstFit();
		(*it)->setNextCell(next->getOffset());
		writeCellHeader(**it);
		delete *it;

		++it;
		if(it!=cells.end()){
			(*it)->setOffset(next->getOffset());
			writeCell(**it);
		}
		--it;
		delete next;
	}
}

std::ostream& RegisterFile::toOstream(std::ostream& out){
	out << "*------Comienzo Register File----------*\n";
	unsigned int pos=0;
	file.seekg(pos);
	while(!file.eof()){
		Cell* cell = readCell(pos);
		out << "\t------------------" << "\n";
		if(cell){
			pos += this->cellSize;
			cell->toOstream(out);

			Register* reg=NULL;
			if(cell->isFree() || cell->isDeleted() || cell->isChained()){
				if(cell->isChainBegin())
					reg = readChainedCell(cell);
				else
					delete cell;
			}else{
				reg = (*factory)(cell->getData());
				delete cell;
			}

			if(reg){
				reg->toOstream(out);
				delete reg;
			}
		}
		out << "\t------------------" << "\n";
		file.seekg(pos);
		file.peek();
	}
	out << "*------Fin Register File----------*\n";
	return out;
}
