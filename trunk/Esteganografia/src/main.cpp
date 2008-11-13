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
#include "DataAccess/Files/ExtensibleRelativeFile.h"
#include "DataAccess/Registries/ListRegistry.h"
#include "DataAccess/Registries/ExtensibleRelativeRegistry.h"
#include "DataAccess/Organizations/OrgList.h"
#include "DataAccess/Organizations/OrgText.h"
#include "DataAccess/Organizations/OrgExtensibleRelative.h"
#include "Common/CompressionManager.h"
#include "Common/EncriptationManager.h"
#include "Common/Exception/eFile.h"

#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

void testDate(){
	struct tm* clock;				// create a time structure
	struct stat attrib;			// create a file attribute structure
	stat("prueba1.txt", &attrib);		// get the attributes of afile.txt
	clock = gmtime(&(attrib.st_mtime));	// Get the last modified time and put it into the time structure
	std::cout<<clock->tm_year<<std::endl;
	std::cout<<clock->tm_mon<<std::endl;
	std::cout<<clock->tm_mday<<std::endl;
	std::cout<<clock->tm_hour<<std::endl;
	std::cout<<clock->tm_min<<std::endl;
	std::cout<<clock->tm_sec<<std::endl;
}


using namespace std;

void testCompresion()
{
	Message m("./prueba1.txt");
	Message temp("");
	Message ansCompress("");
	Message m2("");
	try{
		temp=CompressionManager::Compress(m);
		ansCompress=EncriptationManager::Encrypt(temp);

		/*ifstream fp(ansCompress.GetFilePath(), ios::binary| ios::in);
		if(!fp.good())
				std::cout<<"error";
		unsigned long begin, end, size;
		begin = fp.tellg();
		fp.seekg(0, ios::end);
		end = fp.tellg();
		size = end - begin;
		std::cout<<"el tamaño comprimido es"<<size<<endl;
		fp.close();*/
	}catch(eFile e){
			std::cout<<e.what()<<std::endl;
	}
	if( remove( temp.GetFilePath()) != 0 )
			    perror( "Error deleting file" );

	try{
		m2=EncriptationManager::Decrypt(ansCompress);
		CompressionManager::Decompress(m2);
	}catch(eFile e){
		std::cout<<e.what()<<std::endl;
	}
}


