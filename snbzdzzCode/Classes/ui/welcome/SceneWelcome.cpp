#pragma execution_character_set("utf-8")

#include "SceneWelcome.h"
#include "common/util/UtilRandom.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"
#include "common/util/UtilString.h"
#include "data/config/ManagerCfg.h"
#include "data/define/DefinesRes.h"
#include "data/data/ManagerData.h"
#include "core/timer/ManagerTimer.h"
#include "ui/ManagerUI.h"
#include "common/util/UtilDate.h"

using namespace CocosDenshion;
using namespace cocos2d::ui;

SceneWelcome::SceneWelcome() : _handleImageLoad(nullptr)
{
}

SceneWelcome::~SceneWelcome()
{
	CC_SAFE_RELEASE_NULL(_handleImageLoad);
}

bool SceneWelcome::init()
{
	auto isInit = false;

	do 
	{
		CC_BREAK_IF(!Scene::init());
		
		UtilRandom::initRandomSeed();

		ManagerUI::getInstance()->addKeyEvent(this);
		//
		createSkin();
		//
		/*SimpleAudioEngine::getInstance()->playBackgroundMusic(SOUND_MUSIC_GAME.c_str(), true);*/

		isInit = true;
	} while (0);

	return isInit;
}

void SceneWelcome::createSkin()
{
	auto skin = CSLoader::createNode(RES_MODULES_WELCOME_SCENE_WELCOME_CSB);
	addChild(skin);

	/*auto actionTimeline = CSLoader::createTimeline(RES_MODULES_WELCOME_SCENE_WELCOME_CSB);
	actionTimeline->gotoFrameAndPlay(0, true);
	skin->runAction(actionTimeline);*/
	auto spriteLoading = (Sprite *)skin->getChildByName("spriteLoading");
	spriteLoading->setVisible(false);
	//
	auto txtContinue = (Text *)skin->getChildByName("txtContinue");
	txtContinue->runAction(RepeatForever::create(Sequence::create(FadeOut::create(1.0f), FadeIn::create(1.0f), nullptr)));
	//
	auto layoutBg = (Layout *)skin->getChildByName("layoutBg");
	layoutBg->addTouchEventListener([=](Ref *ref, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			auto time = UtilDate::getSecond();
			log("```````````````LayerWelcome::handleLoading loaded time:%s", Value(time).asString().c_str());
			spriteLoading->setVisible(true);
			spriteLoading->runAction(RepeatForever::create(RotateBy::create(3.0f, 360.0f)));
			spriteLoading->runAction(RepeatForever::create(Sequence::createWithTwoActions(DelayTime::create(0.1f), CallFunc::create(CC_CALLBACK_0(SceneWelcome::handleLoading, this, spriteLoading)))));
		}
	});
}

void SceneWelcome::handleLoading(Sprite *spriteLoading)
{
	auto typeLoadState = ManagerCfg::getInstance()->getTypeLoadState();

	if (typeLoadState == TypeLoadState::UNLOAD)
	{
		handleLoadSound();
		ManagerCfg::getInstance()->loadConfigs();
		return;
	}
	if (typeLoadState == TypeLoadState::LOADING)
	{
		return;
	}
	if (typeLoadState == TypeLoadState::LOADED && _handleImageLoad == nullptr)
	{
		_handleImageLoad = HandleImageLoad::create();
		_handleImageLoad->retain();
		return;
	}
	typeLoadState = _handleImageLoad->getTypeLoadState();
	if (typeLoadState == TypeLoadState::UNLOAD)
	{
		_handleImageLoad->loadImages();
		return;
	}
	if (typeLoadState == TypeLoadState::LOADING)
	{
		return;
	}
	if (typeLoadState == TypeLoadState::LOADED)
	{
		spriteLoading->stopAllActions();
		auto time = UtilDate::getSecond();
		log("```````````````LayerWelcome::handleLoading loaded time:%s", Value(time).asString().c_str());
		//
		ManagerData::getInstance()->dataFileGet();
		time = UtilDate::getSecond();
		log("```````````````LayerWelcome::handleLoading loaded time:%s", Value(time).asString().c_str());
		//
		ManagerTimer::getInstance()->timerStartDeal();
		time = UtilDate::getSecond();
		log("```````````````LayerWelcome::handleLoading loaded time:%s", Value(time).asString().c_str());
		//
		auto isSaveFileExist = ManagerData::getInstance()->isSaveFileExist();
		if (isSaveFileExist)
		{
			ManagerUI::getInstance()->replaceScene(TypeScene::MAIN);
		}
		else
		{
			ManagerUI::getInstance()->replaceScene(TypeScene::PLOT);
		}
		time = UtilDate::getSecond();
		log("```````````````LayerWelcome::handleLoading loaded time:%s", Value(time).asString().c_str());
	}
}

