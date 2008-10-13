///////////////////////////////////////////////////////////
//  Space.h
//  Implementation of the Class Space
//  Created on:      13-Oct-2008 2:49:36 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#if !defined(EA_B792C72C_98EA_11dd_B49B_001B2425640C__INCLUDED_)
#define EA_B792C72C_98EA_11dd_B49B_001B2425640C__INCLUDED_

/**
 * Unidad de espacio del cual se puede recuperar o almacenar infomacion.
 */
class Space
{

public:
	Space();
	virtual ~Space();

	string GetFilePath();
	string GetFormat();
	int GetInitialPosition();
	int GetSize();

private:
	string filePath;
	string fotmat;
	string initialPosition;
	int size;

};
#endif // !defined(EA_B792C72C_98EA_11dd_B49B_001B2425640C__INCLUDED_)
