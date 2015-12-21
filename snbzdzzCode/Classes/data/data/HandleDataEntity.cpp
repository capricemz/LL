#pragma execution_character_set("utf-8")

#include "ManagerData.h"
#include "../config/ManagerCfg.h"
#include "common/util/UtilRandom.h"
#include "common/util/UtilDate.h"
#include "core/grid/ManagerGrid.h"
#include "core/entity/ManagerEntity.h"
#include "ui/ManagerUI.h"

DataEntity::DataEntity() :
	_idEntity(0),
	_index(0),
	_dicAttribute({}),
	_vecSkillActive({}),
	_dicSkillActiveInUse({}),
	_vecSkillActiveUseOver({}),
	_vecSkillBase({}),
	_vecSkillSpecial({}),
	_vecSkillEnergy({}),
	_vecSkillPassive({}),
	_vecSkillRandom({}),
	_round(1)
{

}

DataEntity::~DataEntity()
{
	_dicAttribute.clear();
	vecSkillClear();
}

bool DataEntity::init()
{
	auto isInit = false;
	do
	{
		isInit = true;
	} while (0);
	return isInit;
}

CfgEntity DataEntity::getCfgEntity()
{
	auto cfgEntity = ManagerCfg::getInstance()->getDicCfgEntity()[_idEntity];
	return cfgEntity;
}

void DataEntity::updateAttribute()
{
	auto cfgEntity = getCfgEntity();
	CCASSERT(cfgEntity.attribute != "", "DataEntity::updateAttribute cfgEntity.attribute == """);
	_dicAttribute.clear();
	auto vecAttrItem = UtilString::split(cfgEntity.attribute, "|");
	for (auto strAttrItem : vecAttrItem)
	{
		auto vecAttr = UtilString::split(strAttrItem, ":");
		auto idAttribute = (IdAttribute)Value(vecAttr[0]).asInt();
		auto value = Value(vecAttr[1]).asInt();
		setAttribute(idAttribute, value);
	}
}

void DataEntity::updateSkillGroup()
{
	auto cfgEntity = getCfgEntity();
	CCASSERT(cfgEntity.idSkillGroup != 0,"DataEntity::updateSkillGroup cfgEntity.idSkillGroup == 0");
	vecSkillClear();
	auto managerCfg = ManagerCfg::getInstance();
	auto dicDicCfgSkillGroup = managerCfg->getDicDicDicCfgSkillGroup()[cfgEntity.idSkillGroup];
	auto vecCfgSkillGroupTypeArgs = managerCfg->getDicVecCfgSkillGroupTypeArgs()[cfgEntity.idSkillGroup];
	map<int32_t, CfgSkillGroup> dicCfgSkillGroup;
	CfgSkillGroup cfgSkillGroup;
	for (auto typeArgs : vecCfgSkillGroupTypeArgs)
	{
		auto isArgsMeet = typeArgs == "";
		if (typeArgs != "")
		{
			for (auto var : UtilString::split(typeArgs, "|"))
			{
				auto vecArgs = UtilString::split(var, ":");
				TypeSkillGroup type = (TypeSkillGroup)Value(vecArgs[0]).asInt();
				int value = Value(vecArgs[1]).asInt();
				if (type == TypeSkillGroup::HP_PERCENT)
				{
					auto hp = getAttribute(IdAttribute::ENTITY_HP);
					auto hpMax = getAttribute(IdAttribute::ENTITY_HP_MAX);
					auto hpPercent = (float)hp / (float)hpMax * 100.0f;
					isArgsMeet = hpPercent <= value;
				}
				else if (type == TypeSkillGroup::ENERGY_VALUE)
				{
					auto energy = getAttribute(IdAttribute::ENTITY_ENERGY);
					isArgsMeet = energy == value;
				}
				else if (type == TypeSkillGroup::ROUND_TOTAL)
				{
					auto roundTotal = ManagerData::getInstance()->getHandleDataEntity()->getRoundTotal();
					isArgsMeet = roundTotal == value;
				}
				else if (type == TypeSkillGroup::ROUND)
				{
					isArgsMeet = _round == value;
				}
				if (!isArgsMeet)
				{
					break;
				}
			}
		}
		if (isArgsMeet)
		{
			dicCfgSkillGroup = dicDicCfgSkillGroup[typeArgs];
			auto index = 0;
			if (dicCfgSkillGroup.size() > 1)
			{
				index = UtilRandom::randomBewteen(0.0f, (float)dicCfgSkillGroup.size());
			}
			cfgSkillGroup = dicCfgSkillGroup[index];
			break;
		}
	}
	auto vecDataSkillInfo = cfgSkillGroup.skills;
	for (auto dataSkillInfo : vecDataSkillInfo)
	{
		setSkill(dataSkillInfo);
	}
}

