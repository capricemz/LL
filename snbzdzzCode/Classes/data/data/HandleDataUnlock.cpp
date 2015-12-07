#pragma execution_character_set("utf-8")

#include "ManagerData.h"
#include "common/util/UtilString.h"
#include "../config/ManagerCfg.h"

HandleDataUnlock::HandleDataUnlock() : 
	_isDataFileInit(false),
	_dicTypeUnlockMaid({}), 
	_dicDicTypeUnlockSkill({}),
	_dicDicTypeBuySkill({}),
	_dicTypeUnlockLevel({}),
	_dicTypePassedLevel({}),
	_dicDicTypeCompleteLevelTarget({}),
	_vecDataUnlock({})
{
}

HandleDataUnlock::~HandleDataUnlock()
{
	_dicTypeUnlockMaid.clear();
	_dicDicTypeUnlockSkill.clear();
	_dicDicTypeBuySkill.clear();
	_dicTypeUnlockLevel.clear();
	_dicTypePassedLevel.clear();
	_dicDicTypeCompleteLevelTarget.clear();
	_vecDataUnlock.clear();
}

void HandleDataUnlock::dataFileInit()
{
	if (!_isDataFileInit)
	{
		_isDataFileInit = true;
		/*auto userDefault = UserDefault::getInstance();
		auto key = ManagerData::getInstance()->getUserDefaultKey(USER_DEFAULT_KEY_DU);
		userDefault->setStringForKey(key.c_str(), "");//д���ʼ����
		userDefault->flush();//������һ��Ҫ����flush�����ܴӻ���д��io*/
		createTypeUnlockOther();
		setIsUnlockMaid(DATA_UNLOCK_INIT_MAID);
		setIsUnlockLevel(DATA_UNLOCK_INIT_LEVEL);
		dataFileSet();
	}
}

void HandleDataUnlock::dataFileGet()
{
	createTypeUnlockOther();
	auto userDefault = UserDefault::getInstance();
	auto key = ManagerData::getInstance()->getUserDefaultKey(USER_DEFAULT_KEY_DU);
	auto strData = userDefault->getStringForKey(key.c_str());
	auto vecData = UtilString::split(strData, ":");
	_vecDataUnlock.clear();
	for (int i = vecData.size() - 1; i >= 0; i--)
	{
		_vecDataUnlock.push_back(Value(vecData[i]).asInt());
	}
	/*setIsUnlockMaid(1001);//for test*/
}

void HandleDataUnlock::dataFileSet()
{
	auto userDefault = UserDefault::getInstance();
	string strData = "";
	auto length = (int)_vecDataUnlock.size();
	for (auto i = 0; i < length; i++)
	{
		strData = Value(_vecDataUnlock[i]).asString() + (i == 0 ? "" : (":" + strData));
	}
	auto key = ManagerData::getInstance()->getUserDefaultKey(USER_DEFAULT_KEY_DU);
	userDefault->setStringForKey(key.c_str(), strData);//�޸Ĵ浵
	userDefault->flush();
}

void HandleDataUnlock::createTypeUnlockOther()
{
	auto indexUnlockCurrent = (int)TypeUnlock::LAST_NEXT;
	auto managerCfg = ManagerCfg::getInstance();
	auto dicCfgEntity = managerCfg->getDicCfgEntity();
	for (auto var : dicCfgEntity)
	{
		auto cfgEntity = var.second;
		if (cfgEntity.type == TypeEntity::MAID)
		{
			_dicTypeUnlockMaid[cfgEntity.id] = indexUnlockCurrent++;
		}
	}
	auto dicDicCfgSkill = managerCfg->getDicDicCfgSkill();
	for (auto var : dicDicCfgSkill)
	{
		auto dicCfgSkill = var.second;
		for (auto var1 : dicCfgSkill)
		{
			auto cfgSkill = var1.second;
			if (cfgSkill.buyCost != 0)
			{
				_dicDicTypeUnlockSkill[cfgSkill.id][cfgSkill.index] = indexUnlockCurrent++;
				_dicDicTypeBuySkill[cfgSkill.id][cfgSkill.index] = indexUnlockCurrent++;
			}
		}
	}
	auto dicCfgLevels = managerCfg->getDicCfgLevels();
	for (auto var : dicCfgLevels)
	{
		auto idLevel = var.second.id;
		_dicTypeUnlockLevel[idLevel] = indexUnlockCurrent++;
		_dicTypePassedLevel[idLevel] = indexUnlockCurrent++;
		for (auto var1 : var.second.targets)
		{
			_dicDicTypeCompleteLevelTarget[idLevel][var1] = indexUnlockCurrent++;
		}
	}
}

