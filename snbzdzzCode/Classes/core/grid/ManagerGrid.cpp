#pragma execution_character_set("utf-8")

#include "ManagerGrid.h"
#include "ui/ManagerUI.h"
#include "common/util/UtilString.h"
#include "data/config/ManagerCfg.h"

static ManagerGrid *_instance;

ManagerGrid * ManagerGrid::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new ManagerGrid();
	}
	return _instance;
}

void ManagerGrid::destoryInstance()
{
	CC_SAFE_DELETE(_instance);
}

ManagerGrid::~ManagerGrid()
{
}

void ManagerGrid::setAroundGridCanMoveOver(const int &indexGrid)
{
	auto isFull = _vecDataGridMaidSelected.size() >= GRID_SELECTED_MAX;
	for (auto var : _dicGridMaidSelect)
	{
		auto grid = (Grid *)var.second;
		if (!grid->isDataGridExist())
		{
			grid->setIsCanMoveOver(false);
			continue;
		}
		
		auto indexGridTemp = grid->getIndexGrid();
		if (isFull)
		{
			grid->setIsCanMoveOver(indexGridTemp == indexGrid);
			continue;
		}
		auto isSelected = false;
		for (auto dataGridSelected : _vecDataGridMaidSelected)
		{
			if (dataGridSelected->getIndexGrid() == indexGridTemp)
			{
				isSelected = true;
				break;
			}
		}
		if (isSelected)
		{
			grid->setIsCanMoveOver(indexGridTemp == indexGrid);
		}
		else
		{
			auto postoinBasicDelta = _dicGridMaidSelect.at(4)->getPosition() - _dicGridMaidSelect.at(0)->getPosition();
			auto psotionDelta = _dicGridMaidSelect.at(indexGridTemp)->getPosition() - _dicGridMaidSelect.at(indexGrid)->getPosition();
			auto xCount = psotionDelta.x / postoinBasicDelta.x;
			auto yCount = psotionDelta.y / postoinBasicDelta.y;
			grid->setIsCanMoveOver((xCount <= 1 && xCount >= -1) && (yCount <= 1 && yCount >= -1));
		}
	}
}

bool ManagerGrid::getIsGridMoveOut(const int &index, const Vec2 &postionTouchMove, Vec2 &postionLayoutWorldMoveOver)
{
	auto grid = (Grid *)_dicGridMaidSelect.at(index);
	auto rect = grid->getLayoutTouch()->getBoundingBox();
	rect.origin.x -= 15;
	rect.origin.y -= 15;
	rect.size.width += 30;
	rect.size.height += 30;//允许稍微加大一点触摸位置，游戏实际需要
	auto postionInGrid = grid->convertToNodeSpace(postionTouchMove);
	auto isMoverOut = !rect.containsPoint(postionInGrid);
	if (isMoverOut)
	{
		postionLayoutWorldMoveOver = grid->getLayoutTouch()->getWorldPosition();
	}
	return isMoverOut;
}

bool ManagerGrid::getIsGridMoveToLast(int &indexLast, const float &rotation, const Vec2 &positionBegan)
{
	if (_vecDataGridMaidSelected.size() < 1)
	{
		return false;
	}
	auto dataGridMaidSelected = _vecDataGridMaidSelected.at(_vecDataGridMaidSelected.size() - 1);
	auto indexGridMaidSelect = dataGridMaidSelected->getIndexGrid();
	auto gridMaidSelect = (Grid *)_dicGridMaidSelect.at(indexGridMaidSelect);
	auto postionWorldGridMaidSelectLast = gridMaidSelect->getLayoutTouch()->getWorldPosition();
	auto postionDelta = postionWorldGridMaidSelectLast - positionBegan;
	auto rotationLast = postionDelta.getAngle() * -180.0f / acos(-1.0);
	auto rotationMax = rotationLast + 22.5f;
	auto rotationMin = rotationLast - 22.5f;
	auto rotationTrue = rotation;
	if (rotation < 0 && rotationLast > 0)
	{
		rotationTrue = rotationTrue + 360.0f;
	}
	else if (rotation > 0 && rotationLast < 0)
	{
		rotationTrue = rotationTrue - 360.0f;
	}
	if (rotationTrue < rotationMax && rotationTrue > rotationMin)
	{
		indexLast = indexGridMaidSelect;
		return true;
	}
	return false;
}

