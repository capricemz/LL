#include "Maid.h"
#include "cocostudio/CocoStudio.h"
#include "../ManagerEntity.h"

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

cocos2d::Vec2 Maid::getPostionAppearDisAppear()
{
	auto size = _skin->getContentSize();
	return Vec2(-size.width, -size.height);
}

cocos2d::Vec2 Maid::getPostionEndAttack()
{
	auto size = _skin->getContentSize();
	return Vec2(-size.width * 2.0f, 0.0f);
}

void Maid::switchDataEntity(const int &indexSwitchTo, bool &isSwitchSuccess)
{
	if (indexSwitchTo < 0 || indexSwitchTo > ENTITY_BATTLE_MAX)
	{
		return;
	}
	auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
	if (indexSwitchTo == ENTITY_BATTLE_MAX)//切换到下一个
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
		handleDataEntity->setIndexMaid(indexSwitchTo);
		isSwitchSuccess = true;
	}
}
