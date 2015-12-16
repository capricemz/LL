#pragma execution_character_set("utf-8")

#include "LayerCatch.h"
#include "data/define/DefinesRes.h"
#include "common/util/UtilRandom.h"
#include "ui/ManagerUI.h"
#include "data/data/ManagerData.h"
#include "data/define/DefinesString.h"

LayerCatch::LayerCatch() : _skin(nullptr), _index(-1), _remain(0), _typeSelectedMst(0), _typeSelectedMaid(0)
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
	_skin->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_skin->setPosition(320.0f, 725.0f);
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

	updateIndexRemain();

	updateInfo();

	doWait();
}

void LayerCatch::doWait()
{
	for (auto i = 0; i < 2; i++)
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
	}
}

void LayerCatch::onTouchBtn(Ref *ref, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		auto btn = (Button *)ref;
		_typeSelectedMaid = (int)btn->getUserData();
		_remain--;

		updateInfo();
		
		setBtnVisible(false);

		doReach();
	}
}

void LayerCatch::doReach()
{
	for (auto i = 0; i < 2; i++)
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
	}
}

void LayerCatch::showResult()
{
	auto isWin = _typeSelectedMst % 3 + 1 == _typeSelectedMaid;
	
	auto txtResult = (Text *)_skin->getChildByName("txtResult");
	txtResult->setString(isWin ? "catch" : "missed");

	if (isWin)
	{
		auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
		auto dataEntity = handleDataEntity->getVecDataEntityMst().at(_index);
		auto idEntity = dataEntity->getIdEntity();
		auto handleDataIncome = ManagerData::getInstance()->getHandleDataIncome();
		handleDataIncome->pushVecDataTrainingInfo(idEntity, 0, 0, false);
		handleDataIncome->dataFileSet();
	}

	auto layout = (Layout *)_skin->getChildByName("layout");
	layout->addTouchEventListener([this, isWin](Ref *ref, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			if (isWin || _remain == 0)//若捕获成功或剩余0次
			{
				updateIndexRemain();
			}

			if (_index != -1)//若有下一个
			{
				updateInfo();
				setBtnVisible(true);
				doWait();
			}
			else
			{
				ManagerUI::getInstance()->notify(ID_OBSERVER::LAYER_BATTLE, TYPE_OBSERVER_LAYER_BATTLE::SHOW_LAYER_BATTLE_RESULT);
				removeFromParent();
			}
		}
	});
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
			_remain = numTakes;
			return;
		}
	}
	_index = -1;
	_remain = 0;
}

void LayerCatch::updateInfo()
{
	auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
	auto text = handleDataEntity->getVecDataEntityMst().at(_index)->getCfgEntity().name;
	auto txtName = (Text *)_skin->getChildByName("txtName");
	txtName->setString(text);

	auto txtRemain = (Text *)_skin->getChildByName("txtRemain");
	txtRemain->setString(STR_REMAIN + Value(_remain).asString() + STR_COUNT);

	auto txtResult = (Text *)_skin->getChildByName("txtResult");
	txtResult->setString("");
}

void LayerCatch::setBtnVisible(const bool &value)
{
	auto btn = (Button *)_skin->getChildByName("btnScissors");
	btn->setVisible(value);
	btn = (Button *)_skin->getChildByName("btnRock");
	btn->setVisible(value);
	btn = (Button *)_skin->getChildByName("btnPaper");
	btn->setVisible(value);
}