bool ManagerGrid::getIsGridMoveOver(const Vec2 &postionTouchMove, Vec2 &postionLayoutWorldMoveOver, int &indexGridMoveOver)
{
	for (auto var : _dicGridMaidSelect)
	{
		auto grid = (Grid *)var.second;
		if (!grid->isCanMoveOver())
		{
			continue;
		}
		auto rect = grid->getLayoutTouch()->getBoundingBox();
		auto postionInGrid = grid->convertToNodeSpace(postionTouchMove);
		auto isMoverOver = rect.containsPoint(postionInGrid);
		if (isMoverOver)
		{
			auto layoutTouch = grid->getLayoutTouch();
			postionLayoutWorldMoveOver = layoutTouch->getWorldPosition();
			indexGridMoveOver = grid->getIndexGrid();
			return true;
		}
	}
	return false;
}

void ManagerGrid::linkDataGridSelected()
{
	DataGrid *dataGridMst = nullptr;
	DataGrid *dataGridMaid = nullptr;
	for (auto i = 0; i < GRID_SELECTED_MAX; i++)
	{
		auto grid = (Grid *)_dicGridMstSelected.at(i);
		auto dataGridTemp = grid->getDataGrid();
		if (dataGridMst)
		{
			dataGridMst->setDataGridNext(dataGridTemp);
		}
		dataGridMst = dataGridTemp;
		grid = (Grid *)_dicGridMaidSelected.at(i);
		dataGridTemp = grid->getDataGrid();
		if (dataGridMaid)
		{
			dataGridMaid->setDataGridNext(dataGridTemp);
		}
		dataGridMaid = dataGridTemp;
	}
	dataGridMst->setDataGridNext(nullptr);
	dataGridMaid->setDataGridNext(nullptr);
}

float ManagerGrid::durationPlaySpecialSthBeUse()
{
	return _dicGridBattle.at(1)->durationPlaySpecialSthBeUse();
}

void ManagerGrid::dealSpecialSth()
{
	auto dataEntityMaid = ManagerData::getInstance()->getHandleDataEntity()->getDataEntityMaid();
	auto valueGoldIncome = dataEntityMaid->getAttribute(IdAttribute::ENTITY_GOLD_INCOME);
	auto valueStoneCrushed = dataEntityMaid->getAttribute(IdAttribute::ENTITY_STONE_CRUSHED);
	auto valueIceMelting = dataEntityMaid->getAttribute(IdAttribute::ENTITY_ICE_MELTING);
	auto valueTrapDisarm = dataEntityMaid->getAttribute(IdAttribute::ENTITY_TRAP_DISARM);
	
	auto dataGridMaid = _dicGridBattle.at(1)->getDataGrid();
	auto valueGold = dataGridMaid->getAttribute(IdAttribute::GRID_GOLD);
	auto valueStone = dataGridMaid->getAttribute(IdAttribute::GRID_STONE);
	auto valueIce = dataGridMaid->getAttribute(IdAttribute::GRID_ICE);
	auto valueTrap = dataGridMaid->getAttribute(IdAttribute::GRID_TRAP);
	if (valueGold != 0)
	{
		//调用获得物品处理
		dataGridMaid->setAttribute(IdAttribute::GRID_GOLD_GET, valueGold + valueGoldIncome);
		dataEntityMaid->addAttribute(IdAttribute::ENTITY_GOLD_INCOME_NUM, 1);
	}
	else if (valueStone != 0 && valueStoneCrushed >= valueStone)
	{
		dataGridMaid->setAttribute(IdAttribute::GRID_STONE_CRUSHED, 1);
		dataEntityMaid->addAttribute(IdAttribute::ENTITY_STONE_CRUSHED_NUM, 1);
	}
	else if (valueIce != 0 && valueIceMelting >= valueIce)
	{
		dataGridMaid->setAttribute(IdAttribute::GRID_ICE_MELTING, 1);
		dataEntityMaid->addAttribute(IdAttribute::ENTITY_ICE_MELTING_NUM, 1);
	}
	else if (valueTrap != 0)
	{
		if (valueTrapDisarm >= valueTrap)
		{
			dataGridMaid->setAttribute(IdAttribute::GRID_TRAP_DISARM, 1);
			dataEntityMaid->addAttribute(IdAttribute::ENTITY_TRAP_DISARM_NUM, 1);
		}
		else
		{
			dataGridMaid->setAttribute(IdAttribute::GRID_TRAP_TRIGGER, 1);
		}
	}
}