void DataEntity::updateAttributeSkillPassive()
{
	auto managerCfg = ManagerCfg::getInstance();
	auto handleDataUnlock = ManagerData::getInstance()->getHandleDataUnlock();
	for (auto dataSkillInfo : _vecSkillPassive)
	{
		auto isBuy = handleDataUnlock->getIsBuySkill(dataSkillInfo.idSkill, dataSkillInfo.indexSkill);
		auto indexSkill = dataSkillInfo.indexSkill + (!isBuy ? -1 : 0);
		if (indexSkill < 0)
		{
			continue;
		}
		
		auto cfgSkill = managerCfg->getDicDicCfgSkill()[dataSkillInfo.idSkill][indexSkill];
		auto vecAttrItem = UtilString::split(cfgSkill.effect, "|");
		for (auto strAttrItem : vecAttrItem)
		{
			auto vecAttr = UtilString::split(strAttrItem, ":");
			auto idAttribute = (IdAttribute)Value(vecAttr[0]).asInt();
			auto value = Value(vecAttr[1]).asInt();
			auto cfgAttribute = managerCfg->getDicCfgAttribute()[(int)idAttribute];
			if (cfgAttribute.type == TypeAttribute::ENTITY)
			{
				setAttribute(idAttribute, value);
			}
		}
	}
}

int DataEntity::getAttribute(IdAttribute idAttribute)
{
	if (_dicAttribute.find(idAttribute) == _dicAttribute.end())
	{
		return 0;
	}
	else
	{
		return _dicAttribute[idAttribute];
	}
}

void DataEntity::setAttribute(IdAttribute idAttribute, int value)
{
	if (_dicAttribute.find(idAttribute) == _dicAttribute.end())//若无该值
	{
		if (value != 0)
		{
			_dicAttribute.insert(std::make_pair(idAttribute, value));
		}
	}
	else
	{
		if (value == 0)
		{
			_dicAttribute.erase(idAttribute);
		}
		else
		{
			_dicAttribute[idAttribute] = value;
		}
	}
}

void DataEntity::addAttribute(IdAttribute idAttribute, int value)
{
	if (value == 0)
	{
		return;
	}
	setAttribute(idAttribute, getAttribute(idAttribute) + value);
}

void DataEntity::addAttributeLimit(const IdAttribute &idAttribute, const int &value)
{
	addAttribute(idAttribute, value);
	auto valueMax = INT32_MAX;
	if (idAttribute == IdAttribute::ENTITY_HP)
	{
		valueMax = getAttribute(IdAttribute::ENTITY_HP_MAX);
	}
	else if (idAttribute == IdAttribute::ENTITY_ENERGY)
	{
		valueMax = getAttribute(IdAttribute::ENTITY_ENERGY_MAX);
	}
	auto valueNew = getAttribute(idAttribute);
	if (valueNew < 0)
	{
		setAttribute(idAttribute, 0);
	}
	else if (valueNew > valueMax)
	{
		setAttribute(idAttribute, valueMax);
	}
}

bool DataEntity::getIsAlive()
{
	auto hp = getAttribute(IdAttribute::ENTITY_HP);
	return hp > 0;
}

DataSkillInfo DataEntity::vecSkillActiveInfoGet()
{
	auto dataSkillInfo = _vecSkillActive[0];
	_vecSkillActive.erase(_vecSkillActive.begin());
	for (auto i = 0; i < GRID_SELECT_MAX; i++)
	{
		if (_dicSkillActiveInUse.find(i) == _dicSkillActiveInUse.end())
		{
			_dicSkillActiveInUse.insert(make_pair(i, dataSkillInfo));
			break;
		}
	}
	return dataSkillInfo;
}

void DataEntity::vecSkillActiveInUse2UseOver()
{
	auto dicGridBattle = ManagerGrid::getInstance()->getDicGridBattle();
	auto grid = dicGridBattle.at(1);
	auto index = grid->getDataGrid()->getIndexGrid();

	/*auto dataSkillInfo = _dicSkillActiveInUse[0];
	_dicSkillActiveInUse.erase(_dicSkillActiveInUse.begin());*/
	auto dataSkillInfo = _dicSkillActiveInUse[index];
	_dicSkillActiveInUse.erase(index);
	_vecSkillActiveUseOver.push_back(dataSkillInfo);
}

