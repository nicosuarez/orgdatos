/*#include <iostream>
#include <sstream>
#include <fstream>
#include <list>
#include <queue>

#include "factory.h"
#include "./BppTree/bpptree.h"

void printIteratorValue(TreeIterator& it);
std::string createKey(unsigned int c);
std::string createLongKey(const std::string& start,unsigned int Size);
std::string uintToStr(unsigned int c);
std::string createRandomKey();
void createRandomDump(const std::string& fname,unsigned int size);
void loadRandomDump(const std::string& fname,std::list<std::string>& list);
bool randomDeleteSequence(BppTree& tree,std::set<Key>& inserted,bool record,const std::string& path);
bool loadRandomDeleteSequence(BppTree& tree,const std::string& path,bool printTree,const std::string& tPath);
void insertRandomDump(BppTree& tree,const std::string& path,unsigned int TEST_SIZE,std::list<std::string>& dump,std::set<Key>& inserted);
void insertRandomDumpVar(BppTree& tree,const std::string& path,unsigned int TEST_SIZE,std::list<std::string>& dump,std::set<Key>& inserted);
void fclean();

void testExists(bool clean);
void testRandomDelete(bool clean);
void testLeafUnderflow(bool clean);
void testLevelUnderflow(bool clean);
void testSingleInsert(bool clean);
void testBigRegisterInsert(bool clean);
void testFirstLeafOverflow(bool clean);
void testFirstLeafDoubleOverflow(bool clean);// Obsoleto -> idem testLeafOverflow
void testFirstLevelOverflow(bool clean);
void testFirstLevelDoubleOverflow(bool clean);// Obsoleto -> idem testLevelOverflow
void testRandomInsert(bool clean);
void testIterators(bool clean);
void testUpdate();
void testIterators2(bool clean);

void testInsert(bool clean){
	KeyStFactory  kf;
	VulueIntFactory  vf;
	BppTree tree(128,kf,vf,"dummy.temporal");

	KeySt k1("Armando1.jpg");
	ValueInt v1(1);
	tree.insert(k1,v1);

	std::cout << tree << std::endl;

	if(clean)
		fclean();
}
//int main(int argc,char** argv){

	//createRandomDump("bigDump.txt",5000);

	//testIterators2(true);
	//testUpdate();
	//testExists(true);
	//testRandomDelete(true);
	//testLevelUnderflow(true);
	//testLeafUnderflow(true);
	//testBigRegisterInsert(true);
	//testSingleInsert(true);
	//testFirstLeafOverflow(true);
	//testFirstLeafDoubleOverflow(true);
	//testFirstLevelOverflow(true);
	//testFirstLevelDoubleOverflow(true);
	//testRandomInsert(true);
	//testIterators(true);
//	testInsert(true);
//	return 0;
//}

void testIterators2(bool clean){
	const unsigned int TEST_SIZE = 25;
	DummyKeyFactory  kf;
	DummyValFactory  vf;
	BppTree tree(1024,kf,vf,"dummy.temporal");

	for(unsigned int c=0;c<TEST_SIZE;++c){
		Key k1(uintToStr(c));
		Value v1(12);
		tree.insert(k1,v1);
	}

	// Pruebo el estado del iterador luego de borrada la clave a donde apunta
	Key pk(uintToStr(15));
	TreeIterator& it = tree.iterator(pk);
	it.peekKey().toOstream(std::cout);

	Key rk2(uintToStr(15));
	tree.remove(rk2);
	it.peekKey().toOstream(std::cout);

	tree.deleteIterator(it);

	// Pruebo el estado del iterador luego de un overflow, la clave a la que apunta cambia de nodo
	Key pk2(uintToStr(70));
	TreeIterator& it2 = tree.iterator(pk2);
	it2.peekKey().toOstream(std::cout);

	for(unsigned int c=0;c<3;++c){
		Key k1(uintToStr(c+25));
		Value v1(12);
		tree.insert(k1,v1);
	}

	it2.peekKey().toOstream(std::cout);

	// Pruebo el estado del iterador luego de un underflow(con join), la clave a la que apunta cambia de nodo
	for(unsigned int c=0;c<8;++c){
		Key k1(uintToStr(c+20));
		tree.remove(k1);
	}
	Key k1(uintToStr(9));
	tree.remove(k1);

	it2.peekKey().toOstream(std::cout);

	// Pruebo el estado del iterador luego de un underflow(sin join), la clave a la que apunta cambia de nodo
	Key pk3(uintToStr(2));
	TreeIterator& it3 = tree.iterator(pk3);
	it3.peekKey().toOstream(std::cout);

	for(unsigned int c=0;c<9;++c){
		Key k1(uintToStr(c+10));
		tree.remove(k1);
	}

	it3.peekKey().toOstream(std::cout);

	std::cout << tree << std::endl;

	if(clean)
		fclean();
}

void testUpdate(){
	const unsigned int TEST_SIZE = 20;
	bool ret=true;
	DummyKeyFactory  kf;
	DummyValueVarFactory  vf;
	BppTree tree(1024,kf,vf,"dummy.temporal");
	std::list<std::string> dump;
	loadRandomDump("bigDump.txt",dump);
	std::set<Key> inserted;

	insertRandomDumpVar(tree,"bigDump.txt",TEST_SIZE,dump,inserted);

	std::cout << "DumpSize= " << dump.size() << std::endl;

	std::cout << "Comenzando a probar update..." << std::endl;

	unsigned int w=0,x=0,z=0;
	std::set<Key>::iterator it2 = inserted.begin();
	while(ret && w<inserted.size()/2 && ret){
		ValueVar v("A");
		ret = tree.update(*it2,v);
		++it2;
		w++;
	}

	while(ret && x<inserted.size()/2 && ret){
		ValueVar v(createLongKey("0",1));
		ret = tree.update(*it2,v);
		++it2;
		x++;
	}

	std::set<Key>::iterator it3 = inserted.begin();
	while(it3!=inserted.end() && ret){
		ret = tree.exists(*it3);
		++it3;
		z++;
	}


	if(!ret)
		std::cout << "Un registro modificado no se encontro (ret=true) Iteracion= " << w << std::endl;
	else
		std::cout << tree << std::endl;

	fclean();
}

void testExists(bool value){
	const unsigned int TEST_SIZE = 5000;
	bool ret=true;
	DummyKeyFactory  kf;
	DummyValFactory  vf;
	BppTree tree(64,kf,vf,"dummy.temporal");
	std::list<std::string> dump;
	loadRandomDump("bigDump.txt",dump);
	std::set<Key> inserted;

	insertRandomDump(tree,"bigDump.txt",TEST_SIZE,dump,inserted);

	std::cout << "DumpSize= " << dump.size() << std::endl;

	std::cout << "Comenzando a chequear..." << std::endl;

	unsigned int w=0;
	while(!inserted.empty() && ret){
		std::set<Key>::iterator it2 = inserted.begin();
		Key key = *it2;
		ret = tree.exists(key);
		std::cout << "Key:" << key.getKey() << "Exist:" << ret << "\n";
		inserted.erase(it2);
		w++;
	}

	if(!ret)
		std::cout << "Un registro insertado no se encontro (ret=true) Iteracion= " << w << std::endl;
	else
		std::cout << tree << std::endl;

	fclean();
}

void testRandomDelete(bool clean){
	const unsigned int TEST_SIZE = 49946;
	bool ret=true;
	DummyKeyFactory  kf;
	DummyValFactory  vf;
	// Existesn Registros > 1024 en el bigDump, No existen > a 3*1024
	BppTree tree(1024,kf,vf,"dummy.temporal");
	std::set<Key> inserted;
	std::list<std::string> dump;

	insertRandomDump(tree,"bigDump.txt",TEST_SIZE,dump,inserted);

	std::cout << "DumpSize= " << dump.size() << std::endl;

	std::cout << "Comenzando a borrar..." << std::endl;

	#define __RDS_

	#ifdef __RDS__
		ret = randomDeleteSequence(tree,inserted,true,"./test/seqBorrado.txt");
	#else
		ret = loadRandomDeleteSequence(tree,"./test/seqBorrado.txt",true,"./test/tree.txt");
	#endif

	if(!ret)
		std::cout << "Un registro no pudo ser elminado (ret=true)" << std::endl;
	else
		std::cout << tree << std::endl;

	if(clean)
		fclean();
}

void insertRandomDump(BppTree& tree,const std::string& path,unsigned int TEST_SIZE,std::list<std::string>& dump,std::set<Key>& inserted){
	loadRandomDump(path.c_str(),dump);
	std::list<std::string>::iterator it=dump.begin();

	for(unsigned int c=0;it!=dump.end() && c<TEST_SIZE;++c,++it){
		bool ret=true;

		Key k1(*it);
		Value v1(12);
		ret = tree.insert(k1,v1);
		inserted.insert(k1);
		if(!ret)
			std::cout << "Registro Duplicado en el Dump..." << *it << std::endl;
	}
}

void insertRandomDumpVar(BppTree& tree,const std::string& path,unsigned int TEST_SIZE,std::list<std::string>& dump,std::set<Key>& inserted){
	loadRandomDump(path.c_str(),dump);
	std::list<std::string>::iterator it=dump.begin();

	for(unsigned int c=0;it!=dump.end() && c<TEST_SIZE;++c,++it){
		bool ret=true;

		Key k1(*it);
		ValueVar v1(*it);
		ret = tree.insert(k1,v1);
		inserted.insert(k1);
		if(!ret)
			std::cout << "Registro Duplicado en el Dump..." << *it << std::endl;
	}
}
bool loadRandomDeleteSequence(BppTree& tree,const std::string& path,bool printTree,const std::string& tPath){
	bool ret=true;
	unsigned int w=0;
	std::ifstream entrada(path.c_str());
	std::ofstream treeSalida(tPath.c_str(), std::fstream::trunc);
	std::set<Key>::iterator it2;

	while(!entrada.eof() && ret){
		std::string s;
		entrada >> s;
		if( !entrada.eof()){
			if(printTree){
				treeSalida << "Iteracion w= " << w << std::endl;
				treeSalida << tree << std::endl << std::endl;
			}

			Key k(s);
			ret = tree.remove(k);
			w++;
		}
	}
	return ret;
}

bool randomDeleteSequence(BppTree& tree,std::set<Key>& inserted,bool record,const std::string& path){
	bool ret=true;
	std::ofstream salida(path.c_str(), std::fstream::trunc);
	if(!record){
		salida.close();
		remove(path.c_str());
	}

	std::set<Key>::iterator it2;
	srand ( time(NULL) );
	while(!inserted.empty() && ret){

		unsigned int erasePos = rand()%inserted.size();
		it2=inserted.begin();
		for(unsigned int c=0;it2!=inserted.end() && c<erasePos;c++,++it2);

		if(record)
			salida << it2->getKey() << std::endl;

		ret = tree.remove(*it2);
		inserted.erase(*it2);

		//if(!(w%2) && w!=TEST_SIZE){
			//salida.close();
			//salida.open("./test/seqBorrado.txt", std::fstream::trunc);
		//}
	}
	return ret;
}

void testLevelUnderflow(bool clean){
	const unsigned int TEST_SIZE = 1304;
	DummyKeyFactory  kf;
	DummyValFactory  vf;
	BppTree tree(1024,kf,vf,"dummy.temporal");
	std::queue<Key> keys;

	for(unsigned int c=0;c<TEST_SIZE;++c){
		Key k1(uintToStr(c));
		Value v1(12);
		tree.insert(k1,v1);
		keys.push(k1);
	}

	//std::cout << tree << std::endl;

	unsigned int c=0;
	std::fstream salida("./test/salida.txt", std::fstream::out | std::fstream::trunc);
	//salida << tree << std::endl;
	bool ret=true;
	while(!keys.empty() && c<TEST_SIZE && ret){
		Key key = keys.front();
		if(c==53)
			ret = tree.remove(key);
		else
			ret = tree.remove(key);
		c++;
		//salida << "Iteracion c= " << c << std::endl;salida << tree << std::endl;
		keys.pop();
	}

	if(!ret)
		std::cout << "ret = false => " << c << std::endl;
	else
		std::cout << tree << std::endl;

	if(clean)
		fclean();
}

void testLeafUnderflow(bool clean){
	const unsigned int TEST_SIZE = 20;
	DummyKeyFactory  kf;
	DummyValFactory  vf;
	BppTree tree(1024,kf,vf,"dummy.temporal");
	std::queue<Key> keys;

	for(unsigned int c=0;c<TEST_SIZE;++c){
		Key k1(uintToStr(c));
		Value v1(12);
		tree.insert(k1,v1);
		keys.push(k1);
	}

	//std::cout << tree << std::endl;

	unsigned int c=0;
	while(!keys.empty() && c<20){
		Key key = keys.front();
		if(c==10)
			tree.remove(key);
		else
			tree.remove(key);
		keys.pop();

		c++;
		//std::cout << tree << std::endl;
	}

	std::cout << tree << std::endl;

	if(clean)
		fclean();
}

void testBigRegisterInsert(bool clean){
	DummyKeyFactory  kf;
	DummyValFactory  vf;
	BppTree tree(32,kf,vf,"dummy.temporal");

	Key k1("Armando1");
	Value v1(1);
	tree.insert(k1,v1);

	std::cout << tree << std::endl;

	if(clean)
		fclean();
}

void testSingleInsert(bool clean){
	DummyKeyFactory  kf;
	DummyValFactory  vf;
	BppTree tree(1024,kf,vf,"dummy.temporal");

	Key k1("Armando");
	Value v1(1);
	tree.insert(k1,v1);

	std::cout << tree << std::endl;

	if(clean)
		fclean();
}

void testIterators(bool clean){
	DummyKeyFactory  kf;
	DummyValFactory  vf;
	BppTree tree(1024,kf,vf,"dummy.temporal");

	Key k1("Armando");
	Value v1(1);
	tree.insert(k1,v1);

	Key k21("Armando");
	Value v21(2);
	tree.insert(k21,v21);

	Key k2("Bielsa");
	Value v2(2);
	tree.insert(k2,v2);

	Key k3("Caracas");
	Value v3(3);
	tree.insert(k3,v3);

	Key k4("Dorrego");
	Value v4(4);
	tree.insert(k4,v4);

	Key k5("Urquiza");
	Value v5(5);
	tree.insert(k5,v5);

	Key keyFind("Urquiza");

	if(tree.exists((keyFind)))
	{
		Register* reg = tree.find(keyFind);
		if(reg != NULL)
		{
			Value* value = (Value*)reg;
			std::cout << value->getValue() << "\n";
		}
	}

	Key k6("Arman");
	TreeIterator& it = tree.iterator(k6);
	printIteratorValue(it);
	++it;
	printIteratorValue(it);
	--it;
	printIteratorValue(it);
	--it;
	printIteratorValue(it);
	tree.deleteIterator(it);

	std::cout << "\n\n\n\n";

	Key k7("Alfaro");
	TreeIterator& it2 = tree.iterator(k7);
	while(!it2.end()){
		printIteratorValue(it2);
		++it2;
	}

	std::cout << "\n\n\n\n";

	Key k8("Wolfram");
	TreeIterator& it3 = tree.iterator(k8);
	while(!it3.begin()){
		printIteratorValue(it3);
		--it3;
	}


	//std::cout << tree << std::endl;

	if(clean)
		fclean();
}

void testFirstLeafOverflow(bool clean){
	const unsigned int TEST_SIZE = 25;
	DummyKeyFactory  kf;
	DummyValFactory  vf;
	BppTree tree(1024,kf,vf,"dummy.temporal");

	for(unsigned int c=0;c<TEST_SIZE;++c){
		Key k1(createKey(c));
		Value v1(12);
		tree.insert(k1,v1);
	}

	std::cout << tree << std::endl;

	if(clean)
		fclean();
}

void testFirstLeafDoubleOverflow(bool clean){
	DummyKeyFactory  kf;
	DummyValFactory  vf;
	BppTree tree(1024,kf,vf,"dummy.temporal");

	Key k2(createLongKey("A",502));
	Value v2(12);
	tree.insert(k2,v2);

	Key k1(createLongKey("C",493));
	Value v1(12);
	tree.insert(k1,v1);

	Key k3(createLongKey("B",503));
	Value v3(12);
	tree.insert(k3,v3);

	std::cout << tree << std::endl;

	if(clean)
		fclean();
}


void testFirstLevelOverflow(bool clean){
	const unsigned int TEST_SIZE = 165;
	DummyKeyFactory  kf;
	DummyValFactory  vf;
	BppTree tree(1024,kf,vf,"dummy.temporal");

	for(unsigned int c=0;c<TEST_SIZE;++c){
		Key k1(uintToStr(c));
		Value v1(12);
		if(c!=TEST_SIZE-1)
			tree.insert(k1,v1);
		else
			tree.insert(k1,v1);
	}

	std::cout << tree << std::endl;

	if(clean)
		fclean();
}

//TODO -> encontrar input que provoque este caso si es que existe...
void testFirstLevelDoubleOverflow(bool clean){
	DummyKeyFactory  kf;
	DummyValFactory  vf;
	BppTree tree(1024,kf,vf,"dummy.temporal");

	Key k2(createLongKey("A",502));
	Value v2(12);
	tree.insert(k2,v2);
	Key k1(createLongKey("C",493));
	Value v1(12);
	tree.insert(k1,v1);

	Key k3(createLongKey("B",503));
	Value v3(12);
	tree.insert(k3,v3);

	Key k4(createLongKey("D",903));
	Value v4(12);
	tree.insert(k4,v4);

	std::cout << tree << std::endl;

	if(clean)
		fclean();
}

void testRandomInsert(bool clean){
	const unsigned int TEST_SIZE = 4500;
	DummyKeyFactory  kf;
	DummyValFactory  vf;
	BppTree tree(15*1024,kf,vf,"dummy.temporal");
	std::list<std::string> dump;
	loadRandomDump("dump1.txt",dump);
	std::list<std::string>::iterator it=dump.begin();

	for(unsigned int c=0;it!=dump.end(),c<TEST_SIZE;++c,++it){
		Key k1(*it);
		Value v1(12);
		if(c!=TEST_SIZE-1)
			tree.insert(k1,v1);
		else
			tree.insert(k1,v1);
	}

	std::cout << tree << std::endl;

	if(clean)
		fclean();
}

void createRandomDump(const std::string& fname,unsigned int size){
	srand ( time(NULL) );

	std::ofstream f(fname.c_str());
	for(unsigned int c=0;c<size;++c){
		f << createRandomKey() << "\n";
	}
}

void loadRandomDump(const std::string& fname,std::list<std::string>& list){
	std::ifstream f(fname.c_str());
	while(!f.eof()){
		std::string temp;
		f >> temp;
		//std::cout << temp << "\n";
		list.push_back(temp);
		f.peek();
	}
}

std::string createRandomKey(){
	unsigned int nChar = rand()%890;
	std::string key="";
	for(unsigned int c=0;c<nChar;c++){
		char randChar = rand()%26+65;
		key+=randChar;
	}
	return key;
}

std::string uintToStr(unsigned int c){
	std::string temp="";
	std::stringstream stream;
	stream << c;
	stream >> temp;
	temp.append("0000000000000000000000000000000000000000000000000000000000000000");
	return temp;
}

std::string createKey(unsigned int c){
	std::string temp="test00000000000000000000000000000000";
	temp[c%36]='!'+c%144;
	return temp;
}

std::string createLongKey(const std::string& start,unsigned int size){
	std::string temp=start;
	for(unsigned int c=0;c<size;c++){
		temp +="0";
	}
	return temp;
}

void printIteratorValue(TreeIterator& it){
	std::pair<Register*,Register*>keyval= *it;

	if(keyval.first){
		keyval.first->toOstream(std::cout);
		delete keyval.first;
	}


	if(keyval.second){
		keyval.second->toOstream(std::cout);
		delete keyval.second;
	}
}

void fclean(){
	remove("dummy.temporal");
	remove("dummy.temporal-big-regs");
	remove("dummy.temporal-tmp");
}*/
