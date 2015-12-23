#pragma execution_character_set("utf-8")

#include "LayerGradeUp.h"
#include "data/define/DefinesRes.h"
#include "data/data/ManagerData.h"
#include "ui/ManagerUI.h"
#include "../NodeHead.h"

LayerGradeUp::LayerGradeUp() : _skin(nullptr)
{
}

LayerGradeUp::~LayerGradeUp()
{
	_skin = nullptr;
}

bool LayerGradeUp::init()
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

void LayerGradeUp::runAppearAction(const function<void()> &func /*= nullptr*/)
{
	_isAppearing = true;

	auto txtContinue = (Text *)_skin->getChildByName("txtContinue");
	txtContinue->setVisible(false);

	Vector<FiniteTimeAction *> vecAction;

	auto spriteGradeUpBg = (Sprite *)_skin->getChildByName("spriteGradeUpBg");
	auto spriteGradeUp = (Sprite *)_skin->getChildByName("spriteGradeUp");
	auto duration = 10.0f / 60.0f;
	auto actionCallFunc = CallFunc::create([spriteGradeUpBg, duration]()
	{
		spriteGradeUpBg->runAction(FadeIn::create(duration));
	});
	vecAction.pushBack(actionCallFunc);
	auto actionDelay = DelayTime::create(duration + 1.0f / 60.0f);
	vecAction.pushBack(actionDelay);

	duration = 10.0f / 60.0f;
	actionCallFunc = CallFunc::create([spriteGradeUp, duration]()
	{
		spriteGradeUp->runAction(FadeIn::create(duration));
	});
	vecAction.pushBack(actionCallFunc);
	actionDelay = DelayTime::create(duration + 1.0f / 60.0f);
	vecAction.pushBack(actionDelay);

	duration = 10.0f / 60.0f;
	actionCallFunc = CallFunc::create([spriteGradeUpBg, spriteGradeUp, duration]()
	{
		spriteGradeUpBg->runAction(MoveBy::create(duration, moveDistanceGradeUp));
		spriteGradeUp->runAction(MoveBy::create(duration, moveDistanceGradeUp));
	});
	vecAction.pushBack(actionCallFunc);
	actionDelay = DelayTime::create(duration + 1.0f / 60.0f);
	vecAction.pushBack(actionDelay);

	auto layoutInfoGrade = (Layout *)_skin->getChildByName("layoutInfoGrade");
	duration = 10.0f / 60.0f;
	actionCallFunc = CallFunc::create([layoutInfoGrade, duration]()
	{
		layoutInfoGrade->runAction(FadeIn::create(duration));
	});
	vecAction.pushBack(actionCallFunc);
	actionDelay = DelayTime::create(duration + 1.0f / 60.0f);
	vecAction.pushBack(actionDelay);

	auto layoutNodeHead = (Layout *)_skin->getChildByName("layoutNodeHead");
	
	for (auto node : layoutNodeHead->getChildren())
	{
		if (node->isVisible())
		{
			duration = 10.0f / 60.0f;
			actionCallFunc = CallFunc::create([node, duration]()
			{
				((NodeHead *)node)->getLayoutBg()->runAction(FadeIn::create(duration));
			});
			vecAction.pushBack(actionCallFunc);
			actionDelay = DelayTime::create(duration + 1.0f / 60.0f);
			vecAction.pushBack(actionDelay);
		}
	}

	auto layoutInfoMaid = (Layout *)_skin->getChildByName("layoutInfoMaid");
	duration = 10.0f / 60.0f;
	actionCallFunc = CallFunc::create([layoutInfoMaid, duration]()
	{
		layoutInfoMaid->runAction(FadeIn::create(duration));
	});
	vecAction.pushBack(actionCallFunc);
	actionDelay = DelayTime::create(duration + 1.0f / 60.0f);
	vecAction.pushBack(actionDelay);

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

void LayerGradeUp::createSkin()
{
	_skin = (Layer *)CSLoader::createNode(RES_MODULES_MAIN_LAYER_GRADE_UP_CSB);
	addChild(_skin);

	auto layout = (Layout *)_skin->getChildByName("layoutBg");
	layout->addTouchEventListener(CC_CALLBACK_2(LayerGradeUp::onTouchContinue, this));

	updateSpriteGradeUp();
	updateLayoutInfoGrade();
	updateNodeHead();
	updateLayoutInfoMaid();

	auto txtContinue = (Text *)_skin->getChildByName("txtContinue");
	txtContinue->runAction(RepeatForever::create(Sequence::create(FadeOut::create(1.0f), FadeIn::create(1.0f), nullptr)));
}

void LayerGradeUp::updateSpriteGradeUp()
{
	auto spriteGradeUpBg = (Sprite *)_skin->getChildByName("spriteGradeUpBg");
	spriteGradeUpBg->setPosition(spriteGradeUpBg->getPosition() - moveDistanceGradeUp);
	spriteGradeUpBg->setOpacity(0.0f);

	auto spriteGradeUp = (Sprite *)_skin->getChildByName("spriteGradeUp");
	spriteGradeUp->setPosition(spriteGradeUp->getPosition() - moveDistanceGradeUp);
	spriteGradeUp->setOpacity(0.0f);
}

void LayerGradeUp::updateLayoutInfoGrade()
{
	auto handleDataGrade = ManagerData::getInstance()->getHandleDataGrade();
	auto cfgGrade = handleDataGrade->getCfgGradeLast();
	auto gradeLast = cfgGrade.index;
	auto gradeNow = handleDataGrade->getGrade();

	auto layoutInfoGrade = (Layout *)_skin->getChildByName("layoutInfoGrade");
	layoutInfoGrade->setOpacity(0.0f);

	auto txtGradeLast = (Text *)layoutInfoGrade->getChildByName("txtGradeLast");
	txtGradeLast->setString(Value(gradeLast).asString());

	auto txtGradeNow = (Text *)layoutInfoGrade->getChildByName("txtGradeNow");
	txtGradeNow->setString(Value(gradeNow).asString());
}

void LayerGradeUp::updateNodeHead()
{
	auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
	auto vecDataEntity = handleDataEntity->getVecDataEntityMaid();
	auto length = (int)vecDataEntity.size();

	auto layoutNodeHead = (Layout *)_skin->getChildByName("layoutNodeHead");

	auto index = 0;
	while (true)
	{
		auto spriteIcon = (Sprite *)layoutNodeHead->getChildByName("spriteIcon" + Value(index).asString());
		if (spriteIcon == nullptr)
		{
			break;
		}
		spriteIcon->setVisible(false);
		if (index < length)
		{
			auto postion = spriteIcon->getPosition();
			auto sizeSprite = spriteIcon->getContentSize();
			auto dataEntity = vecDataEntity.at(index);
			auto idEntity = dataEntity->getIdEntity();

			auto nodeHead = NodeHead::create();
			nodeHead->updateSkin(TypeNodeHead::SMALL, false, idEntity);
			nodeHead->updateTxtGrade();
			nodeHead->setPosition(postion);
			auto size = nodeHead->getLayoutBg()->getContentSize();
			auto scale = size.width > size.height ? sizeSprite.width / size.width : sizeSprite.height / size.height;
			nodeHead->setScale(scale);
			layoutNodeHead->addChild(nodeHead);
			nodeHead->getLayoutBg()->setOpacity(0.0f);
		}
		index++;
	}
}

void LayerGradeUp::updateLayoutInfoMaid()
{
	auto layoutInfoMaid = (Layout *)_skin->getChildByName("layoutInfoMaid");
	layoutInfoMaid->setOpacity(0.0f);
}

void LayerGradeUp::onTouchContinue(Ref *ref, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		if (_isAppearing)
		{
			return;
		}
		ManagerUI::getInstance()->notify(ID_OBSERVER::SCENE_MAIN, TYPE_OBSERVER_SCENE_MAIN::SWITCH_LAYER, TYPE_OBSERVER_SCENE_MAIN::SHOW_LEVELS);
		auto handleDataGrade = ManagerData::getInstance()->getHandleDataGrade();
		handleDataGrade->setIdGradeLast();
	}
}
