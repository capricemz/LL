#pragma execution_character_set("utf-8")

#include "NodeHead.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "data/define/DefinesRes.h"
#include "data/config/ManagerCfg.h"
#include "ui/ManagerUI.h"
#include "data/define/DefinesString.h"

using namespace ui;

NodeHead::NodeHead() :
	_skin(nullptr),
	_layout(nullptr),
	_type(TypeNodeHead::NONE),
	_isMst(false),
	_idEntity(0)
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

void NodeHead::updateSkin(const TypeNodeHead &type, const bool &isMst, const int &idEntity)
{
	_type = type;
	_isMst = isMst;
	_idEntity = idEntity;
	
	auto layoutLarge = (Layout *)_skin->getChildByName("layoutLarge");
	layoutLarge->setVisible(_type == TypeNodeHead::LARGE);
	auto layoutMiddle = (Layout *)_skin->getChildByName("layoutMiddle");
	layoutMiddle->setVisible(_type == TypeNodeHead::MIDDLE);
	auto layoutSmall = (Layout *)_skin->getChildByName("layoutSmall");
	layoutSmall->setVisible(_type == TypeNodeHead::SMALL);
	_layout = _type == TypeNodeHead::LARGE ? layoutLarge : (_type == TypeNodeHead::MIDDLE ? layoutMiddle : layoutSmall);
	_layout->setTouchEnabled(false);
	_layout->setAnchorPoint(_isMst ? Vec2::ANCHOR_MIDDLE_TOP : Vec2::ANCHOR_MIDDLE_BOTTOM);
	
	updateAll();
}

void NodeHead::updateAll()
{
	updateSpriteIcon();
	updateBarHp();
	updateTxtHp();
	updateSpriteJob();
	updateSpriteState();
	updateTxtGrade();
}

void NodeHead::updateSpriteIcon()
{
	auto cfgEntity = ManagerCfg::getInstance()->getDicCfgEntity().at(_idEntity);

	auto urlPic = _type == TypeNodeHead::LARGE ? cfgEntity.urlPicHeadLarge : (_type == TypeNodeHead::MIDDLE ? cfgEntity.urlPicHeadMiddle : cfgEntity.urlPicHeadSmall);
	auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(urlPic);

	auto spriteIcon = (Sprite *)_layout->getChildByName("spriteIcon");
	spriteIcon->setSpriteFrame(spriteFrame);
}

void NodeHead::updateBarHp()
{
	if (_type != TypeNodeHead::LARGE)
	{
		return;
	}
	auto dataEntity = getDataEntity();
	if (dataEntity == nullptr)
	{
		return;
	}
	auto hp = dataEntity->getAttribute(IdAttribute::ENTITY_HP);
	auto hpMax = dataEntity->getAttribute(IdAttribute::ENTITY_HP_MAX);

	auto bar = (LoadingBar *)_layout->getChildByName("spriteHpBg")->getChildByName("barHp");
	bar->setPercent(((float)hp / (float)hpMax) * 100.0f);
}

void NodeHead::updateTxtHp()
{
	if (_type != TypeNodeHead::LARGE)
	{
		return;
	}
	auto dataEntity = getDataEntity();
	if (dataEntity == nullptr)
	{
		return;
	}
	auto hp = dataEntity->getAttribute(IdAttribute::ENTITY_HP);
	auto hpMax = dataEntity->getAttribute(IdAttribute::ENTITY_HP_MAX);

	auto txtHp0 = (Text *)_layout->getChildByName("txtHp0");
	txtHp0->setString(Value(hp).asString());
	auto txtHp1 = (Text *)_layout->getChildByName("txtHp1");
	txtHp1->setString(Value(hpMax).asString());
}

void NodeHead::updateSpriteJob()
{
	if (_type != TypeNodeHead::LARGE && _type != TypeNodeHead::SMALL)
	{
		return;
	}
	auto cfgEntity = ManagerCfg::getInstance()->getDicCfgEntity().at(_idEntity);
	auto urlPic = RES_IMAGES_COMMON_TYPE_JOB_PNG_VEC[(int)cfgEntity.typeJob];
	auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(urlPic);

	auto spriteIcon = (Sprite *)_layout->getChildByName("spriteJob");
	spriteIcon->setSpriteFrame(spriteFrame);
}

