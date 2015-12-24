#pragma execution_character_set("utf-8")

#include "LayerBattleResult.h"

#include "data/define/DefinesRes.h"
#include "data/define/DefinesString.h"
#include "ui/ManagerUI.h"
#include "data/data/ManagerData.h"
#include "data/config/ManagerCfg.h"

LayerBattleResult::LayerBattleResult() : _skin(nullptr), _isAppearing(false)
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
	_isAppearing = true;

	auto txtContinue = (Text *)_skin->getChildByName("txtContinue");
	txtContinue->setVisible(false);

	Vector<FiniteTimeAction *> vecAction;

	auto spriteVictoryDefeatBg = (Sprite *)_skin->getChildByName("spriteVictoryDefeatBg");
	auto spriteVictoryDefeat = (Sprite *)_skin->getChildByName("spriteVictoryDefeat");
	auto duration = 10.0f / 60.0f;
	auto actionCallFunc = CallFunc::create([spriteVictoryDefeatBg, duration]()
	{
		spriteVictoryDefeatBg->runAction(FadeIn::create(duration));
	});
	vecAction.pushBack(actionCallFunc);
	auto actionDelay = DelayTime::create(duration + 1.0f / 60.0f);
	vecAction.pushBack(actionDelay);
	
	duration = 10.0f / 60.0f;
	actionCallFunc = CallFunc::create([spriteVictoryDefeat, duration]()
	{
		spriteVictoryDefeat->runAction(FadeIn::create(duration));
	});
	vecAction.pushBack(actionCallFunc);
	actionDelay = DelayTime::create(duration + 1.0f / 60.0f);
	vecAction.pushBack(actionDelay);

	duration = 10.0f / 60.0f;
	actionCallFunc = CallFunc::create([spriteVictoryDefeatBg, spriteVictoryDefeat, duration]()
	{
		spriteVictoryDefeatBg->runAction(MoveBy::create(duration, moveDistanceVictoryDefeat));
		spriteVictoryDefeat->runAction(MoveBy::create(duration, moveDistanceVictoryDefeat));
	});
	vecAction.pushBack(actionCallFunc);
	actionDelay = DelayTime::create(duration + 1.0f / 60.0f);
	vecAction.pushBack(actionDelay);

	auto layoutStar = (Layout *)_skin->getChildByName("layoutStar");
	for (auto node : layoutStar->getChildren())
	{
		duration = 10.0f / 60.0f;
		actionCallFunc = CallFunc::create([node, duration]()
		{
			node->runAction(FadeIn::create(duration));
		});
		vecAction.pushBack(actionCallFunc);
		actionDelay = DelayTime::create(duration + 1.0f / 60.0f);
		vecAction.pushBack(actionDelay);
	}
	
	auto spriteMaid0 = (Sprite *)_skin->getChildByName("spriteMaid0");
	duration = 10.0f / 60.0f;
	actionCallFunc = CallFunc::create([spriteMaid0, duration]()
	{
		spriteMaid0->runAction(MoveBy::create(duration, vecMoveDistanceSpriteMaid[0]));
	});
	vecAction.pushBack(actionCallFunc);
	actionDelay = DelayTime::create(duration + 1.0f / 60.0f);
	vecAction.pushBack(actionDelay);

	auto spriteMaid1 = (Sprite *)_skin->getChildByName("spriteMaid1");
	auto spriteMaid2 = (Sprite *)_skin->getChildByName("spriteMaid2");
	duration = 10.0f / 60.0f;
	actionCallFunc = CallFunc::create([spriteMaid1, spriteMaid2, duration]()
	{
		spriteMaid1->runAction(MoveBy::create(duration, vecMoveDistanceSpriteMaid[1]));
		spriteMaid2->runAction(MoveBy::create(duration, vecMoveDistanceSpriteMaid[2]));
	});
	vecAction.pushBack(actionCallFunc);
	actionDelay = DelayTime::create(duration + 1.0f / 60.0f);
	vecAction.pushBack(actionDelay);

	auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
	auto isBattleWin = handleDataEntity->isBattleWin();
	if (isBattleWin)
	{
		auto layoutAward = (Layout *)_skin->getChildByName("layoutAward");
		for (auto node : layoutAward->getChildren())
		{
			if (node->isVisible())
			{
				duration = 10.0f / 60.0f;
				actionCallFunc = CallFunc::create([node, duration]()
				{
					node->runAction(FadeIn::create(duration));
				});
				vecAction.pushBack(actionCallFunc);
				actionDelay = DelayTime::create(duration + 1.0f / 60.0f);
				vecAction.pushBack(actionDelay);
			}
		}
	}
	else
	{
		auto layoutBtns = (Layout *)_skin->getChildByName("layoutBtns");
		for (auto node : layoutBtns->getChildren())
		{
			duration = 10.0f / 60.0f;
			actionCallFunc = CallFunc::create([node, duration]()
			{
				node->runAction(FadeIn::create(duration));
			});
			vecAction.pushBack(actionCallFunc);
			actionDelay = DelayTime::create(duration + 1.0f / 60.0f);
			vecAction.pushBack(actionDelay);
		}
	}

	actionCallFunc = CallFunc::create([this, func, txtContinue]()
	{
		txtContinue->setVisible(true);
		_isAppearing = false;
		if (func != nullptr)
		{
			func();
		}
	});
	vecAction.pushBack(actionCallFunc);

	_skin->runAction(Sequence::create(vecAction));
}

