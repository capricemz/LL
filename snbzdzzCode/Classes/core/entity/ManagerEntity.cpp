#include "ManagerEntity.h"
#include "common/util/UtilRandom.h"
#include "ui/ManagerUI.h"
#include "../grid/ManagerGrid.h"

static ManagerEntity *_instance = nullptr;

ManagerEntity * ManagerEntity::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new ManagerEntity();
	}
	return _instance;
}

void ManagerEntity::destroyInstance()
{
	CC_SAFE_DELETE(_instance);
}

ManagerEntity::ManagerEntity() : _monster(nullptr), _maid(nullptr), _sceneryMst(nullptr), _sceneryMaid(nullptr)
{
}

ManagerEntity::~ManagerEntity()
{
	_monster = nullptr;
	_maid = nullptr;
	_sceneryMst = nullptr;
	_sceneryMaid = nullptr;
}

void ManagerEntity::stopAllActions()
{
	_monster->stopSkinAllActions();
	_maid->stopSkinAllActions();
}

bool ManagerEntity::isRunAppearOverAll()
{
	return _monster->getIsRunAppearOver() && _maid->getIsRunAppearOver();
}

bool ManagerEntity::isDoActoinOverAll()
{
	return _monster->getIsDoActionOver() && _maid->getIsDoActionOver();
}

bool ManagerEntity::isTurnOverAll()//行动动画全部播放完成
{
	return _monster->getIsTurnOver() && _maid->getIsTurnOver();
}

void ManagerEntity::dealBattleOver()
{
	stopAllActions();
	
	auto managerData = ManagerData::getInstance();

	auto handleDataGrid = managerData->getHandleDataGrid();
	handleDataGrid->resetIndexGridBattle();
	
	auto handleDataEntity = managerData->getHandleDataEntity();
	handleDataEntity->resetDataEntityAttributeTemp();
	handleDataEntity->dealBattleOver();

	auto isAllMaidDead = handleDataEntity->isAllMaidDead();

	auto handleDataLevels = managerData->getHandleDataLevels();
	auto dataLevelCurrent = handleDataLevels->getDataLevelCurrent();
	if (!isAllMaidDead)//战斗胜利
	{
		dataLevelCurrent->dealLevelTarget();
		dataLevelCurrent->dealLevelPassed();//处理通关
	}
	else
	{
		dataLevelCurrent->setVecTargetComplete();
	}

	auto value = handleDataEntity->getDataEntityMaid()->getAttribute(IdAttribute::ENTITY_BREAK_CASE_NUM);
	if (value > 0)//若造成破衣
	{
		ManagerUI::getInstance()->notify(ID_OBSERVER::LAYER_BATTLE, TYPE_OBSERVER_LAYER_BATTLE::SHOW_LAYER_CATCH);
	}
	else
	{
		ManagerUI::getInstance()->notify(ID_OBSERVER::LAYER_BATTLE, TYPE_OBSERVER_LAYER_BATTLE::SHOW_LAYER_BATTLE_RESULT);
	}
}

void ManagerEntity::runSceneryEffect(const bool &isMst)
{
	auto scenery = isMst ? _sceneryMst : _sceneryMaid;
	scenery->runEffect();
}

void ManagerEntity::stopSceneryEffect(const bool &isMst)
{
	auto scenery = isMst ? _sceneryMst : _sceneryMaid;
	scenery->stopEffect();
}
