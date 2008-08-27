#include "SecuencialFile.h"

/* TODO: VER SI USAR STAT O FOPEN modo "r" */ 
bool FileExist(const char* nombre)
{
	struct stat buf;
	int status = stat ( nombre, &buf );
    if (status == 0)    /* Archivo Encontrado */
    {
       return TRUE;
    }
    return FALSE;
}

int S_CREATE(const char* nombre)
{
	if(FileExist(nombre)){ return RES_EXISTE; }
	
	FILE* file = fopen(nombre,"w");
	if(file != NULL)
	{
		fclose(file);
	}
	else
	{
		return RES_ERROR;
	}
	return RES_OK;
}

int S_OPEN(const char* nombre, int modo)
{
	FILE* file = NULL;
	switch (modo)
	{
		case READ:
			file = fopen(nombre,"r");
			break;
		case WRITE:
			file = fopen(nombre,"w");
			break;
		case READ_WRITE:
			file = fopen(nombre,"r+w");
			break;
		case APPEND:
			file = fopen(nombre,"a");
			break;
		default:
			return RES_NULL;
			
	}
	return fileno(file);
}
 
int S_CLOSE(int fhandler)
{
	int status = RES_OK;
	FILE* file = NULL;
	file->_fileno = fhandler;  /*Funciona si descomento esta linea y no uso el fdopen pero el valdgrid
	 * pincha porque hay que inicializar toda la estructura FILE*/
	/*file = fdopen(fhandler,"r");*/
	if(fclose(file))
	{
		status = RES_ERROR;
	}

	return status;
}
 
int S_READ(int fhandler, void* reg)
{
	return RES_OK;
}

int S_WRITE(int fhandler, const void* reg, unsigned long cant)
{
	return 0;
}
