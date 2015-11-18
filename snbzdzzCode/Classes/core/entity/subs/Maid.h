#ifndef __CORE_ENTITY_SUBS_MAID_H__
#define __CORE_ENTITY_SUBS_MAID_H__

#include "Entity.h"

class Maid : public Entity
{
public:
	CREATE_FUNC(Maid);

public:
	Maid();
	~Maid();

	virtual bool init();

protected:
	virtual void setDataEntity();
	virtual Vec2 getPostionAppearDisAppear();
	virtual Vec2 getPostionEndAttack();
	virtual void switchDataEntity(const int &indexSwitchTo, bool &isSwitchSuccess);
	
private:

};

#endif