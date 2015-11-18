#pragma execution_character_set("utf-8")

#include "ManagerData.h"

DataLevels::DataLevels()
{
}

DataLevels::~DataLevels()
{
}

bool DataLevels::init()
{
	auto isInit = false;
	do
	{
		isInit = true;
	} while (0);
	return isInit;
}

HandleDataLevels::HandleDataLevels() : _levelCurrent(0)
{
}

HandleDataLevels::~HandleDataLevels()
{
}

void HandleDataLevels::dataFileInit()
{
	auto userDefault = UserDefault::getInstance();
	userDefault->setStringForKey(USER_DEFAULT_KEY_DL.c_str(), "");//д���ʼ����
	userDefault->flush();//������һ��Ҫ����flush�����ܴӻ���д��io
}

void HandleDataLevels::dataFileGet()
{
	auto userDefault = UserDefault::getInstance();
	auto strDataTimeData = userDefault->getStringForKey(USER_DEFAULT_KEY_DL.c_str());
}

void HandleDataLevels::dataFileSet()
{
	auto userDefault = UserDefault::getInstance();
	userDefault->setStringForKey(USER_DEFAULT_KEY_DL.c_str(), "");//�޸Ĵ浵//TODO
	userDefault->flush();
}