bool HandleDataUnlock::getIsUnlockMaid(const int &idEntity)
{
	auto index = _dicTypeUnlockMaid[idEntity];
	return getIsUnlock(index);
}

void HandleDataUnlock::setIsUnlockMaid(const int &idEntity)
{
	auto index = _dicTypeUnlockMaid[idEntity];
	setIsUnlock(index);
}

bool HandleDataUnlock::getIsUnlockSkill(const int &idSkill, const int &indexSkill)
{
	auto index = _dicDicTypeUnlockSkill[idSkill][indexSkill];
	return getIsUnlock(index);
}

void HandleDataUnlock::setIsUnlockSkill(const int &idSkill, const int &indexSkill)
{
	if (indexSkill == -1)
	{
		auto dicTypeUnlockSkill = _dicDicTypeUnlockSkill[idSkill];
		for (auto var : dicTypeUnlockSkill)
		{
			auto index = _dicDicTypeUnlockSkill[idSkill][var.first];
			setIsUnlock(index);
		}
	}
	else
	{
		auto index = _dicDicTypeUnlockSkill[idSkill][indexSkill];
		setIsUnlock(index);
	}
}

bool HandleDataUnlock::getIsBuySkill(const int &idSkill, const int &indexSkill)
{
	auto index = _dicDicTypeBuySkill[idSkill][indexSkill];
	return getIsUnlock(index);
}

void HandleDataUnlock::setIsBuySkill(const int &idSkill, const int &indexSkill)
{
	auto index = _dicDicTypeBuySkill[idSkill][indexSkill];
	setIsUnlock(index);
}

bool HandleDataUnlock::getIsUnlockLevel(const int &idLevel)
{
	auto index = _dicTypeUnlockLevel[idLevel];
	return getIsUnlock(index);
}

void HandleDataUnlock::setIsUnlockLevel(const int &idLevel)
{
	auto index = _dicTypeUnlockLevel[idLevel];
	setIsUnlock(index);
}

bool HandleDataUnlock::getIsPassedLevel(const int &idLevel)
{
	auto index = _dicTypePassedLevel[idLevel];
	return getIsUnlock(index);
}

void HandleDataUnlock::setIsPassedLevel(const int &idLevel)
{
	auto index = _dicTypePassedLevel[idLevel];
	setIsUnlock(index);
}

bool HandleDataUnlock::getIsCompleteLevelTarget(const int &idLevel, const int &idLevelTarget)
{
	auto index = _dicDicTypeCompleteLevelTarget[idLevel][idLevelTarget];
	return getIsUnlock(index);
}

void HandleDataUnlock::setIsCompleteLevelTarget(const int &idLevel, const int &idLevelTarget)
{
	auto index = _dicDicTypeCompleteLevelTarget[idLevel][idLevelTarget];
	setIsUnlock(index);
}

bool HandleDataUnlock::getIsUnlock(int index)
{
	auto indexVecUnlock = index / 32;
	if ((int)_vecDataUnlock.size() <= indexVecUnlock)
	{
		_vecDataUnlock.resize(indexVecUnlock + 1);
	}
	return (_vecDataUnlock[indexVecUnlock] & (1 << (index % 32))) != 0;
}

void HandleDataUnlock::setIsUnlock(int index)
{
	auto indexVecUnlock = index / 32;
	if ((int)_vecDataUnlock.size() <= indexVecUnlock)
	{
		_vecDataUnlock.resize(indexVecUnlock + 1);
	}
	_vecDataUnlock[indexVecUnlock] |= (1 << (index % 32));
}
