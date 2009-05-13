#ifndef __REGISTER_FILE_H__
#define __REGISTER_FILE_H__

#include <fstream>
#include <map>
#include <string.h>
#include "cell.h"
#include "../Common/register_factory.h"
#include "../Common/register.h"

class RegisterFile{
	private:
		std::fstream file;
		RegisterFactory* factory;
		unsigned int cellSize;

	public:
		static const unsigned int RF_EOF = -1;

		RegisterFile(const std::string,const RegisterFactory& factory,unsigned int cellSize);
		~RegisterFile();

		unsigned int write(Register& data);
		unsigned int write(Register& data,unsigned int offset);
		unsigned int append(Register& data);

		Register* read(unsigned int offset);
		Register* readNext(unsigned int& offset);
		void free(unsigned int offset);

		std::ostream& toOstream(std::ostream& out);

	private:
		Cell* firstFit();
		void writeCell(const Cell& cell);
		Cell* readCell(unsigned int offset);
		Cell* readCellHeader(unsigned int offset);
		void writeCellHeader(const Cell& cell);

		void writeChainedCell(Cell& cell);
		Register* readChainedCell(Cell* cell);
		void freeChainedCell(Cell& cell);
};

#endif /* __REGISTER_FILE_H__ */
