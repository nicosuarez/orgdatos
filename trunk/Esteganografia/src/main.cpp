#include <iostream>
#include <cstdlib>
#include <vector>
#include "Lzss/lzss.h"
#include "Steganographic/BmpHighColor.h"
#include "Steganographic/Jpg.h"
#include "Steganographic/Png.h"
#include "Common/Space.h"
#include "Steganographic/Gif.h"
#include "Commands/AddDirectory.h"
#include "Common/Console.h"
#include "DataAccess/Files/ExtensibleRelativeFile.h"
#include "DataAccess/Registries/ExtensibleRelativeRegistry.h"
#include "DataAccess/Organizations/OrgExtensibleRelative.h"
#include "DataAccess/Organizations/OrgList.h"
#include "DataAccess/Registries/MsgRegistry.h"
#include "DataAccess/Registries/ListImgRegistry.h"
#include "DataAccess/Registries/ListFreeSpaceRegistry.h"
#include "Tree/factory.h"
#include "Tree/BppTree/bpptree.h"

using namespace std;

class Reg : public ExtensibleRelativeRegistry
{
  public:
    Reg() : ExtensibleRelativeRegistry()
    {
      this->numero = 0;
      memset(this->texto, '\0', 11);
    }

    Reg(int numero, std::string texto) : ExtensibleRelativeRegistry()
    {
      this->numero = numero;
      SetTexto(texto);
    }

    void SetTexto(std::string texto)
    {
      memset(this->texto, '\0', 11);
      strcpy(this->texto, texto.c_str());
    }

    unsigned int GetSize() const
    {
      return ExtensibleRelativeRegistry::GetSize() + sizeof(numero) + sizeof(texto) - 1;
    }

    char* Serialize() const
    {
      char *buffer = ExtensibleRelativeRegistry::Serialize();

      unsigned int pos = ExtensibleRelativeRegistry::GetSize();
      AddToSerialization(buffer, &numero, pos, sizeof(numero));

      pos += sizeof(numero);
      AddToSerialization(buffer, texto, pos, 10);

      return buffer;
    }

    void Deserialize(const char* buffer, unsigned int length)
    {
      ExtensibleRelativeRegistry::Deserialize(buffer, length);

      unsigned int pos = ExtensibleRelativeRegistry::GetSize();
      GetFromSerialization(buffer, &numero, pos, sizeof(numero));

      pos += sizeof(numero);
      GetFromSerialization(buffer, texto, pos, 10);
    }

    bool operator==(const Reg &reg)
    {
      if (GetID() != reg.GetID())
        return false;

      if (this->numero != reg.numero)
        return false;

      if (strcmp(this->texto, reg.texto) != 0)
        return false;

      return true;
    }

    bool operator!=(const Reg &reg)
    {
      return !((*this) == reg);
    }

    static ExtensibleRelativeRegistry* Create();

  private:
    int numero;
    char texto[11];

    /* Allocation and copy constructor are private to prevent errors. */
    Reg(const Reg &reg);
    Reg& operator=(const Reg &reg);
};

ExtensibleRelativeRegistry* Reg::Create()
{
  return new Reg();
}

/* -------------------------------------------------------------------------- */

void TestCreateFile()
{
  Reg reg;
  ExtensibleRelativeFile f("test_1.dat", Reg::Create);

  try
  {
    f.Create(reg.GetSize());
    f.Destroy();
  }
  catch (...)
  {
    throw "TestCreateFile failed";
  }
}

/* -------------------------------------------------------------------------- */

void TestCreateFileTwice()
{
  Reg reg;
  ExtensibleRelativeFile f("test_2.dat", Reg::Create);

  try
  {
    f.Create(reg.GetSize());
    f.Create(reg.GetSize());
  }
  catch (char* error)
  {
    f.Destroy();
    return;
  }

  throw "TestCreateFileTwice failed";
}

/* -------------------------------------------------------------------------- */

void TestOpenFileWithoutCreate()
{
  ExtensibleRelativeFile f("test_3.dat", Reg::Create);

  try
  {
    f.Open(ExtensibleRelativeFile::READ_WRITE);
  }
  catch (char* error)
  {
    return;
  }

  throw "TestOpenFileWithoutCreate failed";
}

/* -------------------------------------------------------------------------- */

void TestOpenFileWrongMode()
{
  ExtensibleRelativeFile f("test_4.dat", Reg::Create);

  try
  {
    f.Open(6);
  }
  catch (char* error)
  {
    return;
  }

  throw "TestOpenFileWrongMode failed";
}

/* -------------------------------------------------------------------------- */

void TestOpenFile()
{
  Reg reg;
  ExtensibleRelativeFile f("test_5.dat", Reg::Create);

  try
  {
    f.Create(reg.GetSize());
    f.Open(ExtensibleRelativeFile::READ_WRITE);
    f.Destroy();
  }
  catch (...)
  {
    throw "TestOpenFile failed";
  }
}

