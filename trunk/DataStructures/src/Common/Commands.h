///////////////////////////////////////////////////////////
//  Commands.h
//  Implementation of the Class Commands
//  Created on:      13-Oct-2008 2:49:28 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#if !defined(EA_B3354A7E_98EA_11dd_B49B_001B2425640C__INCLUDED_)
#define EA_B3354A7E_98EA_11dd_B49B_001B2425640C__INCLUDED_

/**
 * Clase que implementa todos los comandos que se pueden ejecutar en el programa.
 */
class Commands
{

public:
	Commands();
	virtual ~Commands();

	void AddDirectory(string path);
	void AddFile(string filePath);
	void ChangePassword(string new, string old);
	void GetFile(string outFile, string filePath);
	void Quit();
	void RemoveDirectory(string path);
	void RemoveFile(string path);
	void ShowDirectories();
	void ShowFiles();

};
#endif // !defined(EA_B3354A7E_98EA_11dd_B49B_001B2425640C__INCLUDED_)
