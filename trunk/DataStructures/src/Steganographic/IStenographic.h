///////////////////////////////////////////////////////////
//  IStenographic.h
//  Implementation of the Class IStenographic
//  Created on:      13-Oct-2008 2:49:33 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#if !defined(EA_B5E3EB86_98EA_11dd_B49B_001B2425640C__INCLUDED_)
#define EA_B5E3EB86_98EA_11dd_B49B_001B2425640C__INCLUDED_

/**
 * Interface que permite a un objeto (Ej: imagen) implementar el comportamiento
 * para que se puedan ocultar y extraer mensajes dentro de el mismo. 
 */
class IStenographic
{

public:
	IStenographic();
	virtual ~IStenographic();

	void Extract(Space space, Message msg);
	virtual void Hide(Space space, Message msg);

};
#endif // !defined(EA_B5E3EB86_98EA_11dd_B49B_001B2425640C__INCLUDED_)
