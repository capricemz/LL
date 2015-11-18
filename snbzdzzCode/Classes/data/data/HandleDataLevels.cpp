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
	userDefault->setStringForKey(USER_DEFAULT_KEY_DL.c_str(), "");//写入初始数据
	userDefault->flush();//设置完一定要调用flush，才能从缓冲写入io
}

void HandleDataLevels::dataFileGet()
{
	auto userDefault = UserDefault::getInstance();
	auto strDataTimeData = userDefault->getStringForKey(USER_DEFAULT_KEY_DL.c_str());
}

void HandleDataLevels::dataFileSet()
{
	auto userDefault = UserDefault::getInstance();
	userDefault->setStringForKey(USER_DEFAULT_KEY_DL.c_str(), "");//修改存档//TODO
	userDefault->flush();
}
