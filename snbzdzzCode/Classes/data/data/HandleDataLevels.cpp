#pragma execution_character_set("utf-8")

#include "ManagerData.h"
#include "common/util/UtilString.h"
#include "../config/ManagerCfg.h"
#include "../define/DefinesString.h"
#include "common/util/UtilRandom.h"
#include "ui/ManagerUI.h"

DataLevel::DataLevel() : _id(0), _index(0), _state(TypeLevelState::NONE), _vecTargetComplete({}), _vecVecAward({})
{
}

DataLevel::~DataLevel()
{
	_vecTargetComplete.clear();
	_vecVecAward.clear();
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
	auto managerData = ManagerData::getInstance();
	auto cfgLevel = getCfgLevel();
	auto handleDataUnlock = managerData->getHandleDataUnlock();
	handleDataUnlock->setIsPassedLevel(_id);
	setState();
	//
	auto targets = cfgLevel.targets;
	auto length = (int)targets.size();
	for (auto i = 0; i < length; i++)
	{
		auto idLevelTarget = targets[i];
		if (_vecTargetComplete[i])//若额外目标完成
		{
			handleDataUnlock->setIsCompleteLevelTarget(cfgLevel.id, idLevelTarget);
		}
	}
	//处理解锁关卡数据
	auto handleDataLevels = managerData->getHandleDataLevels();
	for (auto var : cfgLevel.unlockLevels)
	{
		handleDataUnlock->setIsUnlockLevel(var);
		auto dataLevelUnlock = handleDataLevels->getDicDataLevel().at(var);
		dataLevelUnlock->setState();
	}
	auto handleDataEntity = managerData->getHandleDataEntity();
	for (auto var : cfgLevel.unlockSkills)
	{
		handleDataUnlock->setIsUnlockSkill(var[0], var[1]);
	}
	if (cfgLevel.unlockSkills.size() != 0)
	{
		handleDataEntity->getDataEntityMaid()->updateSkillGroup();
	}
	for (auto var : cfgLevel.unlockMaids)
	{
		handleDataUnlock->setIsUnlockMaid(var);//解锁女仆
		handleDataEntity->createDataEntityMaid(var);//构建女仆数据
	}
	handleDataUnlock->dataFileSet();//保存数据
	//处理收益数据
	auto award = getVecIdThingAward(true);
	dealPassedIncome(award);
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
			isTargetComplete = handleDataEntity->isBattleWin();
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

vector<vector<int>> DataLevel::getVecIdThingAward(const bool &isGetNew /*= false*/)
{
	if (_vecVecAward.size() != 0 && !isGetNew)
	{
		return _vecVecAward;
	}
	auto cfgLevel = getCfgLevel();
	for (auto var : cfgLevel.award)
	{
		auto idThing = (int)var.first;
		auto value = var.second[0];
		auto odds = var.second[1];
		auto random = UtilRandom::randomBewteen(0.0f, 1000.0f);
		if (random < odds)
		{
			auto isFind = false;
			for (auto &var1 : _vecVecAward)
			{
				if (var1[0] == idThing)
				{
					var1[1] += value;
					isFind = true;
					break;
				}
			}
			if (!isFind)
			{
				_vecVecAward.push_back({ (int)idThing, value });
			}
		}
	}

	auto targets = cfgLevel.targets;
	auto length = (int)targets.size();
	for (auto i = 0; i < length; i++)
	{
		auto idLevelTarget = targets[i];
		if (_vecTargetComplete[i])//若额外目标完成
		{
			auto cfgLevelTarget = ManagerCfg::getInstance()->getDicCfgLevelTargets().at(idLevelTarget);
			for (auto var : cfgLevelTarget.award)
			{
				auto idThing = (int)var.first;
				auto value = var.second[0];
				auto odds = var.second[1];
				auto random = UtilRandom::randomBewteen(0.0f, 1000.0f);
				if (random < odds)
				{
					auto isFind = false;
					for (auto &var1 : _vecVecAward)
					{
						if (var1[0] == idThing)
						{
							var1[1] += value;
							isFind = true;
							break;
						}
					}
					if (!isFind)
					{
						_vecVecAward.push_back({ (int)idThing, value });
					}
				}
			}
		}
	}

	return _vecVecAward;
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
	if (cfgLevelTarget.type == TypeLevelTarget::HP_MST || cfgLevelTarget.type == TypeLevelTarget::HP_MAID)
	{
		UtilString::stringReplace(text, "&a", cfgLevelTarget.type == TypeLevelTarget::HP_MST ? vecStr[0] : vecStr[1]);
		UtilString::stringReplace(text, "&b", cfgLevelTarget.args > 0 ? vecStr[4] : vecStr[5]);
		UtilString::stringReplace(text, "&x", Value(abs(cfgLevelTarget.args)).asString());
	}
	else
	{
		UtilString::stringReplace(text, "&x", Value(cfgLevelTarget.args).asString());
	}
	return text;
}

void DataLevel::dealPassedIncome(const vector<vector<int>> &award)
{
	auto handleDataIncome = ManagerData::getInstance()->getHandleDataIncome();
	for (auto var : award)
	{
		auto idThing = (IdThing)var[0];
		auto value = var[1];
		handleDataIncome->addThing(idThing, value);
	}
	handleDataIncome->dataFileSet();
	ManagerUI::getInstance()->notify(ID_OBSERVER::SCENE_MAIN, TYPE_OBSERVER_SCENE_MAIN::UPDATE_LAYOUT_TOP);
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
