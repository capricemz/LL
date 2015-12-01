#pragma execution_character_set("utf-8")

#include "LayerBattleResult.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "data/define/DefinesRes.h"
#include "data/define/DefinesString.h"
#include "ui/ManagerUI.h"

using namespace ui;

LayerBattleResult::LayerBattleResult() : _skin(nullptr)
{
}

LayerBattleResult::~LayerBattleResult()
{
	_skin = nullptr;
}

bool LayerBattleResult::init()
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

void LayerBattleResult::updateSkin(const bool &isWin)
{
	auto txt = (Text *)_skin->getChildByName("txt");
	txt->setString(isWin ? STR_BATTLE_VICTORY : STR_BATTLE_DEFEAT);
}

void LayerBattleResult::runAppearAction(const function<void()> &func /*= nullptr*/)
{
	auto d = 0.4f;
	_skin->setOpacity(0.0f);
	_skin->setScale(10.0f);
	
	auto actionSpawn = Spawn::createWithTwoActions(EaseCubicActionIn::create(FadeIn::create(d)), EaseCubicActionIn::create(ScaleTo::create(d, 1.0f)));
	auto actionCallFunc = CallFunc::create([func]()
	{
		if (func != nullptr)
		{
			func();
		}
	});
	_skin->runAction(Sequence::create(actionSpawn, actionCallFunc, nullptr));
}

void LayerBattleResult::createSkin()
{
	_skin = (Layer *)CSLoader::createNode(RES_MODULES_MAIN_LAYER_BATTLE_RESULT_CSB);
	_skin->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_skin->setPosition(320.0f, 725.0f);
	addChild(_skin);

	auto layout = (Layout *)_skin->getChildByName("layout");
	layout->addTouchEventListener([](Ref *ref, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			ManagerUI::getInstance()->notify(ID_OBSERVER::SCENE_MAIN, TYPE_OBSERVER_SCENE_MAIN::SHOW_LEVELS);
		}
	});
}
