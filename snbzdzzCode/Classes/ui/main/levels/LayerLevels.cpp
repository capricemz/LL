#pragma execution_character_set("utf-8")

#include "LayerLevels.h"
#include "data/define/DefinesRes.h"
#include "ui/ManagerUI.h"
#include "data/data/ManagerData.h"
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

	auto listView = (ListView *)_skin->getChildByName("listViewBtns");
	auto layoutBtns = (Layout *)listView->getChildByName("layoutBtns");
	auto dicCfgLevels = ManagerData::getInstance()->getHandleDataLevels()->getDicCfgLevels();
	auto length = (int)dicCfgLevels.size();
	auto index = 0;
	for (auto var : dicCfgLevels)
	{
		auto cfgLevels = var.second;
		auto nodeLevel = (Node *)layoutBtns->getChildByName("nodeLevel" + Value(index).asString());
		
		updateNodeLevel(nodeLevel, cfgLevels);

		index++;
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

void LayerLevels::updateNodeLevel(Node *nodeLevel, const CfgLevels &cfgLevels)
{
	auto layout = (Layout *)nodeLevel->getChildByName("layout");
	auto spriteState = (Sprite *)layout->getChildByName("spriteState");
	auto txtLevel = (Text *)layout->getChildByName("txtLevel");
	auto txtName = (Text *)layout->getChildByName("txtName");
	txtName->setString(cfgLevels.name);
	auto spriteStar0 = (Sprite *)layout->getChildByName("spriteStar0");
	auto spriteStar1 = (Sprite *)layout->getChildByName("spriteStar1");
	auto spriteStar2 = (Sprite *)layout->getChildByName("spriteStar2");

	auto btn = (Button *)layout->getChildByName("btn");
	btn->addTouchEventListener(CC_CALLBACK_2(LayerLevels::onTouchBtnLv, this));
	btn->setUserData((void *)cfgLevels.id);
}

void LayerLevels::onTouchBtnLv(Ref *ref, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		auto btn = (Button *)ref;
		//在代码里面先获取到button，getComponent()，并把获取的对象强转为Cocos Studio::ComExtensionData* 指针，再调用getCustomProperty()
		/*cocostudio::ComExtensionData* data = dynamic_cast<cocostudio::ComExtensionData*>(btn->getComponent("ComExtensionData"));
		auto idLevel = Value(data->getCustomProperty()).asInt();*/
		auto idLevel = (int)btn->getUserData();
		ManagerData::getInstance()->getHandleDataLevels()->setLevelCurrent(idLevel);
		ManagerUI::getInstance()->notify(ID_OBSERVER::SCENE_MAIN, TYPE_OBSERVER_SCENE_MAIN::SHOW_BATTLE);
	}
}
