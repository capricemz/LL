#pragma execution_character_set("utf-8")

#include "LayerMaidSelect.h"
#include "data/define/DefinesRes.h"
#include "data/data/ManagerData.h"
#include "data/define/DefinesString.h"
#include "ui/ManagerUI.h"
#include "data/config/ManagerCfg.h"
#include "common/util/UtilString.h"

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

		createData();

		createSkin();

		isInit = true;
	} while (0);
	return isInit;
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

void LayerMaidSelect::createData()
{
	auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
	handleDataEntity->createDataEntityMst();
}

void LayerMaidSelect::createSkin()
{
	_skin = (Layer *)CSLoader::createNode(RES_MODULES_MAIN_LAYER_MAID_SELECT_CSB);
	addChild(_skin);

	auto layoutBg = (Layout *)_skin->getChildByName("layoutBg");
	layoutBg->addTouchEventListener(CC_CALLBACK_2(LayerMaidSelect::ontTouchBack, this));

	auto layoutContent = (Layout *)_skin->getChildByName("layoutContent");
	layoutContent->setVisible(false);
	//
	auto handleDataLevels = ManagerData::getInstance()->getHandleDataLevels();
	auto dataLevel = handleDataLevels->getDataLevelCurrent();
	auto cfgLevel = dataLevel->getCfgLevel();

	auto levelTargetNum = dataLevel->levelTargetNumGet();
	auto layoutStar = (Layout *)layoutContent->getChildByName("layoutStar");
	auto sizeLayoutStar = layoutStar->getContentSize();
	auto postion = Vec2(0.0f, sizeLayoutStar.height);
	for (auto i = 0; i < levelTargetNum; i++)
	{
		auto node = (Node *)CSLoader::createNode(RES_MODULES_MAIN_NODE_MAID_SELECT_STAR_CSB);
		if (postion.x == 0.0f)
		{
			postion.x = (sizeLayoutStar.width - node->getChildByName("spriteBg")->getContentSize().width) * 0.5f;
		}
		
		node->setPosition(postion);

		auto text = dataLevel->getLevelTargetStr(i);
		auto txt = (Text *)node->getChildByName("txt");
		txt->setString(text);

		auto isComolete = dataLevel->levelTargetIsComplete(i);
		auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(isComolete ? RES_IMAGES_MAIN_LEVELS_XING_PNG : RES_IMAGES_MAIN_LEVELS_XING_KONG_PNG);
		auto spriteStar = (Sprite *)node->getChildByName("spriteStar");
		spriteStar->setSpriteFrame(spriteFrame);

		layoutStar->addChild(node);
		postion += Vec2(0.0f, -(node->getChildByName("spriteBg")->getContentSize().height));
	}

	auto btn = (Button *)layoutContent->getChildByName("btnEnter");
	btn->addTouchEventListener(CC_CALLBACK_2(LayerMaidSelect::onTouchBtnEnter, this));

	btn = (Button *)layoutContent->getChildByName("btnBack");
	btn->addTouchEventListener(CC_CALLBACK_2(LayerMaidSelect::ontTouchBack, this));
	//
	auto vecIdDataEntityMst = UtilString::split(cfgLevel.msts, ":");

	auto layoutNodeHead = (Layout *)layoutContent->getChildByName("layoutNodeHead");
	auto index = 0;
	while (true)
	{
		auto layout = (Layout *)layoutNodeHead->getChildByName("layoutHeadMst" + Value(index).asString());
		if (layout == nullptr)
		{
			break;
		}

		if ((int)vecIdDataEntityMst.size() > index)
		{
			auto nodeHead = NodeHead::create();
			nodeHead->updateSkin(false, true, index);
			nodeHead->setPosition(layout->getPosition());
			/*nodeHead->getLayoutBg()->setTouchEnabled(true);
			nodeHead->getLayoutBg()->addTouchEventListener(CC_CALLBACK_2(LayerMaidSelect::onTouchNodeHead, this, nodeHead));*/
			layoutNodeHead->addChild(nodeHead);
			_vecNodeHead.pushBack(nodeHead);
		}

		index++;
	}

	auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
	auto vecDataEntityMaid = handleDataEntity->getVecDataEntityMaid();
	index = 0;
	while (true)
	{
		auto layout = (Layout *)layoutNodeHead->getChildByName("layoutHeadMaid" + Value(index).asString());
		if (layout == nullptr)
		{
			break;
		}

		if ((int)vecDataEntityMaid.size() > index)
		{
			auto nodeHead = NodeHead::create();
			nodeHead->updateSkin(false, false, index);
			nodeHead->setPosition(layout->getPosition());
			nodeHead->getLayoutBg()->setTouchEnabled(true);
			nodeHead->getLayoutBg()->addTouchEventListener(CC_CALLBACK_2(LayerMaidSelect::onTouchNodeHead, this, nodeHead));
			layoutNodeHead->addChild(nodeHead);
			_vecNodeHead.pushBack(nodeHead);
		}

		index++;
	}
}

void LayerMaidSelect::ontTouchBack(Ref *ref, Widget::TouchEventType type)
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
		postion = nodeHead->getParent()->convertToNodeSpace(postion);
		nodeHead->setPosition(postion);
	}
	else
	{
		nodeHead->setLocalZOrder(0);
		
		auto postionBegan = layoutBg->getTouchBeganPosition();
		auto postion = postionBegan - _postionDelta;
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
