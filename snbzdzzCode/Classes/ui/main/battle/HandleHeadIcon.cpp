#pragma execution_character_set("utf-8")

#include "HandleHeadIcon.h"

HandleHeadIcon::HandleHeadIcon() : _skin(nullptr)
{
}

HandleHeadIcon::~HandleHeadIcon()
{
	_skin = nullptr;
}

bool HandleHeadIcon::init()
{
	auto isInit = false;
	do
	{
		isInit = true;
	} while (0);
	return isInit;
}

void HandleHeadIcon::setSkin(Layout *skin)
{
	_skin = skin;
	for (int i = 0; i < 6; i++)
	{
		auto index = i % 3;
		auto layout = (Layout *)_skin->getChildByName(i < 3 ? "layoutMaid" + Value(index).asString() : "layoutMst" + Value(index).asString());
		auto spriteIcon = (Sprite *)layout->getChildByName("spriteIcon");
	}
}

cocos2d::Vec2 HandleHeadIcon::getPostionHeadIcon(const int &type, const int &index)
{
	auto layoutMst = (Layout *)_skin->getChildByName((type == 0 ? "layoutMaid" : "layoutMst") + Value(index).asString());
	auto postion = layoutMst->getParent()->convertToWorldSpace(layoutMst->getPosition());
	return postion;
}

void HandleHeadIcon::resetSkin()
{
	for (int i = 0; i < 6; i++)
	{
		auto index = i % 3;
		auto layout = (Layout *)_skin->getChildByName(i < 3 ? "layoutMaid" + Value(index).asString() : "layoutMst" + Value(index).asString());
		auto spriteIcon = (Sprite *)layout->getChildByName("spriteIcon");
	}
}
