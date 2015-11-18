#ifndef __CORE_TIMER_MANAGER_TIMER_H__
#define __CORE_TIMER_MANAGER_TIMER_H__

#include "cocos2d.h"
#include "data/data/ManagerData.h"

USING_NS_CC;

class ManagerTimer : public Node
{
public:
	static ManagerTimer *getInstance();//提供getInstance全局指针
	static void destroyInstance();

public:
	virtual ~ManagerTimer();

	void timerStartDeal();
	
	void timerForegroundDeal();
	void timerBackgroundDeal();

private:
	void dataTimeOffLineDeal();
	void updateCustom(float dt);
	void timeLastReset();
	
private:
	bool _isBackground = false;
	
};

#endif