#include "UIWordsDrift.h"
#include "cocostudio/ActionTimeline/CSLoader.h"
#include "ui/UIText.h"
#include "data/define/DefinesRes.h"

using namespace ui;

UIWordsDrift::UIWordsDrift()
{

}

UIWordsDrift::~UIWordsDrift()
{

}

bool UIWordsDrift::init()
{
	auto isInit = false;
	do 
	{
		CC_BREAK_IF(!Node::init());



		isInit = true;
	} while (0);
	return isInit;
}

void UIWordsDrift::driftWords(const string &words, const Color4B &color, const float &duration)
{
	auto text = Text::create(words, RES_FONTS_KTJT, 30.0f);
	text->setTextColor(color);
	text->setTextHorizontalAlignment(TextHAlignment::CENTER);
	text->setTextVerticalAlignment(TextVAlignment::TOP);
	text->enableOutline(Color4B(75, 75, 75, 255));
	addChild(text);

	auto actionMoveUp = EaseSineOut::create(MoveBy::create(0.4f * duration, Vec2(0, 45)));
	auto actionMoveDown = EaseSineIn::create(MoveBy::create(0.4f * duration, Vec2(0, -45)));
	auto actionDisappear = FadeOut::create(0.2f * duration);
	auto actionRmv4par = CallFunc::create([=]()
	{
		removeFromParent();
	});

	runAction(Sequence::create(actionMoveUp, actionMoveDown, actionDisappear, actionRmv4par, nullptr));
}