/* -------------------------------------------------------------------------- */


void TestOpenCloseOpenFile()
{
  Reg reg;
  ExtensibleRelativeFile f("test_6.dat", Reg::Create);

  try
  {
    f.Create(reg.GetSize());
    f.Open(ExtensibleRelativeFile::READ_WRITE);
    f.Close();
    f.Open(ExtensibleRelativeFile::READ_WRITE);
    f.Destroy();
  }
  catch (...)
  {
    throw "TestOpenCloseOpenFile failed";
  }
}

/* -------------------------------------------------------------------------- */

void TestWriteAndRead()
{
  Reg *reg;
  Reg reg1(61,"LEANDRO_ME");
  Reg reg2(62,"BRUNA_LAVA");
  Reg reg3(63,"OSCAR_COME");

  ExtensibleRelativeFile f1("test_7.dat", Reg::Create);
  ExtensibleRelativeFile f2("test_7.dat", Reg::Create);
  ExtensibleRelativeFile f3("test_7.dat", Reg::Create);

  try
  {
    f1.Create(reg1.GetSize());
    f1.Open(ExtensibleRelativeFile::READ_WRITE);
    f1.Write(reg1);

    if (reg1.GetID() != 1)
      throw "Failed";

    f1.Write(reg2);

    if (reg2.GetID() != 2)
      throw "Failed";

    f1.Close();

    f2.Open(ExtensibleRelativeFile::READ_WRITE);
    f2.Write(reg3);

    if (reg3.GetID() != 3)
      throw "Failed";

    f2.Close();

    f3.Open(ExtensibleRelativeFile::READ);
    reg = dynamic_cast<Reg*>(f3.Read(1));

    if ((*reg) != reg1)
      throw "Failed";

    delete reg;
    reg = dynamic_cast<Reg*>(f3.Read(2));

    if ((*reg) != reg2)
      throw "Failed";

    delete reg;
    reg = dynamic_cast<Reg*>(f3.Read(3));

    if ((*reg) != reg3)
      throw "Failed";

    delete reg;
    f3.Destroy();
  }
  catch (...)
  {
    throw "TestWriteAndRead failed";
  }
}

/* -------------------------------------------------------------------------- */

void TestRegistryActive()
{
  Reg *reg;
  Reg reg1(456,"LEANDRITOS");

  try
  {
    if (reg1.IsDeleted())
      throw "Failed";

    ExtensibleRelativeFile *f1 = new ExtensibleRelativeFile("test_8.dat", Reg::Create);

    f1->Create(reg1.GetSize());
    f1->Open(ExtensibleRelativeFile::WRITE);
    f1->Write(reg1);

    if (reg1.GetID() != 1)
      throw "Failed";

    delete f1;

    f1 = new ExtensibleRelativeFile("test_8.dat", Reg::Create);
    f1->Open(ExtensibleRelativeFile::READ);

    reg = dynamic_cast<Reg*>(f1->Read(1));

    if ((*reg) != reg1)
      throw "Failed";

    if (reg->IsDeleted())
      throw "Failed";

    f1->Destroy();

    delete reg;
    delete f1;
  }
  catch (...)
  {
    throw "TestRegistryActive failed";
  }
}

/* -------------------------------------------------------------------------- */

void TestRegistryDeleted()
{
  Reg *reg;
  Reg reg1(456,"LEANDRITOS");

  try
  {
    if (reg1.IsDeleted())
      throw "Failed";

    ExtensibleRelativeFile *f1 = new ExtensibleRelativeFile("test_9.dat", Reg::Create);

    f1->Create(reg1.GetSize());
    f1->Open(ExtensibleRelativeFile::WRITE);
    f1->Write(reg1);

    if (reg1.GetID() != 1)
      throw "Failed";

    delete f1;

    f1 = new ExtensibleRelativeFile("test_9.dat", Reg::Create);
    f1->Open(ExtensibleRelativeFile::READ_WRITE);

    f1->Delete(1);
    reg = dynamic_cast<Reg*>(f1->Read(1));

    if ((*reg) != reg1)
      throw "Failed";

    if (!reg->IsDeleted())
      throw "Failed";

    f1->Destroy();

    delete reg;
    delete f1;
  }
  catch (...)
  {
    throw "TestRegistryDeleted failed";
  }
}


/* -------------------------------------------------------------------------- */

void TestSeekWrong()
{
  Reg reg1(999,"LEANDRITOS");
  ExtensibleRelativeFile f1("test_10.dat", Reg::Create);

  try
  {
    f1.Create(reg1.GetSize());
    f1.Open(ExtensibleRelativeFile::WRITE);
    f1.Write(reg1);
    f1.Seek(2);
  }
  catch (...)
  {
    f1.Destroy();
    return;
  }

  throw "TestSeekWrong failed";
}

