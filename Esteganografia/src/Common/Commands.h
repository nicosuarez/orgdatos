///////////////////////////////////////////////////////////
//  Commands.h
//  Implementation of the Class Commands
//  Created on:      13-Oct-2008 2:49:28 AM
//  Original author: zebas
///////////////////////////////////////////////////////////

#if !defined(EA_B3354A7E_98EA_11dd_B49B_001B2425640C__INCLUDED_)
#define EA_B3354A7E_98EA_11dd_B49B_001B2425640C__INCLUDED_

#include <string>
#include <vector>
#include "../Steganographic/BmpHighColor.h"
#include "../Steganographic/Jpg.h"
#include "../Steganographic/ImageFactory.h"
#include "Space.h"
#include "FileSystem.h"

using namespace std;
/**
 * Clase que implementa todos los comandos que se pueden ejecutar en el programa.
 */
class Commands
{

public:
	Commands();
	virtual ~Commands();

	static void AddDirectory(const char* path);
	static void AddFile(const char* filePath);
	static void ChangePassword(string newPass, string oldPass);
	static void GetFile(const char* outFile, const char* filePath);
	static void Quit();
	static void RemoveDirectory(const char* path);
	static void RemoveFile(const char* path);
	static void ShowDirectories();
	static void ShowFiles();

};
#endif // !defined(EA_B3354A7E_98EA_11dd_B49B_001B2425640C__INCLUDED_)
