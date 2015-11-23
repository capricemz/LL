#pragma execution_character_set("utf-8")

#include "HandleBg.h"
#include "data/data/ManagerData.h"

HandleBg::HandleBg()
{
}

HandleBg::~HandleBg()
{
}

bool HandleBg::init()
{
	auto isInit = false;
	do
	{

		isInit = true;
	} while (0);
	return isInit;
}

void HandleBg::setSkin(Layout *skin)
{
	_skin = skin;

	auto length = 6;
	for (auto i = 0; i < length; i++)
	{
		auto isMst = i < (length / 2);
		auto index = i % (length / 2);
		auto sprite = (Sprite *)_skin->getChildByName(isMst ? "spriteMst" + Value(index).asString() : "spriteMaid" + Value(index).asString());
		auto postion = sprite->getPosition();
		ManagerData::getInstance()->getHandleDataGrid()->postionGridSelectedPush(isMst, postion);
	}
}
