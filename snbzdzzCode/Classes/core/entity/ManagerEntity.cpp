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

ManagerEntity::ManagerEntity() : _monster(nullptr), _maid(nullptr)
{

}

ManagerEntity::~ManagerEntity()
{
	_monster = nullptr;
	_maid = nullptr;
}

void ManagerEntity::stopAllActions()
{
	_monster->stopSkinAllActions();
	_maid->stopSkinAllActions();
}

void ManagerEntity::resetEntityAttributeTemp()
{
	auto dataEntity = _monster->getDataEntity();
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
	dataEntity = _maid->getDataEntity();
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
	auto managerData = ManagerData::getInstance();
	stopAllActions();
	managerData->getHandleDataGrid()->resetIndexGridBattle();
	managerData->getHandleDataEntity()->dealBattleOver();
	resetEntityAttributeTemp();
	auto isAllMaidDead = managerData->getHandleDataEntity()->isAllMaidDead();
	ManagerUI::getInstance()->notify(ID_OBSERVER::LAYER_BATTLE, TYPE_OBSERVER_LAYER_BATTLE::SHOW_LAYER_BATTLE_RESULT, !isAllMaidDead);
}
