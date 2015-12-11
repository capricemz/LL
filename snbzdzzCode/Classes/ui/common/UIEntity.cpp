#pragma execution_character_set("utf-8")

#include "UIEntity.h"
#include "data/config/ManagerCfg.h"
#include "data/data/ManagerData.h"

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

void UIEntity::updateSkin(const int &idEntity, const float &scale)
{
	auto handleDataUnlock = ManagerData::getInstance()->getHandleDataUnlock();
	auto isBuy = handleDataUnlock->getIsBuyMaid(idEntity);
	auto isUnlock = handleDataUnlock->getIsUnlockMaid(idEntity);

	auto cfgEntity = ManagerCfg::getInstance()->getDicCfgEntity()[idEntity];

	auto urlPic = cfgEntity.urlPicEntity;
	if (_skin == nullptr)
	{
		_skin = Sprite::create(urlPic);
		_skin->setScale(scale);
		addChild(_skin);
	}
	else
	{
		auto texture = Director::getInstance()->getTextureCache()->getTextureForKey(urlPic);
		/*_skin->setContentSize(texture->getContentSize());*/
		_skin->setTexture(texture);
	}
	/*isUnlock = true;//for test
	isBuy = false;//for test*/
	_skin->setColor(isUnlock && !isBuy ? Color3B::BLACK : Color3B::WHITE);

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
