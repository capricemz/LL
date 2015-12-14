#pragma execution_character_set("utf-8")

#include "ManagerData.h"
#include "common/util/UtilString.h"
#include "../config/ManagerCfg.h"

HandleDataUnlock::HandleDataUnlock() : 
	_isDataFileInit(false),
	_dicTypeUnlockMaid({}),
	_dicTypeBuyMaid({}),
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
	_dicTypeBuyMaid.clear();
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
		userDefault->setStringForKey(key.c_str(), "");//写入初始数据
		userDefault->flush();//设置完一定要调用flush，才能从缓冲写入io*/
		createTypeUnlockOther();
		setIsUnlockMaid(DATA_UNLOCK_INIT_MAID);
		setIsBuyMaid(DATA_UNLOCK_INIT_MAID);
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
	userDefault->setStringForKey(key.c_str(), strData);//修改存档
	userDefault->flush();
}

void HandleDataUnlock::createTypeUnlockOther()
{
	auto indexUnlockCurrent = (int)TypeUnlock::LAST_NEXT;
	//默认解锁数据
	_dicTypeUnlockMaid[DATA_UNLOCK_INIT_MAID] = indexUnlockCurrent++;
	_dicTypeBuyMaid[DATA_UNLOCK_INIT_MAID] = indexUnlockCurrent++;
	//
	auto managerCfg = ManagerCfg::getInstance();
	auto dicCfgEntity = managerCfg->getDicCfgEntity();
	
	for (auto var : dicCfgEntity)
	{
		auto cfgEntity = var.second;
		if (cfgEntity.type == TypeEntity::MAID && cfgEntity.cost != 0)
		{
			_dicTypeBuyMaid[cfgEntity.id] = indexUnlockCurrent++;
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
				_dicDicTypeBuySkill[cfgSkill.id][cfgSkill.index] = indexUnlockCurrent++;
			}
		}
	}
	auto dicCfgLevels = managerCfg->getDicCfgLevels();
	for (auto var : dicCfgLevels)
	{
		auto idLevel = var.second.id;
		auto cfgLevel = var.second;

		_dicTypeUnlockLevel[idLevel] = indexUnlockCurrent++;
		_dicTypePassedLevel[idLevel] = indexUnlockCurrent++;
		for (auto idLevelTarget : cfgLevel.targets)
		{
			_dicDicTypeCompleteLevelTarget[idLevel][idLevelTarget] = indexUnlockCurrent++;
		}

		for (auto var1 : cfgLevel.unlockSkills)
		{
			auto idSkill = var1[0];
			auto index = var1[1];
			if (index == -1)
			{
				auto dicDicCfgSkill = managerCfg->getDicDicCfgSkill();
				for (auto var2 : dicDicCfgSkill[idSkill])
				{
					auto cfgSkill = var2.second;
					_dicDicTypeUnlockSkill[cfgSkill.id][cfgSkill.index] = indexUnlockCurrent++;
				}
			}
			else
			{
				_dicDicTypeUnlockSkill[idSkill][index] = indexUnlockCurrent++;
			}
		}
		
		for (auto idEntity : cfgLevel.unlockMaids)
		{
			_dicTypeUnlockMaid[idEntity] = indexUnlockCurrent++;
		}
	}
}

bool HandleDataUnlock::getIsUnlockMaid(const int &idEntity)
{
	if (_dicTypeUnlockMaid.find(idEntity) == _dicTypeUnlockMaid.end())
	{
		return false;
	}
	auto index = _dicTypeUnlockMaid[idEntity];
	return getIsUnlock(index);
}

void HandleDataUnlock::setIsUnlockMaid(const int &idEntity)
{
	if (_dicTypeUnlockMaid.find(idEntity) == _dicTypeUnlockMaid.end())
	{
		return;
	}
	auto index = _dicTypeUnlockMaid[idEntity];
	setIsUnlock(index);
}

bool HandleDataUnlock::getIsBuyMaid(const int &idEntity)
{
	if (_dicTypeBuyMaid.find(idEntity) == _dicTypeBuyMaid.end())
	{
		return false;
	}
	auto index = _dicTypeBuyMaid[idEntity];
	return getIsUnlock(index);
}