void ManagerGrid::dealBattle()
{
	auto dataGridMst = _dicGridBattle.at(0)->getDataGrid();
	auto dataGridMaid = _dicGridBattle.at(1)->getDataGrid();
	auto dataEntityMst = ManagerData::getInstance()->getHandleDataEntity()->getDataEntityMst();
	auto dataEntityMaid = ManagerData::getInstance()->getHandleDataEntity()->getDataEntityMaid();

	dealAttributeCondition(dataGridMst, IdAttribute::GRID_CERTAINLY, dataGridMaid, dataEntityMst);
	dealAttributeCondition(dataGridMaid, IdAttribute::GRID_CERTAINLY, dataGridMst, dataEntityMaid);

	dealQuick(dataGridMst, dataGridMaid, dataEntityMst, dataEntityMaid);
	dealQuick(dataGridMaid, dataGridMst, dataEntityMaid, dataEntityMst);

	dealRestoreCostHp(dataGridMst, dataGridMaid, dataEntityMst, dataEntityMaid);
	dealRestoreCostHp(dataGridMaid, dataGridMst, dataEntityMaid, dataEntityMst);

	dealDamage(dataGridMst, dataGridMaid, dataEntityMst, dataEntityMaid);//处理女仆受到伤害
	dealDamage(dataGridMaid, dataGridMst, dataEntityMaid, dataEntityMst);//处理怪物受到伤害

	dealRestoreCostEnergy(dataGridMst, dataEntityMst);
	dealRestoreCostEnergy(dataGridMaid, dataEntityMaid);

	dataEntityMst->addAttribute(IdAttribute::ENTITY_RESTORE_ENERGY, 1);//每张卡默认恢复一点能量
	dataEntityMaid->addAttribute(IdAttribute::ENTITY_RESTORE_ENERGY, 1);//每张卡默认恢复一点能量

	ManagerUI::getInstance()->notify(ID_OBSERVER::HANDLE_ENTITY, TYPE_OBSERVER_HANDLE_ENTITY::RUN_ENTITY_ACTION);
}

void ManagerGrid::dealQuick(DataGrid *dataGridCase, DataGrid *dataGridTakes, DataEntity *dataEntityCase, DataEntity *dataEntityTakes)
{
	auto quick = dataGridCase->getAttribute(IdAttribute::GRID_QUICK);
	dataEntityCase->setAttribute(IdAttribute::ENTITY_QUICK, quick);
	
	if (quick)
	{
		dealAttributeCondition(dataGridCase, IdAttribute::GRID_OWN_QUICK, dataGridTakes, dataEntityCase);
		dealAttributeCondition(dataGridTakes, IdAttribute::GRID_TAKEN_QUICK, dataGridCase, dataEntityTakes);
	}
	else
	{
		dealAttributeCondition(dataGridCase, IdAttribute::GRID_UNOWN_QUICK, dataGridTakes, dataEntityCase);
		dealAttributeCondition(dataGridTakes, IdAttribute::GRID_UNTAKEN_QUICK, dataGridCase, dataEntityTakes);
	}
}

