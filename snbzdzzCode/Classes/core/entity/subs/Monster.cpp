#include "Monster.h"
#include "../ManagerEntity.h"
#include "ui/ManagerUI.h"
#include "data/define/DefinesString.h"

Monster::Monster()
{
}

Monster::~Monster()
{
}

bool Monster::init()
{
	auto isInit = false;
	do 
	{
		CC_BREAK_IF(!Entity::init());

		isInit = true;
	} while (0);
	return isInit;
}

void Monster::setDataEntity()
{
	_dataEntity = ManagerData::getInstance()->getHandleDataEntity()->getDataEntityMst();
}

void Monster::setMyScale()
{
	_skin->setScaleX(-0.7f);
	_skin->setScaleY(0.7f);
}

cocos2d::Vec2 Monster::getPostionAppearDisAppear()
{
	auto size = _skin->getContentSize();
	return Vec2(-size.width, size.height);
}

cocos2d::Vec2 Monster::getPostionEndAttack()
{
	auto size = _skin->getContentSize();
	return Vec2(size.width * 2.0f, 0.0f);
}

void Monster::updateHp()
{
	ManagerUI::getInstance()->notify(ID_OBSERVER::HANDLE_HEAD, TYPE_OBSERVER_HANDLE_HEAD::UPDATE_HP, true);//界面刷新
}

void Monster::updateHpAll()
{
	ManagerUI::getInstance()->notify(ID_OBSERVER::HANDLE_HEAD, TYPE_OBSERVER_HANDLE_HEAD::UPDATE_HP_ALL, true);//界面刷新
}

void Monster::updateEnergy()
{
	ManagerUI::getInstance()->notify(ID_OBSERVER::HANDLE_HEAD, TYPE_OBSERVER_HANDLE_HEAD::UPDATE_ENERGY, true);//界面刷新
}

void Monster::dealDead()
{
	auto dataEntityMaid = ManagerData::getInstance()->getHandleDataEntity()->getDataEntityMaid();
	dataEntityMaid->addAttribute(IdAttribute::ENTITY_KILL_NUM, 1);
	auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
	auto isBattleOver = handleDataEntity->isBattleOver();
	if (!isBattleOver)
	{
		ManagerUI::getInstance()->notify(ID_OBSERVER::HANDLE_HEAD, TYPE_OBSERVER_HANDLE_HEAD::SWITCH_NODE_HEAD_TO, true, ENTITY_BATTLE_MAX);//参数：是怪物，切换下一个
	}
	else
	{
		ManagerEntity::getInstance()->dealBattleOver();
	}
}

void Monster::switchDataEntity(const int &indexSwitchTo, bool &isSwitchSuccess)
{
	if (indexSwitchTo < 0 || indexSwitchTo > ENTITY_BATTLE_MAX)
	{
		return;
	}
	auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
	if (indexSwitchTo == ENTITY_BATTLE_MAX)//切换到下一个
	{
		auto vecDataEntity = handleDataEntity->getVecDataEntityMst();
		for (auto i = 0; i < ENTITY_BATTLE_MAX; i++)
		{
			auto index = handleDataEntity->getIndexMst();
			auto indexTo = (index + i + 1) % ENTITY_BATTLE_MAX;
			auto isAlive = vecDataEntity.at(indexTo)->getIsAlive();
			if (isAlive)
			{
				handleDataEntity->setIndexMst(indexTo);
				isSwitchSuccess = true;
				break;
			}
		}
	}
	else
	{
		auto vecDataEntityMst = handleDataEntity->getVecDataEntityMst();
		if (vecDataEntityMst.size() <= indexSwitchTo)
		{
			return;
		}
		auto isAlive = vecDataEntityMst.at(indexSwitchTo)->getIsAlive();
		if (!isAlive)
		{
			return;
		}
		handleDataEntity->setIndexMst(indexSwitchTo);
		isSwitchSuccess = true;
	}
}

Vector<DataEntity *> Monster::getVecDataEntity()
{
	auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
	auto vecDataEntityMst = handleDataEntity->getVecDataEntityMst();
	return vecDataEntityMst;
}