bool DataEntity::vecSkillActiveIsAllUse()
{
	return _vecSkillActive.size() < GRID_SELECTED_MAX;
}

void DataEntity::vecSkillActiveSort(const bool &isAll /*= false*/)
{
	if (isAll)
	{
		for (auto var : _dicSkillActiveInUse)
		{
			auto dataSkillInfo = var.second;
			_vecSkillActive.push_back(dataSkillInfo);
		}
		_dicSkillActiveInUse.clear();
	}
	for (auto dataSkillInfo : _vecSkillActiveUseOver)
	{
		_vecSkillActive.push_back(dataSkillInfo);
	}
	_vecSkillActiveUseOver.clear();
	int size = _vecSkillActive.size();
	for (auto i = 0; i < size; i++)
	{
		int random = UtilRandom::randomBewteen(0.0f, (float)size);
		swap(_vecSkillActive[i], _vecSkillActive[random]);
	}
}

void DataEntity::setSkill(DataSkillInfo &dataSkillInfo)
{
	auto idSkill = dataSkillInfo.idSkill;
	auto indexSkill = dataSkillInfo.indexSkill;
	auto num = dataSkillInfo.num;
	auto odds = dataSkillInfo.odds;
	auto handleDataUnlock = ManagerData::getInstance()->getHandleDataUnlock();
	auto dicCfgSkill = ManagerCfg::getInstance()->getDicDicCfgSkill()[idSkill];
	auto cfgSkill = dicCfgSkill[indexSkill];
	if (cfgSkill.type == TypeSkill::BASE || cfgSkill.type == TypeSkill::SPECIAL || cfgSkill.type == TypeSkill::ENERGY)
	{
		if (getCfgEntity().type == TypeEntity::MAID)
		{
			if (cfgSkill.type == TypeSkill::BASE)
			{
				_vecSkillBase.push_back(dataSkillInfo);
			}
			else if (cfgSkill.type == TypeSkill::SPECIAL)
			{
				_vecSkillSpecial.push_back(dataSkillInfo);
			}
			else if (cfgSkill.type == TypeSkill::ENERGY)
			{
				_vecSkillEnergy.push_back(dataSkillInfo);
			}
			
			auto isUnlock = handleDataUnlock->getIsUnlockSkill(idSkill, indexSkill);
			if (!isUnlock)//若未解锁
			{
				return;
			}

			auto isBuy = handleDataUnlock->getIsBuySkill(idSkill, indexSkill);
			if (!isBuy)//若未购买
			{
				return;
			}
		}
		auto numTemp = num;
		while (numTemp--)
		{
			_vecSkillActive.push_back(dataSkillInfo);
		}
	}
	else if (cfgSkill.type == TypeSkill::PASSIVE)
	{
		auto isExist = handleDataUnlock->getIsBuySkillExist(idSkill, indexSkill);
		if (isExist/*getCfgEntity().type == TypeEntity::MAID && cfgSkill.buyCost != 0*/)//若技能需要购买
		{
			auto indexSkillUnbuyMin = INT32_MAX;
			auto indexSkillMax = 0;
			for (auto var : dicCfgSkill)
			{
				auto indexSkillCurrent = var.first;
				auto isBuy = handleDataUnlock->getIsBuySkill(idSkill, indexSkillCurrent);
				if (!isBuy && (indexSkillUnbuyMin > indexSkillCurrent))//若未购买且最小未购买大于当前
				{
					indexSkillUnbuyMin = indexSkillCurrent;
				}
				if (indexSkillMax < indexSkillCurrent)
				{
					indexSkillMax = indexSkillCurrent;
				}
			}
			if (indexSkillUnbuyMin != INT32_MAX)//若获取到最小未购买index
			{
				dataSkillInfo.indexSkill = indexSkillUnbuyMin;
			}
			else
			{
				dataSkillInfo.indexSkill = indexSkillMax;
			}
		}
		_vecSkillPassive.push_back(dataSkillInfo);
	}
	else if (cfgSkill.type == TypeSkill::RANDOM)
	{
		_vecSkillRandom.push_back(dataSkillInfo);
	}
}

