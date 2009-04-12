

#include <stdio.h>
#include <stdlib.h>

int main ( int argc, char** argv)
{
	int i, fclose_status;

	// crea los archivos

	for (i = 1 ; i < argc ; i++)
	{
		printf ("%s \n",argv[i]);
		FILE* archivo = fopen ( argv[i], "r+" );
		if ( archivo == NULL )
		{
			archivo = fopen ( argv[i], "w+" );
			int j;
			for ( j = 0 ; j < 5 ; j++ )
				fprintf ( archivo,"%c",'h');
				//fprintf ( archivo,"%c",argv[i][j]);

		}
		fclose_status = fclose (archivo);
	}

	printf ("\n \n");

	// lee los archivos

	for (i = 1 ; i < argc ; i++)
	{
		FILE* archivo = fopen ( argv[i], "r+" );
		if ( archivo != NULL )
		{
			char caracter;
			while ( !feof(archivo) )
			{
				fscanf ( archivo , "%c" , &caracter);
				printf ("%c",caracter);
			}
		}
		fclose_status = fclose (archivo);
		printf ("\n");
	}
	return 0;
}