void ManagerGrid::dealDamage(DataGrid *dataGridCase, DataGrid *dataGridTakes, DataEntity *dataEntityCase, DataEntity *dataEntityTakes)
{
	auto damagePhysicalCase = dataGridCase->getAttribute(IdAttribute::GRID_DAMAGE_PHYSICAL);
	auto damageMagicCase = dataGridCase->getAttribute(IdAttribute::GRID_DAMAGE_MAGIC);
	auto damageAnyCase = dataGridCase->getAttribute(IdAttribute::GRID_DAMAGE_ANY);
	auto unblockableCase = dataGridCase->getAttribute(IdAttribute::GRID_UNBLOCKABLE);

	auto blockPhysicalTakes = dataGridTakes->getAttribute(IdAttribute::GRID_BLOCK_PHYSICAL);
	auto blockMagicTakes = dataGridTakes->getAttribute(IdAttribute::GRID_BLOCK_MAGIC);
	auto blockAnyTakes = dataGridTakes->getAttribute(IdAttribute::GRID_BLOCK_ANY);
	auto blockAllTakes = dataGridTakes->getAttribute(IdAttribute::GRID_BLOCK_ALL);

	if (unblockableCase)
	{
		dealAttributeCondition(dataGridCase, IdAttribute::GRID_OWN_UNBLOCKABLE, dataGridTakes, dataEntityCase);
		dealAttributeCondition(dataGridTakes, IdAttribute::GRID_TAKEN_UNBLOCKABLE, dataGridCase, dataEntityTakes);
	}
	else
	{
		dealAttributeCondition(dataGridCase, IdAttribute::GRID_UNOWN_UNBLOCKABLE, dataGridTakes, dataEntityCase);
		dealAttributeCondition(dataGridTakes, IdAttribute::GRID_UNTAKEN_UNBLOCKABLE, dataGridCase, dataEntityTakes);
	}

	auto blockAnyTakesRemain = blockAnyTakes - damagePhysicalCase;//减去物理伤害后的任意抵挡
	blockAnyTakesRemain = blockAnyTakesRemain < 0 ? 0 : blockAnyTakesRemain;

	auto damagePhysical = damagePhysicalCase - (unblockableCase == 0 ? blockAnyTakes : 0);//物理伤害扣除任意抵挡
	damagePhysical -= unblockableCase == 0 ? blockPhysicalTakes : 0;//物理伤害扣除物理抵挡
	damagePhysical = damagePhysical < 0 ? 0 : damagePhysical;

	auto damageMagic = damageMagicCase - (unblockableCase == 0 ? blockAnyTakesRemain : 0);//魔法伤害扣除剩余任意抵挡
	damageMagic -= unblockableCase == 0 ? blockMagicTakes : 0;//魔法伤害扣除魔法抵挡
	damageMagic = damageMagic < 0 ? 0 : damageMagic;

	damagePhysical = blockAllTakes == 0 ? damagePhysical : 0;//若有抵挡全部伤害，物理伤害置为0
	damageMagic = blockAllTakes == 0 ? damageMagic : 0;//若有抵挡全部伤害，魔法伤害置为0

	auto physicalAttackCase = dataEntityCase->getAttribute(IdAttribute::ENTITY_PHYSICAL_ATTACK);//物理攻击
	physicalAttackCase += dataEntityCase->getAttribute(IdAttribute::ENTITY_PHYSICAL_ATTACK_EXTRA);//物理攻击额外
	auto magicAttackCase = dataEntityCase->getAttribute(IdAttribute::ENTITY_MAGIC_ATTACK);//魔法攻击
	magicAttackCase += dataEntityCase->getAttribute(IdAttribute::ENTITY_MAGIC_ATTACK_EXTRA);//魔法攻击额外

	auto valueDamage = damagePhysical * physicalAttackCase + damageMagic * magicAttackCase;//实际伤害值

	dataEntityCase->setAttribute(IdAttribute::ENTITY_DAMAGE_CASE, valueDamage);
	dataEntityTakes->setAttribute(IdAttribute::ENTITY_DAMAGE_TAKES, valueDamage);

	dealDamageAttributeCondition(dataGridCase, dataGridTakes, damagePhysical, damageMagic, dataEntityCase, dataEntityTakes);
	//额外伤害处理
	auto damagePhysicalExtra = dataGridCase->getAttribute(IdAttribute::GRID_DAMAGE_PHYSICAL_EXTRA);
	auto damageMagicExtra = dataGridCase->getAttribute(IdAttribute::GRID_DAMAGE_MAGIC_EXTRA);

	auto valueDamageExtra = damagePhysicalExtra * physicalAttackCase + damageMagicExtra * magicAttackCase;//实际额外伤害值

	dataEntityCase->setAttribute(IdAttribute::ENTITY_DAMAGE_CASE_EXTRA, valueDamageExtra);
	dataEntityTakes->setAttribute(IdAttribute::ENTITY_DAMAGE_TAKES_EXTRA, valueDamageExtra);

	auto damageTotal = damagePhysical + damagePhysicalExtra + damageMagic + damageMagicExtra;
	dataEntityTakes->addAttribute(IdAttribute::ENTITY_DAMAGE_BREAK_COUNT, damageTotal);
	auto damageBreakCount = dataEntityTakes->getAttribute(IdAttribute::ENTITY_DAMAGE_BREAK_COUNT);
	if (damageBreakCount >= BREAK_DAMAGE_TAKES)
	{
		dataEntityTakes->setAttribute(IdAttribute::ENTITY_DAMAGE_BREAK_COUNT, 0);
		dataEntityCase->addAttribute(IdAttribute::ENTITY_BREAK_CASE_NUM, 1);
		dataEntityTakes->setAttribute(IdAttribute::ENTITY_BREAK_TAKES, 1);
		dataEntityTakes->addAttribute(IdAttribute::ENTITY_BREAK_TAKES_NUM, 1);
	}
}

