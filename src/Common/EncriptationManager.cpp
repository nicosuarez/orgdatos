#include "EncriptationManager.h"
#include "../Encrypter/bits_inverter.h"
#include "../Encrypter/transposition.h"
#include "Constant.h"

using std::cout;

Message EncriptationManager::Decrypt(const Message& msg){
	Message temp("./temp.dat");
	Message ans(PATH_TARGET_DECRYPT_EM);
	Transposition::decrypt(msg.GetFilePath(),temp.GetFilePath());
	BitsInverter::decrypt(temp.GetFilePath(),ans.GetFilePath());
	  if( remove( temp.GetFilePath() ) != 0 )
	    perror( "Error deleting file" );
	 return ans;
}

void EncriptationManager::Encrypt(const Message& msg,const Message& msgTarget){
	Message temp("./temp.dat");
	BitsInverter::encrypt(msg.GetFilePath(),temp.GetFilePath());
	Transposition::encrypt(temp.GetFilePath(),msgTarget.GetFilePath());
	if( remove( temp.GetFilePath()) != 0 )
	    perror( "Error deleting file" );
}
