#include "lzss.h"
#include <string>
#include <math.h>
#include <iostream>
using namespace std;

Lzss::Lzss():bitsLong(getCantBitsLong()),bitsPos(getCantBitsPos()){}

Lzss::~Lzss(){}

string Lzss::compress(std::string toCompress){
	string answer;
	vector<unsigned char> ans;
	unsigned int emptyBits=0;
	this->buffer.clear();
	bool match=false;
	bool endWindow=false;
	unsigned int posWindMin=0;
	const char* windows=toCompress.c_str();
	unsigned int posWindMax;
	unsigned int posMatch;
	unsigned int longMatch;
	int floor=0;
	if (toCompress.length()>Lzss::sizeWin)
		posWindMax=Lzss::sizeWin;
		
	else if (toCompress.length()>0) 
		posWindMax=toCompress.length();
	else
		endWindow=true;

	while (endWindow==false){
		int test;
		posMatch=0;
		longMatch=0;
		unsigned int currentPos=0;
		unsigned int posCurrMatch=0;
		unsigned int longCurrMatch=0;
		bool currentMatch=false;
		vector<unsigned char>::reverse_iterator itAux;
		test=this->buffer.size();
		for(vector<unsigned char>::reverse_iterator it=this->buffer.rbegin();it!=this->buffer.rend();it++){
			if ((floor+longCurrMatch<toCompress.length())&&((*it)==windows[floor+longCurrMatch])&&(longCurrMatch<Lzss::lMax)){
				if (currentMatch==false){
					itAux=it;
					currentMatch=true;
					posCurrMatch=currentPos;
				}
				longCurrMatch++;
				if ((longMatch<longCurrMatch)&&(longCurrMatch>=Lzss::lMin)){
						longMatch=longCurrMatch;
						posMatch=posCurrMatch;
				}
			}else{
				if (currentMatch==true){
					currentMatch=false;
					it=itAux;
					longCurrMatch=0;
				}
			}
			currentPos++;
		}
		if(longMatch>Lzss::lMin){
			
			insertCodePosLong(longMatch,posMatch,&ans,emptyBits);
			//avanza el buffer
			for (int i=floor;i<floor+longMatch;i++){
				this->buffer.push_back(windows[i]);
				if (this->buffer.size()>Lzss::sizeBuffer)
					this->buffer.erase(this->buffer.begin());
			}
			floor+=longMatch;
		}else{
			insertChar(windows[floor],&ans, emptyBits);
			this->buffer.push_back(windows[floor]);
			if (this->buffer.size()>Lzss::sizeBuffer)
				this->buffer.erase(this->buffer.begin());
			floor++;
		}
		if (floor==toCompress.length())
			endWindow=true;
	}

/*		TMP NO SIRVE PERO VERIFICARLO CON EL GRUPO
	//completa con 10...0
	if (emptyBits==0){
		unsigned char	aux=0x80;
		ans.push_back(aux);
	}else{
		unsigned char& lastChar=ans.back();
		unsigned char aux=0x01;
		aux=aux<<emptyBits-1;
		lastChar=lastChar|aux;
	}
*/

	if (emptyBits!=0){
		unsigned char& lastChar=ans.back();
		unsigned char aux=0x00;
		//aux=aux<<emptyBits-1; tmp
		lastChar=lastChar|aux;
	}
	answer.append(1,(unsigned char)toCompress.length());
	for(int i=0;i<ans.size();i++)
		answer.append(1,ans[i]);
	return answer;
}

void Lzss::insertCodePosLong(unsigned int longMatch,unsigned int posMatch,vector<unsigned char>* ans,unsigned int& emptyBits){
	unsigned char bit=0x00;
	unsigned char lastChar;
	unsigned char aux;
	if (emptyBits==0){
		emptyBits=8; //aca le saque un -1 tmp
		lastChar=0x00;
	}else{
		lastChar=ans->back();
		ans->pop_back();
	}	
	bit=bit<<emptyBits-1;
	lastChar=lastChar| bit;
	emptyBits--;
	if (emptyBits==0){
		emptyBits=8;
		ans->push_back(lastChar);
		lastChar=0x00;
	}
	
	aux=(unsigned char)(longMatch-Lzss::lMin);
	aux=aux<<8-this->bitsLong;
	aux=aux>>8-emptyBits;
	lastChar=lastChar|aux;
	if (this->bitsLong<=emptyBits) //le saque un -1 y = tmp
		emptyBits=emptyBits-this->bitsLong;
	else{
		ans->push_back(lastChar);
		lastChar=(unsigned char)longMatch;
		lastChar=lastChar<<(8-this->bitsLong)+emptyBits;
		emptyBits=(8-this->bitsLong)+emptyBits;
	}
	aux=(unsigned char)posMatch;
	aux=aux<<8-this->bitsPos;
	aux=aux>>8-emptyBits;
	lastChar=lastChar|aux;
	ans->push_back(lastChar);
	if (this->bitsPos<=emptyBits)//le saque un -1 tmp y sg y =
		emptyBits=emptyBits-this->bitsPos;
	else{
		lastChar=(unsigned char)posMatch;
		lastChar=lastChar<<(8-this->bitsPos)+emptyBits;
		emptyBits=(8-this->bitsPos)+emptyBits;
		ans->push_back(lastChar);
		
	}
}

