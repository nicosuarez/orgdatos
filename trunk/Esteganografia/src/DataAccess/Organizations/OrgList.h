/* -------------------------------------------------------------------------- */
// OrgList.h
// Developer: Leandro Oscar Mencias
/* -------------------------------------------------------------------------- */

#ifndef _ORG_LIST_
#define _ORG_LIST_

#include <string>
#include "../Files/ExtensibleRelativeFile.h"
#include "../Registries/ListRegistry.h"

/* This class handles the ExtensibleRelativeFile as an organization of 
 * linked registries, building a list. */
class OrgList
{
  public:
    /* Constructor. 
     * filename: Name of the file that the organization uses. 
     * ptrMethodCreateRegistry: Pointer to a method that return a 
     * pointer to a new ListRegistry. */
    OrgList(const string &fileName, ListRegistry* (*ptrMethodCreateRegistry)());

    /* Destructor. */ 
    virtual ~OrgList();
    
    void GetList();

    void AddToListFirst();

    void AddToListLast();

    void DeleteList();

    void DeleteFromList();

  private:
    ExtensibleRelativeFile *file;

    /* Allocation and copy constructor are private to prevent errors. */
    OrgList(const OrgList &org);
    OrgList& operator=(const OrgList &org);
};

#endif

