#include "lzss.h"
#include <stdio.h>
#include <math.h>
#include "../Common/Exception/eFile.h"

using namespace std;

Lzss::Lzss() :
	bitsLong(getCantBitsLong()), bitsPos(getCantBitsPos()) {
}

Lzss::~Lzss() {
}
void Lzss::save(ostream* fp,unsigned char& lastChar, unsigned int& emptyBits,
				 unsigned int valueToemptyBits,unsigned char c){
	 emptyBits = valueToemptyBits;
	 fp->write((char*)&lastChar,sizeof(char));
	 lastChar=c;
}
void Lzss::compress(const char* toCompress, const char* temporaryFile)  {
	vector<unsigned char> ans;
	unsigned int emptyBits = 0;
	this->buffer.clear();
	unsigned int posMatch, longMatch;
	unsigned char lastChar=0x00;
	ifstream fpOrigin(toCompress,ios::in | ios::binary);
	if(!fpOrigin.good())
		throw eFile(toCompress);
	ofstream fpTarget(temporaryFile, ios::binary| ios::out| ios::trunc);
	if (!fpTarget.good())
		throw eFile(temporaryFile);
	writeVarLong(&fpOrigin,&fpTarget);
	readFile(fpOrigin, Lzss::sizeWin);
	while (this->windows.size() > 0) {
		posMatch = 0;
		longMatch = 0;
		char charComp;
		int currPos = this->buffer.size() - 1;
		unsigned int currPosMatch, currLongMatch = 0;
		for (vector<unsigned char>::iterator it = this->buffer.begin(); it
				!= this->buffer.end(); it++) {
			if (*it == windows[0]) {
				currPosMatch = currPos;
				currLongMatch++;
				bool endMatch = false;
				while (endMatch == false) {
					if ((currLongMatch < this->windows.size()) && (currPos - 1
							>= 0) && (currLongMatch < Lzss::lMax))
						charComp = this->buffer[this->buffer.size() - currPos];
					else if ((currLongMatch < this->windows.size())
							&& (currLongMatch < Lzss::lMax))
						charComp = windows[(currPos) * (-1)];
					else
						endMatch = true;
					if ((charComp == windows[currLongMatch]) && (!endMatch))
						currLongMatch++;
					else
						endMatch = true;
					currPos--;
				}
				if ((longMatch < currLongMatch)
						&& (currLongMatch >= Lzss::lMin)) {
					longMatch = currLongMatch;
					posMatch = currPosMatch;
				}
				currLongMatch = 0;
				currPos = currPosMatch;
			}
			currPos--;
		}
		unsigned int readit;
		if (longMatch >= Lzss::lMin) {

			insertCodePosLong(longMatch, posMatch, &fpTarget,&lastChar, emptyBits);
			//avanza el buffer
			for (unsigned int i = 0; i < longMatch; i++) {
				this->buffer.push_back(windows[i]);
				if (this->buffer.size() > Lzss::sizeBuffer) {
					//fpTarget<< *this->buffer.begin(); AntiTEST
					this->buffer.erase(this->buffer.begin());
				}
			}
			readit = longMatch;
		} else {
			insertChar(windows[0], &fpTarget,&lastChar, emptyBits);
			this->buffer.push_back(windows[0]);
			if (this->buffer.size() > Lzss::sizeBuffer) {
				//fpTarget << *this->buffer.begin(); AntiTEST
				this->buffer.erase(this->buffer.begin());
			}
			readit = 1;
		}
		readFile(fpOrigin, readit);
		for (unsigned int i = 0; i < readit; i++)
			this->windows.erase(this->windows.begin());
	}
	//lastChar=lastChar<<emptyBits;
	if (emptyBits!=0)
		fpTarget<<lastChar;

	fpOrigin.close();
	fpTarget.close();
}

void Lzss::insertCodePosLong(unsigned int longMatch, unsigned int posMatch,
			ostream* fp,unsigned char* lastChar, unsigned int& emptyBits) {
	unsigned char bit = 0x00;
	unsigned char aux;
	if (emptyBits == 0){
		emptyBits = 8;
		*lastChar=0x00;
	}
	bit = bit << emptyBits - 1;
	*lastChar = *lastChar | bit;
	emptyBits--;
	if (emptyBits == 0)
		save(fp,*lastChar,emptyBits);
	aux = (unsigned char) (longMatch - Lzss::lMin);
	aux = aux << 8 - this->bitsLong;
	aux = aux >> 8 - emptyBits;
	*lastChar = *lastChar | aux;
	if (this->bitsLong <= emptyBits)
		emptyBits -= this->bitsLong;
	else {
		save(fp,*lastChar,emptyBits,emptyBits,(unsigned char) (longMatch - Lzss::lMin));
		*lastChar = *lastChar << ((unsigned int)8 - this->bitsLong) + emptyBits;
		emptyBits = (8 - this->bitsLong) + emptyBits;
	}
	if (emptyBits == 0)
		save(fp,*lastChar,emptyBits);
	aux = (unsigned char) posMatch;
	aux = aux << 8 - this->bitsPos;
	aux = aux >> 8 - emptyBits;
	*lastChar = *lastChar | aux;
	//ans->push_back(lastChar);
	if (this->bitsPos <= (int)emptyBits)
		emptyBits = emptyBits - this->bitsPos;
	else {
		save(fp,*lastChar,emptyBits,emptyBits,(unsigned char) posMatch);
		*lastChar = *lastChar << (8 - this->bitsPos) + emptyBits;
		emptyBits = (8 - this->bitsPos) + emptyBits;
	}
	if (emptyBits==0)
		save(fp,*lastChar,emptyBits);
}