void ManagerGrid::dealDamageAttributeCondition(DataGrid *dataGridCase, DataGrid *dataGridTakes, const int &damagePhysical, const int &damageMagic, DataEntity *dataEntityCase, DataEntity *dataEntityTakes)
{
	auto damagePhysicalCase = dataGridCase->getAttribute(IdAttribute::GRID_DAMAGE_PHYSICAL);
	auto damageMagicCase = dataGridCase->getAttribute(IdAttribute::GRID_DAMAGE_MAGIC);
	auto damageAnyCase = dataGridCase->getAttribute(IdAttribute::GRID_DAMAGE_ANY);
	auto unblockableCase = dataGridCase->getAttribute(IdAttribute::GRID_UNBLOCKABLE);

	auto blockPhysicalTakes = dataGridTakes->getAttribute(IdAttribute::GRID_BLOCK_PHYSICAL);
	auto blockMagicTakes = dataGridTakes->getAttribute(IdAttribute::GRID_BLOCK_MAGIC);
	auto blockAnyTakes = dataGridTakes->getAttribute(IdAttribute::GRID_BLOCK_ANY);
	auto blockAllTakes = dataGridTakes->getAttribute(IdAttribute::GRID_BLOCK_ALL);

	auto idAttribute = damagePhysical > 0 ? IdAttribute::GRID_PHYSICAL_DAMAGE_SUCCESS : IdAttribute::GRID_PHYSICAL_DAMAGE_FAILED;//物理伤害成功或失败
	auto value2Count = damagePhysical > 0 ? damagePhysical : -1;//若物理伤害成功，则传入最终物理伤害
	dealAttributeCondition(dataGridCase, idAttribute, dataGridTakes, dataEntityCase, value2Count);

	idAttribute = damagePhysical > 0 ? IdAttribute::GRID_PHYSICAL_BLOCK_FAILED : IdAttribute::GRID_PHYSICAL_BLOCK_SUCCESS;//物理抵挡失败或成功
	value2Count = damagePhysical > 0 ? -1 : damagePhysicalCase;//若物理抵挡成功，则传入造成方物理伤害
	dealAttributeCondition(dataGridTakes, idAttribute, dataGridCase, dataEntityTakes, value2Count);

	idAttribute = damageMagic > 0 ? IdAttribute::GRID_MAGIC_DAMAGE_SUCCESS : IdAttribute::GRID_MAGIC_DAMAGE_FAILED;//魔法伤害成功或失败
	value2Count = damageMagic > 0 ? damageMagic : -1;//若魔法伤害成功，则传入最终魔法伤害
	dealAttributeCondition(dataGridCase, idAttribute, dataGridTakes, dataEntityCase, value2Count);

	idAttribute = damageMagic > 0 ? IdAttribute::GRID_MAGIC_BLOCK_FAILED : IdAttribute::GRID_MAGIC_BLOCK_SUCCESS;//魔法抵挡失败或成功
	value2Count = damageMagic > 0 ? -1 : damageMagicCase;//若魔法抵挡成功，则传入造成方魔法伤害
	dealAttributeCondition(dataGridTakes, idAttribute, dataGridCase, dataEntityTakes, value2Count);

	idAttribute = damagePhysical > 0 || damageMagic > 0 ? IdAttribute::GRID_ANY_DAMAGE_SUCCESS : IdAttribute::ATTRIBUTE_NONE;//任意伤害成功
	value2Count = damagePhysical > 0 || damageMagic > 0 ? damagePhysical + damageMagic : -1;//若任意伤害成功，则传入最终所有伤害
	dealAttributeCondition(dataGridCase, idAttribute, dataGridTakes, dataEntityCase, value2Count);
	
	idAttribute = damagePhysical <= 0 || damageMagic <= 0 ? IdAttribute::GRID_ANY_DAMAGE_FAILED : IdAttribute::ATTRIBUTE_NONE;//任意伤害失败
	dealAttributeCondition(dataGridCase, idAttribute, dataGridTakes, dataEntityCase);
	
	idAttribute = damagePhysical > 0 || damageMagic > 0 ? IdAttribute::GRID_ANY_BLOCK_FAILED : IdAttribute::ATTRIBUTE_NONE;//任意抵挡失败
	dealAttributeCondition(dataGridTakes, idAttribute, dataGridCase, dataEntityTakes);
	
	idAttribute = damagePhysical <= 0 || damageMagic <= 0 ? IdAttribute::GRID_ANY_BLOCK_SUCCESS : IdAttribute::ATTRIBUTE_NONE;//任意抵挡成功
	value2Count = damagePhysical <= 0 || damageMagic <= 0 ? 
		(damagePhysical <= 0 && damageMagic <= 0 ? damagePhysicalCase + damageMagicCase : (damagePhysical <= 0 ? damagePhysicalCase : damageMagicCase)) :
		-1;//若任意抵挡成功，则传入接受方被抵挡类型伤害抵挡
	dealAttributeCondition(dataGridTakes, idAttribute, dataGridCase, dataEntityTakes, value2Count);

	value2Count = damagePhysical > 0 ? damagePhysical : -1;//若物理伤害成功，则传入最终物理伤害
	idAttribute = damagePhysical > 0 ? IdAttribute::GRID_N_PHYSICAL_DAMAGE : IdAttribute::ATTRIBUTE_NONE;//造成n点物理伤害
	dealAttributeCondition(dataGridCase, idAttribute, dataGridTakes, dataEntityCase, value2Count, value2Count);
	idAttribute = damagePhysical > 0 ? IdAttribute::GRID_N_PHYSICAL_TAKES : IdAttribute::ATTRIBUTE_NONE;//受到n点物理伤害
	dealAttributeCondition(dataGridTakes, idAttribute, dataGridCase, dataEntityTakes, value2Count, value2Count);

	idAttribute = damagePhysical > 0 ? IdAttribute::GRID_N_PHYSICAL_BLOCK : IdAttribute::ATTRIBUTE_NONE;//抵挡n点物理伤害
	value2Count = damagePhysical > 0 ? -1 : damagePhysicalCase;//若物理抵挡成功，则传入造成方物理伤害
	dealAttributeCondition(dataGridTakes, idAttribute, dataGridCase, dataEntityTakes, value2Count, value2Count);

	idAttribute = damageMagic > 0 ? IdAttribute::GRID_N_MAGIC_DAMAGE : IdAttribute::ATTRIBUTE_NONE;//造成n点魔法伤害
	value2Count = damageMagic > 0 ? damageMagic : -1;//若物理伤害成功，则传入最终物理伤害
	dealAttributeCondition(dataGridCase, idAttribute, dataGridTakes, dataEntityCase, value2Count, value2Count);
	idAttribute = damageMagic > 0 ? IdAttribute::GRID_N_MAGIC_TAKES : IdAttribute::ATTRIBUTE_NONE;//受到n点魔法伤害
	dealAttributeCondition(dataGridTakes, idAttribute, dataGridCase, dataEntityTakes, value2Count, value2Count);

	idAttribute = damagePhysical > 0 ? IdAttribute::GRID_N_MAGIC_BLOCK : IdAttribute::ATTRIBUTE_NONE;//抵挡n点魔法伤害
	value2Count = damageMagic > 0 ? -1 : damageMagicCase;//若魔法抵挡成功，则传入造成方魔法伤害
	dealAttributeCondition(dataGridTakes, idAttribute, dataGridCase, dataEntityTakes, value2Count, value2Count);

	value2Count = damagePhysical > 0 || damageMagic > 0 ? damagePhysical + damageMagic : -1;//若任意伤害成功，则传入最终所有伤害
	idAttribute = damagePhysical > 0 || damageMagic > 0 ? IdAttribute::GRID_N_ANY_DAMAGE : IdAttribute::ATTRIBUTE_NONE;//造成n点任意伤害
	dealAttributeCondition(dataGridCase, idAttribute, dataGridTakes, dataEntityCase, value2Count, value2Count);
	idAttribute = damagePhysical > 0 || damageMagic > 0 ? IdAttribute::GRID_N_ANY_TAKES: IdAttribute::ATTRIBUTE_NONE;//受到n点任意伤害
	dealAttributeCondition(dataGridTakes, idAttribute, dataGridCase, dataEntityTakes, value2Count, value2Count);

	idAttribute = damagePhysical <= 0 || damageMagic <= 0 ? IdAttribute::GRID_N_ANY_BLOCK : IdAttribute::ATTRIBUTE_NONE;//抵挡n点任意伤害
	value2Count = damagePhysical <= 0 || damageMagic <= 0 ?
		(damagePhysical <= 0 && damageMagic <= 0 ? damagePhysicalCase + damageMagicCase : (damagePhysical <= 0 ? damagePhysicalCase : damageMagicCase)) :
		-1;//若任意抵挡成功，则传入接受方被抵挡类型伤害抵挡
	dealAttributeCondition(dataGridTakes, idAttribute, dataGridCase, dataEntityTakes, value2Count, value2Count);
}

