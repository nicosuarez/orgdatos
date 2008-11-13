#include "EncriptationManager.h"
#include "../Encrypter/bits_inverter.h"
#include "../Encrypter/transposition.h"

using namespace std;
const string EncriptationManager::targetEncrypt="./ansEncrypt.txt";
const string EncriptationManager::targetDecrypt="./ansDecrypt.dat";

Message EncriptationManager::Decrypt(const Message& msg){
	Message temp("./temp.dat");
	Message ans(EncriptationManager::targetDecrypt.c_str());
	Transposition::encrypt(msg.GetFilePath(),temp.GetFilePath());
	BitsInverter::encrypt(temp.GetFilePath(),ans.GetFilePath());
	  if( remove( temp.GetFilePath() ) != 0 )
	    perror( "Error deleting file" );
	 return ans;
}

Message EncriptationManager::Encrypt(const Message& msg){
	Message temp("./temp.dat");
	Message ans(EncriptationManager::targetEncrypt.c_str());
	BitsInverter::decrypt(msg.GetFilePath(),temp.GetFilePath());
	Transposition::decrypt(temp.GetFilePath(),ans.GetFilePath());
	if( remove( temp.GetFilePath()) != 0 )
	    perror( "Error deleting file" );
	return ans;
}
