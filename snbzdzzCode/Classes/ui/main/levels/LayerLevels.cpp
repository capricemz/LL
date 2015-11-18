#pragma execution_character_set("utf-8")

#include "LayerLevels.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "data/define/DefinesRes.h"
#include "ui/ManagerUI.h"
#include "data/data/ManagerData.h"

using namespace ui;

LayerLevels::LayerLevels() : _skin(nullptr)
{
}

LayerLevels::~LayerLevels()
{
	_skin = nullptr;
}

bool LayerLevels::init()
{
	auto isInit = false;
	do 
	{
		CC_BREAK_IF(!Layer::init());

		createSkin();

		isInit = true;
	} while (0);
	return isInit;
}

Layer * LayerLevels::getThis()
{
	return this;
}

void LayerLevels::afterRunAppear()
{
}

void LayerLevels::afterRunDisappear()
{
}

void LayerLevels::dealRemoveFromParent()
{
	if (getParent())
	{
		removeFromParent();
	}
}

void LayerLevels::createSkin()
{
	_skin = (Layer *)CSLoader::createNode(RES_MODULES_MAIN_LAYER_LEVELS_CSB);
	addChild(_skin);

	auto btn = (Button *)_skin->getChildByName("btn");
	btn->addTouchEventListener([](Ref *ref, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			ManagerData::getInstance()->getHandleDataLevels()->setLevelCurrent(9999);//for test
			ManagerUI::getInstance()->notify(ID_OBSERVER::SCENE_MAIN, TYPE_OBSERVER_SCENE_MAIN::SHOW_BATTLE);
		}
	});
}