void DataEntity::vecSkillClear()
{
	_vecSkillSpecial.clear();
	_vecSkillActive.clear();
	_dicSkillActiveInUse.clear();
	_vecSkillActiveUseOver.clear();
	_vecSkillPassive.clear();
	_vecSkillRandom.clear();
}

void DataEntity::addRound()
{
	_round++;
}

HandleDataEntity::HandleDataEntity() :
	_isDataFileInit(false),
	_vecDataEntityMst({}),
	_vecDataEntityMaid({}),
	_indexMst(0), 
	_indexMaid(0),
	_roundTotal(1)
{
}

HandleDataEntity::~HandleDataEntity()
{
	_vecDataEntityMst.clear();
	_vecDataEntityMaid.clear();
}

void HandleDataEntity::dataFileInit()
{
	if (!_isDataFileInit)
	{
		_isDataFileInit = true;
		auto userDefault = UserDefault::getInstance();
		auto key = ManagerData::getInstance()->getUserDefaultKey(USER_DEFAULT_KEY_DE);
		userDefault->setStringForKey(key.c_str(), Value(DATA_UNLOCK_INIT_MAID).asString());//写入初始数据
		userDefault->flush();//设置完一定要调用flush，才能从缓冲写入io
	}
}

void HandleDataEntity::dataFileGet()
{
	auto userDefault = UserDefault::getInstance();
	auto key = ManagerData::getInstance()->getUserDefaultKey(USER_DEFAULT_KEY_DE);
	auto strData = userDefault->getStringForKey(key.c_str());
	auto vecData = UtilString::split(strData, ":");
	auto length = (int)vecData.size();
	for (auto i = 0; i < length; i++)
	{
		_dicSortIdEntityMaid[Value(vecData[i]).asInt()] = i;
	}
}

void HandleDataEntity::dataFileSet()
{
	string strData = "";
	auto length = (int)_vecDataEntityMaid.size();
	for (auto i = 0; i < length; i++)
	{
		strData += i == 0 ? "" : ":";
		strData += Value(_vecDataEntityMaid.at(i)->getIdEntity()).asString();
	}
	auto key = ManagerData::getInstance()->getUserDefaultKey(USER_DEFAULT_KEY_DE);
	auto userDefault = UserDefault::getInstance();
	userDefault->setStringForKey(key.c_str(), strData);//修改存档
	userDefault->flush();
}

void HandleDataEntity::updateAttributeGrade()
{
	auto handleDataIncome = ManagerData::getInstance()->getHandleDataIncome();
	auto value = handleDataIncome->getThing(IdThing::EXP);//当前经验

	auto managerCfg = ManagerCfg::getInstance();
	auto dicCfgGrade = managerCfg->getDicCfgGrade();
	auto id = 1000;
	string effect = "";
	while (true)
	{
		if (dicCfgGrade.find(id) == dicCfgGrade.end())
		{
			break;
		}

		auto cfgGradeTemp = dicCfgGrade[id];

		if (value < cfgGradeTemp.exp)
		{
			break;
		}

		effect = cfgGradeTemp.effect;

		id++;
	}//获取当前等级配置

	if (effect == "")
	{
		return;
	}

	auto vecAttrItem = UtilString::split(effect, "|");
	for (auto strAttrItem : vecAttrItem)
	{
		auto vecAttr = UtilString::split(strAttrItem, ":");
		auto idEntity = Value(vecAttr[0]).asInt();
		auto length = (int)_vecDataEntityMaid.size();
		for (auto i = 0; i < length; i++)
		{
			auto dataEntity = _vecDataEntityMaid.at(i);
			if (dataEntity->getIdEntity() == idEntity)
			{
				auto idAttribute = (IdAttribute)Value(vecAttr[1]).asInt();
				auto value = Value(vecAttr[2]).asInt();
				auto cfgAttribute = managerCfg->getDicCfgAttribute()[(int)idAttribute];
				if (cfgAttribute.type == TypeAttribute::ENTITY)
				{
					dataEntity->setAttribute(idAttribute, value);
				}
				break;
			}
		}
	}
}