/* -------------------------------------------------------------------------- */

void TestUpdateDeleted()
{
  Reg *reg = NULL;
  Reg reg1(73,"MANZANITAS");
  Reg reg2(374,"MANDARINAS");

  ExtensibleRelativeFile f1("test_12.dat", Reg::Create);

  try
  {
    f1.Create(reg1.GetSize());
    f1.Open(ExtensibleRelativeFile::READ_WRITE);

    f1.Write(reg1);
    f1.Write(reg1);
    f1.Write(reg2);

    f1.Delete(2);

    reg = dynamic_cast<Reg*>(f1.Read(2));
    f1.Update(*reg);
  }
  catch (...)
  {
    delete reg;
    f1.Destroy();
    return;
  }

  throw "TestDeleteWithUpdate failed";
}

/* -------------------------------------------------------------------------- */

void TestOrgExtensibleRelative()
{
  OrgExtensibleRelative org("organization.dat", Reg::Create);

  Reg reg1(101, "CINTIA_LUC");
  Reg reg2(102, "LEANDRO_OS");
  Reg reg3(103, "CECILIA_BE");
  Reg reg4(104, "EUGENIA_BE");

  org.WriteRegistry(reg1);
  org.WriteRegistry(reg2);
  org.WriteRegistry(reg3);
  org.WriteRegistry(reg4);

  if (reg1.GetID() != 1 || reg2.GetID() != 2 || reg3.GetID() != 3 || reg4.GetID() != 4)
    throw "TestOrgExtensibleRelative failed.";

  org.DeleteRegistry(4);
  org.DeleteRegistry(2);

  Reg reg5(105, "MARINA_BEA");
  Reg reg6(106, "BRUNA_ESTR");
  Reg reg7(107, "OSCAR_ALBE");

  org.WriteRegistry(reg5);
  org.WriteRegistry(reg6);
  org.WriteRegistry(reg7);

  if (reg5.GetID() != 2 || reg6.GetID() != 4 || reg7.GetID() != 5)
    throw "TestOrgExtensibleRelative failed.";

  reg6.SetTexto("ESTR_BRUNA");
  org.UpdateRegistry(reg6);

  org.Destroy();
}

void TestMsgRegistry()
{
	OrgExtensibleRelative org("mesajes.dat", MsgRegistry::Create);
	MsgRegistry reg1(10);
	MsgRegistry reg2(15);
	MsgRegistry reg3(100);
	MsgRegistry *reg;

	org.WriteRegistry(reg1);
	org.WriteRegistry(reg2);
	org.WriteRegistry(reg3);

	reg = dynamic_cast<MsgRegistry*>( org.GetRegistry(reg1.GetID()));
	cout << " - ptrImg: " << reg->GetPtrImgList() << endl;
	delete reg;
	reg = dynamic_cast<MsgRegistry*>( org.GetRegistry(reg2.GetID()));
	cout << " - ptrImg: " << reg->GetPtrImgList() << endl;
	delete reg;
	reg = dynamic_cast<MsgRegistry*>( org.GetRegistry(reg3.GetID()));
	cout << " - ptrImg: " << reg->GetPtrImgList() << endl;
	delete reg;
}


void TestListImgRegistry()
{
//	OrgList org("mesajesList.dat", ListImgRegistry::Create);
//
//	ListImgRegistry reg1(1, 10, 50);
//	ListImgRegistry reg2(2, 15, 100);
//	ListImgRegistry reg3(3, 100, 1000);
//	ListImgRegistry reg4(4, 200, 1500);
//	ListImgRegistry *reg;
//
//	org.CreateList(reg1);
//	org.AddToListLast(reg2, reg1.GetID());
//	org.AddToListLast(reg3, reg2.GetID());
//	org.AddToListLast(reg4, reg3.GetID());
//	list<ListRegistry*> *lista = org.GetList(reg1.GetID());
//	list<ListRegistry*>::iterator it;
//
//	for( it= lista->begin(); it != lista->end(); it++)
//	{
//		reg = dynamic_cast<ListImgRegistry*>( (*it) );
//		cout << "idImage: " << reg->GetIDImage() << " - offsetImg: " << reg->GetOffsetImg() <<  " - sizePartitionMsg: " << reg->GetSizePartitionMsg() << endl;
//		delete reg;
//	}

	OrgList org("mesajesList.dat", ListFreeSpaceRegistry::Create);

	ListFreeSpaceRegistry reg1(1, 10);
	ListFreeSpaceRegistry reg2(2, 15);
	ListFreeSpaceRegistry reg3(3, 100);
	ListFreeSpaceRegistry reg4(4, 200);
	ListFreeSpaceRegistry *reg;

	org.CreateList(reg1);
	org.AddToListLast(reg2, reg1.GetID());
	org.AddToListLast(reg3, reg2.GetID());
	org.AddToListLast(reg4, reg3.GetID());
	list<ListRegistry*> *lista = org.GetList(reg1.GetID());
	list<ListRegistry*>::iterator it;

	for( it= lista->begin(); it != lista->end(); it++)
	{
		reg = dynamic_cast<ListFreeSpaceRegistry*>( (*it) );
		cout << "Reg: " << reg->GetID() <<" - offsetImg: " << reg->GetOffsetImage() << " - sizeFreeSpace: " << reg->GetSizeFreeSpace() <<  " - Next: " << reg->GetNextID()<< endl;
		delete reg;
	}

}




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
	Bmp bmp(argv[1]);
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
	BmpHighColor* bmp = new BmpHighColor(argv[1]);
	//bmp.ValidateFormat(&space);
	bmp->Hide(&spaceHide,&msg);

	Space spaceExtract(argv[1]);
	spaceExtract.SetInitialPosition(STARTBYTE);
	spaceExtract.SetSize(msg.GetSize()*4);
	bmp->Extract(&spaceExtract,&msgOut);
}

