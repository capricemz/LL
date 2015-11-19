#pragma execution_character_set("utf-8")

#include "LayerLevels.h"
#include "data/define/DefinesRes.h"
#include "ui/ManagerUI.h"
#include "data/data/ManagerData.h"
#include "data/config/ManagerCfg.h"
#include "cocostudio/CCComExtensionData.h"

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

	auto layoutBtns = (Layout *)_skin->getChildByName("layoutBtns");
	for (auto i = 0; i < 15; i++)
	{
		auto btn = (Button *)layoutBtns->getChildByName("btn" + Value(i).asString());
		btn->addTouchEventListener(CC_CALLBACK_2(LayerLevels::onTouchBtnLv, this));
	}

	auto btnSkills = (Button *)_skin->getChildByName("btnSkills");
	btnSkills->addTouchEventListener([](Ref *ref, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			ManagerUI::getInstance()->notify(ID_OBSERVER::SCENE_MAIN, TYPE_OBSERVER_SCENE_MAIN::SHOW_SKILLS);
		}
	});
}

void LayerLevels::onTouchBtnLv(Ref *ref, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		auto btn = (Button *)ref;
		//在代码里面先获取到button，getComponent()，并把获取的对象强转为Cocos Studio::ComExtensionData* 指针，再调用getCustomProperty()
		cocostudio::ComExtensionData* data = dynamic_cast<cocostudio::ComExtensionData*>(btn->getComponent("ComExtensionData"));
		auto idLevel = Value(data->getCustomProperty()).asInt();
		ManagerData::getInstance()->getHandleDataLevels()->setLevelCurrent(idLevel);//for test
		ManagerUI::getInstance()->notify(ID_OBSERVER::SCENE_MAIN, TYPE_OBSERVER_SCENE_MAIN::SHOW_BATTLE);
	}
}