void HandleDataEntity::resetDataEntityMaid()
{
	for (auto var : _vecDataEntityMaid)
	{
		auto hpMax = var->getAttribute(IdAttribute::ENTITY_HP_MAX);
		var->setAttribute(IdAttribute::ENTITY_HP, hpMax);
		var->setAttribute(IdAttribute::ENTITY_ENERGY, 0);
		var->setAttribute(IdAttribute::ENTITY_KILL_NUM, 0);
		var->setAttribute(IdAttribute::ENTITY_BREAK_CASE_NUM, 0);
		var->setAttribute(IdAttribute::ENTITY_BREAK_TAKES_NUM, 0);
		var->setAttribute(IdAttribute::ENTITY_GOLD_INCOME_NUM, 0);
		var->setAttribute(IdAttribute::ENTITY_STONE_CRUSHED_NUM, 0);
		var->setAttribute(IdAttribute::ENTITY_ICE_MELTING_NUM, 0);
		var->setAttribute(IdAttribute::ENTITY_TRAP_DISARM_NUM, 0);
	}
}

void HandleDataEntity::createDataEntityMaid()
{
	auto handleDataUnlock = ManagerData::getInstance()->getHandleDataUnlock();
	if (_dicSortIdEntityMaid.size() < 2)
	{
		auto dicCfgEntity = ManagerCfg::getInstance()->getDicCfgEntity();
		for (auto var : dicCfgEntity)
		{
			auto cfgEntity = var.second;
			auto idEntity = cfgEntity.id;
			if (cfgEntity.type == TypeEntity::MAID && handleDataUnlock->getIsUnlockMaid(idEntity))
			{
				auto dataEntity = createDataEntity(Value(idEntity).asInt());
				_vecDataEntityMaid.pushBack(dataEntity);
			}
		}
	}
	else
	{
		vector<DataEntity *> vecTemp(_dicSortIdEntityMaid.size());
		for (auto var : _dicSortIdEntityMaid)
		{
			auto dataEntity = createDataEntity(var.first);
			vecTemp[var.second] = dataEntity;
		}
		for (auto var : vecTemp)
		{
			if (handleDataUnlock->getIsUnlockMaid(var->getIdEntity()))
			{
				_vecDataEntityMaid.pushBack(var);
			}
		}
	}
	updateAttributeGrade();
}

void HandleDataEntity::createDataEntityMaid(const int &idEntity)
{
	for (auto var : _vecDataEntityMaid)
	{
		if (var->getIdEntity() == idEntity)
		{
			log("``````````HandleDataEntity::createDataEntityMaid dataEntity already exist");
			return;
		}
	}
	auto handleDataUnlock = ManagerData::getInstance()->getHandleDataUnlock();
	if (handleDataUnlock->getIsUnlockMaid(idEntity))
	{
		auto dataEntity = createDataEntity(Value(idEntity).asInt());
		_vecDataEntityMaid.pushBack(dataEntity);
	}
	dataFileSet();
}

void HandleDataEntity::createDataEntityMst()
{
	_vecDataEntityMst.clear();
	auto levelCurrent = ManagerData::getInstance()->getHandleDataLevels()->getLevelCurrent();//获取关卡id
	auto cfgLevels = ManagerCfg::getInstance()->getDicCfgLevels()[levelCurrent];
	auto vecIdDataEntity = UtilString::split(cfgLevels.msts, ":");
	for (auto idDataEntity : vecIdDataEntity)
	{
		auto dataEntity = createDataEntity(Value(idDataEntity).asInt());
		_vecDataEntityMst.pushBack(dataEntity);
	}
}

void HandleDataEntity::vecSkillActiveSortMaid()
{
	getDataEntityMaid()->vecSkillActiveSort(true);
	/*for (auto dataEntity : _vecDataEntityMaid)
	{
		dataEntity->vecSkillActiveSort(true);
	}*/
}