void testJPG(int argc,char* argv[])
{

//	Space spaceHide(argv[1]);
//	spaceHide.SetInitialPosition(STARTBYTE);
	Message msg(argv[2]);
	Message msgOut(argv[3]);
//	spaceHide.SetSize(spaceHide.GetTotalSize());
	Jpg* jpg = new Jpg(argv[1]);
	Space* space = jpg->Load();
	jpg->Hide(space,&msg);

    Space spaceExtract(argv[1]);
	spaceExtract.SetInitialPosition(space->GetInitialPosition());
	spaceExtract.SetSize(msg.GetHiddenSize());
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
	//Console::Run(argc,argv);
}

void testPNG(int argc,char* argv[])
{
	Png* png = new Png(argv[1]);
	Space* spaceHide = png->GetFreeSpace();
	Message msg(argv[2]);
	Message msgOut(argv[3]);
	png->Hide(spaceHide,&msg);

	Space* spaceExtract = new Space(argv[1]);
	spaceExtract->SetInitialPosition(0);
	std::cout << msg.GetHiddenSize() << "\n";
	spaceExtract->SetSize(msg.GetHiddenSize());
	png->Extract(spaceExtract,&msgOut);
}

void testGif(int argc, char *argv[])
{

	Message msg(argv[2]);
	Message msgOut(argv[3]);
//	Gif *gif = new Gif(argv[1]);
	//Space *space = gif->GetFreeSpace();
//	if( space == NULL )
//		return;
//	gif->Hide(space,&msg);
//	gif->Extract(space,&msgOut);

}

void testStenographic(int argc, char *argv[])
{
	//testBmpLSB1bit(argc,argv);
	testBmpLSB2bit(argc,argv);
	//testJPG(argc,argv);
	//testFileSystem(argv[1]);
	//testGif(argc, argv);
	//testConsole(argc,argv);
	//testGif(argc, argv);
	//testConsole(argc,argv);
	//testPNG(argc,argv);
}

int testDataAccess(int argc, char *argv[])
{
  try
  {
//    TestCreateFile();
//    TestCreateFileTwice();
//    TestOpenFileWithoutCreate();
//    TestOpenFileWrongMode();
//    TestOpenFile();
//    TestOpenCloseOpenFile();
//    TestWriteAndRead();
//    TestRegistryActive();
//    TestRegistryDeleted();
//    TestSeekWrong();
//    TestUpdateDeleted();
//    TestOrgExtensibleRelative();
//	  TestMsgRegistry();
	  TestListImgRegistry();
  }
  catch (char* error)
  {
    std::cout << error << std::endl;
  }

  return 0;
}

void testPass(int argc, char *argv[]){
	Console::Run(argc,argv);
}

void testInsertValueInt(){
	KeyStrFactory  kf;
	ValueIntFactory  vf;
	BppTree tree(512,kf,vf,"dummy.temporal");

	KeyStr k1("Armando1.jpg");
	ValueInt v1(1);
	tree.insert(k1,v1);
	KeyStr k2("JULIO.jpg");
	ValueInt v2(2);
	tree.insert(k2,v2);
	KeyStr k3("home/nicolas/600x800.jpg");
	ValueInt v3(3);
	tree.insert(k3,v3);
	KeyStr k4("./etc/include/wallpaper.jpg");
	ValueInt v4(4);
	tree.insert(k4,v4);

	std::cout << tree << std::endl;

}


 void testArbol()
 {
	 testInsertValueInt();

 }

int main(int argc, char *argv[])
{
	//testPass(argc,argv);
	//testCompresion();
//	testStenographic(argc, argv);
	//testDataAccess(argc, argv);
	testArbol();


	return EXIT_SUCCESS;
}


