#pragma execution_character_set("utf-8")

#include "LayerMaidSelect.h"
#include "data/define/DefinesRes.h"
#include "data/data/ManagerData.h"
#include "data/define/DefinesString.h"
#include "ui/ManagerUI.h"

LayerMaidSelect::LayerMaidSelect() : _skin(nullptr), _vecNodeHead({}), _postionDelta(Vec2::ZERO)
{
}

LayerMaidSelect::~LayerMaidSelect()
{
	_skin = nullptr;
	_vecNodeHead.clear();
	_postionDelta.setZero();
}

bool LayerMaidSelect::init()
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

void LayerMaidSelect::createSkin()
{
	_skin = (Layer *)CSLoader::createNode(RES_MODULES_MAIN_LAYER_MAID_SELECT_CSB);
	addChild(_skin);

	auto layoutBg = (Layout *)_skin->getChildByName("layoutBg");
	layoutBg->addTouchEventListener(CC_CALLBACK_2(LayerMaidSelect::ontTouchLayoutBg, this));

	auto layoutContent = (Layout *)_skin->getChildByName("layoutContent");
	layoutContent->setVisible(false);
	//
	auto handleDataLevels = ManagerData::getInstance()->getHandleDataLevels();
	auto dataLevel = handleDataLevels->getDataLevelCurrent();
	auto cfgLevel = dataLevel->getCfgLevel();

	auto txtLevel = (Text *)layoutContent->getChildByName("txtLevel");
	txtLevel->setString(STR_LEVEL_0 + Value(dataLevel->getIndex() + 1).asString() + STR_LEVEL_1);

	auto txtName = (Text *)layoutContent->getChildByName("txtName");
	txtName->setString(cfgLevel.name);

	auto levelTargetNum = dataLevel->levelTargetNumGet();
	auto layoutStar = (Layout *)layoutContent->getChildByName("layoutStar");
	auto sizeLayoutStar = layoutStar->getContentSize();
	auto postion = Vec2(5.0f, sizeLayoutStar.height - 5.0f);
	for (auto i = 0; i < levelTargetNum; i++)
	{
		auto isComolete = dataLevel->levelTargetIsComplete(i);
		auto text = dataLevel->getLevelTargetStr(i);
		auto txtStar = Text::create(text, RES_FONTS_KTJT, 18);
		txtStar->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
		txtStar->setName("txtStar" + Value(i).asInt());
		txtStar->setPosition(postion);
		layoutStar->addChild(txtStar);
		postion += Vec2(0.0f, -(txtStar->getContentSize().height + 5.0f));
	}

	auto btn = (Button *)layoutContent->getChildByName("btnEnter");
	btn->addTouchEventListener(CC_CALLBACK_2(LayerMaidSelect::onTouchBtnEnter, this));
	//
	auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
	auto vecDataEntityMaid = handleDataEntity->getVecDataEntityMaid();

	auto layoutNodeHead = (Layout *)layoutContent->getChildByName("layoutNodeHead");
	auto index = 0;
	while (true)
	{
		auto sprite = (Sprite *)layoutNodeHead->getChildByName("sprite" + Value(index).asString());
		if (sprite == nullptr)
		{
			break;
		}
		sprite->setVisible(false);

		if ((int)vecDataEntityMaid.size() > index)
		{
			auto nodeHead = NodeHead::create();
			nodeHead->setScale(0.8f);
			nodeHead->setInfo(false, index);
			nodeHead->setPosition(sprite->getPosition());
			nodeHead->getLayoutBg()->setTouchEnabled(true);
			nodeHead->getLayoutBg()->addTouchEventListener(CC_CALLBACK_2(LayerMaidSelect::onTouchNodeHead, this, nodeHead));
			layoutNodeHead->addChild(nodeHead);
			_vecNodeHead.pushBack(nodeHead);
		}

		index++;
	}
}

void LayerMaidSelect::ontTouchLayoutBg(Ref *ref, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		runDisappear(nullptr);
	}
}

void LayerMaidSelect::onTouchBtnEnter(Ref *ref, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		ManagerUI::getInstance()->notify(ID_OBSERVER::SCENE_MAIN, TYPE_OBSERVER_SCENE_MAIN::SHOW_BATTLE);
	}
}

