#pragma execution_character_set("utf-8")

#include "ManagerData.h"

static ManagerData *_instance;

ManagerData * ManagerData::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new ManagerData();
	}
	return _instance;
}

void ManagerData::destroyInstance()
{
	CC_SAFE_DELETE(_instance);
}

ManagerData::~ManagerData()
{
	CC_SAFE_DELETE(_handleDataTime);
	CC_SAFE_DELETE(_handleDataGrid);
	CC_SAFE_DELETE(_handleDataEntity);
	CC_SAFE_DELETE(_handleDataLevels);
}

void ManagerData::setSaveFileExist()
{
	auto userDefault = UserDefault::getInstance();
	userDefault->setBoolForKey(USER_DEFAULT_KEY_ISFE.c_str(), true);//写入bool判断位
}

bool ManagerData::isSaveFileExist()
{
	auto userDefault = UserDefault::getInstance();
	if (!userDefault->getBoolForKey(USER_DEFAULT_KEY_ISFE.c_str()))//通过设置的bool型标志位判断，如果不存在
	{
		_handleDataTime->dataFileInit();
		_handleDataEntity->dataFileInit();
		_handleDataLevels->dataFileInit();
		return false;
	}
	else
	{
		return true;
	}
}

void ManagerData::dataFileGet()
{
	if (isSaveFileExist())
	{
		_handleDataTime->dataFileGet();
		_handleDataEntity->dataFileGet();
		_handleDataLevels->dataFileGet();
	}
}

void ManagerData::dataFileSet()
{
	_handleDataTime->dataFileSet();
	_handleDataEntity->dataFileSet();
	_handleDataLevels->dataFileSet();
}

ManagerData::ManagerData()
{
	initHandleDatas();
}

void ManagerData::initHandleDatas()
{
	_handleDataTime = new HandleDataTime();
	_handleDataGrid = new HandleDataGrid();
	_handleDataEntity = new HandleDataEntity();
	_handleDataLevels = new HandleDataLevels();
}
