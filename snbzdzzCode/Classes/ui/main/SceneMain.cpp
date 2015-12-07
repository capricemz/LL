#include "SceneMain.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "data/define/DefinesRes.h"
#include "ui/ManagerUI.h"
#include "battle/LayerBattle.h"
#include "levels/LayerLevels.h"
#include "skills/LayerSkills.h"
#include "guild/LayerGuild.h"

using namespace ui;

SceneMain::SceneMain() : _skin(nullptr)
{
}

SceneMain::~SceneMain()
{
	ManagerUI::getInstance()->detach(this);
	_skin = nullptr;
}

bool SceneMain::init()
{
	auto isInit = false;
	do 
	{
		CC_BREAK_IF(!Scene::init());

		idObserverSet(ID_OBSERVER::SCENE_MAIN);
		ManagerUI::getInstance()->attach(this);

		ManagerUI::getInstance()->addKeyEvent(this);

		createSkin();

		isInit = true;
	} while (0);
	return isInit;
}

void SceneMain::updateBySubject(va_list values)
{
	auto type = va_arg(values, TYPE_OBSERVER_SCENE_MAIN);
	auto managerUI = ManagerUI::getInstance();
	
	if (managerUI->getTypeLayerRunning() == type)
	{
		return;
	}
	managerUI->setTypeLayerRunning(type);

	auto layoutContent = (Layout *)_skin->getChildByName("layoutContent");
	ILayerAppearDisappear *layer;
	if (type == TYPE_OBSERVER_SCENE_MAIN::SHOW_GUILD)
	{
		auto layerGuild = LayerGuild::create();
		layoutContent->addChild(layerGuild);
		layer = layerGuild;
	}
	else if (type == TYPE_OBSERVER_SCENE_MAIN::SHOW_BATTLE)
	{
		auto layerBattle = LayerBattle::create();
		layoutContent->addChild(layerBattle);
		layer = layerBattle;
	}
	else if (type == TYPE_OBSERVER_SCENE_MAIN::SHOW_LEVELS)
	{
		auto layerLevels = LayerLevels::create();
		layoutContent->addChild(layerLevels);
		layer = layerLevels;
	}
	else if (type == TYPE_OBSERVER_SCENE_MAIN::SHOW_SKILLS)
	{
		auto layerSkills = LayerSkills::create();
		layoutContent->addChild(layerSkills);
		layer = layerSkills;
	}
	managerUI->runLayerAppearDisappear(layer);
}

void SceneMain::createSkin()
{
	_skin = (Scene *)CSLoader::createNode(RES_MODULES_MAIN_SCENE_MAIN_CSB);
	addChild(_skin);

	auto layoutContent = (Layout *)_skin->getChildByName("layoutContent");
	auto managerUI = ManagerUI::getInstance();

	auto layerGuild = LayerGuild::create();
	layoutContent->addChild(layerGuild);
	managerUI->setTypeLayerRunning(TYPE_OBSERVER_SCENE_MAIN::SHOW_GUILD);
	managerUI->setLayerRunning(layerGuild);

	/*auto layerLevels = LayerLevels::create();
	layoutContent->addChild(layerLevels);
	managerUI->setTypeLayerRunning(TYPE_OBSERVER_SCENE_MAIN::SHOW_LEVELS);
	managerUI->setLayerRunning(layerLevels);*/

	/*auto layerBattle = LayerBattle::create();
	addChild(layerBattle);
	managerUI->setTypeLayerRunning(TYPE_OBSERVER_SCENE_MAIN::SHOW_BATTLE);
	managerUI->setLayerRunning(layerBattle);*/

	auto btnGuild = (Button *)_skin->getChildByName("btnGuild");
	btnGuild->addTouchEventListener([](Ref *ref, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			ManagerUI::getInstance()->notify(ID_OBSERVER::SCENE_MAIN, TYPE_OBSERVER_SCENE_MAIN::SHOW_GUILD);
		}
	});

	auto btnSkills = (Button *)_skin->getChildByName("btnSkills");
	btnSkills->addTouchEventListener([](Ref *ref, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			ManagerUI::getInstance()->notify(ID_OBSERVER::SCENE_MAIN, TYPE_OBSERVER_SCENE_MAIN::SHOW_SKILLS);
		}
	});

	auto btnLevels = (Button *)_skin->getChildByName("btnLevels");
	btnLevels->addTouchEventListener([](Ref *ref, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			ManagerUI::getInstance()->notify(ID_OBSERVER::SCENE_MAIN, TYPE_OBSERVER_SCENE_MAIN::SHOW_LEVELS);
		}
	});
}