void Lzss::insertChar(char c, ostream* fp,unsigned char* lastChar,
	unsigned int& emptyBits) {
	unsigned char auxC = c;
	unsigned char bit = 0x01;
	if (emptyBits > 0) {
		bit = bit << emptyBits - 1;
		auxC = auxC >> 8 - (emptyBits - 1);
		auxC = bit | auxC;
		c = c << emptyBits - 1;
		emptyBits--;
		*lastChar = (*lastChar)| auxC;
		save(fp,*lastChar,emptyBits,emptyBits,c);
		if (emptyBits==0)
			save(fp,*lastChar,emptyBits);
	} else {
		bit = bit << 7;
		auxC = auxC >> 1;
		*lastChar = bit | auxC;
		c = c << 7;
		save(fp,*lastChar,emptyBits,7,c);
	}
}

void Lzss::uncompress(const char* origin, const char* target) {
	unsigned char lastChar;
	unsigned int nBit = 8;
	unsigned int readChar = 1;
	if(strcmp(origin,target)==0)
		throw eFile("el archivo destino es igual al de origen" );
	ifstream fpOri(origin,ios::binary| ios::in);
	if(!fpOri.good())
		throw eFile(origin);
	ofstream fpTarget(target, ios::binary| ios::out| ios::trunc);
	if (!fpTarget.good())
		throw eFile(target);
	unsigned long cant=readVarLong(&fpOri);
	fpOri.read((char*)&lastChar,sizeof(char));
	this->buffer.clear();
	for (unsigned long i = 0; i < cant; i += (unsigned long)readChar) {
		unsigned int flag = getFlag(&fpOri, nBit, lastChar);
		if (flag == 1) {
			unsigned char c=getChar(&fpOri, nBit, lastChar);
			fpTarget.write((char*)&c,sizeof(char));
			readChar = 1;
		} else
			readChar = getPosLong(&fpOri,&fpTarget, nBit, lastChar);
	}
	fpOri.close();
	fpTarget.close();
}

unsigned int Lzss::getFlag(ifstream* fpOrigin,unsigned int& nBit,
							unsigned char& lastChar){
	if (nBit == 0) {
		nBit = 8;
		(*fpOrigin).read((char*)&lastChar,sizeof(char));
	}
	unsigned char c = lastChar;
	c = c << 8 - (nBit);
	c = c >> 7;
	if (nBit < 1) {
		nBit = 8;
		(*fpOrigin).read((char*)&lastChar,sizeof(char));
	} else
		nBit--;
	return (unsigned int) c;
}
char Lzss::getChar (ifstream* fpOrigin,unsigned int& nBit,
					unsigned char& lastChar){
	unsigned char c = lastChar;
	(*fpOrigin).read((char*)&lastChar,sizeof(char));
	if (nBit != 8) {
		c = c << 8 - nBit;
		unsigned char aux = lastChar;
		aux = aux >> nBit;
		c = c | aux;
	}
	this->buffer.push_back(c);
	if (this->buffer.size() > Lzss::sizeBuffer)
		this->buffer.erase(this->buffer.begin());
	return (char)c;
}
unsigned int Lzss::getPosLong (ifstream* fpOrigin,ofstream* fpTarget,
						unsigned int& nBit,unsigned char& lastChar){
	unsigned int pos,lMatch;
	unsigned char c = lastChar;
	c = c << 8 - nBit;
	c = c >> 8 - this->bitsLong;
	if (nBit < this->bitsLong) {
		(*fpOrigin).read((char*)&lastChar,sizeof(char));
		unsigned char aux = lastChar;
		aux = aux >> 8 - (this->bitsLong - nBit);
		nBit = 8 - (this->bitsLong - nBit);
		c = c | aux;
	} else {
		nBit -= bitsLong;
	}
	lMatch = (unsigned int) c + Lzss::lMin;
	if (nBit == 0) {
		(*fpOrigin).read((char*)&lastChar,sizeof(char));
		nBit = 8;
	}
	c = lastChar;
	c = c << 8 - nBit;
	c = c >> 8 - this->bitsPos;
	if ((int)nBit < this->bitsPos) {
		(*fpOrigin).read((char*)&lastChar,sizeof(char));
		unsigned char aux = lastChar;
		aux = aux >> 8 - (this->bitsPos - nBit);
		nBit = 8 - (this->bitsPos - nBit);
		c = c | aux;
	} else {
		nBit -= bitsPos;
	}
	pos = (unsigned int) c;
	if (nBit == 0) {
		nBit = 8;
		(*fpOrigin).read((char*)&lastChar,sizeof(char));
	}
	/*tmp*/
	vector<unsigned char>::iterator it = buffer.begin();
	vector<unsigned char>::reverse_iterator itr = buffer.rbegin();
	/*Fin tmp*/
	for (unsigned int i = 0; i < lMatch; i++) {
		char copy = this->buffer[buffer.size() - (1 + pos)];
		this->buffer.push_back(copy);
		fpTarget->write(&copy,sizeof(char));
		if (this->buffer.size() > Lzss::sizeBuffer)
			this->buffer.erase(buffer.begin());
	}
	return lMatch;
}

