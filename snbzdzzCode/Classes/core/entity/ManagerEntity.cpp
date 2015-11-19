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

bool ManagerEntity::isRunAppearOverAll()
{
	return _monster->getIsRunAppearOver() && _maid->getIsRunAppearOver();
}

bool ManagerEntity::isDoActoinOverAll()
{
	return _monster->getIsDoActionOver() && _maid->getIsDoActionOver();
}

bool ManagerEntity::isTurnOverAll()//�ж�����ȫ���������
{
	return _monster->getIsTurnOver() && _maid->getIsTurnOver();
}

void ManagerEntity::dealBattleOver()
{
	stopAllActions();
	
	auto managerData = ManagerData::getInstance();
	managerData->getHandleDataGrid()->resetIndexGridBattle();
	
	auto handleDataEntity = managerData->getHandleDataEntity();
	handleDataEntity->resetDataEntityAttributeTemp();
	handleDataEntity->dealBattleOver();

	auto isAllMaidDead = managerData->getHandleDataEntity()->isAllMaidDead();
	ManagerUI::getInstance()->notify(ID_OBSERVER::LAYER_BATTLE, TYPE_OBSERVER_LAYER_BATTLE::SHOW_LAYER_BATTLE_RESULT, !isAllMaidDead);
}
