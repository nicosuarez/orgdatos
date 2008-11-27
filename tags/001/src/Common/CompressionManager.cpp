#include "CompressionManager.h"
#include "../Lzss/lzss.h"
#include "Constant.h"

using namespace std;

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
	Message ans(PATH_TARGET_COMPRESS_CM);
	lz.compress(msg.GetFilePath(),ans.GetFilePath());
	return ans;
}
/* -------------------------------------------------------------------------- */
void CompressionManager::Decompress(const Message& msg,const Message& msgTarget){
	Lzss lz;
	lz.uncompress(msg.GetFilePath(),msgTarget.GetFilePath());
}
