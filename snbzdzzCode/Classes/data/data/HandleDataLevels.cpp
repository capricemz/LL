#pragma execution_character_set("utf-8")

#include "ManagerData.h"
#include "common/util/UtilString.h"
#include "../config/ManagerCfg.h"

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
	auto strDatalevels = userDefault->getStringForKey(USER_DEFAULT_KEY_DL.c_str());
	auto vecDataLevels = UtilString::split(strDatalevels, "|");
	_levelCurrent = Value(vecDataLevels[0]).asInt();
}

void HandleDataLevels::dataFileSet()
{
	auto userDefault = UserDefault::getInstance();
	auto strDatalevels = Value(_levelCurrent).asString();
	userDefault->setStringForKey(USER_DEFAULT_KEY_DL.c_str(), strDatalevels);//�޸Ĵ浵//TODO
	userDefault->flush();
}

CfgLevels HandleDataLevels::getCfgLevels()
{
	auto cfgLevels = ManagerCfg::getInstance()->getDicCfgLevels()[_levelCurrent];
	return cfgLevels;
}