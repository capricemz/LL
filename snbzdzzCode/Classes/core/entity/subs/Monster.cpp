#include "Monster.h"
#include "..\ManagerEntity.h"

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

cocos2d::Vec2 Monster::getPostionAppearDisAppear()
{
	auto size = _skin->getContentSize();
	return Vec2(size.width, -size.height);
}

cocos2d::Vec2 Monster::getPostionEndAttack()
{
	auto size = _skin->getContentSize();
	return Vec2(-size.width, 0.0f);
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
