/* -------------------------------------------------------------------------- */
// OrgList.h
// Developer: Leandro Oscar Mencias
/* -------------------------------------------------------------------------- */

#ifndef _ORG_LIST_
#define _ORG_LIST_

#include <list>
#include <string>
#include "../Files/ExtensibleRelativeFile.h"
#include "../Registries/ListRegistry.h"

typedef std::list<ListRegistry*> tRegisterList;
typedef std::list<ListRegistry*>::iterator itRegisterList;

/* This class handles the ExtensibleRelativeFile as an organization of 
 * linked registries, building a list. */
class OrgList
{
  public:
    /* Constructor. 
     * filename: Name of the file that the organization uses. 
     * ptrMethodCreateRegistry: Pointer to a method that return a 
     * pointer to a new ListRegistry. */
    OrgList(const string &fileName, ExtensibleRelativeRegistry* (*ptrMethodCreateRegistry)());

    /* Destructor. */ 
    virtual ~OrgList();
    
    /* Gets the entire list. The caller must free the allocated memory.
     * first: The ID of the first registry in the list. */
    tRegisterList* GetList(ID_type first);
    
    /* Starts a new list.
     * firstReg: The first registry of the new list. */
    void CreateList(ListRegistry &firstReg);

    /* Adds a regitry at the top of the list.
     * reg: Registry to add at the top of the list.
     * first: The ID of the first registry in the list. */
    void AddToListFirst(ListRegistry &reg, ID_type first);

    /* Adds a regitry at the end of the list.
     * reg: Registry to add at the end of the list.
     * last: The ID of the last registry in the list. */
    void AddToListLast(ListRegistry &reg, ID_type last);

    /* Deletes the entire list.
     * first: The ID of the first registry in the list. */
    void DeleteList(ID_type first);

    /* Deletes a registry from the list.
     * id: The ID of the registry to delete. */
    void DeleteFromList(ID_type id);

    /* Destroys the organization deleting all the files. */
    void Destroy();

    /* Static method that deletes correctly a list of 
     * pointer ListRegistry. 
     * list; Pointer to the list that will be erased/freed. */
    static void FreeList(std::list<ListRegistry*> *list);

  private:
    ExtensibleRelativeFile *file;

    /* Asserts. */
    void AssertLastReg(const ListRegistry &reg) const;
    void AssertFirstReg(const ListRegistry &reg) const;
    void AssertNotDeleted(const ListRegistry &reg) const;

    /* Allocation and copy constructor are private to prevent errors. */
    OrgList(const OrgList &org);
    OrgList& operator=(const OrgList &org);
};

#endif