void HandleDataUnlock::setIsBuyMaid(const int &idEntity)
{
	if (_dicTypeBuyMaid.find(idEntity) == _dicTypeBuyMaid.end())
	{
		return;
	}
	auto index = _dicTypeBuyMaid[idEntity];
	setIsUnlock(index);
}

bool HandleDataUnlock::getIsUnlockSkill(const int &idSkill, const int &indexSkill)
{
	if (_dicDicTypeUnlockSkill.find(idSkill) == _dicDicTypeUnlockSkill.end())
	{
		return false;
	}
	if (_dicDicTypeUnlockSkill[idSkill].find(indexSkill) == _dicDicTypeUnlockSkill[idSkill].end())
	{
		return false;
	}
	auto index = _dicDicTypeUnlockSkill[idSkill][indexSkill];
	return getIsUnlock(index);
}

void HandleDataUnlock::setIsUnlockSkill(const int &idSkill, const int &indexSkill)
{
	if (_dicDicTypeUnlockSkill.find(idSkill) == _dicDicTypeUnlockSkill.end())
	{
		return;
	}
	if (_dicDicTypeUnlockSkill[idSkill].find(indexSkill) == _dicDicTypeUnlockSkill[idSkill].end())
	{
		return;
	}
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
	if (_dicDicTypeBuySkill.find(idSkill) == _dicDicTypeBuySkill.end())
	{
		return false;
	}
	if (_dicDicTypeBuySkill[idSkill].find(indexSkill) == _dicDicTypeBuySkill[idSkill].end())
	{
		return false;
	}
	auto index = _dicDicTypeBuySkill[idSkill][indexSkill];
	return getIsUnlock(index);
}

void HandleDataUnlock::setIsBuySkill(const int &idSkill, const int &indexSkill)
{
	if (_dicDicTypeBuySkill.find(idSkill) == _dicDicTypeBuySkill.end())
	{
		return;
	}
	if (_dicDicTypeBuySkill[idSkill].find(indexSkill) == _dicDicTypeBuySkill[idSkill].end())
	{
		return;
	}
	auto index = _dicDicTypeBuySkill[idSkill][indexSkill];
	setIsUnlock(index);
}

bool HandleDataUnlock::getIsUnlockLevel(const int &idLevel)
{
	if (_dicTypeUnlockLevel.find(idLevel) == _dicTypeUnlockLevel.end())
	{
		return false;
	}
	auto index = _dicTypeUnlockLevel[idLevel];
	return getIsUnlock(index);
}

void HandleDataUnlock::setIsUnlockLevel(const int &idLevel)
{
	if (_dicTypeUnlockLevel.find(idLevel) == _dicTypeUnlockLevel.end())
	{
		return;
	}
	auto index = _dicTypeUnlockLevel[idLevel];
	setIsUnlock(index);
}

bool HandleDataUnlock::getIsPassedLevel(const int &idLevel)
{
	if (_dicTypePassedLevel.find(idLevel) == _dicTypePassedLevel.end())
	{
		return false;
	}
	auto index = _dicTypePassedLevel[idLevel];
	return getIsUnlock(index);
}

void HandleDataUnlock::setIsPassedLevel(const int &idLevel)
{
	if (_dicTypePassedLevel.find(idLevel) == _dicTypePassedLevel.end())
	{
		return;
	}
	auto index = _dicTypePassedLevel[idLevel];
	setIsUnlock(index);
}

bool HandleDataUnlock::getIsCompleteLevelTarget(const int &idLevel, const int &idLevelTarget)
{
	if (_dicDicTypeCompleteLevelTarget.find(idLevel) == _dicDicTypeCompleteLevelTarget.end())
	{
		return false;
	}
	if (_dicDicTypeCompleteLevelTarget[idLevel].find(idLevelTarget) == _dicDicTypeCompleteLevelTarget[idLevel].end())
	{
		return false;
	}
	auto index = _dicDicTypeCompleteLevelTarget[idLevel][idLevelTarget];
	return getIsUnlock(index);
}

void HandleDataUnlock::setIsCompleteLevelTarget(const int &idLevel, const int &idLevelTarget)
{
	if (_dicDicTypeCompleteLevelTarget.find(idLevel) == _dicDicTypeCompleteLevelTarget.end())
	{
		return;
	}
	if (_dicDicTypeCompleteLevelTarget[idLevel].find(idLevelTarget) == _dicDicTypeCompleteLevelTarget[idLevel].end())
	{
		return;
	}
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
