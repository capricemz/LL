#pragma execution_character_set("utf-8")

#include "ManagerData.h"
#include "common/util/UtilString.h"

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
	CC_SAFE_DELETE(_handleDataUnlock);
	CC_SAFE_DELETE(_handleDataGrid);
	CC_SAFE_DELETE(_handleDataEntity);
	CC_SAFE_DELETE(_handleDataLevels);
	CC_SAFE_DELETE(_handleDataIncome);
}

void ManagerData::setSaveFileExist()
{
	auto userDefault = UserDefault::getInstance();
	auto key = getUserDefaultKey(USER_DEFAULT_KEY_ISFE);
	userDefault->setBoolForKey(key.c_str(), true);//д��bool�ж�λ
}

bool ManagerData::isSaveFileExist()
{
	auto userDefault = UserDefault::getInstance();
	auto key = getUserDefaultKey(USER_DEFAULT_KEY_ISFE);
	if (!userDefault->getBoolForKey(key.c_str()))//ͨ�����õ�bool�ͱ�־λ�жϣ����������
	{
		_handleDataTime->dataFileInit();
		_handleDataUnlock->dataFileInit();
		_handleDataEntity->dataFileInit();
		_handleDataIncome->dataFileInit();
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
		_handleDataUnlock->dataFileGet();
		_handleDataEntity->dataFileGet();
		_handleDataIncome->dataFileGet();
	}
}

void ManagerData::dataFileAllSet()
{
	_handleDataTime->dataFileSet();
	_handleDataUnlock->dataFileSet();
	_handleDataEntity->dataFileSet();
	_handleDataIncome->dataFileSet();
}

ManagerData::ManagerData() : _indexCareer(0)
{
	initHandleDatas();
}

void ManagerData::initHandleDatas()
{
	_handleDataTime = new HandleDataTime();
	_handleDataUnlock = new HandleDataUnlock();
	_handleDataGrid = new HandleDataGrid();
	_handleDataEntity = new HandleDataEntity();
	_handleDataLevels = new HandleDataLevels();
	_handleDataIncome = new HandleDataIncome();
}
