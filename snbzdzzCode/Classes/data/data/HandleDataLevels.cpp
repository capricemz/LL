#pragma execution_character_set("utf-8")

#include "ManagerData.h"
#include "common/util/UtilString.h"
#include "../config/ManagerCfg.h"
#include "../define/DefinesString.h"

DataLevel::DataLevel() : _id(0), _index(0), _state(TypeLevelState::NONE), _vecTargetComplete({})
{
}

DataLevel::~DataLevel()
{
}

bool DataLevel::init()
{
	auto isInit = false;
	do
	{
		isInit = true;
	} while (0);
	return isInit;
}

void DataLevel::assignCfgLevel(const int &idLevel)
{
	_id = idLevel;
	setState();
	setVecTargetComplete();
}

void DataLevel::dealLevelPassed()
{
	auto cfgLevel = getCfgLevel();
	auto handleDataUnlock = ManagerData::getInstance()->getHandleDataUnlock();
	handleDataUnlock->setIsPassedLevel(_id);
	setState();
	//
	auto targets = cfgLevel.targets;
	auto length = (int)targets.size();
	for (auto i = 0; i < length; i++)
	{
		auto idLevelTarget = targets[i];
		if (_vecTargetComplete[i])
		{
			handleDataUnlock->setIsCompleteLevelTarget(cfgLevel.id, idLevelTarget);
		}
	}
	//处理解锁关卡数据
	auto handleDataLevels = ManagerData::getInstance()->getHandleDataLevels();
	handleDataUnlock->setIsUnlockLevel(cfgLevel.unlockLevel);
	auto dataLevelUnlock = handleDataLevels->getDicDataLevel().at(cfgLevel.unlockLevel);
	dataLevelUnlock->setState();
	//保存数据
	handleDataUnlock->dataFileSet();
}

void DataLevel::dealLevelTarget()
{
	auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
	auto handleDataUnlock = ManagerData::getInstance()->getHandleDataUnlock();

	auto cfgLevel = getCfgLevel();
	auto targets = cfgLevel.targets;
	auto length = (int)targets.size();
	for (auto i = 0; i < length; i++)
	{
		auto idLevelTarget = targets[i];

		auto isComplete = handleDataUnlock->getIsCompleteLevelTarget(cfgLevel.id, idLevelTarget);
		if (isComplete)
		{
			continue;
		}

		auto cfgLevelTarget = ManagerCfg::getInstance()->getDicCfgLevelTargets()[idLevelTarget];

		auto type = cfgLevelTarget.type;
		auto args = cfgLevelTarget.args;
		auto roundLimitMst = cfgLevelTarget.roundLimitMst;
		auto roundLimitMaid = cfgLevelTarget.roundLimitMaid;
		auto roundLimitTotal = cfgLevelTarget.roundLimitTotal;
		auto isTargetComplete = false;

		auto roundMst = handleDataEntity->getDataEntityMst()->getRound();
		if (roundLimitMst != 0 && roundLimitMst < roundMst)
		{
			continue;
		}
		auto roundMaid = handleDataEntity->getDataEntityMaid()->getRound();
		if (roundLimitMaid != 0 && roundLimitMaid < roundMaid)
		{
			continue;
		}
		auto roundTotal = handleDataEntity->getRoundTotal();
		if (roundLimitTotal != 0 && roundLimitTotal < roundTotal)
		{
			continue;
		}

		if (type == TypeLevelTarget::HP_MST || type == TypeLevelTarget::HP_MAID)
		{
			auto dataEntity = type == TypeLevelTarget::HP_MST ? handleDataEntity->getDataEntityMst() : handleDataEntity->getDataEntityMaid();
			auto hp = dataEntity->getAttribute(IdAttribute::ENTITY_HP);
			auto hpMax = dataEntity->getAttribute(IdAttribute::ENTITY_HP_MAX);
			auto hpPrecent = ((float)hp / (float)hpMax) * 100.0f;

			isTargetComplete = (args > 0 && hpPrecent >= args) || (args < 0 && hpPrecent <= abs(args));
		}
		else if (type == TypeLevelTarget::PASS)
		{
			auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
			auto isAllMstDead = handleDataEntity->isAllMstDead();
			auto isAllMaidDead = handleDataEntity->isAllMaidDead();
			isTargetComplete = isAllMstDead && !isAllMaidDead;
		}
		else
		{
			auto dataEntityMaid = handleDataEntity->getDataEntityMaid();
			auto idAttribute = dicTypeLevelTarget2IdAttribute.at(type);
			auto value = dataEntityMaid->getAttribute(idAttribute);
			isTargetComplete = value >= args;
		}
		_vecTargetComplete[i] = isTargetComplete;
	}
}

