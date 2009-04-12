

#include <stdio.h>
#include <stdlib.h>


void showFile (const char* fileName) {
	char caracter;
	FILE* arch = fopen (fileName,"r");
	if (arch!=NULL)
		while (!feof(arch))
		{
			fscanf (arch,"%c",&caracter);
			printf ("%c", caracter);
		}
	fclose(arch);
}

void contar ( int* ncero, int* nuno, char tipo ) {
	switch ( tipo )
	{
		case '1': (*nuno)++;
				  break;
		case '0': (*ncero)++;
				  break;
		default: *nuno = 0;
		         *ncero = 0;
			break;
	}
}

void rleFile (const char* fileName) {
	char caracter;
	FILE* arch = fopen (fileName,"r");
	if (arch!=NULL)
	{
		FILE* arch2 = fopen ("rle.txt","w");
		if (arch2!=NULL)
		{
			int cont0 = 0,cont1 = 0;
			fscanf (arch,"%c",&caracter);
			char temp = caracter;
			while (!feof(arch))
			{
				contar ( &cont0, &cont1, caracter);
				fscanf (arch,"%c",&caracter);
				if ( temp != caracter )
				{
					if (temp == '1') {
							fprintf (arch2,"%d%c ",cont1,'1');
							cont1 = 0;
						}
					 else if (temp == '0' ){
					 	fprintf (arch2,"%d%c ",cont0,'0');
					 	cont0 = 0;
						}
					temp = caracter;
				}
			}
		}
		fclose(arch2);
	}
	fclose(arch);
}


int main( int argc, char** argv ) {
	//showFile ("temp.txt");
	rleFile ("temp.txt");
	return 0;
}