void Lzss::readFile(ifstream& fp, unsigned int cant) {
	char* read = new char[cant+1];
	fp.get(read, (cant+1) * sizeof(char), EOF);
	unsigned int countChar = fp.gcount();
	for (int i = 0; i < (int) countChar; i++)
		this->windows.push_back(read[i]);
	delete read;
}

//devuelve la cantidad de bytes leido , llena valor
unsigned long Lzss::readVarLong(ifstream* fp) {
	unsigned long ans;
	fp->read((char*)&ans,sizeof(unsigned long));
	return ans;
	/*
	unsigned long long intaux,valor=0;
	unsigned char aux=0x00;
	unsigned char prox;
	unsigned char masc = 0x7F;
	int cont = 0;
	bool last = false;
	while (last == false) {
		fp->read((char*)&aux,sizeof(char));
		prox = aux >> 7;
		if (prox == 0)
			last = true;
		intaux = aux & masc; //le quita el primer bit
		intaux = intaux << (7 * cont);
		valor = valor + intaux;
		cont++;
	}
	return valor;*/
}

void Lzss::writeVarLong(ifstream* fp, ofstream* fpTarget) {
	unsigned long begin, end, size;
	begin = fp->tellg();
	fp->seekg(0, ios::end);
	end = fp->tellg();
	size = end - begin;
	fp->seekg(0, ios::beg);
	fpTarget->write((char*)&size,sizeof(long));
	/*unsigned char masc1=0x80;
	unsigned char masc3=0x7F;
	unsigned long long begin, end, size;
	begin = fp->tellg();
	fp->seekg(0, ios::end);
	end = fp->tellg();
	size = end - begin;
	cout <<"el tamaño a comprimir es: "<<size<<endl; //TESSSSSSSSSSSSST TEST PRUEBA
//	unsigned char newChar[8];
	Valor val;
	val.vlong=size;
//	newChar=reinterpret_cast<unsigned char*>(&size);
	int cont=0;
	bool startNumber=false;
	for(int pos=7;pos>=0;pos--){
		if (!startNumber){
			if (val.st[pos]!=0x00){
				cont++;
				startNumber=true;
			}
		}else
			cont++;
	}
	unsigned int nbit=0;
	unsigned char toWrite[9];
	for(int i=0;i<cont;i++){
		unsigned char c=0x00;
		unsigned char c2=0x00;
		if (i<0)
			nbit=0;
		else{
			nbit=i;
			//c=newChar[i-1];
			c=val.st[i-1];
		}

		c=c>>8-nbit;
		//c2=newChar[i]<<nbit;
		c2=val.st[i]<<nbit;
		//apago el ultimo bit
		c2=c2&masc3;
		c2=c2|c;
		if (i!=cont-1)
			toWrite[i]=c2|masc1;
		else
			toWrite[i]=c2&masc3;
	}
	if (cont==8)
		toWrite[9]=val.st[8]&masc3;
		//toWrite[9]=newChar[8]&masc3;
	//delete newChar;
	for(int i=0;i<cont;i++)
		cout<<(unsigned int)toWrite[cont];
	fp->seekg(0, ios::beg);
	fpTarget->write((char*)toWrite,sizeof(char)*cont);*/
}

unsigned int Lzss::getCantBitsPos() {
	unsigned int aux;
	bool end = false;
	unsigned int ans = 0;
	while (end == false) {
		aux = pow(2, ans);
		if (aux >= Lzss::sizeBuffer)
			end = true;
		else
			ans++;
	}
	return ans;
}

unsigned int Lzss::getCantBitsLong() {
	unsigned int aux;
	bool end = false;
	unsigned int ans = 0;
	while (end == false) {
		aux = pow(2, ans);
		if (aux >= Lzss::lMax - Lzss::lMin + 1)
			end = true;
		else
			ans++;
	}
	return ans;
}