void SceneWelcome::handleLoadSound()
{
	/*SimpleAudioEngine::getInstance()->preloadBackgroundMusic(SOUND_MUSIC_BATTLE_0.c_str());
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(SOUND_MUSIC_BATTLE_1.c_str());

	SimpleAudioEngine::getInstance()->preloadEffect(SOUND_EFFECT_BATTLE_AIM.c_str());
	SimpleAudioEngine::getInstance()->preloadEffect(SOUND_EFFECT_BATTLE_ANGER.c_str());
	SimpleAudioEngine::getInstance()->preloadEffect(SOUND_EFFECT_BATTLE_ARMADD.c_str());
	SimpleAudioEngine::getInstance()->preloadEffect(SOUND_EFFECT_BATTLE_ARMHURT.c_str());
	SimpleAudioEngine::getInstance()->preloadEffect(SOUND_EFFECT_BATTLE_ARMSUB.c_str());
	SimpleAudioEngine::getInstance()->preloadEffect(SOUND_EFFECT_BATTLE_BURN.c_str());
	SimpleAudioEngine::getInstance()->preloadEffect(SOUND_EFFECT_BATTLE_COMA.c_str());
	SimpleAudioEngine::getInstance()->preloadEffect(SOUND_EFFECT_BATTLE_COOK.c_str());
	SimpleAudioEngine::getInstance()->preloadEffect(SOUND_EFFECT_BATTLE_ELEMENT.c_str());
	SimpleAudioEngine::getInstance()->preloadEffect(SOUND_EFFECT_BATTLE_FURY.c_str());
	SimpleAudioEngine::getInstance()->preloadEffect(SOUND_EFFECT_BATTLE_HEAL_CURE.c_str());
	SimpleAudioEngine::getInstance()->preloadEffect(SOUND_EFFECT_BATTLE_MAID_ATTACK.c_str());
	SimpleAudioEngine::getInstance()->preloadEffect(SOUND_EFFECT_BATTLE_MST_ATTACK_0.c_str());
	SimpleAudioEngine::getInstance()->preloadEffect(SOUND_EFFECT_BATTLE_MST_ATTACK_1.c_str());
	SimpleAudioEngine::getInstance()->preloadEffect(SOUND_EFFECT_BATTLE_PALSY.c_str());
	SimpleAudioEngine::getInstance()->preloadEffect(SOUND_EFFECT_BATTLE_PENETRATE.c_str());
	SimpleAudioEngine::getInstance()->preloadEffect(SOUND_EFFECT_BATTLE_POISON.c_str());
	SimpleAudioEngine::getInstance()->preloadEffect(SOUND_EFFECT_BATTLE_PURIFY.c_str());
	SimpleAudioEngine::getInstance()->preloadEffect(SOUND_EFFECT_BATTLE_REMOVE.c_str());
	SimpleAudioEngine::getInstance()->preloadEffect(SOUND_EFFECT_BATTLE_SENSITIVE.c_str());
	SimpleAudioEngine::getInstance()->preloadEffect(SOUND_EFFECT_BATTLE_WEAK.c_str());*/
	SimpleAudioEngine::getInstance()->preloadEffect(SOUND_EFFECT_SYSTEM_BTN_0_MP3.c_str());
	SimpleAudioEngine::getInstance()->preloadEffect(SOUND_EFFECT_SYSTEM_BTN_1_MP3.c_str());
}
