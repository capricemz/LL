#pragma execution_character_set("utf-8")

#include "UIConfirm.h"
#include "cocostudio/ActionTimeline/CSLoader.h"
#include "common/util/UtilHelper.h"
#include "common/util/UtilString.h"
#include "SimpleAudioEngine.h"
#include "data/define/DefinesRes.h"
#include "data/define/DefinesString.h"

using namespace CocosDenshion;

void UIConfirm::show(const TypeConfirms &type, std::string textAssgin, const std::function<void()> &confirmFunc)
{
	/*auto parent = getParent();
	if (parent == nullptr)
	{
		log("ConfirmPanel::show parent is null");
		return;
	}
	//
	_mask = Layout::create();
	_mask->setTouchEnabled(true);
	_mask->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
	_mask->setBackGroundColor(Color3B::BLACK);
	_mask->setOpacity(127);
	auto sizeWin = Director::getInstance()->getWinSize();
	_mask->setContentSize(sizeWin);
	_mask->addTouchEventListener(CC_CALLBACK_2(UIConfirm::onTouchCancel, this));
	addChild(_mask);
	//
	auto node = CSLoader::createNode(UI_COMMON_CONFIRM);
	_mask->addChild(node);
	node->setPosition(sizeWin.width / 2, sizeWin.height / 2);
	//
	auto btnCancel = (Button *)node->getChildByName("btnCancel");
	btnCancel->addTouchEventListener(CC_CALLBACK_2(UIConfirm::onTouchCancel, this));
	auto btnConfirm = (Button *)node->getChildByName("btnConfirm");
	btnConfirm->addTouchEventListener(CC_CALLBACK_2(UIConfirm::onTouchConfirm, this, confirmFunc));
	//
	auto layoutCs = (Layout *)node->getChildByName("layoutCs");
	layoutCs->setVisible(false);
	auto layoutBuy = (Layout *)node->getChildByName("layoutBuy");
	layoutBuy->setVisible(false);
	auto layoutGj = (Layout *)node->getChildByName("layoutGj");
	layoutGj->setVisible(false);
	auto txtTitle = (Text *)node->getChildByName("txtTitle");
	if (type == TypeConfirms::MAP_TRANSFER)
	{
		layoutCs->setVisible(true);
		txtTitle->setString(STR_CONFIRM_CS);
		auto txtAssgin = (Text *)layoutCs->getChildByName("txtAssign");
		txtAssgin->setString(textAssgin);
	}
	else if (type == TypeConfirms::OFF_LINE_DROP)
	{
		btnCancel->setVisible(false);
		layoutGj->setVisible(true);
		txtTitle->setString(STR_CONFIRM_GJ);
		auto vecInfo = UtilString::split(textAssgin, "|");
		auto txtTime = (Text *)layoutGj->getChildByName("txtTime");
		txtTime->setString(vecInfo[0]);
		auto txtGet = (Text *)layoutGj->getChildByName("txtGet");
		txtGet->setString(vecInfo[1]);
	}
	else
	{
		layoutBuy->setVisible(true);
		txtTitle->setString(STR_CONFIRM_BUY);
		auto txtCost = (Text *)layoutBuy->getChildByName("txtCost");
		auto text = txtCost->getString();
		auto valueCost = 0;
		string textAssgin = "";
		if (type == TypeConfirms::BUY_ACTION_POINT)
		{
			valueCost = COST_BUY_ACTION_POINT;
			textAssgin = STR_CONFIRM_TEXT_BUY_ACTION_POINT;
		}
		else if (type == TypeConfirms::BUY_CARRIAGE)
		{
			valueCost = COST_BUY_CARRIAGE;
			textAssgin = STR_CONFIRM_TEXT_BUY_CARRIAGE;
		}
		else if (type == TypeConfirms::BUY_MAID_CLOTHS)
		{
			valueCost = COST_BUY_MAID_CLOTHS;
			textAssgin = STR_CONFIRM_TEXT_BUY_MAID_CLOTHS;
		}
		 UtilString::stringReplace(text, "&x", Value(valueCost).asString());
		txtCost->setString(text);
		//
		auto txtAssgin = (Text *)layoutBuy->getChildByName("txtAssign");
		txtAssgin->setString(textAssgin);
	}*/
}

void UIConfirm::hide()
{
	if (_mask && _mask->getParent())
	{
		_mask->removeFromParent();
		_mask = nullptr;
	}
}

bool UIConfirm::isShowed()
{
	return _mask && _mask->getParent();
}

void UIConfirm::onTouchConfirm(Ref *ref, Widget::TouchEventType type, const std::function<void()> &confirmFunc)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		if (confirmFunc != nullptr)
		{
			confirmFunc();
		}
		hide();
		//
		SimpleAudioEngine::getInstance()->playEffect(SOUND_EFFECT_SYSTEM_BTN_0_MP3.c_str());
	}
}

void UIConfirm::onTouchCancel(Ref *ref, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		hide();
		//
		SimpleAudioEngine::getInstance()->playEffect(SOUND_EFFECT_SYSTEM_BTN_0_MP3.c_str());
	}
}
