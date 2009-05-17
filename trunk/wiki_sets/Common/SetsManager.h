/*
 * SetsManager.h
 *
 */

#ifndef SETSMANAGER_H_
#define SETSMANAGER_H_
#include "Resource.h"
#include "Constants.h"
#include <list>
#include <glibmm/ustring.h>
#include <fstream>
#include "../DataAccess/Organizations/OrgExtensibleRelative.h"
#include "../DataAccess/Registries/SetRegistry.h"

using Glib::ustring;
using std::list;
using std::fstream;

class SetsManager {
public:

	static SetsManager* getInstance();

	~SetsManager();

	/*Agrega un nuevo set de palabras*/
	ID_type addSet(list<ustring> *listWords);

	ID_type addSet();

	/*Retorna la lista de palabras de un set*/
	list<ustring>* getSet(ID_type idSet);

private:

	/*Constructor privado*/
	SetsManager();

	list<ustring>* getList (long int offset, string &cant, ifstream &arch);

	/*Puntero a la unica instancia del SetManager*/
	static SetsManager *instance;

	OrgExtensibleRelative orgSets;

//	fstream arch;

	int count;


};

#endif /* SETSMANAGER_H_ */
