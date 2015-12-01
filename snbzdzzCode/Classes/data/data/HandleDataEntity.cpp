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
	auto vecSkillItem = UtilString::split(cfgSkillGroup.skills, "|");
	for (auto skillInfo : vecSkillItem)
	{
		setSkill(skillInfo);
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

vector<int> DataEntity::vecSkillActiveInfoGet()
{
	auto vecSkill = _vecSkillActive[0];
	_vecSkillActive.erase(_vecSkillActive.begin());
	_vecSkillActiveInUse.push_back(vecSkill);
	return vecSkill;
}

void DataEntity::vecSkillActiveInUse2UseOver()
{
	auto vecSkill = _vecSkillActiveInUse[0];
	_vecSkillActiveInUse.erase(_vecSkillActiveInUse.begin());
	_vecSkillActiveUseOver.push_back(vecSkill);
}

bool DataEntity::vecSkillActiveIsAllUse()
{
	return _vecSkillActive.size() < GRID_SELECTED_MAX;
}

void DataEntity::vecSkillActiveSort(const bool &isAll /*= false*/)
{
	if (isAll)
	{
		for (auto vecSkill : _vecSkillActiveInUse)
		{
			_vecSkillActive.push_back(vecSkill);
		}
		_vecSkillActiveInUse.clear();
	}
	for (auto vecSkill : _vecSkillActiveUseOver)
	{
		_vecSkillActive.push_back(vecSkill);
	}
	_vecSkillActiveUseOver.clear();
	int size = _vecSkillActive.size();
	for (auto i = 0; i < size; i++)
	{
		int random = UtilRandom::randomBewteen(0.0f, (float)size);
		swap(_vecSkillActive[i], _vecSkillActive[random]);
	}
}

void DataEntity::setSkill(const string &skillInfo)
{
	auto vecSkillStr = UtilString::split(skillInfo, ":");
	auto idSkill = Value(vecSkillStr[0]).asInt();
	auto indexSkill = Value(vecSkillStr[1]).asInt();
	auto num = Value(vecSkillStr[2]).asInt();
	auto odds = Value(vecSkillStr[3]).asInt();
	vector<int> vecSkillInfo = { idSkill, indexSkill, num, odds};
	auto handleDataUnlock = ManagerData::getInstance()->getHandleDataUnlock();
	auto dicCfgSkill = ManagerCfg::getInstance()->getDicDicCfgSkill()[idSkill];
	auto cfgSkill = dicCfgSkill[indexSkill];
	if (cfgSkill.type == TypeSkill::ACTIVE)
	{
		if (getCfgEntity().type == TypeEntity::MAID && cfgSkill.unlock != "")//若技能需要解锁
		{
			auto isUnlockSkill = handleDataUnlock->getIsUnlockSkill(idSkill, indexSkill);
			if (!isUnlockSkill)//若未解锁
			{
				return;
			}
		}
		auto numTemp = num;
		while (numTemp--)
		{
			_vecSkillActive.push_back(vecSkillInfo);
		}
	}
	else if (cfgSkill.type == TypeSkill::PASSIVE)
	{
		if (getCfgEntity().type == TypeEntity::MAID && cfgSkill.unlock != "")//若技能需要解锁
		{
			auto indexSkillUnlockMax = -1;
			for (auto var : dicCfgSkill)
			{
				auto indexSkillCurrent = var.first;
				auto isUnlockSkill = handleDataUnlock->getIsUnlockSkill(idSkill, indexSkillCurrent);
				if (isUnlockSkill && (indexSkillUnlockMax < indexSkillCurrent))//若解锁且最大小于当前
				{
					indexSkillUnlockMax = indexSkillCurrent;
				}
			}
			if (indexSkillUnlockMax == -1)
			{
				return;
			}
			vecSkillInfo[1] = indexSkillUnlockMax;
		}
		_vecSkillPassive.push_back(vecSkillInfo);
	}
	else if (cfgSkill.type == TypeSkill::RANDOM)
	{
		_vecSkillRandom.push_back(vecSkillInfo);
	}
}

void DataEntity::vecSkillClear()
{
	_vecSkillActive.clear();
	_vecSkillActiveInUse.clear();
	_vecSkillActiveUseOver.clear();
	_vecSkillPassive.clear();
	_vecSkillRandom.clear();
}

HandleDataEntity::HandleDataEntity() :
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
	auto userDefault = UserDefault::getInstance();
	userDefault->setStringForKey(USER_DEFAULT_KEY_DE.c_str(), "");//写入初始数据
	userDefault->flush();//设置完一定要调用flush，才能从缓冲写入io
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
	for (auto skillInfo : vecSkillRandom)
	{
		auto idSkill = skillInfo[0];
		auto indexSkill = skillInfo[1];
		auto num = skillInfo[2];
		auto odds = skillInfo[3];
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
	for (auto dataEntity : _vecDataEntityMaid)
	{
		auto hp = dataEntity->getAttribute(IdAttribute::ENTITY_HP);
		if (hp > 0)
		{
			isAllDead = false;
			break;
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
	for (auto skillInfo : vecSkillRandom)
	{
		auto idSkill = skillInfo[0];
		auto indexSkill = skillInfo[1];
		auto num = skillInfo[2];
		auto odds = skillInfo[3];
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
	return dataEntity;
}
