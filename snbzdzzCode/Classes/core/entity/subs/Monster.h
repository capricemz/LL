#ifndef __CORE_ENTITY_SUBS_MONSTER_H__
#define __CORE_ENTITY_SUBS_MONSTER_H__

#include "Entity.h"

class Monster : public Entity
{
public:
	CREATE_FUNC(Monster);

public:
	Monster();
	~Monster();

	virtual bool init();

protected:
	virtual void setDataEntity();
	virtual void setMyScale();
	virtual Vec2 getPostionAppearDisAppear();
	virtual Vec2 getPostionEndAttack();
	virtual void updateHp();
	virtual void updateEnergy();
	virtual void dealDead();
	virtual void switchDataEntity(const int &indexSwitchTo, bool &isSwitchSuccess);
	
};

#endif