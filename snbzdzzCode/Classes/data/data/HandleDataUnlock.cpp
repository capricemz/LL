#pragma execution_character_set("utf-8")

#include "ManagerData.h"
#include "common/util/UtilString.h"
#include "../config/ManagerCfg.h"

HandleDataUnlock::HandleDataUnlock() : 
	_dicTypeUnlockMaid({}), 
	_dicDicTypeUnlockSkill({}),
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
	_dicTypeUnlockLevel.clear();
	_dicTypePassedLevel.clear();
	_dicDicTypeCompleteLevelTarget.clear();
	_vecDataUnlock.clear();
}

void HandleDataUnlock::dataFileInit()
{
	/*auto userDefault = UserDefault::getInstance();
	userDefault->setStringForKey(USER_DEFAULT_KEY_DU.c_str(), "");//写入初始数据
	userDefault->flush();//设置完一定要调用flush，才能从缓冲写入io*/
	createTypeUnlockOther();
	setIsUnlockMaid(DATA_UNLOCK_INIT_MAID);
	setIsUnlockLevel(DATA_UNLOCK_INIT_LEVEL);
	dataFileSet();
}

void HandleDataUnlock::dataFileGet()
{
	createTypeUnlockOther();
	auto userDefault = UserDefault::getInstance();
	auto strDataUnlock = userDefault->getStringForKey(USER_DEFAULT_KEY_DU.c_str());
	auto vecDataUnlock = UtilString::split(strDataUnlock, ":");
	_vecDataUnlock.clear();
	for (auto var : vecDataUnlock)
	{
		_vecDataUnlock.push_back(Value(var).asInt());
	}
	setIsUnlockMaid(1001);//for test
}

void HandleDataUnlock::dataFileSet()
{
	auto userDefault = UserDefault::getInstance();
	string strDataUnlock = "";
	auto length = (int)_vecDataUnlock.size();
	for (auto i = 0; i < length; i++)
	{
		strDataUnlock += Value(_vecDataUnlock[i]).asString() + (i == length - 1 ? "" : ":");
	}
	userDefault->setStringForKey(USER_DEFAULT_KEY_DU.c_str(), strDataUnlock);//修改存档
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
			if (cfgSkill.unlock != "")
			{
				_dicDicTypeUnlockSkill[cfgSkill.id][cfgSkill.index] = indexUnlockCurrent++;
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
	auto index = _dicDicTypeUnlockSkill[idSkill][indexSkill];
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