void DataLevel::setState()
{
	auto managerData = ManagerData::getInstance();
	auto isUnlock = managerData->getHandleDataUnlock()->getIsUnlockLevel(_id);
	if (!isUnlock)
	{
		_state = TypeLevelState::LOCK;
		return;
	}
	auto isPassed = managerData->getHandleDataUnlock()->getIsPassedLevel(_id);
	if (isPassed)
	{
		_state = TypeLevelState::PASSED;
		return;
	}
	_state = TypeLevelState::CURRENT;
}

void DataLevel::setVecTargetComplete()
{
	_vecTargetComplete.clear();
	auto handleDataUnlock = ManagerData::getInstance()->getHandleDataUnlock();
	auto cfgLevel = getCfgLevel();
	auto targets = cfgLevel.targets;
	auto length = (int)targets.size();
	for (auto i = 0; i < length; i++)
	{
		auto idLevelTarget = targets[i];
		auto isComplete = handleDataUnlock->getIsCompleteLevelTarget(cfgLevel.id, idLevelTarget);
		_vecTargetComplete.push_back(isComplete);
	}
}

CfgLevel DataLevel::getCfgLevel() const
{
	auto cfgLevel = ManagerCfg::getInstance()->getDicCfgLevels()[_id];
	return cfgLevel;
}

std::string DataLevel::getLevelTargetStr(const int &index) const
{
	auto vecIdLevelTarget = getCfgLevel().targets;
	if ((int)vecIdLevelTarget.size() <= index)
	{
		return "";
	}
	string text = "";
	auto vecStr = UtilString::split(STR_LEVEL_TARGET, "|");
	auto idLevelTarget = vecIdLevelTarget.at(index);
	auto cfgLevelTarget = ManagerCfg::getInstance()->getDicCfgLevelTargets()[idLevelTarget];
	if (cfgLevelTarget.roundLimitMst != 0)
	{
		text += vecStr[0] + vecStr[2] + STR_COMMA;
		UtilString::stringReplace(text, "&x", Value(cfgLevelTarget.roundLimitMst).asString());
	}
	if (cfgLevelTarget.roundLimitMaid != 0)
	{
		text += vecStr[1] + vecStr[2] + STR_COMMA;
		UtilString::stringReplace(text, "&x", Value(cfgLevelTarget.roundLimitMaid).asString());
	}
	if (cfgLevelTarget.roundLimitTotal != 0)
	{
		text += vecStr[3] + STR_COMMA;
		UtilString::stringReplace(text, "&x", Value(cfgLevelTarget.roundLimitTotal).asString());
	}
	text += DIC_STR_BY_LEVEL_TARGET_TYPE.at(cfgLevelTarget.type);
	if (cfgLevelTarget.type == TypeLevelTarget::HP_MST)
	{
		UtilString::stringReplace(text, "&a", vecStr[0]);
		UtilString::stringReplace(text, "&b", cfgLevelTarget.args > 0 ? vecStr[4] : vecStr[5]);
		UtilString::stringReplace(text, "&x", Value(abs(cfgLevelTarget.args)).asString());
	}
	else if (cfgLevelTarget.type == TypeLevelTarget::HP_MAID)
	{
		UtilString::stringReplace(text, "&a", vecStr[1]);
		UtilString::stringReplace(text, "&b", cfgLevelTarget.args > 0 ? vecStr[4] : vecStr[5]);
		UtilString::stringReplace(text, "&x", Value(abs(cfgLevelTarget.args)).asString());
	}
	else
	{
		UtilString::stringReplace(text, "&x", Value(cfgLevelTarget.args).asString());
	}
	return text;
}

HandleDataLevels::HandleDataLevels() : _dicDataLevel({}), _levelCurrent(0)
{
}

HandleDataLevels::~HandleDataLevels()
{
}

void HandleDataLevels::createDicDataLevel()
{
	auto dicCfgLevels = ManagerCfg::getInstance()->getDicCfgLevels();
	for (auto var : dicCfgLevels)
	{
		auto cfgLevel = var.second;
		auto idLevel = cfgLevel.id;
		auto dataLevel = DataLevel::create();
		dataLevel->assignCfgLevel(idLevel);
		_dicDataLevel.insert(idLevel, dataLevel);
	}
}
