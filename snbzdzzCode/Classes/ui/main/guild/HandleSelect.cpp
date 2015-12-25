#pragma execution_character_set("utf-8")

#include "HandleSelect.h"
#include "data/define/DefinesRes.h"
#include "data/data/ManagerData.h"
#include "data/define/DefinesString.h"
#include "ui/ManagerUI.h"

HandleSelect::HandleSelect() : _skin(nullptr)
{
}

HandleSelect::~HandleSelect()
{
	_skin = nullptr;
}

bool HandleSelect::init()
{
	auto isInit = false;
	do
	{
		isInit = true;
	} while (0);
	return isInit;
}

void HandleSelect::setSkin(Layout *skin)
{
	_skin = skin;

	createPageSelectItem();
	createTxtCount();
}

void HandleSelect::createPageSelectItem()
{
	auto pageSelectItem = (PageView *)_skin->getChildByName("pageSelectItem");
	pageSelectItem->setCustomScrollThreshold(0.2f);
	auto interval = 10.0f;
	auto length = (int)3;
	for (auto i = 0; i < length; i++)
	{
		auto selectItem = createSelectItem();

		auto size = selectItem->getContentSize();

		auto postion = Vec2::ZERO;
		auto children = pageSelectItem->getChildren();
		if (children.size() > 0)
		{
			auto nodeLast = children.at(children.size() - 1);
			postion = nodeLast->getPosition();
			postion = Vec2(postion.x + size.width + interval, postion.y);
		}

		auto layout = Layout::create();
		layout->setBackGroundColorType(Layout::BackGroundColorType::NONE);
		layout->setContentSize(size);
		layout->setPosition(postion);
		layout->addChild(selectItem);

		pageSelectItem->addPage(layout);
	}
}

Layer * HandleSelect::createSelectItem()
{
	auto selectItem = (Layer *)CSLoader::createNode(RES_MODULES_MAIN_LAYER_GUILD_SELECT_ITEM_CSB);

	auto index = 0;
	while (true)
	{
		auto layout = (Layout *)selectItem->getChildByName("layout" + Value(index).asString());
		if (layout == nullptr)
		{
			break;
		}
		auto sprite = (Sprite *)layout->getChildByName("sprite");
		/*auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("");
		sprite->setSpriteFrame(spriteFrame);*/
		auto layoutTouch = (Layout *)layout->getChildByName("layoutTouch");
		layoutTouch->addTouchEventListener([](Ref *ref, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
			{

			}
		});
		auto btn = (Button *)layout->getChildByName("btn");
		btn->addTouchEventListener([](Ref *ref, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
			{
				ManagerUI::getInstance()->notify(ID_OBSERVER::LAYER_GUILD, TYPE_OBSERVER_LAYER_GUILD::SWITCH_LAYOUT, TYPE_OBSERVER_LAYER_GUILD::LAYOUT_DATING);
			}
		});
		auto txt = (Text *)layout->getChildByName("txt");
		txt->setString("99");
		index++;
	}
	return selectItem;
}

void HandleSelect::createTxtCount()
{
	auto handleDataIncome = ManagerData::getInstance()->getHandleDataIncome();
	auto value = handleDataIncome->getThing(IdThing::DATING);

	auto txt = (Text *)_skin->getChildByName("txtCount");
	txt->setString(STR_DATING_COUNT + Value(value).asString());
}
