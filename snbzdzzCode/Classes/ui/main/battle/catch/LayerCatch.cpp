#pragma execution_character_set("utf-8")

#include "LayerCatch.h"
#include "data/define/DefinesRes.h"
#include "common/util/UtilRandom.h"

LayerCatch::LayerCatch() : _skin(nullptr), _typeSelectedMst(0), _typeSelectedMaid(0)
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

void LayerCatch::createSkin()
{
	_skin = (Layer *)CSLoader::createNode(RES_MODULES_MAIN_LAYER_CATCH_CSB);
	addChild(_skin);

	auto btn = (Button *)_skin->getChildByName("btnScissors");
	btn->setUserData((void *)TypeSRP::SCISSORS);
	btn->addTouchEventListener(CC_CALLBACK_2(LayerCatch::onTouchBtn, this));
	
	btn = (Button *)_skin->getChildByName("btnRock");
	btn->setUserData((void *)TypeSRP::ROCK);
	btn->addTouchEventListener(CC_CALLBACK_2(LayerCatch::onTouchBtn, this));

	btn = (Button *)_skin->getChildByName("btnPaper");
	btn->setUserData((void *)TypeSRP::PAPER);
	btn->addTouchEventListener(CC_CALLBACK_2(LayerCatch::onTouchBtn, this));

	doWait();
}

void LayerCatch::doWait()
{
	for (auto i = 0; i < 2; i++)
	{
		auto isMst = i < 1;
		auto rotationBegan = isMst ? -20.0f : 20.0f;
		auto rotationEnd = isMst ? -30.0f : 30.0f;
		auto sprite = (Sprite *)(isMst ? _skin->getChildByName("spriteMst") : _skin->getChildByName("spriteMaid"));
		sprite->setRotation(rotationBegan);
		auto actionRotateTo = EaseQuadraticActionInOut::create(RotateTo::create(1.0f / 3.0f, rotationEnd));
		auto actionRotateBack = EaseQuadraticActionInOut::create(RotateTo::create(1.0f / 3.0f, rotationBegan));
		auto actionWait = RepeatForever::create(Sequence::createWithTwoActions(actionRotateTo, actionRotateBack));
		actionWait->setTag(1);
		_skin->runAction(actionWait);
	}
}

void LayerCatch::onTouchBtn(Ref *ref, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		auto btn = (Button *)ref;
		_typeSelectedMaid = (int)btn->getUserData();
		doReach();
	}
}

void LayerCatch::doReach()
{
	auto btn = (Button *)_skin->getChildByName("btnScissors");
	btn->setVisible(false);
	btn = (Button *)_skin->getChildByName("btnRock");
	btn->setVisible(false);
	btn = (Button *)_skin->getChildByName("btnPaper");
	btn->setVisible(false);

	for (auto i = 0; i < 2; i++)
	{
		auto isMst = i < 1;
		auto rotationBegan = isMst ? -30.0f : 30.0f;
		auto rotationEnd0 = isMst ? -50.0f : 50.0f;
		auto rotationEnd1 = isMst ? -70.0f : 70.0f;
		auto sprite = (Sprite *)(isMst ? _skin->getChildByName("spriteMst") : _skin->getChildByName("spriteMaid"));
		_skin->stopActionByTag(1);
		
		auto actionRotateReset = RotateTo::create(0.01f, rotationBegan);
		auto actionRotateTo0 = EaseQuadraticActionInOut::create(RotateTo::create(0.2f, rotationEnd0));
		auto actionRotateBack0 = EaseQuadraticActionInOut::create(RotateTo::create(0.2f, rotationBegan));
		auto actionRotateTo1 = EaseQuadraticActionInOut::create(RotateTo::create(1.0f / 6.0f, rotationEnd0));
		auto actionRotateBack1 = EaseQuadraticActionInOut::create(RotateTo::create(1.0f / 6.0f, rotationBegan));
		auto actionReachOut = CallFunc::create([sprite, this]()
		{
			_typeSelectedMst = UtilRandom::randomBewteen((float)TypeSRP::SCISSORS, (float)TypeSRP::PAPER);
			auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(RES_IMAGES_MAIN_SRP_PNG_VEC[_typeSelectedMst]);
			sprite->setSpriteFrame(spriteFrame);
		});
		auto actionRotateTo2 = EaseQuadraticActionInOut::create(RotateTo::create(1.0f / 6.0f, rotationEnd1));

		auto actionOver = CallFunc::create([this]()
		{
			showResult((_typeSelectedMst + 1) % 3 == _typeSelectedMaid);
		});

		_skin->runAction(Sequence::create(actionRotateReset, actionRotateTo0, actionRotateBack0, actionRotateTo1, actionRotateBack1, actionReachOut, actionRotateTo2, actionOver, nullptr));
	}
}

void LayerCatch::showResult(const bool &isWin)
{
	auto layout = (Layout *)_skin->getChildByName("layout");
	layout->addTouchEventListener([this](Ref *ref, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			removeFromParent();
		}
	});

	auto txt = Text::create("catch", RES_FONTS_KTJT, 40);
	txt->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	auto sizeSkin = layout->getContentSize();
	txt->setPosition(Vec2(sizeSkin.width * 0.5f, sizeSkin.height * 0.5f));
	_skin->addChild(txt);
}