void ManagerGrid::dealRestoreCostHp(DataGrid *dataGridCase, DataGrid *dataGridTakes, DataEntity *dataEntityCase, DataEntity *dataEntityTakes)
{
	auto hpMax = dataEntityCase->getAttribute(IdAttribute::ENTITY_HP_MAX);

	auto restoreHpCancel = dataGridCase->getAttribute(IdAttribute::GRID_RESTORE_HP_CANCEL);
	if (restoreHpCancel == 0)//若无取消恢复生命
	{
		auto restoreHp = dataGridCase->getAttribute(IdAttribute::GRID_RESTORE_HP);
		auto valueRestore = restoreHp * hpMax * 0.1f;
		dataEntityCase->setAttribute(IdAttribute::ENTITY_RESTORE_HP, valueRestore);

		auto idAttribute = restoreHp > 0 ? IdAttribute::GRID_OWN_RESTORE_HP : IdAttribute::GRID_N_ANY_BLOCK;//若拥有恢复生命
		auto value2Count = restoreHp > 0 ? valueRestore : -1;//若拥有恢复生命，则传入恢复值
		dealAttributeCondition(dataGridCase, idAttribute, dataGridTakes, dataEntityCase, value2Count);
	}
	auto costHpCancel = dataGridCase->getAttribute(IdAttribute::GRID_COST_HP_CANCEL);
	if (costHpCancel == 0)//若无取消消耗生命
	{
		auto costHp = dataGridCase->getAttribute(IdAttribute::GRID_COST_HP);
		auto valueCost = costHp * hpMax * 0.1f;
		dataEntityCase->setAttribute(IdAttribute::ENTITY_COST_HP, valueCost);

		auto idAttribute = costHp > 0 ? IdAttribute::GRID_OWN_COST_HP : IdAttribute::GRID_N_ANY_BLOCK;//若拥有消耗生命
		auto value2Count = costHp > 0 ? costHp : -1;//若拥有消耗生命，则传入消耗值
		dealAttributeCondition(dataGridCase, idAttribute, dataGridTakes, dataEntityCase, value2Count);
	}

	auto restoreHpAll = dataGridCase->getAttribute(IdAttribute::GRID_RESTORE_HP_ALL);
	dataEntityCase->setAttribute(IdAttribute::ENTITY_RESTORE_HP_ALL, restoreHpAll);
	
	auto costHpAll = dataGridCase->getAttribute(IdAttribute::GRID_COST_HP_ALL);
	dataEntityCase->setAttribute(IdAttribute::ENTITY_COST_HP_ALL, costHpAll);
}

