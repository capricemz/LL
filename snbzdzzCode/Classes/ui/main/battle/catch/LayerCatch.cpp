#pragma execution_character_set("utf-8")

#include "LayerCatch.h"
#include "data/define/DefinesRes.h"
#include "common/util/UtilRandom.h"
#include "ui/ManagerUI.h"
#include "data/data/ManagerData.h"
#include "data/define/DefinesString.h"
#include "data/config/ManagerCfg.h"

LayerCatch::LayerCatch() : _skin(nullptr), _index(-1), _remain(0), _typeSelectedMaid(0), _typeSelectedMst(0), _isSuccess(false)
{
}

LayerCatch::~LayerCatch()
{
	_skin = nullptr;
}

bool LayerCatch::init()
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

void LayerCatch::runAppearAction(const function<void()> &func /*= nullptr*/)
{
	auto d = 0.6f;

	auto layoutSelect = (Layout *)_skin->getChildByName("layoutSelect");
	layoutSelect->setScale(0.0f);
	auto actionScale = EaseBackOut::create(ScaleTo::create(d, 1.0f));
	auto actionCallFunc = CallFunc::create([func]()
	{
		if (func != nullptr)
		{
			func();
		}
	});
	layoutSelect->runAction(Sequence::create(actionScale, actionCallFunc, nullptr));
}

void LayerCatch::createSkin()
{
	auto size = Director::getInstance()->getWinSize();
	_skin = (Layer *)CSLoader::createNode(RES_MODULES_MAIN_LAYER_CATCH_CSB);
	_skin->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_skin->setPosition(size.width * 0.5f, size.height * 0.5f);
	addChild(_skin);

	auto actionTimeline = CSLoader::createTimeline(RES_MODULES_MAIN_LAYER_CATCH_CSB);
	_skin->runAction(actionTimeline);

	addTouchEvent();

	updateIndexRemain();

	doWait();
}

void LayerCatch::addTouchEvent()
{
	auto layoutSelect = (Layout *)_skin->getChildByName("layoutSelect");

	auto btn = (Button *)layoutSelect->getChildByName("btnScissors");
	btn->setUserData((void *)TypeSRP::SCISSORS);
	btn->addTouchEventListener(CC_CALLBACK_2(LayerCatch::onTouchBtnSelect, this));

	btn = (Button *)layoutSelect->getChildByName("btnRock");
	btn->setUserData((void *)TypeSRP::ROCK);
	btn->addTouchEventListener(CC_CALLBACK_2(LayerCatch::onTouchBtnSelect, this));

	btn = (Button *)layoutSelect->getChildByName("btnPaper");
	btn->setUserData((void *)TypeSRP::PAPER);
	btn->addTouchEventListener(CC_CALLBACK_2(LayerCatch::onTouchBtnSelect, this));

	auto layoutResult = (Layout *)_skin->getChildByName("layoutResult");
	layoutResult->addTouchEventListener(CC_CALLBACK_2(LayerCatch::onTouchBtnResult, this));
}

void LayerCatch::updateIndexRemain()
{
	auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
	auto vecDataEntity = handleDataEntity->getVecDataEntityMst();
	auto length = (int)vecDataEntity.size();
	for (auto i = _index + 1; i < length; i++)
	{
		auto numTakes = vecDataEntity.at(i)->getAttribute(IdAttribute::ENTITY_BREAK_TAKES_NUM);
		if (numTakes > 0)
		{
			_index = i;
			_remain = /*numTakes*/1;
			return;
		}
	}
	_index = -1;
	_remain = 0;
}

void LayerCatch::getTypeSelectedMst()
{
	auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
	auto dataEntity = handleDataEntity->getVecDataEntityMst().at(_index);
	auto idEntity = dataEntity->getIdEntity();
	auto cfgEntity = ManagerCfg::getInstance()->getDicCfgEntity()[idEntity];
	auto random = UtilRandom::randomBewteen(0.0f, 1000.0f);
	_isSuccess = random < cfgEntity.oddsCatch;
	log("`````````` LayerCatch::getTypeSelectedMst _isSuccess%s", Value(_isSuccess).asString().c_str());
	auto subValue = _isSuccess ? 1 : (UtilRandom::random() < 0.5f ? 2 : 3);//若捕捉成功则为1，否则为2或3
	_typeSelectedMst = _typeSelectedMaid - subValue;
	_typeSelectedMst = _typeSelectedMst == (int)TypeSRP::NONE ? (int)TypeSRP::PAPER : _typeSelectedMst;
}

void LayerCatch::doWait()
{
	/*for (auto i = 0; i < 2; i++)
	{
		auto isMst = i < 1;
		auto rotationBegan = isMst ? -20.0f : 20.0f;
		auto rotationEnd = isMst ? -30.0f : 30.0f;
		string name = RES_IMAGES_MAIN_SRP_PNG_VEC[(int)TypeSRP::ROCK];
		auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);

		auto sprite = (Sprite *)(isMst ? _skin->getChildByName("spriteMst") : _skin->getChildByName("spriteMaid"));
		sprite->setRotation(rotationBegan);
		sprite->setSpriteFrame(spriteFrame);

		auto actionRotateTo = EaseQuadraticActionInOut::create(RotateTo::create(1.0f / 3.0f, rotationEnd));
		auto actionRotateBack = EaseQuadraticActionInOut::create(RotateTo::create(1.0f / 3.0f, rotationBegan));
		auto actionWait = RepeatForever::create(Sequence::createWithTwoActions(actionRotateTo, actionRotateBack));
		actionWait->setTag(1);
		sprite->runAction(actionWait);
	}*/
	auto layoutResult = (Layout *)_skin->getChildByName("layoutResult");
	layoutResult->setTouchEnabled(false);
	auto txtContinue = (Text *)_skin->getChildByName("layoutResult");
	txtContinue->stopAllActions();

	auto actionTimeline = (cocostudio::timeline::ActionTimeline *)_skin->getActionByTag(_skin->getTag());
	actionTimeline->play(ANIMATION_WAIT, false);
}

