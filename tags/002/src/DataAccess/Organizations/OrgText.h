/* -------------------------------------------------------------------------- */
// OrgText.h
// Developer: Leandro Oscar Mencias
/* -------------------------------------------------------------------------- */

#ifndef _ORG_TEXT_
#define _ORG_TEXT_

#include <string>
#include <fstream>
#include "OrgExtensibleRelative.h"
#include "../Registries/TextRegistry.h"

using namespace std;

/* The aim of this organization is to handle texts of variable length.
 * Internally it uses two OrgExtensibleRelative and a stream file. */
class OrgText
{
  public:
    /* Constructor. 
     * filename: Name of the file that the organization uses. */
    OrgText(const string &path, const string &fileName);

    /* Destructor. */ 
    virtual ~OrgText();

    /* Gets a text with the ID from the organization. 
     * id: The ID of the text to get. */
    string GetText(ID_type id);

    /* Writes the text to the organization and returns the ID. 
     * text: The text to write. */
    ID_type WriteText(const string &text);

    /* Updates the text in the organization. 
     * id: The ID where the text will be updated.
     * text: The text to update. */
    void UpdateText(ID_type id, const string &text);

    /* Deletes the text with the ID from the organization. 
     * id: The ID of the text to delete. */
    void DeleteText(ID_type id);

    /* Destroys the organization deleting all the files. */
    void Destroy();

  private:
    /* Stream where the text will go to. */
    fstream stream;
    const string *fileName;

    /* Organizations to handle the active and deleted texts. */
    OrgExtensibleRelative *orgActive;
    OrgExtensibleRelative *orgDeleted;
    
    /* Some methods to manage the deleted spaces and the stream. */
    void OpenStream(const string &fileName);
    unsigned int InternalWriteText(const string &text);
    TextRegistry* SearchDeletedSpace(unsigned int length);
    void InternalDeleteText(TextRegistry *reg, unsigned int offset, unsigned int length);

    /* Asserts. */
    void AssertStreamOpened() const;
    void AssertNotDeleted(const TextRegistry &reg) const;

    /* Static TextRegistry creator. */
    static ExtensibleRelativeRegistry* CreateTextRegistry();

    /* Allocation and copy constructor are private to prevent errors. */
    OrgText(const OrgText &org);
    OrgText& operator=(const OrgText &org);
};

#endif

