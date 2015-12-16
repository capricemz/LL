#include "SceneMain.h"
#include "data/define/DefinesRes.h"
#include "ui/ManagerUI.h"
#include "battle/LayerBattle.h"
#include "levels/LayerLevels.h"
#include "skills/LayerSkills.h"
#include "guild/LayerGuild.h"
#include "training/LayerTraining.h"

SceneMain::SceneMain() : _skin(nullptr), _isLayoutTopVisible(true), _isLayoutBottomVisible(true)
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

		switchVisibleLayoutTop(true);
		switchVisibleLayoutBottom(true);
	}
	else if (type == TYPE_OBSERVER_SCENE_MAIN::SHOW_SKILLS)
	{
		auto idEntity = va_arg(values, int);
		auto layerSkills = LayerSkills::create();
		if (idEntity != INT32_MIN)
		{
			layerSkills->updateSkin(idEntity);
		}
		layoutContent->addChild(layerSkills);
		layer = layerSkills;

		switchVisibleLayoutTop(false);
		switchVisibleLayoutBottom(true);
	}
	else if (type == TYPE_OBSERVER_SCENE_MAIN::SHOW_SHOP)
	{

		switchVisibleLayoutTop(true);
		switchVisibleLayoutBottom(true);
	}
	else if (type == TYPE_OBSERVER_SCENE_MAIN::SHOW_TRAINING)
	{
		auto index = va_arg(values, int);
		auto layerTraining = LayerTraining::create();
		if (index != INT32_MIN)
		{
			layerTraining->updateSkin(index);
		}
		layoutContent->addChild(layerTraining);
		layer = layerTraining;

		switchVisibleLayoutTop(false);
		switchVisibleLayoutBottom(true);
	}
	else if (type == TYPE_OBSERVER_SCENE_MAIN::SHOW_LEVELS)
	{
		auto layerLevels = LayerLevels::create();
		layoutContent->addChild(layerLevels);
		layer = layerLevels;

		switchVisibleLayoutTop(true);
		switchVisibleLayoutBottom(true);
	}
	else if (type == TYPE_OBSERVER_SCENE_MAIN::SHOW_BATTLE)
	{
		auto layerBattle = LayerBattle::create();
		layoutContent->addChild(layerBattle);
		layer = layerBattle;

		switchVisibleLayoutTop(false);
		switchVisibleLayoutBottom(false);
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

	auto layoutBottom = (Layout *)_skin->getChildByName("layoutBottom");
	auto btn = (Button *)layoutBottom->getChildByName("btnGuild");
	btn->addTouchEventListener(CC_CALLBACK_2(SceneMain::onTouchBtn, this));
	btn->setUserData((void *)TYPE_OBSERVER_SCENE_MAIN::SHOW_GUILD);

	btn = (Button *)layoutBottom->getChildByName("btnSkills");
	btn->addTouchEventListener(CC_CALLBACK_2(SceneMain::onTouchBtn, this));
	btn->setUserData((void *)TYPE_OBSERVER_SCENE_MAIN::SHOW_SKILLS);

	btn = (Button *)layoutBottom->getChildByName("btnShop");
	btn->addTouchEventListener(CC_CALLBACK_2(SceneMain::onTouchBtn, this));
	btn->setUserData((void *)TYPE_OBSERVER_SCENE_MAIN::SHOW_SHOP);

	btn = (Button *)layoutBottom->getChildByName("btnTraining");
	btn->addTouchEventListener(CC_CALLBACK_2(SceneMain::onTouchBtn, this));
	btn->setUserData((void *)TYPE_OBSERVER_SCENE_MAIN::SHOW_TRAINING);

	btn = (Button *)layoutBottom->getChildByName("btnLevels");
	btn->addTouchEventListener(CC_CALLBACK_2(SceneMain::onTouchBtn, this));
	btn->setUserData((void *)TYPE_OBSERVER_SCENE_MAIN::SHOW_LEVELS);
}

void SceneMain::onTouchBtn(Ref *ref, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		auto btn = (Button *)ref;
		auto typeShow = (TYPE_OBSERVER_SCENE_MAIN)(int)btn->getUserData();
		ManagerUI::getInstance()->notify(ID_OBSERVER::SCENE_MAIN, typeShow, INT32_MIN);
	}
}

void SceneMain::switchVisibleLayoutTop(const bool &isVisibe)
{
	if (_isLayoutTopVisible == isVisibe)
	{
		return;
	}
	_isLayoutTopVisible = isVisibe;
	auto layoutTop = (Layout *)_skin->getChildByName("layoutTop");
	auto size = layoutTop->getContentSize();
	auto mask = Layout::create();
	mask->setContentSize(size);
	mask->setBackGroundColorType(Layout::BackGroundColorType::NONE);
	mask->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	layoutTop->addChild(mask);
	auto actionDeal = EaseCircleActionIn::create(MoveBy::create(0.2f, Vec2(0.0f, isVisibe ? -size.height : size.height)));
	auto actionCallFunc = CallFunc::create([mask]()
	{
		mask->removeFromParent();
	});
	layoutTop->runAction(Sequence::createWithTwoActions(actionDeal, actionCallFunc));
}

void SceneMain::switchVisibleLayoutBottom(const bool &isVisibe)
{
	if (_isLayoutBottomVisible == isVisibe)
	{
		return;
	}
	_isLayoutBottomVisible = isVisibe;
	auto layoutBottom = (Layout *)_skin->getChildByName("layoutBottom");
	auto size = layoutBottom->getContentSize();
	auto mask = Layout::create();
	mask->setContentSize(size);
	mask->setBackGroundColorType(Layout::BackGroundColorType::NONE);
	mask->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	layoutBottom->addChild(mask);
	auto actionDeal = EaseCircleActionIn::create(MoveBy::create(0.2f, Vec2(0.0f, isVisibe ? size.height : -size.height)));
	auto actionCallFunc = CallFunc::create([mask]()
	{
		mask->removeFromParent();
	});
	layoutBottom->runAction(Sequence::createWithTwoActions(actionDeal, actionCallFunc));
}