void Lzss::insertChar(char c,std::vector<unsigned char>* ans, unsigned int& emptyBits){
	unsigned char auxC=c;
	unsigned char bit=0x01;
	if (emptyBits>0){
		bit=bit<<emptyBits-1;
		auxC=auxC>>8-(emptyBits-1);
		auxC=bit | auxC;
		c=c<<emptyBits-1;
		emptyBits--;
		unsigned char lastChar;
		if (ans->empty())
			lastChar=0x00;
		else{
			lastChar=ans->back();
			ans->pop_back();
		}
		lastChar=lastChar | auxC;
		ans->push_back(lastChar);
		ans->push_back(c);
	}else{
		bit=bit<<7;
	 	auxC=auxC>>1;
		auxC=bit | auxC;
		c=c<<7;
		emptyBits=7;
		ans->push_back(auxC);
		ans->push_back(c);
	}
}

string Lzss::uncompress(const unsigned char* compress, unsigned int cant){
	unsigned int floor=0;
	unsigned int nBit=8;
	string st;
	this->buffer.clear();
	for (unsigned int i=0; i<cant;i++){
		unsigned int flag=getFlag(compress,floor,nBit);
		if (flag==1)
			st.append(1,getChar(compress,nBit,floor));
		else
			getPosLong(compress,st,nBit,floor);
	}
	return st;
}	

unsigned int Lzss::getFlag(const unsigned char* compress,unsigned int& floor, unsigned int& nBit){
	if (nBit==0){
		nBit=8;
		floor++;
	}
	unsigned char c=compress[floor];
	c=c<<8-(nBit);
	c=c>>7;
	if (nBit<1){
		nBit=8;
		floor++;
	}else
		nBit--;
	return (unsigned int)c;
}

char Lzss::getChar (const unsigned char* compress, unsigned int& nBit,unsigned int& floor){
	char c=compress[floor];
	if (nBit!=8){
		c=c<<8-nBit;
		floor++;
		unsigned char aux=compress[floor];
		aux=aux>>nBit;
		c=c|aux;
	}else{
		floor++;
	}
	this->buffer.push_back(c);
	if(this->buffer.size()>Lzss::sizeBuffer)
		this->buffer.erase(this->buffer.begin());
	return c;
}

void Lzss::getPosLong (const unsigned char* compress,string& st, unsigned int& nBit,unsigned int& floor){
	unsigned int pos;
	unsigned int lMatch;
	unsigned char c=compress[floor];
	c=c<<8-nBit;
	c=c>>8-this->bitsLong;
	if (nBit<this->bitsLong){
		floor++;
		unsigned char aux=compress[floor];
		aux=aux>>8-(this->bitsLong-nBit);
		nBit=8-(this->bitsLong-nBit);
		c=c|aux;
	}else{
		nBit-=bitsLong;
	}
	lMatch=(unsigned int)c + Lzss::lMin;
	if (nBit==0){
		floor++;
		nBit=8;
	}
	c=compress[floor];
	c=c<<8-nBit;
	c=c>>8-this->bitsPos;
	if (nBit<this->bitsPos){
		floor++;
		unsigned char aux=compress[floor];
		aux=aux>>8-(this->bitsPos-nBit);
		nBit=8-(this->bitsPos-nBit);
		c=c|aux;
	}else{
		nBit-=bitsPos;
	}
	pos=(unsigned int)c;
	if (nBit==0){
		nBit=8;
		floor++;
	}
	for (unsigned int i=0;i<lMatch;i++){
		int test=this->buffer.size();
		char copy=this->buffer[buffer.size()-(1+pos)];
		this->buffer.push_back(copy);
		st.append(1,copy);
		if (this->buffer.size()>Lzss::sizeBuffer)
			this->buffer.erase(buffer.begin());
		
	}
}


unsigned int Lzss::getCantBitsPos(){
	int aux;
	bool end=false;
	unsigned int ans=0;
	while (end==false){
		aux=pow(ans,2);
		if (ans>=Lzss::sizeBuffer-1)
			end=true;
		else
			ans++;
	}
	return ans;
}

unsigned int Lzss::getCantBitsLong(){
	int aux;
	bool end=false;
	unsigned int ans=0;
	while (end==false){
		aux=pow(ans,2);
		if (ans>=Lzss::lMax-Lzss::lMin-1)
			end=true;
		else
			ans++;
	}
	return ans;
}
