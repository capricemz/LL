#pragma execution_character_set("utf-8")

#include "NodeHead.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "data/define/DefinesRes.h"

using namespace ui;

NodeHead::NodeHead() : _skin(nullptr), _isMst(false), _indexDataEntity(0)
{
}

NodeHead::~NodeHead()
{
	_skin = nullptr;
}

bool NodeHead::init()
{
	auto isInit = false;
	do
	{
		CC_BREAK_IF(!Node::init());
		
		createSkin();
		
		isInit = true;
	} while (0);
	return isInit;
}

void NodeHead::createSkin()
{
	_skin = (Node *)CSLoader::createNode(RES_MODULES_MAIN_NODE_HEAD_CSB);
	addChild(_skin);

	getLayoutBg()->setTouchEnabled(false);
}

void NodeHead::setInfo(const bool &isMst, const int &indexDataEntity)
{
	_isMst = isMst;
	_indexDataEntity = indexDataEntity;
	
	auto size = getLayoutBg()->getContentSize();
	_isMst ? _skin->setPosition(0.0f, -size.height * 0.5f) : _skin->setPosition(0.0f, size.height * 0.5f);
}

void NodeHead::updateAll()
{
	auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
	auto &vecDataEntity = _isMst ? handleDataEntity->getVecDataEntityMst() : handleDataEntity->getVecDataEntityMaid();
	if (vecDataEntity.size() <= _indexDataEntity)
	{
		_skin->setVisible(false);
	}
	else
	{
		_skin->setVisible(true);
		updateSpriteIcon();
		updateBarHp();
		updateSpriteJob();
	}
}

void NodeHead::updateSpriteIcon()
{
	auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
	auto dataEntity = _isMst ? handleDataEntity->getVecDataEntityMst().at(_indexDataEntity) : handleDataEntity->getVecDataEntityMaid().at(_indexDataEntity);
	auto cfgEntity = dataEntity->getCfgEntity();
	auto urlPic = cfgEntity.vecUrlPic[1];
	auto texture = Director::getInstance()->getTextureCache()->getTextureForKey(urlPic);

	auto spriteIcon = (Sprite *)_skin->getChildByName("spriteIcon");
	spriteIcon->setTexture(texture);
}

void NodeHead::updateBarHp()
{
	auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
	auto dataEntity = _isMst ? handleDataEntity->getVecDataEntityMst().at(_indexDataEntity) : handleDataEntity->getVecDataEntityMaid().at(_indexDataEntity);
	auto hp = dataEntity->getAttribute(IdAttribute::ENTITY_HP);
	auto hpMax = dataEntity->getAttribute(IdAttribute::ENTITY_HP_MAX);

	auto bar = (LoadingBar *)_skin->getChildByName("spriteHpBg")->getChildByName("barHp");
	bar->setPercent(((float)hp / (float)hpMax) * 100.0f);
}

void NodeHead::updateSpriteJob()
{
	auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
	auto dataEntity = _isMst ? handleDataEntity->getVecDataEntityMst().at(_indexDataEntity) : handleDataEntity->getVecDataEntityMaid().at(_indexDataEntity);
	auto cfgEntity = dataEntity->getCfgEntity();
	auto urlPic = RES_IMAGES_COMMON_TYPE_JOB_PNG_VEC[(int)cfgEntity.typeJob];
	auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(urlPic);

	auto spriteIcon = (Sprite *)_skin->getChildByName("spriteJob");
	spriteIcon->setSpriteFrame(spriteFrame);
}

void NodeHead::moveFrom(const Vec2 &postion, const bool &isBack, const float &scaleBegan, const float &scaleEnd, const Vec2 & offsetEnd, const function<void()> &func /*= nullptr*/)
{
	setLocalZOrder(1);

	setVisible(true);

	auto postionFrom = convertToNodeSpace(postion);
	_skin->setPosition(postionFrom);

	_skin->setScale(scaleBegan);

	Vector<FiniteTimeAction *> vecActions;

	auto postionDelta = postionFrom - offsetEnd;
	auto postionDeltaNomalized = postionDelta.getNormalized();

	float xMid, xBezier1, yBezier1, xBezier2, yBezier2;
	if (postionDeltaNomalized.x == 0 && postionDeltaNomalized.y == 0)
	{
		xMid = 0.0f;
		xBezier1 = 0.0f;
		yBezier1 = 0.0f;
		xBezier2 = 0.0f;
		yBezier2 = 0.0f;
	}
	else if (postionDeltaNomalized.x == 0)
	{
		xMid = postionDeltaNomalized.x > 0 ? 50.0f : -50.0f;
		xBezier1 = postionDeltaNomalized.y > 0 ? 50.0f : -50.0f;
		yBezier1 = 0.0f;
		xBezier2 = postionDeltaNomalized.y > 0 ? -50.0f : 50.0f;
		yBezier2 = 0.0f;
	}
	else if (postionDeltaNomalized.y == 0)
	{
		xMid = postionDeltaNomalized.x > 0 ? 50.0f : -50.0f;
		xBezier1 = 0.0f;
		yBezier1 = postionDeltaNomalized.x > 0 ? 50.0f : -50.0f;
		xBezier2 = 0.0f;
		yBezier2 = postionDeltaNomalized.x > 0 ? -50.0f : 50.0f;
	}
	else
	{
		xMid = postionDeltaNomalized.x > 0 ? 50.0f : -50.0f;
		auto kNDelta = -postionDeltaNomalized.x / postionDeltaNomalized.y;
		kNDelta *= postionDeltaNomalized.y < 0 ? 1.0f : -1.0f;
		xBezier1 = postionDeltaNomalized.x > 0 ? 50.0f : -50.0f;
		yBezier1 = kNDelta * xBezier1;
		xBezier2 = postionDeltaNomalized.x > 0 ? -50.0f : 50.0f;
		yBezier2 = kNDelta * xBezier2;
	}

	auto postionMid = postionDelta + postionDeltaNomalized * xMid;
	ccBezierConfig cfg;
	cfg.controlPoint_1 = postionDelta + Vec2(xBezier1, yBezier1);
	cfg.controlPoint_2 = postionMid;
	cfg.endPosition = postionMid;
	auto actionToMid = Spawn::createWithTwoActions(BezierTo::create(0.2f, cfg), ScaleTo::create(0.2f, 1.0f));
	vecActions.pushBack(actionToMid);

	ccBezierConfig cfg1;
	cfg1.controlPoint_1 = postionMid + Vec2(xBezier2, yBezier2);
	cfg1.controlPoint_2 = offsetEnd;
	cfg1.endPosition = offsetEnd;
	auto actoinToEnd = Spawn::createWithTwoActions(BezierTo::create(0.3f, cfg1), ScaleTo::create(0.3f, scaleEnd));
	vecActions.pushBack(actoinToEnd);

	auto actionCallFunc = CallFunc::create([func, this]()
	{
		setLocalZOrder(0);
		if (func != nullptr)
		{
			func();
		}
	});
	vecActions.pushBack(actionCallFunc);

	auto actoinSequence = Sequence::create(vecActions);
	_skin->runAction(actoinSequence);
}

NodeHead * NodeHead::clone()
{
	auto nodeHead = create();
	nodeHead->setInfo(_isMst, _indexDataEntity);
	nodeHead->updateAll();
	return nodeHead;
}