void testBmpLSB1bit(int argc, char *argv[])
{
//	Space spaceHide(argv[1]);
//	spaceHide.SetInitialPosition(STARTBYTE);
//	Message msg(argv[2]);
//	Message msgOut(argv[3]);
//	spaceHide.SetSize(spaceHide.GetTotalSize());
//	Bmp bmp(argv[1]);
//	//bmp.ValidateFormat(&space);
//	bmp.Hide(&spaceHide,&msg);
//
//	Space spaceExtract(argv[1]);
//	spaceExtract.SetInitialPosition(STARTBYTE);
//	spaceExtract.SetSize(msg.GetSize()*8);
//	bmp.Extract(&spaceExtract,&msgOut);
	if( !Bmp::ValidateFormat(argv[1]) )
	{
		cout << "FORMATO DE IMAGEN NO VALIDO" << endl;
		return;
	}
	Message msg(argv[2]);
	Message msgOut(argv[3]);
	Bmp bmp(argv[1]);
	Space *spaceHide = bmp.Load();
	Space spaceExtract(argv[1]);
	spaceExtract.SetInitialPosition(STARTBYTE);
	spaceExtract.SetSize(msg.GetSize()*8);
	if( spaceHide != NULL)
	{
		bmp.Hide(spaceHide,&msg);
		bmp.Extract(&spaceExtract,&msgOut);
	}
	delete spaceHide;
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
//	Message msg(argv[2]);
//	Message msgOut(argv[3]);
//	spaceHide.SetSize(spaceHide.GetTotalSize());
//	Jpg* jpg = new Jpg(argv[1]);
//	jpg->Hide(&spaceHide,&msg);
//
//	Space spaceExtract(argv[1]);
//	spaceExtract.SetInitialPosition(STARTBYTE);
//	spaceExtract.SetSize(msg.GetSize()*4);
//	jpg->Extract(&spaceExtract,&msgOut);
	Message msg(argv[2]);
	Message msgOut(argv[3]);
	if( !Jpg::ValidateFormat(argv[1]) )
	{
		cout << "FORMATO DE IMAGEN NO VALIDO" << endl;
		return;
	}
	Jpg* jpg = new Jpg(argv[1]);
	Space *spaceHide = jpg->Load();
	Space spaceExtract(argv[1]);
	spaceExtract.SetInitialPosition(STARTBYTE);
	spaceExtract.SetSize(msg.GetSize());
	if( spaceHide != NULL)
	{
		jpg->Hide(spaceHide,&msg);
		jpg->Extract(&spaceExtract,&msgOut);
	}
	delete jpg;
	delete spaceHide;
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

void testPNG(int argc,char* argv[])
{

	Space spaceHide(argv[1]);
	spaceHide.SetInitialPosition(STARTBYTE);
	Message msg(argv[2]);
	Message msgOut(argv[3]);
	spaceHide.SetSize(spaceHide.GetTotalSize());
	Png* png = new Png(argv[1]);
	png->Hide(&spaceHide,&msg);

//	Space spaceExtract(argv[1]);
//	spaceExtract.SetInitialPosition(STARTBYTE);
//	spaceExtract.SetSize(msg.GetSize()*4);
//	jpg->Extract(&spaceExtract,&msgOut);
}


void testGif(int argc, char *argv[])
{
	Message msg(argv[2]);
	Message msgOut(argv[3]);
	if( ! Gif::ValidateFormat(argv[1]) )
		return;
	Gif *gif = new Gif(argv[1]);
	Space *space = gif->Load();
	if( space != NULL)
	{
		gif->Hide(space,&msg);
		gif->Extract(space,&msgOut);
	}
}

void testStenographic(int argc, char *argv[])
{
	testBmpLSB1bit(argc,argv);
	//testBmpLSB2bit(argc,argv);
//	testJPG(argc,argv);
	//testFileSystem(argv[1]);
//	testGif(argc, argv);
//	testConsole(argc,argv);
	//testPNG(argc,argv);
}

/* -------------------------------------------------------------------------- */
//                     - TEST DE DATA ACCESS -
/* -------------------------------------------------------------------------- */

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

    char* GetTexto()
    {
      return this->texto;
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

    static ExtensibleRelativeRegistry* CreateReg();

  private:
    int numero;
    char texto[11];

    /* Allocation and copy constructor are private to prevent errors. */
    Reg(const Reg &reg);
    Reg& operator=(const Reg &reg);
};

ExtensibleRelativeRegistry* Reg::CreateReg()
{
  return new Reg();
}

/* -------------------------------------------------------------------------- */

class RegList : public ListRegistry
{
  public:
    RegList() : ListRegistry()
    {
      this->numero = 0;
      memset(this->texto, '\0', 11);
    }

    RegList(int numero, std::string texto) : ListRegistry()
    {
      this->numero = numero;
      SetTexto(texto);
    }

    char* GetTexto()
    {
      return this->texto;
    }

    void SetTexto(std::string texto)
    {
      memset(this->texto, '\0', 11);
      strcpy(this->texto, texto.c_str());
    }

    unsigned int GetSize() const
    {
      return ListRegistry::GetSize() + sizeof(numero) + sizeof(texto) - 1;
    }

    char* Serialize() const
    {
      char *buffer = ListRegistry::Serialize();

      unsigned int pos = ListRegistry::GetSize();
      AddToSerialization(buffer, &numero, pos, sizeof(numero));

      pos += sizeof(numero);
      AddToSerialization(buffer, texto, pos, 10);

      return buffer;
    }

    void Deserialize(const char* buffer, unsigned int length)
    {
      ListRegistry::Deserialize(buffer, length);

      unsigned int pos = ListRegistry::GetSize();
      GetFromSerialization(buffer, &numero, pos, sizeof(numero));

      pos += sizeof(numero);
      GetFromSerialization(buffer, texto, pos, 10);
    }

    bool operator==(const RegList &reg)
    {
      if (GetID() != reg.GetID())
        return false;

      if (this->numero != reg.numero)
        return false;

      if (strcmp(this->texto, reg.texto) != 0)
        return false;

      return true;
    }

    bool operator!=(const RegList &reg)
    {
      return !((*this) == reg);
    }

    static ExtensibleRelativeRegistry* CreateRegList();

  private:
    int numero;
    char texto[11];

    /* Allocation and copy constructor are private to prevent errors. */
    RegList(const RegList &reg);
    RegList& operator=(const RegList &reg);
};

ExtensibleRelativeRegistry* RegList::CreateRegList()
{
  return new RegList();
}

/* -------------------------------------------------------------------------- */

void TestCreateFile()
{
  Reg reg;
  ExtensibleRelativeFile f("test_1.dat", Reg::CreateReg);

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
  ExtensibleRelativeFile f("test_2.dat", Reg::CreateReg);

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
  ExtensibleRelativeFile f("test_3.dat", Reg::CreateReg);

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
  ExtensibleRelativeFile f("test_4.dat", Reg::CreateReg);

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
  ExtensibleRelativeFile f("test_5.dat", Reg::CreateReg);

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
  ExtensibleRelativeFile f("test_6.dat", Reg::CreateReg);

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

  ExtensibleRelativeFile f1("test_7.dat", Reg::CreateReg);
  ExtensibleRelativeFile f2("test_7.dat", Reg::CreateReg);
  ExtensibleRelativeFile f3("test_7.dat", Reg::CreateReg);

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

    ExtensibleRelativeFile *f1 = new ExtensibleRelativeFile("test_8.dat", Reg::CreateReg);

    f1->Create(reg1.GetSize());
    f1->Open(ExtensibleRelativeFile::WRITE);
    f1->Write(reg1);

    if (reg1.GetID() != 1)
      throw "Failed";

    delete f1;

    f1 = new ExtensibleRelativeFile("test_8.dat", Reg::CreateReg);
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

    ExtensibleRelativeFile *f1 = new ExtensibleRelativeFile("test_9.dat", Reg::CreateReg);

    f1->Create(reg1.GetSize());
    f1->Open(ExtensibleRelativeFile::WRITE);
    f1->Write(reg1);

    if (reg1.GetID() != 1)
      throw "Failed";

    delete f1;

    f1 = new ExtensibleRelativeFile("test_9.dat", Reg::CreateReg);
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
  ExtensibleRelativeFile f1("test_10.dat", Reg::CreateReg);

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

  ExtensibleRelativeFile f1("test_12.dat", Reg::CreateReg);

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
  OrgExtensibleRelative org("organization.dat", Reg::CreateReg);

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

/* -------------------------------------------------------------------------- */

void TestOrgListCreate()
{
  RegList reg(101, "CINTIA_LUC");
  OrgList org("orglist.dat", RegList::CreateRegList);

  org.CreateList(reg);
  std::list<ListRegistry*> *list = org.GetList(1);

  if (list->size() != 1)
  {
    OrgList::FreeList(list);
    throw "TestOrgListCreate failed.";
  }

  OrgList::FreeList(list);

  org.Destroy();
}

/* -------------------------------------------------------------------------- */

void TestOrgListTwoList()
{
  RegList reg1(101, "CINTIA_LUC");
  RegList reg2(102, "CECILIA_BE");
  RegList reg3(103, "MARINA_BEA");
  RegList reg4(104, "EUGENIA_BE");
  RegList reg5(105, "EMILIO_HEC");
  RegList reg6(106, "LUISA_ROSA");

  RegList reg7(201, "LEANDRO_OS");
  RegList reg8(202, "PAULA_ANDR");
  RegList reg9(203, "BRUNA_LAVA");
  RegList reg10(204, "OSCAR_ALBE");
  RegList reg11(205, "COREY_ROLE");

  RegList reg12(206, "BETH_PERRO");
  RegList reg13(207, "NANO_PERRO");

  OrgList org("orglist_reloaded.dat", RegList::CreateRegList);

  // 2
  // 8
  org.CreateList(reg2);
  org.CreateList(reg8);

  // 2->3
  // 8->9
  org.AddToListLast(reg3, reg2.GetID());
  org.AddToListLast(reg9, reg8.GetID());

  // 2->3->4
  // 8->9->10
  org.AddToListLast(reg4, reg3.GetID());
  org.AddToListLast(reg10, reg9.GetID());

  // 1->2->3->4
  // 7->8->9->10
  org.AddToListFirst(reg1, reg2.GetID());
  org.AddToListFirst(reg7, reg8.GetID());

  // 1->2->3->4->5
  // 7->8->9->10->11
  org.AddToListLast(reg5, reg4.GetID());
  org.AddToListLast(reg11, reg10.GetID());

  // 1->2->3->4->5->6
  // 7->8->9->10->11
  org.AddToListLast(reg6, reg5.GetID());

  // 1->2->4->5->6
  // 7->8->10->11
  org.DeleteFromList(reg3.GetID());
  org.DeleteFromList(reg9.GetID());

  // 12->1->2->3->4->5
  // 7->8->9->10->11->13
  org.AddToListFirst(reg12, reg1.GetID());
  org.AddToListLast(reg13, reg11.GetID());

  std::list<ListRegistry*> *list_yo = org.GetList(reg7.GetID());
  std::list<ListRegistry*> *list_cin = org.GetList(reg12.GetID());

  if (list_yo->size() != 5)
  {
    OrgList::FreeList(list_yo);
    throw "TestOrgListTwoList failed.";
  }

  if (list_cin->size() != 6)
  {
    OrgList::FreeList(list_cin);
    throw "TestOrgListTwoList failed.";
  }
/*
  std::list<ListRegistry*>::iterator i;

  for (i = list_yo->begin(); i != list_yo->end(); ++i)
    std::cout << dynamic_cast<RegList*>(*i)->GetTexto() << std::endl;

  for (i = list_cin->begin(); i != list_cin->end(); ++i)
    std::cout << dynamic_cast<RegList*>(*i)->GetTexto() << std::endl;
*/
  OrgList::FreeList(list_yo);
  OrgList::FreeList(list_cin);

  org.Destroy();
}

/* -------------------------------------------------------------------------- */

void TestOrgText()
{
  OrgText org("orgtext.dat");
  ID_type id1, id2, id3, id4, id5, id6, id9;
  std::string s1("Leandro Oscar Mencias");
  std::string s2("Organización de Datos");
  std::string s3("Facultad de Ingeniería - Universidad de Buenos Aires");
  std::string s4("Puto el que lee!!");
  std::string s5("La gran prueba gran......");
  std::string s6("Club Atlético Boca Juniors.");
  std::string s7("Boca Juniors, Club Atlético");
  std::string s8("Leandro Oscar");
  std::string s9("Fachero!");
  std::string s10("xxxxxxxxx");
  std::string s11("LaLaLaLaLaLaLaLa");

  id1 = org.WriteText(s1);
  id2 = org.WriteText(s2);
  id3 = org.WriteText(s3);
  id4 = org.WriteText(s4);

  if (id1 != 1 || id2 != 2 || id3 != 3 || id4 != 4)
    throw "TestOrgText failed.";

  if ((org.GetText(id3).compare(s3) | org.GetText(id1).compare(s1) | org.GetText(id4).compare(s4) | org.GetText(id2).compare(s2)) != 0)
    throw "TestOrgText failed.";

  org.DeleteText(id3);

  id5 = org.WriteText(s5);
  id6 = org.WriteText(s6);

  if (id5 != id3 || id6 != 5)
    throw "TestOrgText failed.";

  if ((org.GetText(id5).compare(s5) | org.GetText(id6).compare(s6)) != 0)
    throw "TestOrgText failed.";

  org.UpdateText(id3, s3);
  org.UpdateText(id6, s7);

  if ((org.GetText(id3).compare(s3) | org.GetText(id6).compare(s7)) != 0)
    throw "TestOrgText failed.";

  org.UpdateText(id1, s8);
  id9 = org.WriteText(s9);

  if (id9 != 6)
    throw "TestOrgText failed.";

  if ((org.GetText(id1).compare(s8) | org.GetText(id9).compare(s9)) != 0)
    throw "TestOrgText failed.";

  org.WriteText(s10);
  org.WriteText(s11);
  org.WriteText("FIN");

  org.Destroy();
}

/* -------------------------------------------------------------------------- */

int testDataAccess(int argc, char *argv[])
{
  try
  {
    TestCreateFile();
    TestCreateFileTwice();
    TestOpenFileWithoutCreate();
    TestOpenFileWrongMode();
    TestOpenFile();
    TestOpenCloseOpenFile();
    TestWriteAndRead();
    TestRegistryActive();
    TestRegistryDeleted();
    TestSeekWrong();
    TestUpdateDeleted();
    TestOrgExtensibleRelative();
    TestOrgListCreate();
    TestOrgListTwoList();
    TestOrgText();
  }
  catch (char* error)
  {
    std::cout << error << std::endl;
  }

  return 0;
}

/* -------------------------------------------------------------------------- */
//                     - FIN TEST DE DATA ACCESS -
/* -------------------------------------------------------------------------- */

void TestPassword(int argc, char *argv[])
{
  try{
    Console::Run(argc,argv);
  }catch (eFile e){
    throw e.what();
  }
}
/* -------------------------------------------------------------------------- */


int main(int argc, char *argv[])
{
	//testCompresion();
//	testConsole(argc,argv);
	//testDate();
	testStenographic(argc, argv);
	//testDataAccess(argc, argv);
	return EXIT_SUCCESS;
}


