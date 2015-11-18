#include "SceneMain.h"
#include "cocostudio/CocoStudio.h"
#include "data/define/DefinesRes.h"
#include "ui/ManagerUI.h"
#include "battle/LayerBattle.h"
#include "levels/LayerLevels.h"

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

	ILayerAppearDisappear *layer;
	if (type == TYPE_OBSERVER_SCENE_MAIN::SHOW_BATTLE)
	{
		auto layerBattle = LayerBattle::create();
		addChild(layerBattle);
		layer = layerBattle;
	}
	else if (type == TYPE_OBSERVER_SCENE_MAIN::SHOW_LEVELS)
	{
		auto layerLevels = LayerLevels::create();
		addChild(layerLevels);
		layer = layerLevels;
	}
	managerUI->runLayerAppearDisappear(layer);
}

void SceneMain::createSkin()
{
	_skin = (Scene *)CSLoader::createNode(RES_MODULES_MAIN_SCENE_MAIN_CSB);
	addChild(_skin);

	auto managerUI = ManagerUI::getInstance();

	auto layerLevels = LayerLevels::create();
	addChild(layerLevels);
	managerUI->setTypeLayerRunning(TYPE_OBSERVER_SCENE_MAIN::SHOW_LEVELS);
	managerUI->setLayerRunning(layerLevels);

	/*auto layerBattle = LayerBattle::create();
	addChild(layerBattle);
	managerUI->setTypeLayerRunning(TYPE_OBSERVER_SCENE_MAIN::SHOW_BATTLE);
	managerUI->setLayerRunning(layerBattle);*/
}
