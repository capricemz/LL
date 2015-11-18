#pragma execution_character_set("utf-8")

#include "UIGuide.h"
#include "ui/CocosGUI.h"
#include "common/util/UtilHelper.h"
#include "data/data/ManagerData.h"
#include "data/config/ManagerCfg.h"
#include "data/define/DefinesRes.h"

UIGuide::UIGuide()
{
}

UIGuide::~UIGuide()
{
	_chipper = nullptr;
	_target = nullptr;
}

bool UIGuide::init()
{
	auto isInit = false;
	do 
	{
		CC_BREAK_IF(!Node::init());

		isInit = true;
	} while (0);
	return isInit;
}

bool UIGuide::show()
{
	if (isShowed())
	{
		return false;
	}
	/*auto guideStep = ManagerData::getInstance()->guideStepGet();
	/ *guideStep = 2;//for test* /
	auto cfgGuide = ManagerCfg::getInstance()->dicCfgGuideGet()[guideStep];
	auto idRegionStart = ManagerData::getInstance()->idRegionStartGet();
	if (idRegionStart != cfgGuide.idRegion)
	{
		return false;
	}
	auto vecDirName = UtilString::split(cfgGuide.dirName, "/");
	_target = UtilHelper::seekNodeByDirName(vecDirName);
	if (_target == nullptr)
	{
		return false;
	}
	auto sizeTarget = _target->getContentSize();
	auto anchorTarget = _target->getAnchorPoint();
	auto postion = _target->getPosition();
	postion = _target->getParent()->convertToWorldSpace(postion);
	//
	auto stencil = LayerColor::create(Color4B::WHITE);
	stencil->ignoreAnchorPointForPosition(false);
	stencil->setAnchorPoint(anchorTarget);
	stencil->setPosition(postion);
	stencil->setContentSize(sizeTarget);
	//
	auto skinGuide = CSLoader::createNode(UI_COMMON_GUIDE);

	auto layoutMask = (Layout *)skinGuide->getChildByName("layoutMask");
	layoutMask->addTouchEventListener(CC_CALLBACK_2(UIGuide::onTouch, this));

	auto layoutInfo = (Layout *)skinGuide->getChildByName("layoutInfo");
	auto sizeWin = Director::getInstance()->getWinSize();
	auto sizeLayoutInfo = layoutInfo->getContentSize();
	auto anchorLayoutInfo = layoutInfo->getAnchorPoint();

	auto isDownOut = postion.y - sizeLayoutInfo.height * anchorLayoutInfo.y < 0;
	auto isRightOut = postion.x + sizeLayoutInfo.width * (1 - anchorLayoutInfo.x) > sizeWin.width;
	
	anchorLayoutInfo.y = isDownOut ? 1.0f - anchorLayoutInfo.y : anchorLayoutInfo.y;//若底部超出，锚点Y值取反
	anchorLayoutInfo.x = isRightOut ? 1.0f - anchorLayoutInfo.x : anchorLayoutInfo.x;//若右侧超出，锚点X值取反
	layoutInfo->setAnchorPoint(anchorLayoutInfo);

	postion.y += isDownOut ? sizeTarget.height * (1 - anchorTarget.y) : -sizeTarget.height * anchorTarget.y;//若底部超出，上移目标半高
	layoutInfo->setPosition(postion);

	auto dy = isDownOut ? 10.0f : -10.0f;//若底部超出，浮动初始向上
	layoutInfo->runAction(RepeatForever::create(Sequence::createWithTwoActions(MoveBy::create(1.5f, Vec2(0.0f, dy)), MoveBy::create(1.5f, Vec2(0.0f, -dy)))));

	auto image = (ImageView *)layoutInfo->getChildByName("image");
	image->setScaleY(isDownOut ? -1.0f : 1.0f);//若底部超出，图片上下反转
	image->setScaleX(isRightOut ? -1.0f : 1.0f);//若右侧超出，锚点左右反转

	auto txt = (Text *)layoutInfo->getChildByName("txt");
	txt->setString(cfgGuide.desc);
	//
	_chipper = ClippingNode::create(stencil);
	_chipper->setInverted(true);
	/ *_chipper->setAlphaThreshold(0);* /
	_chipper->addChild(skinGuide);
	addChild(_chipper);*/

	return true;
}

void UIGuide::onTouch(Ref *ref, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		if (!isShowed())
		{
			return;
		}

		/*ManagerData::getInstance()->onGuideStepAdd();*/
		
		hide();
		
		auto anchor = _target->getAnchorPoint();
		auto size = _target->getContentSize();
		auto postion = _target->getPosition();
		postion.add(Vec2((0.5f - anchor.x) * size.width, (0.5f - anchor.y) * size.height));
		postion = _target->getParent()->convertToWorldSpace(postion);
		postion = Director::getInstance()->convertToGL(postion);

		Touch touch;
		touch.setTouchInfo(0, postion.x, postion.y);
		auto widget = (Widget *)_target;
		widget->onTouchBegan(&touch, nullptr);
		widget->onTouchEnded(&touch, nullptr);
	}
}

void UIGuide::hide()
{
	if (isShowed())
	{
		_chipper->removeFromParent();
		_chipper = nullptr;
	}
}

bool UIGuide::isShowed()
{
	return _chipper != nullptr && _chipper->getParent() != nullptr;
}