void NodeHead::updateSpriteState()
{
	if (_type != TypeNodeHead::MIDDLE)
	{
		return;
	}

	auto handleDataUnlock = ManagerData::getInstance()->getHandleDataUnlock();
	auto isUnlock = handleDataUnlock->getIsUnlockMaid(_idEntity);
	auto isBuy = handleDataUnlock->getIsBuyMaid(_idEntity);

	auto spriteState = (Sprite *)_layout->getChildByName("spriteState");
	auto name = !isUnlock ? RES_IMAGES_MAIN_MAID_UNLOCK_PNG : (!isBuy ? RES_IMAGES_MAIN_MAID_BUY_PNG : "");
	if (name != "")
	{
		auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
		spriteState->setSpriteFrame(spriteFrame);
	}
	else
	{
		spriteState->setVisible(false);
	}

	if (!isUnlock)
	{
		GLProgramState *glState = GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_GRAYSCALE);
		auto spriteIcon = (Sprite *)_layout->getChildByName("spriteIcon");
		spriteIcon->setGLProgramState(glState);
	}

	_layout->setTouchEnabled(isUnlock);
}

void NodeHead::updateTxtGrade()
{
	auto layoutGrade = (Layout *)_layout->getChildByName("layoutGrade");
	if (layoutGrade == nullptr)
	{
		return;
	}

	if (_type != TypeNodeHead::SMALL)
	{
		layoutGrade->setVisible(false);
		return;
	}

	auto handleDataGrade = ManagerData::getInstance()->getHandleDataGrade();
	auto isGradeUp = handleDataGrade->getIsGradeUp();

	if (!isGradeUp)
	{
		layoutGrade->setVisible(false);
		return;
	}

	auto idGradeLast = handleDataGrade->getIdGradeLast();
	if (idGradeLast == 0)
	{
		layoutGrade->setVisible(false);
		return;
	}
	auto cfgGrade = ManagerCfg::getInstance()->getDicCfgGrade()[idGradeLast];
	auto vecEffect = UtilString::split(cfgGrade.effect, "|");
	for (auto var : vecEffect)
	{
		auto vecInfo = UtilString::split(var, ":");
		auto idEntity = Value(vecInfo[0]).asInt();
		auto idAttribute = Value(vecInfo[1]).asInt();
		auto value = Value(vecInfo[2]).asInt();
		if (idEntity == _idEntity)
		{
			auto txtHpLast = (Text *)layoutGrade->getChildByName("txtHpLast");
			txtHpLast->setString(Value(value).asString());
			break;
		}
	}
	
	auto effect = handleDataGrade->getGradeEffect();
	vecEffect = UtilString::split(effect, "|");
	for (auto var : vecEffect)
	{
		auto vecInfo = UtilString::split(var, ":");
		auto idEntity = Value(vecInfo[0]).asInt();
		auto idAttribute = Value(vecInfo[1]).asInt();
		auto value = Value(vecInfo[2]).asInt();
		if (idEntity == _idEntity)
		{
			auto txtHpNow = (Text *)layoutGrade->getChildByName("txtHpNow");
			txtHpNow->setString(Value(value).asString());
			break;
		}
	}
}

void NodeHead::showWordsDrift(const int &valueChange, const IdAttribute &idAttributeBeChange, const Color4B &color, const float &duration)
{
	if (_type != TypeNodeHead::LARGE)
	{
		return;
	}
	auto dataEntity = getDataEntity();
	if (dataEntity == nullptr)
	{
		return;
	}
	if (valueChange == 0)
	{
		return;
	}
	auto words = Value(valueChange).asString();
	if (idAttributeBeChange == IdAttribute::ENTITY_HP)
	{
		words = STR_HP + words;
	}
	else if (idAttributeBeChange == IdAttribute::ENTITY_ENERGY)
	{
		words = STR_EP + words;
	}
	auto managerUI = ManagerUI::getInstance();
	auto halfHeight = _skin->getContentSize().height * 0.5f;
	managerUI->showWordsDrift(this, _skin->getPosition(), words, color, duration);
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
	nodeHead->updateSkin(_type, _isMst, _idEntity);
	return nodeHead;
}

int NodeHead::getIndexDataEntity() const
{
	auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
	auto vecDataEntity = _isMst ? handleDataEntity->getVecDataEntityMst() : handleDataEntity->getVecDataEntityMaid();
	auto length = (int)vecDataEntity.size();
	for (auto i = 0; i < length; i++)
	{
		if (vecDataEntity.at(i)->getIdEntity() == _idEntity)
		{
			return i;
		}
	}
	return 0;
}

DataEntity * NodeHead::getDataEntity()
{
	auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
	auto vecDataEntity = _isMst ? handleDataEntity->getVecDataEntityMst() : handleDataEntity->getVecDataEntityMaid();
	for (auto var : vecDataEntity)
	{
		if (var->getIdEntity() == _idEntity)
		{
			return var;
		}
	}
	return nullptr;
}
