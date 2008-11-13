#include "CompressionManager.h"
#include "../Lzss/lzss.h"

using namespace std;
const string CompressionManager::targetCompress="./rchTemp2.dat";
const string CompressionManager::targetDescompress="./ans.txt";

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
Message CompressionManager::Decompress(const Message& msg){
	Lzss lz;
	Message ans(CompressionManager::targetDescompress.c_str());
	lz.uncompress(msg.GetFilePath(),ans.GetFilePath());
	return ans;
}
