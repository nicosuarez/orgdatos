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
#include "../DataAccess/Organizations/OrgExtensibleRelative.h"
#include "../DataAccess/Registries/SetRegistry.h"

using Glib::ustring;
using std::list;

class SetsManager {
public:

	SetsManager* getInstance();

	~SetsManager();

	/*Agrega un nuevo set de palabras*/
	ID_type addSet(list<ustring> *listWords);

	/*Retorna la lista de palabras de un set*/
	list<ustring>* getSet(ID_type idSet)const;

private:

	/*Constructor privado*/
	SetsManager();

	/*Puntero a la unica instancia del SetManager*/
	static SetsManager *instance;

	OrgExtensibleRelative orgSets;


};

#endif /* SETSMANAGER_H_ */
