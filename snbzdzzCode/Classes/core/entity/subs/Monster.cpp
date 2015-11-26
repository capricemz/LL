#include "Monster.h"
#include "..\ManagerEntity.h"
#include "ui\ManagerUI.h"

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

void Monster::updateEnergy()
{
	ManagerUI::getInstance()->notify(ID_OBSERVER::HANDLE_HEAD, TYPE_OBSERVER_HANDLE_HEAD::UPDATE_ENERGY, true);//界面刷新
}

void Monster::dealDead()
{
	ManagerUI::getInstance()->notify(ID_OBSERVER::HANDLE_HEAD, TYPE_OBSERVER_HANDLE_HEAD::SWITCH_NODE_HEAD_TO, true, ENTITY_BATTLE_MAX);//参数：不是怪物，切换下一个
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
