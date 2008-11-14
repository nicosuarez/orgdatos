#ifndef __CONSTANT__H_
#define __CONSTANT__H_

#include <string>

class Constant
{
	public:
		/*---------------Estructura----------*/
		static const std::string ImgFile;
		static const std::string PassFile;
		static const std::string MessageFile;
		static const std::string ImgListFile;
		static const std::string MsgListFile;
		static const std::string FreeSpaceFile;

		/*------------Temporarios------------*/
		static const std::string PassTemp;
};

const std::string Constant::PassTemp="../Files/passTemp.txt";
const std::string Constant::ImgFile="../Files/img.dat";
const std::string Constant::PassFile="../Files/pass.dat";
const std::string Constant::MessageFile="../Files/Message.dat";
const std::string Constant::ImgListFile="../Files/ImgList.dat";
const std::string Constant::MsgListFile="../Files/MsgList.dat";
const std::string Constant::FreeSpaceFile="../Files/FreeSpaceList.dat";

#endif /*__CONSTANT__H_*/


