#pragma execution_character_set("utf-8")

#include "LayerSkills.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "data/define/DefinesRes.h"
#include "ui/ManagerUI.h"

using namespace ui;

LayerSkills::LayerSkills() : _skin(nullptr)
{
}

LayerSkills::~LayerSkills()
{
	_skin = nullptr;
}

bool LayerSkills::init()
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

Layer * LayerSkills::getThis()
{
	return this;
}

void LayerSkills::afterRunAppear()
{
}

void LayerSkills::afterRunDisappear()
{
}

void LayerSkills::dealRemoveFromParent()
{
	if (getParent())
	{
		removeFromParent();
	}
}

void LayerSkills::createSkin()
{
	_skin = (Layer *)CSLoader::createNode(RES_MODULES_MAIN_LAYER_SKILLS_CSB);
	addChild(_skin);

	auto btn = (Button *)_skin->getChildByName("btnBack");
	btn->addTouchEventListener([](Ref *ref, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			ManagerUI::getInstance()->notify(ID_OBSERVER::SCENE_MAIN, TYPE_OBSERVER_SCENE_MAIN::SHOW_LEVELS);
		}
	});

}
