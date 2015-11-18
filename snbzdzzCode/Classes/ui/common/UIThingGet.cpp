#pragma execution_character_set("utf-8")

#include "UIThingGet.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "common/util/UtilHelper.h"
#include "data/config/ManagerCfg.h"
#include "SimpleAudioEngine.h"
#include "data/define/DefinesRes.h"

using namespace ui;
using namespace CocosDenshion;

UIThingGet::UIThingGet()
{
}

UIThingGet::~UIThingGet()
{
}

bool UIThingGet::init(const int &type, const int &idThing, const int &num, const std::function<void()> &func)
{
	auto isInit = false;

	do
	{
		CC_BREAK_IF(!Layer::init());

		/*auto skin = CSLoader::createNode(UI_COMMON_GET_THING);

		string name;
		switch (type)
		{
		default:
		case 0:
			name = COMMON_GET_THING_TITLE_0;
			break;
		case 1:
			name = COMMON_GET_THING_TITLE_1;
			break;
		case 2:
			name = COMMON_GET_THING_TITLE_2;
			break;
		}
		auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
		auto spriteTitle = (Sprite *)UtilHelper::seekNodeByName(skin, "spriteTitle");
		spriteTitle->setSpriteFrame(spriteFrame);

		auto cfgThing = ManagerCfg::getInstance()->dicCfgThingGet()[idThing];
		name = ICON_THING_ + cfgThing.urlPic;
		spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
		auto spriteIcon = (Sprite *)UtilHelper::seekNodeByName(skin, "spriteIcon");
		spriteIcon->setSpriteFrame(spriteFrame);
		auto sizeOriginal = spriteIcon->getContentSize();
		auto scale = sizeOriginal.width > sizeOriginal.height ? 80.0f / sizeOriginal.width : 80.0f / sizeOriginal.height;
		spriteIcon->setScale(scale);

		auto txtInfo = (Text *)UtilHelper::seekNodeByName(skin, "txtInfo");
		auto text = cfgThing.name + (num > 0 ? "x" + Value(num).asString() : "");
		txtInfo->setString(text);

		addChild(skin);

		auto actionTimeline = CSLoader::createTimeline(UI_COMMON_GET_THING);
		actionTimeline->gotoFrameAndPlay(actionTimeline->getStartFrame(), false);
		actionTimeline->setLastFrameCallFunc([=]()
		{
			auto layoutBg = (Layout *)skin->getChildByName("Panel_1");
			layoutBg->addTouchEventListener([=](Ref *ref, Widget::TouchEventType type)
			{
				if (type == Widget::TouchEventType::ENDED)
				{
					if (func != nullptr)
					{
						func();
					}
					removeFromParent();
				}
			});
			auto layoutBg2 = (Layout *)layoutBg->getChildByName("Panel_2");
			layoutBg2->setTouchEnabled(false);
			/ *removeFromParent();* /
		});
		skin->runAction(actionTimeline);

		SimpleAudioEngine::getInstance()->playEffect(SOUND_EFFECT_SYSTEM_GET_THING.c_str());*/

		isInit = true;
	} while (0);

	return isInit;
}