void LayerCatch::doReach()
{
	/*for (auto i = 0; i < 2; i++)
	{
		auto isMst = i < 1;
		auto rotationBegan = isMst ? -30.0f : 30.0f;
		auto rotationEnd0 = isMst ? -50.0f : 50.0f;
		auto rotationEnd1 = isMst ? -70.0f : 70.0f;
		auto sprite = (Sprite *)(isMst ? _skin->getChildByName("spriteMst") : _skin->getChildByName("spriteMaid"));
		sprite->stopActionByTag(1);
		
		auto actionRotateReset = RotateTo::create(0.01f, rotationBegan);
		auto actionRotateTo0 = EaseQuadraticActionInOut::create(RotateTo::create(0.2f, rotationEnd0));
		auto actionRotateBack0 = EaseQuadraticActionInOut::create(RotateTo::create(0.2f, rotationBegan));
		auto actionRotateTo1 = EaseQuadraticActionInOut::create(RotateTo::create(1.0f / 6.0f, rotationEnd0));
		auto actionRotateBack1 = EaseQuadraticActionInOut::create(RotateTo::create(1.0f / 6.0f, rotationBegan));
		auto actionReachOut = CallFunc::create([this, isMst, sprite]()
		{
			string name = "";
			if (isMst)
			{
				_typeSelectedMst = UtilRandom::randomBewteen((float)TypeSRP::SCISSORS, (float)TypeSRP::PAPER);
				name = RES_IMAGES_MAIN_SRP_PNG_VEC[_typeSelectedMst];
			}
			else
			{
				name = RES_IMAGES_MAIN_SRP_PNG_VEC[_typeSelectedMaid];
			}
			auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
			sprite->setSpriteFrame(spriteFrame);
		});
		auto actionRotateTo2 = EaseQuadraticActionInOut::create(RotateTo::create(1.0f / 6.0f, rotationEnd1));

		auto actionOver = CallFunc::create([this, sprite, isMst]()
		{
			sprite->stopActionByTag(1);
			if (!isMst)
			{
				showResult();
			}
		});
		auto actionReach = Sequence::create(actionRotateReset, actionRotateTo0, actionRotateBack0, actionRotateTo1, actionRotateBack1, actionReachOut, actionRotateTo2, actionOver, nullptr);
		actionReach->setTag(1);
		sprite->runAction(actionReach);
	}*/
	auto actionTimeline = (cocostudio::timeline::ActionTimeline *)_skin->getActionByTag(_skin->getTag());
	actionTimeline->setLastFrameCallFunc([this, actionTimeline]()
	{
		actionTimeline->setLastFrameCallFunc(nullptr);
		showResult();
	});
	actionTimeline->play(ANIMATION_RECH, false);
}

void LayerCatch::showResult()
{
	getTypeSelectedMst();

	auto actionTimeline = (cocostudio::timeline::ActionTimeline *)_skin->getActionByTag(_skin->getTag());
	actionTimeline->play(ANIMATION_RESULT, false);

	auto layoutResult = (Layout *)_skin->getChildByName("layoutResult");
	layoutResult->setTouchEnabled(true);
	
	auto name = RES_IMAGES_MAIN_SRP_PNG_VEC[_typeSelectedMst];
	auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
	auto sprite = (Sprite *)layoutResult->getChildByName("spriteMst");
	sprite->setSpriteFrame(spriteFrame);

	name = RES_IMAGES_MAIN_SRP_PNG_VEC[_typeSelectedMaid];
	spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
	sprite = (Sprite *)layoutResult->getChildByName("spriteMaid");
	sprite->setSpriteFrame(spriteFrame);

	auto spriteSuccess = (Sprite *)layoutResult->getChildByName("spriteSuccess");
	spriteSuccess->setVisible(_isSuccess);
	auto spriteFailure = (Sprite *)layoutResult->getChildByName("spriteFailure");
	spriteFailure->setVisible(!_isSuccess);
	
	if (_isSuccess)
	{
		auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
		auto dataEntity = handleDataEntity->getVecDataEntityMst().at(_index);
		auto idEntity = dataEntity->getIdEntity();
		auto handleDataIncome = ManagerData::getInstance()->getHandleDataIncome();
		handleDataIncome->pushVecDataTrainingInfo(idEntity, 0, 0, false);
		handleDataIncome->dataFileSet();
	}

	auto txtContinue = (Text *)layoutResult->getChildByName("txtContinue");
	txtContinue->runAction(RepeatForever::create(Sequence::create(FadeOut::create(1.0f), FadeIn::create(1.0f), nullptr)));
}

void LayerCatch::onTouchBtnSelect(Ref *ref, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		auto btn = (Button *)ref;
		_typeSelectedMaid = (int)btn->getUserData();
		_remain--;

		doReach();
	}
}

void LayerCatch::onTouchBtnResult(Ref *ref, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		if (_isSuccess || _remain == 0)//若捕获成功或剩余0次
		{
			updateIndexRemain();
		}

		if (_index != -1)//若有下一个
		{
			doWait();
		}
		else
		{
			ManagerUI::getInstance()->notify(ID_OBSERVER::LAYER_BATTLE, TYPE_OBSERVER_LAYER_BATTLE::SHOW_LAYER_BATTLE_RESULT);
			removeFromParent();
		}
	}
}
