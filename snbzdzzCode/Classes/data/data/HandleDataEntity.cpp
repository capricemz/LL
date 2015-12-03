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
	_vecSkillActiveNeedBuy({}),
	_vecSkillActiveInUse({}),
	_vecSkillActiveUseOver({}),
	_vecSkillActive({}),
	_vecSkillPassive({}),
	_vecSkillRandom({}),
	_round(0)
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
	CCASSERT(cfgEntity.skillGroup != 0,"DataEntity::updateSkillGroup cfgEntity.skillGroup == 0");
	vecSkillClear();
	auto managerCfg = ManagerCfg::getInstance();
	auto dicDicCfgSkillGroup = managerCfg->getDicDicDicCfgSkillGroup()[cfgEntity.skillGroup];
	auto vecCfgSkillGroupTypeArgs = managerCfg->getDicVecCfgSkillGroupTypeArgs()[cfgEntity.skillGroup];
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
		auto isBuy = handleDataUnlock->getIsBuySkill(dataSkillInfo.id, dataSkillInfo.index);
		auto indexSkill = dataSkillInfo.index + (!isBuy ? -1 : 0);
		if (indexSkill < 0)
		{
			continue;
		}
		
		auto cfgSkill = managerCfg->getDicDicCfgSkill()[dataSkillInfo.id][indexSkill];
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
	if (_dicAttribute.find(idAttribute) == _dicAttribute.end())
	{
		_dicAttribute.insert(std::make_pair(idAttribute, value));
	}
	else
	{
		_dicAttribute[idAttribute] += value;
	}
}

bool DataEntity::getIsAlive()
{
	auto hp = getAttribute(IdAttribute::ENTITY_HP);
	return hp > 0;
}

DataSkillInfo & DataEntity::vecSkillActiveInfoGet()
{
	auto &dataSkillInfo = _vecSkillActive[0];
	_vecSkillActive.erase(_vecSkillActive.begin());
	_vecSkillActiveInUse.push_back(dataSkillInfo);
	return dataSkillInfo;
}

void DataEntity::vecSkillActiveInUse2UseOver()
{
	auto dataSkillInfo = _vecSkillActiveInUse[0];
	_vecSkillActiveInUse.erase(_vecSkillActiveInUse.begin());
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
		for (auto dataSkillInfo : _vecSkillActiveInUse)
		{
			_vecSkillActive.push_back(dataSkillInfo);
		}
		_vecSkillActiveInUse.clear();
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
	auto idSkill = dataSkillInfo.id;
	auto indexSkill = dataSkillInfo.index;
	auto num = dataSkillInfo.num;
	auto odds = dataSkillInfo.odds;
	auto handleDataUnlock = ManagerData::getInstance()->getHandleDataUnlock();
	auto dicCfgSkill = ManagerCfg::getInstance()->getDicDicCfgSkill()[idSkill];
	auto cfgSkill = dicCfgSkill[indexSkill];
	if (cfgSkill.type == TypeSkill::ACTIVE)
	{
		if (getCfgEntity().type == TypeEntity::MAID && cfgSkill.buyCost != 0)//若技能需要购买
		{
			_vecSkillActiveNeedBuy.push_back(dataSkillInfo);
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
		if (getCfgEntity().type == TypeEntity::MAID && cfgSkill.buyCost != 0)//若技能需要购买
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
				dataSkillInfo.index = indexSkillUnbuyMin;
			}
			else
			{
				dataSkillInfo.index = indexSkillMax;
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
	_vecSkillActiveNeedBuy.clear();
	_vecSkillActive.clear();
	_vecSkillActiveInUse.clear();
	_vecSkillActiveUseOver.clear();
	_vecSkillPassive.clear();
	_vecSkillRandom.clear();
}

HandleDataEntity::HandleDataEntity() :
	_isDataFileInit(false),
	_vecDataEntityMst({}),
	_vecDataEntityMaid({}),
	_indexMst(0), 
	_indexMaid(0),
	_roundTotal(0)
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
		userDefault->setStringForKey(USER_DEFAULT_KEY_DE.c_str(), "");//写入初始数据
		userDefault->flush();//设置完一定要调用flush，才能从缓冲写入io
	}
}

void HandleDataEntity::dataFileGet()
{
	auto userDefault = UserDefault::getInstance();
	auto strDataTimeData = userDefault->getStringForKey(USER_DEFAULT_KEY_DE.c_str());
	auto vecInfo = UtilString::split(strDataTimeData, "|");
	auto vecIdEntity = UtilString::split(vecInfo[0], ":");
	createDataEntityMaid();
}

void HandleDataEntity::dataFileSet()
{
	auto userDefault = UserDefault::getInstance();
	string strDataTimeData = "";
	userDefault->setStringForKey(USER_DEFAULT_KEY_DE.c_str(), strDataTimeData);//修改存档
	userDefault->flush();
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
	_vecDataEntityMaid.clear();
	auto handleDataUnlock = ManagerData::getInstance()->getHandleDataUnlock();
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
		auto idSkill = dataSkillInfo.id;
		auto indexSkill = dataSkillInfo.index;
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

void HandleDataEntity::resetDataEntityAttributeTemp()
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
		dataEntity->setAttribute(IdAttribute::ENTITY_BREAK_CASE, 0);
		dataEntity->setAttribute(IdAttribute::ENTITY_BREAK_TAKES, 0);
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

void HandleDataEntity::addRound()
{
	_roundTotal++;
	auto dataEntityMst = getDataEntityMst();
	dataEntityMst->addRound();
	auto dataEntityMaid = getDataEntityMaid();
	dataEntityMaid->addRound();
}

void HandleDataEntity::resetRound()
{
	_roundTotal = 0;
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
		auto idSkill = dataSkillInfo.id;
		auto indexSkill = dataSkillInfo.index;
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

DataEntity * HandleDataEntity::createDataEntity(const int &idEntity)
{
	auto dataEntity = DataEntity::create();
	dataEntity->setIdEntity(idEntity);
	dataEntity->updateAttribute();
	dataEntity->updateSkillGroup();
	dataEntity->updateAttributeSkillPassive();
	return dataEntity;
}