void LayerBattleResult::createSkin()
{
	auto size = Director::getInstance()->getWinSize();
	_skin = (Layer *)CSLoader::createNode(RES_MODULES_MAIN_LAYER_BATTLE_RESULT_CSB);
	_skin->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_skin->setPosition(size.width * 0.5f, size.height * 0.5f);
	addChild(_skin);
	
	auto layout = (Layout *)_skin->getChildByName("layoutBg");
	layout->addTouchEventListener(CC_CALLBACK_2(LayerBattleResult::onTouchContinue, this));

	updateVictoryDefeat();
	updateLayoutStar();
	updateSpriteMaid();
	updateLayoutAward();
	updateLayoutBtns();

	auto txtContinue = (Text *)_skin->getChildByName("txtContinue");
	txtContinue->runAction(RepeatForever::create(Sequence::create(FadeOut::create(1.0f), FadeIn::create(1.0f), nullptr)));
}

void LayerBattleResult::updateVictoryDefeat()
{
	auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
	auto isBattleWin = handleDataEntity->isBattleWin();

	auto spriteVictoryDefeatBg = (Sprite *)_skin->getChildByName("spriteVictoryDefeatBg");
	spriteVictoryDefeatBg->setPosition(spriteVictoryDefeatBg->getPosition() - moveDistanceVictoryDefeat);
	spriteVictoryDefeatBg->setOpacity(0.0f);

	auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(isBattleWin ? RES_IMAGES_BATTLE_RESULT_VICTORY : RES_IMAGES_BATTLE_RESULT_DEFEAT);
	auto spriteVictoryDefeat = (Sprite *)_skin->getChildByName("spriteVictoryDefeat");
	spriteVictoryDefeat->setSpriteFrame(spriteFrame);
	spriteVictoryDefeat->setPosition(spriteVictoryDefeat->getPosition() - moveDistanceVictoryDefeat);
	spriteVictoryDefeat->setOpacity(0.0f);
}

