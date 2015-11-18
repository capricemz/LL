#pragma execution_character_set("utf-8")

#ifndef __UI_COMMON_UI_THING_GET_H__
#define __UI_COMMON_UI_THING_GET_H__

#include "cocos2d.h"

USING_NS_CC;

class UIThingGet : public Layer
{
public:
	/*
	type 0获得物品，1目标奖励，2食谱解锁
	idThing 物品id
	num 物品数量
	*/
	static UIThingGet* create(const int &type, const int &idThing, const int &num, const std::function<void()> &func = nullptr)
	{
		UIThingGet *pRet = new(std::nothrow) UIThingGet();
		if (pRet && pRet->init(type, idThing, num, func))
		{
			pRet->autorelease();
			return pRet;
		}
		else
		{
			delete pRet;
			pRet = nullptr;
			return nullptr;
		}
	}

public:
	UIThingGet();
	~UIThingGet();

	virtual bool init(const int &type, const int &idThing, const int &num, const std::function<void()> &func);

private:

};

#endif