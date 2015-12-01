#pragma execution_character_set("utf-8")

#include "ManagerData.h"
#include "common/util/UtilString.h"
#include "../config/ManagerCfg.h"

DataLevel::DataLevel() : _id(0), _state(TypeLevelState::NONE), _vecTargetComplete({})
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

	auto cfgLevel = getCfgLevel();
	auto targets = cfgLevel.targets;
	auto length = (int)targets.size();
	for (auto i = 0; i < length; i++)
	{
		auto idLevelTarget = targets[i];

		if (_vecTargetComplete[i])
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
			isTargetComplete = _state == TypeLevelState::PASSING;
		}
		else
		{
			auto value = handleDataEntity->getDataEntityMaid()->getAttribute(dicTypeLevelTarget2IdAttribute.at(type));
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

CfgLevel DataLevel::getCfgLevel() const
{
	auto cfgLevel = ManagerCfg::getInstance()->getDicCfgLevels()[_id];
	return cfgLevel;
}

void DataLevel::setVecTargetComplete()
{
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