void LayerMaidSelect::onTouchNodeHead(Ref *ref, Widget::TouchEventType type, NodeHead *nodeHead)
{
	auto layoutBg = (Layout *)ref;
	if (type == Widget::TouchEventType::BEGAN)
	{
		_postionDelta = layoutBg->getTouchBeganPosition() - layoutBg->getWorldPosition();
		nodeHead->setLocalZOrder(1);
	}
	else if (type == Widget::TouchEventType::MOVED)
	{
		auto postionMove = layoutBg->getTouchMovePosition();
		auto postion = postionMove - _postionDelta;
		postion.y -= nodeHead->getLayoutBg()->getContentSize().height * 0.8f * 0.5f;
		postion = nodeHead->getParent()->convertToNodeSpace(postion);
		nodeHead->setPosition(postion);
	}
	else
	{
		nodeHead->setLocalZOrder(0);
		
		auto postionBegan = layoutBg->getTouchBeganPosition();
		auto postion = postionBegan - _postionDelta;
		postion.y -= nodeHead->getLayoutBg()->getContentSize().height * 0.8f * 0.5f;
		postion = nodeHead->getParent()->convertToNodeSpace(postion);
		nodeHead->setPosition(postion);
		
		auto indexDataEntityMoveOver = -1;
		auto postionEnd = layoutBg->getTouchEndPosition();
		auto isMoveOver = isMoveOverNodeHead(postionEnd, indexDataEntityMoveOver);
		auto indexDataEntity = nodeHead->getIndexDataEntity();

		if (isMoveOver && indexDataEntityMoveOver != indexDataEntity)//若划入其他NodeHead
		{
			auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
			handleDataEntity->swapVecDataEntityMaid(indexDataEntity, indexDataEntityMoveOver);
			auto nodeHeadMoveOver = _vecNodeHead.at(indexDataEntityMoveOver);
			nodeHeadMoveOver->updateAll();

			nodeHead->updateAll();
		}
	}
}

bool LayerMaidSelect::isMoveOverNodeHead(const Vec2 &postionTouchMove, int &indexDataEntityMoveOver)
{
	for (auto var : _vecNodeHead)
	{
		auto layoutBg = var->getLayoutBg();
		auto rect = layoutBg->getBoundingBox();
		auto postionIn = var->convertToNodeSpace(postionTouchMove);
		auto isMoverOver = rect.containsPoint(postionIn);
		if (isMoverOver)
		{
			indexDataEntityMoveOver = var->getIndexDataEntity();
			return true;
		}
	}
	return false;
}

void LayerMaidSelect::runAppear(const function<void()> &funcOver)
{
	auto duration = 0.4f;
	auto layoutContent = (Layout *)_skin->getChildByName("layoutContent");
	layoutContent->setVisible(true);
	layoutContent->stopActionsByFlags(1);

	auto postion = layoutContent->getPosition();
	layoutContent->setPosition(Vec2::ZERO);

	Vector<FiniteTimeAction *> vecActions;

	auto actionMove = EaseBackOut::create(MoveTo::create(duration, postion));
	actionMove->setFlags(1);
	vecActions.pushBack(actionMove);

	if (funcOver != nullptr)
	{
		auto actionCallFunc = CallFunc::create([funcOver]()
		{
			funcOver();
		});
		actionCallFunc->setFlags(1);
		vecActions.pushBack(actionCallFunc);
	}

	layoutContent->runAction(Sequence::create(vecActions));
}

void LayerMaidSelect::runDisappear(const function<void()> &funcOver)
{
	auto duration = 0.4f;
	auto layoutContent = (Layout *)_skin->getChildByName("layoutContent");
	layoutContent->stopActionsByFlags(1);

	Vector<FiniteTimeAction *> vecActions;

	auto actionMove = EaseBackIn::create(MoveTo::create(duration, Vec2::ZERO));
	actionMove->setFlags(1);
	vecActions.pushBack(actionMove);

	auto actionCallFunc = CallFunc::create([this]()
	{
		removeFromParent();
	});
	actionCallFunc->setFlags(1);
	vecActions.pushBack(actionCallFunc);

	if (funcOver != nullptr)
	{
		auto actionCallFunc = CallFunc::create([funcOver]()
		{
			funcOver();
		});
		actionCallFunc->setFlags(1);
		vecActions.pushBack(actionCallFunc);
	}

	layoutContent->runAction(Sequence::create(vecActions));
}
