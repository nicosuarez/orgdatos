/*
 * BlackWordsManager.h
 *
 */

#ifndef BLACKWORDSMANAGER_H_
#define BLACKWORDSMANAGER_H_
#include "../DataAccess/Organizations/OrgList.h"
#include "../DataAccess/Registries/ListBlackWordRegistry.h"
#include "../DataAccess/Organizations/OrgText.h"
#include "../Tree/BppTree/bpptree.h"
#include "../Tree/factory.h"
#include "Constants.h"
#include <glibmm/ustring.h>
#include <list>

using Glib::ustring;
using std::list;

class BlackWordsManager {
public:
	static BlackWordsManager* getInstance();
	~BlackWordsManager();
	void addBlackWordToQuery(list<ustring> *query, ustring blackWord);
	void removeBlackWordFromQuery(list<ustring> *query, ustring wordToDelete);
	list<ustring>* getBlackWords(list<ustring> *query);

private:
	BlackWordsManager();
	ustring concatWords(list<ustring> *words);

	static BlackWordsManager *instance;
	OrgList fileListBlackWords;
	OrgText fileBlackWords;
	BppTree treeQueries;
};

#endif /* BLACKWORDSMANAGER_H_ */
