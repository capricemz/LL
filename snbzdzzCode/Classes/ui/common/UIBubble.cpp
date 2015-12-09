#pragma execution_character_set("utf-8")

#include "UIBubble.h"
#include "data/define/DefinesRes.h"
#include "data/define/DefinesValue.h"
#include "data/config/ManagerCfg.h"
#include "common/util/UtilRandom.h"

UIBubble::UIBubble() : 
	_skin(nullptr),
	_idPlot(0),
	_funcOverAppear(nullptr),
	_funcOverDisappear(nullptr),
	_isTxtShowImmediately(false),
	_isAppearImmediately(false),
	_isDisappearImmediately(false),
	_numWordShow(0),
	_isAppear(false)
{
}

UIBubble::~UIBubble()
{
	_skin = nullptr;
	_funcOverAppear = nullptr;
	_funcOverDisappear = nullptr;
}

bool UIBubble::init()
{
	auto isInit = false;
	do
	{
		CC_BREAK_IF(!Node::init());

		_skin = CSLoader::createNode(RES_MODULES_COMMON_NODE_BUBBLE_CSB);
		addChild(_skin);

		isInit = true;
	} while (0);
	return isInit;
}

void UIBubble::setAnchorPoint(const Vec2& point)
{
	CCASSERT(dicAnchorPoint2BubbleAnchorPoint.find(point) != dicAnchorPoint2BubbleAnchorPoint.end(), "`````````` UIBubble::setAnchorPoint error point");
	CCASSERT(dicAnchorPoint2BubbleBgScale.find(point) != dicAnchorPoint2BubbleBgScale.end(), "`````````` UIBubble::setAnchorPoint error point");

	auto anchor = dicAnchorPoint2BubbleAnchorPoint.at(point);
	Node::setAnchorPoint(anchor);
	auto spriteBg = (Sprite *)_skin->getChildByName("spriteBg");
	auto scale = dicAnchorPoint2BubbleBgScale.at(point);
	spriteBg->setScaleX(scale.x);
	spriteBg->setScaleY(scale.y);
}

void UIBubble::show(
	const int &idPlot,
	const int &index,
	const function<void()> funcOverAppear,
	const function<void()> funcOverDisappear,
	const bool &isTxtShowImmediately /*= false*/,
	const bool &isAppearImmediately /*= false*/,
	const bool &isDisappearImmediately /*= false*/)
{
	_idPlot = idPlot;
	_index = index;
	_funcOverAppear = funcOverAppear;
	_funcOverDisappear = funcOverDisappear;
	_isTxtShowImmediately = isTxtShowImmediately;
	_isAppearImmediately = isAppearImmediately;
	_isDisappearImmediately = isDisappearImmediately;

	if (!_isAppear)
	{
		runAppear();
	}
	else
	{
		runDisappear();
	}
}

void UIBubble::runAppear()
{
	_isAppear = true;
	if (!_isAppearImmediately)//非立即显示
	{
		_skin->setScale(0.0f);
		auto actionAppear = EaseCircleActionIn::create(ScaleTo::create(0.2f, 1.0f));
		auto actionCallFunc = CallFunc::create([this]()
		{
			if (_funcOverAppear != nullptr)
			{
				_funcOverAppear();
			}
			playPlot();
		});
		_skin->runAction(Sequence::createWithTwoActions(actionAppear, actionCallFunc));
	}
	else
	{
		if (_funcOverAppear != nullptr)
		{
			_funcOverAppear();
		}
		playPlot();
	}
}

void UIBubble::runDisappear()
{
	if (!_isDisappearImmediately)//非立即消失
	{
		auto actionAppear = EaseCircleActionIn::create(ScaleTo::create(0.2f, 0.0f));
		auto actionCallFunc = CallFunc::create([this]()
		{
			if (_funcOverDisappear != nullptr)
			{
				_funcOverDisappear();
			}
			removeFromParent();
		});
		_skin->runAction(Sequence::createWithTwoActions(actionAppear, actionCallFunc));
	}
	else
	{
		if (_funcOverDisappear != nullptr)
		{
			_funcOverDisappear();
		}
		removeFromParent();
	}
}

void UIBubble::playPlot()
{
	auto cfg = ManagerCfg::getInstance()->getDicDicCfgPlot()[_idPlot][_index];
	auto interval = cfg.time / 1000.0f;
	//
	auto delay = 0.5f;
	if (!_isTxtShowImmediately)//非立即显示文本
	{
		schedule(schedule_selector(UIBubble::updateNodeBubbleTxt), interval, kRepeatForever, 0.0f);
		auto wordTotal = UtilString::utf8Strlen(cfg.textPlot.c_str());
		delay += interval * wordTotal;
	}
	else
	{
		auto text = cfg.textPlot;
		auto txt = (Text *)_skin->getChildByName("txt");
		txt->setString(text);
	}
	//
	auto actionDelay = DelayTime::create(delay);
	auto actionCallFunc = CallFunc::create([this]()
	{
		unschedule(schedule_selector(UIBubble::updateNodeBubbleTxt));
		_skin->stopAllActions();
		_numWordShow = 0;
		runDisappear();
	});
	_skin->runAction(Sequence::create(actionDelay, actionCallFunc, nullptr));
}

void UIBubble::updateNodeBubbleTxt(float dt)
{
	/*log("dt:%f",dt);*/
	_numWordShow++;
	/*log("count:%d", _numWordShow);*/
	auto cfg = ManagerCfg::getInstance()->getDicDicCfgPlot()[_idPlot][_index];
	auto text = UtilString::utf8StrSub(cfg.textPlot, 0, _numWordShow);
	/*log("text:%s", text.c_str());*/
	auto txt = (Text *)_skin->getChildByName("txt");
	txt->setString(text);
}
