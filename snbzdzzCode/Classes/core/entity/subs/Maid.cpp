#include "Maid.h"
#include "cocostudio/CocoStudio.h"
#include "../ManagerEntity.h"
#include "ui/ManagerUI.h"

Maid::Maid()
{
}

Maid::~Maid()
{
}

bool Maid::init()
{
	auto isInit = false;
	do 
	{
		CC_BREAK_IF(!Entity::init());

		
		isInit = true;
	} while (0);
	return isInit;
}

void Maid::setDataEntity()
{
	_dataEntity = ManagerData::getInstance()->getHandleDataEntity()->getDataEntityMaid();
}

void Maid::setMyScale()
{
	_skin->setScaleX(-0.7f);
	_skin->setScaleY(0.7f);
}

cocos2d::Vec2 Maid::getPostionAppearDisAppear()
{
	auto size = _skin->getContentSize();
	return Vec2(size.width, -size.height);
}

cocos2d::Vec2 Maid::getPostionEndAttack()
{
	auto size = _skin->getContentSize();
	return Vec2(-size.width * 2.0f, 0.0f);
}

void Maid::updateHp()
{
	ManagerUI::getInstance()->notify(ID_OBSERVER::HANDLE_HEAD, TYPE_OBSERVER_HANDLE_HEAD::UPDATE_HP, false);//����ˢ��
}

void Maid::updateEnergy()
{
	ManagerUI::getInstance()->notify(ID_OBSERVER::HANDLE_HEAD, TYPE_OBSERVER_HANDLE_HEAD::UPDATE_ENERGY, false);//����ˢ��
}

void Maid::dealDead()
{
	auto isBattleOver = dealIsBattleOver();
	if (!isBattleOver)
	{
		ManagerUI::getInstance()->notify(ID_OBSERVER::HANDLE_HEAD, TYPE_OBSERVER_HANDLE_HEAD::SWITCH_NODE_HEAD_TO, false, ENTITY_BATTLE_MAX);//���������ǹ���л���һ��
	}
}

void Maid::switchDataEntity(const int &indexSwitchTo, bool &isSwitchSuccess)
{
	if (indexSwitchTo < 0 || indexSwitchTo > ENTITY_BATTLE_MAX)
	{
		return;
	}
	auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
	if (indexSwitchTo == ENTITY_BATTLE_MAX)//�л�����һ��
	{
		auto vecDataEntity = handleDataEntity->getVecDataEntityMaid();
		for (auto i = 0; i < ENTITY_BATTLE_MAX; i++)
		{
			auto index = handleDataEntity->getIndexMaid();
			auto indexTo = (index + i + 1) % ENTITY_BATTLE_MAX;
			if (vecDataEntity.at(indexTo)->getIsAlive())
			{
				handleDataEntity->setIndexMaid(indexTo);
				isSwitchSuccess = true;
				break;
			}
		}
	}
	else
	{
		auto vecDataEntityMaid = handleDataEntity->getVecDataEntityMaid();
		if (vecDataEntityMaid.size() <= indexSwitchTo)
		{
			return;
		}
		auto isAlive = vecDataEntityMaid.at(indexSwitchTo)->getIsAlive();
		if (!isAlive)
		{
			return;
		}
		handleDataEntity->setIndexMaid(indexSwitchTo);
		isSwitchSuccess = true;
	}
}
