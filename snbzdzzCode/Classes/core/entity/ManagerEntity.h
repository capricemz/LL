#ifndef __CORE_ENTITY_MANAGER_ENTITY_H__
#define __CORE_ENTITY_MANAGER_ENTITY_H__

#include "cocos2d.h"
#include "subs/Entity.h"
#include "subs/Maid.h"
#include "subs/Monster.h"
#include "subs/Scenery.h"

USING_NS_CC;

class ManagerEntity
{
public:
	//提供getInstance全局指针
	static ManagerEntity * getInstance();;
	static void destroyInstance();

public:
	virtual ~ManagerEntity();

	void stopAllActions();

	bool isRunAppearOverAll();
	bool isDoActoinOverAll();
	bool isTurnOverAll();

	void dealBattleOver();

	void runSceneryEffect(const bool &isMst);
	void stopSceneryEffect(const bool &isMst);
	
public:
	Monster * getMonster() const
	{
		return _monster;
	}
	void setMonster(Monster * val)
	{
		_monster = val;
	}
	Maid * getMaid() const
	{
		return _maid;
	}
	void setMaid(Maid * val)
	{
		_maid = val;
	}
	Scenery * getSceneryMst() const
	{
		return _sceneryMst;
	}
	void setSceneryMst(Scenery * val)
	{
		_sceneryMst = val;
	}
	Scenery * getsSceneryMaid() const
	{
		return _sceneryMaid;
	}
	void setSceneryMaid(Scenery * val)
	{
		_sceneryMaid = val;
	}
	
private:
	ManagerEntity();
	
private:
	Monster *_monster;
	Maid *_maid;
	Scenery *_sceneryMst;
	Scenery *_sceneryMaid;
	
};

#endif