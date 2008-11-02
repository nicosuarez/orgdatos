#include <iostream>
#include <cstdlib>
#include <vector>
#include "Lzss/lzss.h"
#include "Steganographic/BmpHighColor.h"
#include "Steganographic/Jpg.h"
#include "Common/Space.h"
#include "Steganographic/Gif.h"
#include "Commands/AddDirectory.h"
#include "Common/Console.h"



using namespace std;

void testCompresion()
{
//	Lzss lz;
//	string postaPosta="ciudado con la ca";// bombachita";/*"hhachaLa Papa, Ciudado con la petiza que te tiza cuak, esto en realidad es muuuy pelotudo de hacer ya que seria mejor cortar un texto de lanacion.com y despues pegarlo aca pasa que este año estoy muy boludo y ademas, esta bueno, esto de ir probrando un poco este texto de mierda y ver si el lzss realmente puede comprimir algo";*/
//	string st=lz.compress(postaPosta,postaPosta);
//	/*TEST*/
//	const unsigned char* aux =(unsigned char*) st.c_str();
//	cout<<"ESTE ES EL ARCHIVO COMPRIMIDO  ";
//	for(unsigned int i=0;i<st.length();i++)
//		cout<<(unsigned int)aux[i]<<" ";
//	cout<<endl;
//	/*ESTO LO DEBE HACER AL LEER EL ARCHIVO*/
//	string descomprimir;
//	unsigned char* aux2=(unsigned char*)st.c_str();
//	for(unsigned int i=0;i<(unsigned int)aux2[0];i++)
//		descomprimir.append(1,aux2[i+1]);
//	/*FIN DE ESTO*/
//	string ans=lz.uncompress((unsigned char*)descomprimir.c_str(),st.size());
//	
//	const char * a=ans.c_str();
//	cout<<"la verdadera resp deberia ser:  "<<postaPosta<<endl<<endl;
//	cout<<"LA RESPUESTA ES: TA TAN TA TAN...  "<<a<<endl;
}

void testBmpLSB1bit(int argc, char *argv[])
{
	Space spaceHide(argv[1]);
	spaceHide.SetInitialPosition(STARTBYTE);
	Message msg(argv[2]);
	Message msgOut(argv[3]);
	spaceHide.SetSize(spaceHide.GetTotalSize());
	Bmp bmp;
	//bmp.ValidateFormat(&space);
	bmp.Hide(&spaceHide,&msg);
	
	Space spaceExtract(argv[1]);
	spaceExtract.SetInitialPosition(STARTBYTE);
	spaceExtract.SetSize(msg.GetSize()*8);
	bmp.Extract(&spaceExtract,&msgOut);
}

void testBmpLSB2bit(int argc, char *argv[])
{
	Space spaceHide(argv[1]);
	spaceHide.SetInitialPosition(STARTBYTE);
	Message msg(argv[2]);
	Message msgOut(argv[3]);
	spaceHide.SetSize(spaceHide.GetTotalSize());
	BmpHighColor* bmp = new BmpHighColor();
	//bmp.ValidateFormat(&space);
	bmp->Hide(&spaceHide,&msg);
	
	Space spaceExtract(argv[1]);
	spaceExtract.SetInitialPosition(STARTBYTE);
	spaceExtract.SetSize(msg.GetSize()*4);
	bmp->Extract(&spaceExtract,&msgOut);
}

void testJPG(int argc,char* argv[])
{
	
	Space spaceHide(argv[1]);
	spaceHide.SetInitialPosition(STARTBYTE);
	Message msg(argv[2]);
	Message msgOut(argv[3]);
	spaceHide.SetSize(spaceHide.GetTotalSize());
	Jpg* jpg = new Jpg();
	jpg->Hide(&spaceHide,&msg);
	
	Space spaceExtract(argv[1]);
	spaceExtract.SetInitialPosition(STARTBYTE);
	spaceExtract.SetSize(msg.GetSize()*4);
	jpg->Extract(&spaceExtract,&msgOut);
}

void testFileSystem(const char* path)
{
	vector<string> fileList = FileSystem::GetFiles(path , File);
	for(size_t i=0; i < fileList.size(); i++)
	{
		cout << fileList[i] << "\n";
	}
	
	ImageFactory::SupportedFormats(path);
	Image* image = ImageFactory::GetImage(path);
	cout << image->GetFilePath() << "\n"; 
	
	Bmp::ImageInfo(path);
}

void testAddDirectory(int argc, char *argv[])
{
	
}

void testConsole(int argc, char *argv[])
{
	Console::Run(argc,argv);
}




void testGif(int argc, char *argv[])
{
	
	Message msg(argv[2]);
	Message msgOut(argv[3]);
	Gif *gif = new Gif();
	list<Space*> *lista = gif->getSpaces(argv[1]);
	if( lista == NULL)
		return;
//	list<Space*>::iterator it;
//	for( it=lista->begin(); it !=lista->end(); it++)
//	{
//		cout << "Posicion Inicial: " << (*it)->GetInitialPosition() << " - ";
//		cout << "Tamaño: " << (*it)->GetSize() << endl;
//	}
	gif->Hide(lista->front(),&msg);
	gif->Extract(lista->front(),&msgOut);
	
}

void testStenographic(int argc, char *argv[])
{
	//testBmpLSB1bit(argc,argv);
	//testBmpLSB2bit(argc,argv);
	//testJPG(argc,argv);
	//testFileSystem(argv[1]);
	//testGif(argc, argv);
//	testConsole(argc,argv);
}


int main(int argc, char *argv[])
{
	//testCompresion();
	testStenographic(argc, argv);
	
	return EXIT_SUCCESS;
}


