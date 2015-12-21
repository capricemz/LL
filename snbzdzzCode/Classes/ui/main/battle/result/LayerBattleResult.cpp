#pragma execution_character_set("utf-8")

#include "LayerBattleResult.h"

#include "data/define/DefinesRes.h"
#include "data/define/DefinesString.h"
#include "ui/ManagerUI.h"
#include "data/data/ManagerData.h"

LayerBattleResult::LayerBattleResult() : _skin(nullptr), _isActionRunning(false)
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

void LayerBattleResult::runAppearAction(const function<void()> &func /*= nullptr*/)
{
	_isActionRunning = true;
	auto d = 0.4f;
	_skin->setOpacity(0.0f);
	_skin->setScale(10.0f);
	
	auto actionSpawn = Spawn::createWithTwoActions(EaseCubicActionIn::create(FadeIn::create(d)), EaseCubicActionIn::create(ScaleTo::create(d, 1.0f)));
	auto actionCallFunc = CallFunc::create([func, this]()
	{
		_isActionRunning = false;
		if (func != nullptr)
		{
			func();
		}
	});
	_skin->runAction(Sequence::create(actionSpawn, actionCallFunc, nullptr));
}

void LayerBattleResult::createSkin()
{
	auto size = Director::getInstance()->getWinSize();
	_skin = (Layer *)CSLoader::createNode(RES_MODULES_MAIN_LAYER_BATTLE_RESULT_CSB);
	_skin->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_skin->setPosition(size.width * 0.5f, size.height * 0.5f);
	addChild(_skin);
	
	updateLayoutVictory();
	updateLayoutDefeat();
}

void LayerBattleResult::updateLayoutVictory()
{
	auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
	auto isBattleWin = handleDataEntity->isBattleWin();
	auto handleDataLevels = ManagerData::getInstance()->getHandleDataLevels();
	auto dataLevel = handleDataLevels->getDataLevelCurrent();
	
	auto layout = (Layout *)_skin->getChildByName("layoutVictory");
	layout->setVisible(isBattleWin);
	
	if (!isBattleWin)
	{
		return;
	}
	
	layout->addTouchEventListener(CC_CALLBACK_2(LayerBattleResult::onTouchContinue, this));
	
	updateLayoutStar();
	updateLayoutDrop();

	auto txtContinue = (Text *)layout->getChildByName("txtContinue");
	txtContinue->runAction(RepeatForever::create(Sequence::create(FadeOut::create(1.0f), FadeIn::create(1.0f), nullptr)));

	playAnimationVictory();
}

void LayerBattleResult::updateLayoutDefeat()
{
	auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
	auto isBattleWin = handleDataEntity->isBattleWin();

	auto layout = (Layout *)_skin->getChildByName("layoutDefeat");
	layout->setVisible(!isBattleWin);

	if (isBattleWin)
	{
		return;
	}

	layout->addTouchEventListener(CC_CALLBACK_2(LayerBattleResult::onTouchContinue, this));

	auto spriteContinue = (Sprite *)layout->getChildByName("spriteContinue");
	spriteContinue->runAction(RepeatForever::create(Sequence::create(FadeOut::create(1.0f), FadeIn::create(1.0f), nullptr)));
}

void LayerBattleResult::onTouchContinue(Ref *ref, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		if (_isActionRunning)
		{
			return;
		}
		ManagerUI::getInstance()->notify(ID_OBSERVER::SCENE_MAIN, TYPE_OBSERVER_SCENE_MAIN::SWITCH_LAYER, TYPE_OBSERVER_SCENE_MAIN::SHOW_LEVELS);
	}
}

void LayerBattleResult::updateLayoutStar()
{
	auto handleDataLevels = ManagerData::getInstance()->getHandleDataLevels();
	auto dataLevel = handleDataLevels->getDataLevelCurrent();

	auto layout = (Layout *)_skin->getChildByName("layoutVictory");

	auto levelTargetNum = dataLevel->levelTargetNumGet();
	auto layoutStar = (Layout *)layout->getChildByName("layoutStar");
	auto isSpriteNullptr = false;
	auto widthSpriteStar = 0.0f;
	for (auto i = 0; i < levelTargetNum; i++)
	{
		auto spriteStar = (Sprite *)layoutStar->getChildByName("spriteStar" + Value(i).asInt());
		if (spriteStar == nullptr)
		{
			spriteStar = Sprite::create();
			spriteStar->setName("spriteStar" + Value(i).asInt());
			layoutStar->addChild(spriteStar);
			isSpriteNullptr = true;
		}

		auto isComolete = dataLevel->levelTargetIsComplete(i);
		auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(isComolete ? RES_IMAGES_MAIN_LEVELS_XING_PNG : RES_IMAGES_MAIN_LEVELS_XING_KONG_PNG);
		spriteStar->setSpriteFrame(spriteFrame);

		auto size = spriteStar->getContentSize();
		auto scale = size.width > size.height ? sizeBattleResultStar.width / size.width : sizeBattleResultStar.height / size.height;
		spriteStar->setScale(scale);

		if (isSpriteNullptr && (widthSpriteStar == 0.0f || sizeBattleResultStar.width > widthSpriteStar))
		{
			widthSpriteStar = sizeBattleResultStar.width;
		}
	}
	if (widthSpriteStar != 0.0f)
	{
		widthSpriteStar += 5.0f;
		auto size = layoutStar->getContentSize();
		auto postion = Vec2((size.width - widthSpriteStar * (levelTargetNum - 1)) * 0.5f, size.height * 0.5f);
		for (auto i = 0; i < levelTargetNum; i++)
		{
			auto spriteStar = (Sprite *)layoutStar->getChildByName("spriteStar" + Value(i).asInt());
			spriteStar->setPosition(postion);
			postion += Vec2(widthSpriteStar, 0.0f);
		}
	}
}

void LayerBattleResult::updateLayoutDrop()
{

}

void LayerBattleResult::playAnimationVictory()
{

}