void HandleDataEntity::dealSkillRandom(const function<void()> &func /*= nullptr*/)
{
	auto dicGridMaidSelect = ManagerGrid::getInstance()->getDicGridMaidSelect();
	for (auto var : dicGridMaidSelect)
	{
		auto grid = (Grid *)var.second;
		if (!grid->isVisible() && grid->getIsNotCard())
		{
			grid->resetSpecialSth();
		}
	}
	auto isSet = false;
	auto vecSkillRandom = getDataEntityMst()->getVecSkillRandom();
	for (auto dataSkillInfo : vecSkillRandom)
	{
		auto idSkill = dataSkillInfo.idSkill;
		auto indexSkill = dataSkillInfo.indexSkill;
		auto num = dataSkillInfo.num;
		auto odds = dataSkillInfo.odds;
		auto random = UtilRandom::randomBewteen(0.0f, 100.0f);
		if (random < odds)
		{
			auto cfgSkill = ManagerCfg::getInstance()->getDicDicCfgSkill()[idSkill][indexSkill];
			auto vecStr = UtilString::split(cfgSkill.effect, ":");
			auto idAttribute = (IdAttribute)Value(vecStr[0]).asInt();
			if (idAttribute != IdAttribute::ENTITY_SWITCH)
			{
				auto value = Value(vecStr[1]).asInt();
				while (num--)
				{
					int index = UtilRandom::randomBewteen(0.0f, GRID_SELECT_MAX);
					auto grid = dicGridMaidSelect.at(index);
					grid->createDataGrid();
					grid->getDataGrid()->setAttribute(idAttribute, value);
					isSet = true;
				}
			}
		}
	}
	if (isSet)
	{
		ManagerUI::getInstance()->notify(ID_OBSERVER::LAYER_GRID_SELECT, TYPE_OBSERVER_LAYER_GRID_SELECT::RUN_MAID_GRID_PLAY_SPECIAL_STH_GENERATE, CallFunc::create(func));
	}
	else
	{
		CCASSERT(func != nullptr, "HandleDataEntity::dealSkillRandom func is nullptr");
		func();
	}
}

void HandleDataEntity::resetDataEntityAttributeTempTurnOver()
{
	for (auto i = 0; i < 2; i++)
	{
		auto isMst = i < 1;
		auto dataEntity = isMst ? getDataEntityMst() : getDataEntityMaid();
		dataEntity->setAttribute(IdAttribute::ENTITY_QUICK, 0);
		dataEntity->setAttribute(IdAttribute::ENTITY_DAMAGE_CASE, 0);
		dataEntity->setAttribute(IdAttribute::ENTITY_DAMAGE_TAKES, 0);
		dataEntity->setAttribute(IdAttribute::ENTITY_RESTORE_HP, 0);
		dataEntity->setAttribute(IdAttribute::ENTITY_COST_HP, 0);
		dataEntity->setAttribute(IdAttribute::ENTITY_RESTORE_ENERGY, 0);
		dataEntity->setAttribute(IdAttribute::ENTITY_COST_ENERGY, 0);
		dataEntity->setAttribute(IdAttribute::ENTITY_RESTORE_HP_ALL, 0);
		dataEntity->setAttribute(IdAttribute::ENTITY_COST_HP_ALL, 0);
		dataEntity->setAttribute(IdAttribute::ENTITY_DAMAGE_CASE_EXTRA, 0);
		dataEntity->setAttribute(IdAttribute::ENTITY_DAMAGE_TAKES_EXTRA, 0);
		dataEntity->setAttribute(IdAttribute::ENTITY_BREAK_TAKES, 0);
	}
}

void HandleDataEntity::resetDataEntityAttributeTempRoundOver()
{
	for (auto i = 0; i < 2; i++)
	{
		auto isMst = i < 1;
		auto dataEntity = isMst ? getDataEntityMst() : getDataEntityMaid();
		dataEntity->setAttribute(IdAttribute::ENTITY_DAMAGE_BREAK_COUNT, 0);
	}
}

void HandleDataEntity::dealVecSkillActiveInUse2UseOverMaid()
{
	getDataEntityMaid()->vecSkillActiveInUse2UseOver();
}

void HandleDataEntity::dealDataEntitySkillSort(const bool &isForce /*= false*/)
{
	auto dataEntityMst = getDataEntityMst();
	dataEntityMst->updateSkillGroup();//洗怪物牌

	auto dataEntityMaid = getDataEntityMaid();
	auto isAllUse = dataEntityMaid->vecSkillActiveIsAllUse();//是否要洗玩家牌
	if (isForce || isAllUse)
	{
		dataEntityMaid->vecSkillActiveSort(isForce);//洗玩家牌, 在某方死亡时才会调用强制刷新，同时需要刷新全部
	}
}

void HandleDataEntity::dealBattleOver()
{
	resetIndexMst();
	resetIndexMaid();
	resetRound();
}

int HandleDataEntity::getLengthVecDataEntity(const bool &isMst)
{
	if (isMst)
	{
		return _vecDataEntityMst.size();
	}
	else
	{
		if (_vecDataEntityMaid.size() > ENTITY_BATTLE_MAX)
		{
			return ENTITY_BATTLE_MAX;
		}
		else
		{
			return _vecDataEntityMaid.size();
		}
	}
}