void LayerBattleResult::updateLayoutStar()
{
	auto handleDataLevels = ManagerData::getInstance()->getHandleDataLevels();
	auto dataLevel = handleDataLevels->getDataLevelCurrent();

	auto levelTargetNum = dataLevel->levelTargetNumGet();
	auto layoutStar = (Layout *)_skin->getChildByName("layoutStar");
	auto isSpriteNullptr = false;
	auto widthSpriteStar = 0.0f;
	for (auto i = 0; i < levelTargetNum; i++)
	{
		auto spriteStar = (Sprite *)layoutStar->getChildByName("spriteStar" + Value(i).asInt());
		if (spriteStar == nullptr)
		{
			spriteStar = Sprite::create();
			spriteStar->setName("spriteStar" + Value(i).asInt());
			spriteStar->setOpacity(0.0f);
			layoutStar->addChild(spriteStar);
			isSpriteNullptr = true;
		}

		auto isComolete = dataLevel->levelTargetIsComplete(i);
		auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(isComolete ? RES_IMAGES_MAIN_COMMON_STAR_PNG : RES_IMAGES_MAIN__COMMON_STAR_DARK_PNG);
		spriteStar->setSpriteFrame(spriteFrame);

		auto size = spriteStar->getContentSize();
		auto scale = size.width > size.height ? sizeStarBattleResult.width / size.width : sizeStarBattleResult.height / size.height;
		spriteStar->setScale(scale);

		if (isSpriteNullptr && (widthSpriteStar == 0.0f || sizeStarBattleResult.width > widthSpriteStar))
		{
			widthSpriteStar = sizeStarBattleResult.width;
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

void LayerBattleResult::updateSpriteMaid()
{
	auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
	auto isBattleWin = handleDataEntity->isBattleWin();
	auto lengthVecDataEntity = handleDataEntity->getLengthVecDataEntity(false);
	auto vecDataEntity = handleDataEntity->getVecDataEntityMaid();
	auto dicCfgEntity = ManagerCfg::getInstance()->getDicCfgEntity();

	for (auto i = 0; i < ENTITY_BATTLE_MAX; i++)
	{
		auto sprite = (Sprite *)_skin->getChildByName("spriteMaid" + Value(i).asString());
		sprite->setScale(0.38f);
		sprite->setPosition(sprite->getPosition() - vecMoveDistanceSpriteMaid[i]);
		if (i < lengthVecDataEntity)
		{
			auto dataEntity = vecDataEntity.at(i);
			auto idEntity = dataEntity->getIdEntity();
			auto cfgEntity = dicCfgEntity[idEntity];
			auto texture = Director::getInstance()->getTextureCache()->getTextureForKey(isBattleWin ? cfgEntity.urlPicEntity : cfgEntity.urlPicEntityBreak);
			sprite->setTexture(texture);
		}
		else
		{
			sprite->setVisible(false);
		}
	}
}

void LayerBattleResult::updateLayoutAward()
{
	auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
	auto isBattleWin = handleDataEntity->isBattleWin();
	auto handleDataGrade = ManagerData::getInstance()->getHandleDataGrade();
	auto grade = handleDataGrade->getGrade();
	auto gradeExpNow = handleDataGrade->getGradeExpNow();
	auto gradeExpNeed = handleDataGrade->getGradeExpNeed();

	auto layout = (Layout *)_skin->getChildByName("layoutAward");
	if (!isBattleWin)
	{
		layout->setVisible(false);
		return;
	}

	auto handleDataLevels = ManagerData::getInstance()->getHandleDataLevels();
	auto dataLevel = handleDataLevels->getDataLevelCurrent();
	auto dicCfgThing = ManagerCfg::getInstance()->getDicCfgThing();
	
	auto vecIdThingAward = dataLevel->getVecIdThingAward();
	auto length = (int)vecIdThingAward.size();
	auto index = 0;
	while (true)
	{
		auto sprite = (Sprite *)layout->getChildByName("spriteAward" + Value(index).asString());
		if (sprite == nullptr)
		{
			break;
		}
		if (index < length)
		{
			auto var = vecIdThingAward[index];
			auto idThing = var[0];
			auto value = var[1];
			auto cfgThing = dicCfgThing[idThing];
			auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cfgThing.urlPic);
			sprite->setSpriteFrame(spriteFrame);
			sprite->setOpacity(0.0f);
		}
		else
		{
			sprite->setVisible(false);
		}
		index++;
	}

	auto txtGrade = (Text *)layout->getChildByName("txtGrade");
	txtGrade->setString(Value(grade).asString());
	txtGrade->setOpacity(0.0f);
	auto spriteExpBg = (Sprite *)layout->getChildByName("spriteExpBg");
	spriteExpBg->setOpacity(0.0f);
	auto barExp = (LoadingBar *)layout->getChildByName("barExp");
	barExp->setPercent((float)gradeExpNow / (float)gradeExpNeed * 100.0f);
	barExp->setOpacity(0.0f);
}

void LayerBattleResult::updateLayoutBtns()
{
	auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
	auto isBattleWin = handleDataEntity->isBattleWin();

	auto layout = (Layout *)_skin->getChildByName("layoutBtns");
	if (isBattleWin)
	{
		layout->setVisible(false);
		return;
	}

	auto btn = (Button *)layout->getChildByName("btn0");
	btn->setUserData((void *)TYPE_OBSERVER_SCENE_MAIN::SHOW_SKILLS);
	btn->setOpacity(0.0f);
	btn->addTouchEventListener(CC_CALLBACK_2(LayerBattleResult::onTouchBtnTo, this));
	
	btn = (Button *)layout->getChildByName("btn1");
	btn->setUserData((void *)TYPE_OBSERVER_SCENE_MAIN::SHOW_TRAINING);
	btn->setOpacity(0.0f);
	btn->addTouchEventListener(CC_CALLBACK_2(LayerBattleResult::onTouchBtnTo, this));

	btn = (Button *)layout->getChildByName("btn2");
	btn->setUserData((void *)TYPE_OBSERVER_SCENE_MAIN::SHOW_SHOP);
	btn->setOpacity(0.0f);
	btn->addTouchEventListener(CC_CALLBACK_2(LayerBattleResult::onTouchBtnTo, this));
}

void LayerBattleResult::onTouchContinue(Ref *ref, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		if (_isAppearing)
		{
			return;
		}
		auto handleDataGrade = ManagerData::getInstance()->getHandleDataGrade();
		auto isGradeUp = handleDataGrade->getIsGradeUp();
		if (isGradeUp)
		{
			ManagerUI::getInstance()->notify(ID_OBSERVER::LAYER_BATTLE, TYPE_OBSERVER_LAYER_BATTLE::SHOW_LAYER_GRADE_UP);
			removeFromParent();
		}
		else
		{
			ManagerUI::getInstance()->notify(ID_OBSERVER::SCENE_MAIN, TYPE_OBSERVER_SCENE_MAIN::SWITCH_LAYER, TYPE_OBSERVER_SCENE_MAIN::SHOW_LEVELS);
		}
	}
}

void LayerBattleResult::onTouchBtnTo(Ref *ref, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		if (_isAppearing)
		{
			return;
		}
		auto btn = (Button *)ref;
		auto typeShow = (TYPE_OBSERVER_SCENE_MAIN)(int)btn->getUserData();
		ManagerUI::getInstance()->notify(ID_OBSERVER::SCENE_MAIN, TYPE_OBSERVER_SCENE_MAIN::SWITCH_LAYER, typeShow);
	}
}
