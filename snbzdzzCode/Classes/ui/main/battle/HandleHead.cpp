#pragma execution_character_set("utf-8")

#include "HandleHead.h"

HandleHead::HandleHead() : _skin(nullptr)
{
}

HandleHead::~HandleHead()
{
	_skin = nullptr;
}

bool HandleHead::init()
{
	auto isInit = false;
	do
	{
		isInit = true;
	} while (0);
	return isInit;
}

void HandleHead::setSkin(Layout *skin)
{
	_skin = skin;
	for (int i = 0; i < 6; i++)
	{
		auto index = i % 3;
		auto isMst = i < 3;
		auto layout = (Layout *)_skin->getChildByName(isMst ? "layoutMst" + Value(index).asString() : "layoutMaid" + Value(index).asString());
		auto spriteIcon = (Sprite *)layout->getChildByName("spriteIcon");
	}
	for (size_t i = 0; i < 2; i++)
	{
		auto isMst = i < 1;
		auto layout = (Layout *)_skin->getChildByName(isMst ? "layoutEnergyMst" : "layoutEnergyMaid");
	}
}

cocos2d::Vec2 HandleHead::getPostionHeadIcon(const int &type, const int &index)
{
	auto layoutMst = (Layout *)_skin->getChildByName((type == 0 ? "layoutMaid" : "layoutMst") + Value(index).asString());
	auto postion = layoutMst->getParent()->convertToWorldSpace(layoutMst->getPosition());
	return postion;
}

void HandleHead::resetSkin()
{
	for (int i = 0; i < 6; i++)
	{
		auto index = i % 3;
		auto layout = (Layout *)_skin->getChildByName(i < 3 ? "layoutMaid" + Value(index).asString() : "layoutMst" + Value(index).asString());
		auto spriteIcon = (Sprite *)layout->getChildByName("spriteIcon");
	}
}
