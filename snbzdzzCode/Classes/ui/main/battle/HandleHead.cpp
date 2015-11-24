#pragma execution_character_set("utf-8")

#include "HandleHead.h"
#include "ui/UILoadingBar.h"
#include "data/data/ManagerData.h"
#include "ui/ManagerUI.h"
#include "NodeHead.h"

HandleHead::HandleHead() : _skin(nullptr), _vecNodeHeadMst({}), _vecNodeHeadMaid({})
{
}

HandleHead::~HandleHead()
{
	ManagerUI::getInstance()->detach(this);
	_vecNodeHeadMaid.clear();
	_vecNodeHeadMst.clear();
	_skin = nullptr;
}

bool HandleHead::init()
{
	auto isInit = false;
	do
	{
		idObserverSet(ID_OBSERVER::HANDLE_HEAD);
		ManagerUI::getInstance()->attach(this);

		isInit = true;
	} while (0);
	return isInit;
}

void HandleHead::updateBySubject(va_list values)
{
	auto type = va_arg(values, TYPE_OBSERVER_HANDLE_HEAD);
	if (type == TYPE_OBSERVER_HANDLE_HEAD::UPDATE_HP)
	{
		auto isMst = va_arg(values, bool);
		updateBarHp(isMst, 0);
	}
	else if (type == TYPE_OBSERVER_HANDLE_HEAD::UPDATE_HP_ALL)
	{
		auto isMst = va_arg(values, bool);
		for (auto i = 0; i < ENTITY_BATTLE_MAX; i++)
		{
			updateBarHp(isMst, i);
		}
	}
	else if (type == TYPE_OBSERVER_HANDLE_HEAD::UPDATE_ENERGY)
	{
		auto isMst = va_arg(values, bool);
		updateBarEnergy(isMst);
	}
}

void HandleHead::setSkin(Layout *skin)
{
	_skin = skin;

	for (int i = 0; i < 6; i++)
	{
		auto index = i % 3;
		auto isMst = i < 3;

		auto layout = (Layout *)_skin->getChildByName(isMst ? "layoutHeadMst" : "layoutHeadMaid");
		layout->addTouchEventListener(CC_CALLBACK_2(HandleHead::onTouchMoveHead, this, isMst));//添加头像拖动事件

		auto skinNodeHead = (Node *)layout->getChildByName("nodeHead" + Value(index).asString());
		
		auto nodeHead = NodeHead::create();
		nodeHead->setIsMst(isMst);
		nodeHead->setIndexDataEntity(index);
		nodeHead->setSkin(skinNodeHead);
		nodeHead->updateAll();

		isMst ? _vecNodeHeadMst.pushBack(nodeHead) : _vecNodeHeadMaid.pushBack(nodeHead);
	}
	
	for (size_t i = 0; i < 2; i++)
	{
		auto isMst = i < 1;
		updateBarEnergy(isMst);
	}
}

cocos2d::Vec2 HandleHead::getPostionHeadIcon(const int &type, const int &index)
{
	auto vec = type == 1 ? _vecNodeHeadMst : _vecNodeHeadMaid;
	CCASSERT(vec.size() > index, "HandleHead::getPostionHeadIcon vec.size() <= index");
	auto nodeHead = vec.at(index);
	auto postion = nodeHead->getParent()->convertToWorldSpace(nodeHead->getPosition());
	return postion;
}

void HandleHead::switchHead()
{

}

void HandleHead::onTouchMoveHead(Ref *ref, Widget::TouchEventType type, const bool &isMst)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:

		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		auto layout = (Layout *)ref;
		/*auto touchBeganPostion = layout->getTouchBeganPosition();
		auto touchMovePostion = layout->getTouchMovePosition();*/
		/*auto touchDelta = touchMovePostion - touchBeganPostion;*/
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
	case cocos2d::ui::Widget::TouchEventType::CANCELED:

		break;
	}
}

void HandleHead::resetSkin()
{
	for (int i = 0; i < 6; i++)
	{
		auto index = i % 3;
	}
}

void HandleHead::updateBarHp(const bool &isMst, const int &indexNodeHead)
{
	auto vec = isMst ? _vecNodeHeadMst : _vecNodeHeadMaid;
	if (vec.size() > indexNodeHead)
	{
		auto nodeHead = vec.at(indexNodeHead);
		nodeHead->updateBarHp();
	}
}

void HandleHead::updateBarEnergy(const bool &isMst)
{
	auto name = isMst ? "layoutEnergyMst" : "layoutEnergyMaid";
	auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
	auto dataEntity = isMst ? handleDataEntity->getDataEntityMst() : handleDataEntity->getDataEntityMaid();

	auto energy = dataEntity->getAttribute(IdAttribute::ENTITY_ENERGY);
	auto energyMax = dataEntity->getAttribute(IdAttribute::ENTITY_ENERGY_MAX);

	auto layout = (Layout *)_skin->getChildByName(name);
	auto bar = (LoadingBar *)layout->getChildByName("barEnergy");
	bar->setPercent(((float)energy / (float)energyMax) * 100.0f);
}