bool HandleDataEntity::isAllMstDead()
{
	auto isAllDead = true;
	for (auto dataEntity : _vecDataEntityMst)
	{
		auto hp = dataEntity->getAttribute(IdAttribute::ENTITY_HP);
		if (hp != 0)
		{
			isAllDead = false;
			break;
		}
	}
	return isAllDead;
}

bool HandleDataEntity::isAllMaidDead()
{
	auto isAllDead = true;
	for (auto i = 0; i < ENTITY_BATTLE_MAX; i++)
	{
		if ((int)_vecDataEntityMaid.size() > i)
		{
			auto dataEntity = _vecDataEntityMaid.at(i);
			auto hp = dataEntity->getAttribute(IdAttribute::ENTITY_HP);
			if (hp > 0)
			{
				isAllDead = false;
				break;
			}
		}
	}
	return isAllDead;
}

bool HandleDataEntity::isBattleOver()
{
	auto isAllMstDeadGet = isAllMstDead();
	auto isAllMaidDeadGet = isAllMaidDead();
	return isAllMstDeadGet || isAllMaidDeadGet;
}

bool HandleDataEntity::isRoundLimitOver()
{
	auto handleDataLevels = ManagerData::getInstance()->getHandleDataLevels();
	auto cfgLevel = handleDataLevels->getDataLevelCurrent()->getCfgLevel();
	return cfgLevel.roundLimit != 0 && cfgLevel.roundLimit < _roundTotal;
}

bool HandleDataEntity::isBattleWin()
{
	auto isAllMstDeadGet = isAllMstDead();
	auto isAllMaidDeadGet = isAllMaidDead();
	auto isRoundLimitOverGet = isRoundLimitOver();
	auto handleDataLevels = ManagerData::getInstance()->getHandleDataLevels();
	auto cfgLevel = handleDataLevels->getDataLevelCurrent()->getCfgLevel();
	return (isAllMstDeadGet && !isAllMaidDeadGet) || (isRoundLimitOverGet && cfgLevel.isRoundLimitWin);
}

void HandleDataEntity::addRound()
{
	_roundTotal++;
	auto dataEntityMst = getDataEntityMst();
	dataEntityMst->addRound();
	auto dataEntityMaid = getDataEntityMaid();
	dataEntityMaid->addRound();
	ManagerUI::getInstance()->notify(ID_OBSERVER::LAYER_BATTLE, TYPE_OBSERVER_LAYER_BATTLE::UPDATE_TXT_ROUND);
}

void HandleDataEntity::resetRound()
{
	_roundTotal = 1;
	auto dataEntityMst = getDataEntityMst();
	dataEntityMst->resetRound();
	auto dataEntityMaid = getDataEntityMaid();
	dataEntityMaid->resetRound();
}

bool HandleDataEntity::getIsSkillNeedSwitchMst(int &indexTo)
{
	auto vecSkillRandom = getDataEntityMst()->getVecSkillRandom();
	for (auto dataSkillInfo : vecSkillRandom)
	{
		auto idSkill = dataSkillInfo.idSkill;
		auto indexSkill = dataSkillInfo.indexSkill;
		auto num = dataSkillInfo.num;
		auto odds = dataSkillInfo.odds;
		auto random = UtilRandom::randomBewteen(0.0f, 100.0f);
		if (random < odds)
		{
			auto cfgSkill = ManagerCfg::getInstance()->getDicDicCfgSkill()[idSkill][indexSkill];
			auto vecStr = UtilString::split(cfgSkill.effect, ":");
			auto idAttributeEntity = (IdAttribute)Value(vecStr[0]).asInt();
			if (idAttributeEntity == IdAttribute::ENTITY_SWITCH)
			{
				indexTo = Value(vecStr[1]).asInt();
				return true;
			}
		}
	}
	return false;
}

bool HandleDataEntity::getIsAnyMstCanCatch()
{
	for (auto var : _vecDataEntityMst)
	{
		auto value = var->getAttribute(IdAttribute::ENTITY_BREAK_TAKES_NUM);
		if (value > 0)
		{
			return true;
		}
	}
	return false;
}

DataEntity * HandleDataEntity::createDataEntity(const int &idEntity)
{
	auto dataEntity = DataEntity::create();
	dataEntity->setIdEntity(idEntity);
	dataEntity->updateAttribute();
	dataEntity->updateSkillGroup();
	dataEntity->updateAttributeSkillPassive();
	return dataEntity;
}
