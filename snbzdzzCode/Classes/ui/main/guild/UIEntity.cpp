#pragma execution_character_set("utf-8")

#include "UIEntity.h"
#include "data/config/ManagerCfg.h"

UIEntity::UIEntity() : _idEntity(0), _skin(nullptr), _layoutBg(nullptr)
{
}

UIEntity::~UIEntity()
{
	_skin = nullptr;
	_layoutBg = nullptr;
}

bool UIEntity::init()
{
	auto isInit = false;
	do
	{
		CC_BREAK_IF(!Node::init());

		isInit = true;
	} while (0);
	return isInit;
}

void UIEntity::updateSkin(const int &idEntity)
{
	auto cfgEntity = ManagerCfg::getInstance()->getDicCfgEntity()[idEntity];

	auto urlPic = cfgEntity.vecUrlPic[0];
	if (_skin == nullptr)
	{
		_skin = Sprite::create(urlPic);
		_skin->setScale(0.15f);
		addChild(_skin);
	}
	else
	{
		auto texture = Director::getInstance()->getTextureCache()->getTextureForKey(urlPic);
		_skin->setTexture(texture);
	}

	if (_layoutBg == nullptr)
	{
		_layoutBg = Layout::create();
		_layoutBg->setBackGroundColorType(Layout::BackGroundColorType::NONE);
		_layoutBg->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		_layoutBg->setTouchEnabled(true);
		addChild(_layoutBg);
	}
	_layoutBg->setContentSize(_skin->getContentSize() * _skin->getScale());
}
