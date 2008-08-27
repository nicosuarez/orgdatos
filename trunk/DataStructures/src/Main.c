/*
 ============================================================================
 Name        : main.c
 Author      : Sebastian Camjayi
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : Test organization files
 ============================================================================
 */

#include "FilesType/SecuencialFile.h"

int testSecuencialFile(int argc,char* argv[])
{
	char nombre[20] = "testSecuencial.txt";
	int status = 0,fd=0;
	status = S_CREATE(nombre);
	printf("Creacion Test:\n");
	if(status == RES_EXISTE)
	{
		printf("El archivo ya existe. {%d}\n", status);
	}
	else if(status == RES_OK)
	{
		printf("El archivo %s se creo correctamente.  {%d}\n", nombre, status);
	}
	else
	{
		printf("Se produjo un error al crear el archivo. {%d}\n", status);
	}
	
	printf("Abrir Test:\n");
	fd = S_OPEN(nombre,READ);
	if(fd==RES_NULL)
	{
		printf("No se pudo abrir el archivo %s .  {%d}\n", nombre, RES_NULL);
	}
	else
	{
		printf("El archivo %s se abrio correctamente.  fd:{%d}\n", nombre, fd);
		status=S_CLOSE(fd);
		printf("Cerrar Test:\n");
		if(status==RES_OK)
		{
			printf("El archivo %s se cerro correctamente.  fd:{%d}\n", nombre, fd);
		}
	}
	
	return status;
}

int main(int argc,char* argv[]) 
{
	testSecuencialFile(argc,argv);
	return 0;
}