void ManagerGrid::dealRestoreCostEnergy(DataGrid *dataGrid, DataEntity *dataEntity)
{
	auto energyMax = dataEntity->getAttribute(IdAttribute::ENTITY_ENERGY_MAX);

	auto cancelRestoreEnergy = dataGrid->getAttribute(IdAttribute::GRID_RESTORE_ENERGY_CANCEL);
	if (cancelRestoreEnergy == 0)//若无取消恢复能量
	{
		auto restoreEnergy = dataGrid->getAttribute(IdAttribute::GRID_RESTORE_ENERGY);
		dataEntity->addAttribute(IdAttribute::ENTITY_RESTORE_ENERGY, restoreEnergy);
	}
	auto cancelCostEnergy = dataGrid->getAttribute(IdAttribute::GRID_COST_ENERGY_CANCEL);
	if (cancelCostEnergy == 0)//若无取消消耗能量
	{
		auto energy = dataEntity->getAttribute(IdAttribute::ENTITY_ENERGY);
		auto costEnergy = dataGrid->getAttribute(IdAttribute::GRID_COST_ENERGY);
		if (energy >= costEnergy)
		{
			dataEntity->addAttribute(IdAttribute::ENTITY_COST_ENERGY, costEnergy);
		}
	}
}

void ManagerGrid::dealAttributeCondition(DataGrid *dataGridCase, const IdAttribute &idAttribute, DataGrid *dataGridTakes, DataEntity *dataEntity, const int &value2Count /*= -1*/, const int &value2Judge /*= -1*/)
{
	auto value = dataGridCase->getAttributeCondition(idAttribute);
	if (value == "")
	{
		return;
	}
	auto cancelCostEnergy = dataGridCase->getAttribute(IdAttribute::GRID_COST_ENERGY_CANCEL);
	if (cancelCostEnergy == 0)//若无取消消耗能量
	{
		auto costEnergy = dataGridCase->getAttribute(IdAttribute::GRID_COST_ENERGY);
		auto energy = dataEntity->getAttribute(IdAttribute::ENTITY_ENERGY);
		if (energy < costEnergy)
		{
			return;
		}
	}
	DataGrid *dataGrid = nullptr;
	auto vecArgs = UtilString::split(value, "|");
	for (auto varArgs : vecArgs)
	{
		auto vecArg = UtilString::split(varArgs, ":");
		auto idAttribute = (IdAttribute)Value(vecArg[0]).asInt();//条件类型
		vecArg.erase(vecArg.begin());
		if (value2Judge != -1)//若有条件类型值
		{
			auto valueJudgment = Value(vecArg[0]).asInt();//条件类型值
			vecArg.erase(vecArg.begin());
			if (valueJudgment > value2Judge)//判断阀值大于实际值
			{
				continue;
			}
		}
		idAttribute = (IdAttribute)Value(vecArg[0]).asInt();
		vecArg.erase(vecArg.begin());
		if (idAttribute == IdAttribute::GIRD_EFFECTIVE_TO_OTHER)//若是402，‘对对方’
		{
			idAttribute = (IdAttribute)Value(vecArg[0]).asInt();//对对方后必须是，400或401
			vecArg.erase(vecArg.begin());
			dataGrid = dataGridTakes;
		}
		else
		{
			dataGrid = dataGridCase;
		}
		if (idAttribute == IdAttribute::GRID_EFFECTIVE_ROUND)
		{
			auto round = Value(vecArg[0]).asInt();
			vecArg.erase(vecArg.begin());
			if (value2Count != -1)
			{
				dealEffectiveEach(vecArg, value2Count);
			}
			dealEffectiveRound(dataGrid, round, vecArg);
		}
		else if (idAttribute == IdAttribute::GRID_EFFECTIVE_ROUND_COUNT)
		{
			auto round = Value(vecArg[0]).asInt();
			vecArg.erase(vecArg.begin());
			if (value2Count != -1)
			{
				dealEffectiveEach(vecArg, value2Count);
			}
			dealEffectiveRoundCount(dataGrid, round, vecArg);
		}
	}
}

