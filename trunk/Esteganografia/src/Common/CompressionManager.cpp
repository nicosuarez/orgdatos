#include "CompressionManager.h"
#include "../Lzss/lzss.h"

using namespace std;
const string CompressionManager::targetCompress="../Files/rchTemp2.dat";
const string CompressionManager::targetDescompress="../Files/ans.txt";

CompressionManager* CompressionManager:: instance = NULL;
/* -------------------------------------------------------------------------- */


CompressionManager::CompressionManager(){

}
/* -------------------------------------------------------------------------- */


CompressionManager* CompressionManager::GetInstance()
{
	if(instance == NULL)
		instance = new CompressionManager();
	return instance;
}
/* -------------------------------------------------------------------------- */


CompressionManager::~CompressionManager(){

}
/* -------------------------------------------------------------------------- */

Message CompressionManager::Compress(const Message& msg){
	Lzss lz;
	Message ans(CompressionManager::targetCompress.c_str());
	lz.compress(msg.GetFilePath(),ans.GetFilePath());
	return ans;
}
/* -------------------------------------------------------------------------- */
void CompressionManager::Decompress(const Message& msg,const Message& msgTarget){
	Lzss lz;
	lz.uncompress(msg.GetFilePath(),msgTarget.GetFilePath());
}
