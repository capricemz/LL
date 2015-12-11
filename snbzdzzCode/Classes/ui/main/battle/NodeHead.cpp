#pragma execution_character_set("utf-8")

#include "NodeHead.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "data/define/DefinesRes.h"

using namespace ui;

NodeHead::NodeHead() : _skin(nullptr), _layout(nullptr), _isLarge(false), _isMst(false), _indexDataEntity(0)
{
}

NodeHead::~NodeHead()
{
	_skin = nullptr;
	_layout = nullptr;
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
}

void NodeHead::updateSkin(const bool &isLarge, const bool &isMst, const int &indexDataEntity)
{
	_isLarge = isLarge;
	_isMst = isMst;
	_indexDataEntity = indexDataEntity;
	
	/*auto size = getLayoutBg()->getContentSize();
	_isMst ? _skin->setPosition(0.0f, -size.height * 0.5f) : _skin->setPosition(0.0f, size.height * 0.5f);*/
	auto layoutLarge = (Layout *)_skin->getChildByName("layoutLarge");
	layoutLarge->setVisible(_isLarge);
	auto layoutSmall = (Layout *)_skin->getChildByName("layoutSmall");
	layoutSmall->setVisible(!_isLarge);
	_layout = _isLarge ? layoutLarge : layoutSmall;
	_layout->setTouchEnabled(false);
	_layout->setAnchorPoint(_isMst ? Vec2::ANCHOR_MIDDLE_TOP : Vec2::ANCHOR_MIDDLE_BOTTOM);
	
	updateAll();
}

void NodeHead::updateAll()
{
	updateSpriteIcon();
	updateBarHp();
	updateSpriteJob();
}

void NodeHead::updateSpriteIcon()
{
	auto dataEntity = getDataEntity();
	auto cfgEntity = dataEntity->getCfgEntity();
	auto urlPic = _isLarge ? cfgEntity.urlPicHeadLarge : cfgEntity.urlPicHeadSmall;
	/*auto texture = Director::getInstance()->getTextureCache()->getTextureForKey(urlPic);*/
	auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(urlPic);

	auto spriteIcon = (Sprite *)_layout->getChildByName("spriteIcon");
	/*spriteIcon->setTexture(texture);*/
	spriteIcon->setSpriteFrame(spriteFrame);
}

void NodeHead::updateBarHp()
{
	if (!_isLarge)
	{
		return;
	}
	auto dataEntity = getDataEntity();
	auto hp = dataEntity->getAttribute(IdAttribute::ENTITY_HP);
	auto hpMax = dataEntity->getAttribute(IdAttribute::ENTITY_HP_MAX);

	auto bar = (LoadingBar *)_layout->getChildByName("spriteHpBg")->getChildByName("barHp");
	bar->setPercent(((float)hp / (float)hpMax) * 100.0f);
}

void NodeHead::updateSpriteJob()
{
	auto dataEntity = getDataEntity();
	auto cfgEntity = dataEntity->getCfgEntity();
	auto urlPic = RES_IMAGES_COMMON_TYPE_JOB_PNG_VEC[(int)cfgEntity.typeJob];
	auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(urlPic);

	auto spriteIcon = (Sprite *)_layout->getChildByName("spriteJob");
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
	nodeHead->updateSkin(true, _isMst, _indexDataEntity);
	return nodeHead;
}

DataEntity * NodeHead::getDataEntity()
{
	auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
	auto dataEntity = _isMst ? handleDataEntity->getVecDataEntityMst().at(_indexDataEntity) : handleDataEntity->getVecDataEntityMaid().at(_indexDataEntity);
	return dataEntity;
}