void ManagerGrid::dealEffectiveEach(vector<string> &args, const int &value2Count)
{
	auto idAttribute = (IdAttribute)Value(args[0]).asInt();
	if (idAttribute == IdAttribute::GRID_EFFECTIVE_EACH)//若是每点
	{
		args.erase(args.begin());
		args[1] = Value(Value(args[1]).asInt() * value2Count).asString();
	}
}

void ManagerGrid::dealEffectiveRound(DataGrid *dataGridCase, const int &round, const vector<string> &args)
{
	auto dataGridTemp = dataGridCase;
	auto roundTemp = round;
	while (roundTemp--)
	{
		dataGridTemp = dataGridTemp->getDataGridNext();
	}
	if (dataGridTemp == nullptr)
	{
		return;
	}
	dealEffective(dataGridTemp, args);
}

void ManagerGrid::dealEffectiveRoundCount(DataGrid *dataGridCase, const int &round, const vector<string> &args)
{
	auto dataGridTemp = dataGridCase;
	auto roundTemp = round;
	while (roundTemp--)
	{
		dataGridTemp = dataGridTemp->getDataGridNext();
		if (dataGridTemp == nullptr)
		{
			return;
		}
		dealEffective(dataGridTemp, args);
	}
}

void ManagerGrid::dealEffective(DataGrid *dataGrid, const vector<string> &args)
{
	auto idAttribute = (IdAttribute)Value(args[0]).asInt();
	
	auto value = Value(args[1]).asInt();
	dataGrid->addAttribute(idAttribute, value);

	auto cfgAttribute = ManagerCfg::getInstance()->getDicCfgAttribute()[(int)idAttribute];
	if (cfgAttribute.type == TypeAttribute::GRID_COMPLEX)
	{
		auto vec = UtilString::split(cfgAttribute.args, ":");
		auto idAttribute = (IdAttribute)Value(vec[0]).asInt();
		dataGrid->addAttributeCondition(idAttribute, cfgAttribute.args);
	}

	ManagerUI::getInstance()->notify(ID_OBSERVER::HANDLE_GRID, TYPE_OBSERVER_HANDLE_GRID::UPDATE_GRID, dataGrid->getId());
}
