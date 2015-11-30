#pragma execution_character_set("utf-8")

#include "Scenery.h"
#include "data/data/ManagerData.h"
#include "ui/common/SpriteBlur.h"

Scenery::Scenery() : _skin(nullptr), _skinBlur(nullptr)
{
}

Scenery::~Scenery()
{
	_skin = nullptr;
	_skinBlur = nullptr;
}

bool Scenery::init()
{
	auto isInit = false;
	do
	{
		CC_BREAK_IF(!Node::init());

		isInit = true;
	} while (0);
	return isInit;
}

void Scenery::updateSkin(const bool &isMst)
{
	_isMst = isMst;

	auto dataLevel = ManagerData::getInstance()->getHandleDataLevels()->getDataLevelCurrent();
	auto urlPic = dataLevel->getCfgLevel().vecUrlPic[_isMst ? 0 : 1];
	if (_skin == nullptr)
	{
		_skin = Sprite::create(urlPic);
		auto size = _skin->getContentSize();
		_skin->setPosition(size.width * 0.5f, size.height * 0.5f);
		addChild(_skin);
	}
	else
	{
		auto texture = Director::getInstance()->getTextureCache()->getTextureForKey(urlPic);
		_skin->setTexture(texture);
	}
}

void Scenery::runEffect()
{
	auto postion = _skin->getPosition();
	auto dataLevel = ManagerData::getInstance()->getHandleDataLevels()->getDataLevelCurrent();
	auto urlPic = dataLevel->getCfgLevel().vecUrlPic[_isMst ? 0 : 1];
	_skinBlur = (SpriteBlur *)SpriteBlur::create(urlPic.c_str());
	_skinBlur->setBlurSampleNum(1.0f);
	_skinBlur->setBlurRadius(10.0f);
	_skinBlur->setPosition(postion);
	addChild(_skinBlur);
	//
	/*auto widthSpriteBlur = _skinBlur->getContentSize().width;
	auto duration = 1.0f;
	auto actionMoveBy = MoveBy::create(duration, Vec2(_isMst ? -widthSpriteBlur : widthSpriteBlur, 0.0f));
	auto actionCallFunc = CallFunc::create([this]()
	{
		_skinBlur->removeFromParent();
	});
	_skinBlur->runAction(Sequence::createWithTwoActions(actionMoveBy, actionCallFunc));*/
}

void Scenery::stopEffect()
{
	if (_skinBlur != nullptr && _skinBlur->getParent() != nullptr)
	{
		_skinBlur->removeFromParent();
		_skinBlur = nullptr;
	}
}
