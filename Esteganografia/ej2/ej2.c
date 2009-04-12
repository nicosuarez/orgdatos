
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char magicnumber[2]; // It is used to identify the BMP file
	int size; // Size of the BMP file in bytes
	short reservedvalue1; // Reserved; actual value depends on the application that creates the image.
	short reservedvalue2; // Ditto reservedvalue1.
	int offset; // Starting address of the byte where the bitmap data can be found.

}Bmpfileheader;  // Stores general information about the BMP file.

typedef struct {
	int size; // Size of this header
	int width; // Bitmap width in pixels.
	int height; // Bitmap height in pixels
	short planes; // Number of color planes being used (must be set to 1).
	short bitcount; // Number of bits per pixel, which is the color depth of the image.
					// Typical values are 1, 4, 8, 16, 24 and 32.
	int compression; // Compression method being used.
	int imagesize; // Size of the raw bitmap data (this is not the file size).
	int hresolpermeter; // Horizontal resolution of the image (pixel per meter).
	int vresolpermeter; // Vertical resolution of the image (pixel per meter).
	int cpalette; // Number of colors in the color palette, or 0 to default to 2n.
	int cimportant; // Number of important colors used, or 0 when every color is important.
}Dibheader;  // Stores detailed information about the bitmap image.


typedef struct {
	unsigned char Red;
	unsigned char Green;
	unsigned char Blue;
	unsigned char Alpha;
} RGBA;

typedef struct {
	unsigned char Blue;
	unsigned char Green;
	unsigned char Red;
	unsigned char Alpha;
} BGRA;


void readBmpHeader ( FILE* file , Bmpfileheader* bmph) {

	fread( bmph->magicnumber, sizeof(char),2, file);
	fread( &bmph->size, sizeof(int),1, file);
	fread( &bmph->reservedvalue1, sizeof(short),1, file);
	fread( &bmph->reservedvalue2, sizeof(short),1, file);
	fread( &bmph->offset, sizeof(int),1, file);

}

void readDibHeader ( FILE* file , Dibheader* dibh) {
	char* buffer;

	buffer = (char*)malloc(sizeof(Dibheader));
	fread( buffer, sizeof(Dibheader), 1, file);

	memcpy ( &dibh->size, &buffer[0], sizeof(int) );
	memcpy ( &dibh->width, &buffer[4], sizeof(int) );
	memcpy ( &dibh->height, &buffer[8], sizeof(int) );
	memcpy ( &dibh->planes, &buffer[12], sizeof(short) );
	memcpy ( &dibh->bitcount, &buffer[14], sizeof(short) );
	memcpy ( &dibh->compression, &buffer[16], sizeof(int) );
	memcpy ( &dibh->imagesize, &buffer[20], sizeof(int) );
	memcpy ( &dibh->hresolpermeter, &buffer[24], sizeof(int) );
	memcpy ( &dibh->vresolpermeter, &buffer[28], sizeof(int) );
	memcpy ( &dibh->cpalette, &buffer[32], sizeof(int) );
	memcpy ( &dibh->cimportant, &buffer[36], sizeof(int) );

	free (buffer);
}

void readColorTable ( FILE* file , BGRA* cTable ) {
	char* buffer;

	buffer = (char*)malloc(sizeof(BGRA));
	fread( buffer, sizeof(BGRA), 1, file);

	memcpy ( &cTable->Blue, &buffer[0], sizeof(unsigned char) );
	memcpy ( &cTable->Green, &buffer[2], sizeof(unsigned char) );
	memcpy ( &cTable->Red, &buffer[4], sizeof(unsigned char) );
	memcpy ( &cTable->Alpha, &buffer[6], sizeof(unsigned char) );

	free (buffer);
}

unsigned int getWidth( Dibheader* dibh ) {
		return dibh->width < 0 ? -dibh->width : dibh->width;
}

unsigned int getHeight( Dibheader* dibh ) {
		return dibh->height < 0 ? -dibh->height : dibh->height;
}

void readBit ( unsigned char value, char byte[] ) {
	unsigned char mask = 1 << 7; int c;
	for (c = 1; c <= 8; c++)
	{
		byte[c-1] = value & mask ? '1' : '0';
		value <<= 1;
	}
}

int getSequenceFile ( const char* filename, FILE* sFile )
{
	FILE* imgFile;

	int error = 0;

	imgFile = fopen ( filename, "rb" );
	if ( imgFile == NULL ) error = 1;
	 else
		{
		  Bmpfileheader bmph;
		  Dibheader dibh;

		  unsigned char *bitmapImage;

		  readBmpHeader ( imgFile, &bmph);
		  readDibHeader ( imgFile, &dibh);

		  bitmapImage = (unsigned char*)malloc(dibh.imagesize);

		  fread( bitmapImage,dibh.imagesize,1,imgFile );

		  int i;

		  sFile =  fopen ( "temp.txt", "w" );

		  char byte[8];

		  for ( i = 1; i <= dibh.imagesize; i++)
		  {
			  readBit( bitmapImage[dibh.imagesize-i], byte );
			  fprintf( sFile,"%s " , byte );
		  }
		  fclose(sFile);
		  free (bitmapImage);
		}

	return error;
}


int main(int argc, char** argv)
{
	FILE* arch;
	if ( getSequenceFile ( "hola.bmp" , arch) )
	{
		printf(" ");
	}

	return 0;
}
