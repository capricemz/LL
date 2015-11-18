#pragma execution_character_set("utf-8")

#include "ManagerUI.h"
#include "plot/ScenePlot.h"
#include "main/SceneMain.h"
#include "data/config/ManagerCfg.h"
#include "data/data/ManagerData.h"
#include "common/UIWordsDrift.h"

static ManagerUI *_instance;

ManagerUI * ManagerUI::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new ManagerUI();
	}
	return _instance;
}

void ManagerUI::destroyInstance()
{
	CC_SAFE_DELETE(_instance);
}

ManagerUI::ManagerUI() : _typeSceneRunning(TypeScene::WELCOME), _layerRunning(nullptr)
{
}

ManagerUI::~ManagerUI()
{
	_layerRunning = nullptr;
}

void ManagerUI::addKeyEvent(Scene *scene)
{
	auto director = Director::getInstance();
	auto listenerKeyboard = EventListenerKeyboard::create();
	listenerKeyboard->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event *event)
	{
		if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
		{
			ManagerData::getInstance()->dataFileSet();

			ManagerCfg::getInstance()->destroyInstance();
			ManagerData::getInstance()->destroyInstance();

			Director::getInstance()->end();
		}
	};
	director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerKeyboard, scene);
}

void ManagerUI::replaceScene(TypeScene type)
{
	if (_typeSceneRunning != TypeScene::WELCOME && _typeSceneRunning == type)
	{
		return;
	}
	Scene *scene;
	if (type == TypeScene::PLOT)
	{
		scene = ScenePlot::create();
	}
	else if (type == TypeScene::MAIN)
	{
		scene = SceneMain::create();
	}
	auto animateScene = TransitionFade::create(0.3f, scene);
	Director::getInstance()->replaceScene(animateScene);
}

void ManagerUI::runLayerAppearDisappear(ILayerAppearDisappear *layerNew)
{
	//Òþ²Ø¾É²ã
	auto actionMoveBy0 = EaseCircleActionIn::create(MoveBy::create(0.4f, Vec2(-640.0f, 0.0f)));
	auto actionAffterRunDisappear = CallFunc::create(CC_CALLBACK_0(ILayerAppearDisappear::afterRunDisappear, _layerRunning));
	auto actionRemove4Parent = CallFunc::create(CC_CALLBACK_0(ILayerAppearDisappear::dealRemoveFromParent, _layerRunning));
	_layerRunning->getThis()->runAction(Sequence::create(actionMoveBy0, actionAffterRunDisappear, actionRemove4Parent, nullptr));
	//
	_layerRunning = layerNew;
	//ÏÔÊ¾ÐÂ²ã
	auto layer = _layerRunning->getThis();
	auto postion = layer->getPosition() + Vec2(640.0f, 0.0f);
	layer->setPosition(postion);
	auto actionMoveBy1 = EaseCircleActionIn::create(MoveBy::create(0.4f, Vec2(-640.0f, 0.0f)));
	auto actionCallFunc = CallFunc::create(CC_CALLBACK_0(ILayerAppearDisappear::afterRunAppear, _layerRunning));
	layer->runAction(Sequence::create(actionMoveBy1, actionCallFunc, nullptr));
}

void ManagerUI::showWordsDrift(Node *parent, const Vec2 &postion, const string &words, const Color4B &color, const float &duration)
{
	auto uiWordsDrift = UIWordsDrift::create();
	uiWordsDrift->setPosition(postion);
	uiWordsDrift->driftWords(words, color, duration);
	parent->addChild(uiWordsDrift);
}
