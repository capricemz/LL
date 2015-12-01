#pragma execution_character_set("utf-8")

#include "LayerLevels.h"
#include "data/define/DefinesRes.h"
#include "ui/ManagerUI.h"
#include "data/data/ManagerData.h"
#include "cocostudio/CCComExtensionData.h"
#include "data/define/DefinesString.h"

using namespace ui;

LayerLevels::LayerLevels() : _skin(nullptr)
{
}

LayerLevels::~LayerLevels()
{
	_skin = nullptr;
}

bool LayerLevels::init()
{
	auto isInit = false;
	do 
	{
		CC_BREAK_IF(!Layer::init());

		createSkin();

		isInit = true;
	} while (0);
	return isInit;
}

Layer * LayerLevels::getThis()
{
	return this;
}

void LayerLevels::afterRunAppear()
{
}

void LayerLevels::afterRunDisappear()
{
}

void LayerLevels::dealRemoveFromParent()
{
	if (getParent())
	{
		removeFromParent();
	}
}

void LayerLevels::createSkin()
{
	_skin = (Layer *)CSLoader::createNode(RES_MODULES_MAIN_LAYER_LEVELS_CSB);
	addChild(_skin);

	auto listView = (ListView *)_skin->getChildByName("listViewBtns");
	auto layoutBtns = (Layout *)listView->getChildByName("layoutBtns");
	auto dicDataLevel = ManagerData::getInstance()->getHandleDataLevels()->getDicDataLevel();
	auto index = 0;
	Node *nodeLevel = nullptr;
	while (true)
	{
		nodeLevel = (Node *)layoutBtns->getChildByName("nodeLevel" + Value(index).asString());
		if (nodeLevel == nullptr)
		{
			break;
		}
		//在代码里面先获取到button，getComponent()，并把获取的对象强转为Cocos Studio::ComExtensionData* 指针，再调用getCustomProperty()
		cocostudio::ComExtensionData* data = dynamic_cast<cocostudio::ComExtensionData*>(nodeLevel->getComponent("ComExtensionData"));
		auto idLevel = Value(data->getCustomProperty()).asInt();
		auto dataLevel = dicDataLevel.at(idLevel);
		
		updateNodeLevel(index, nodeLevel, dataLevel);

		index++;
	}

	auto btnSkills = (Button *)_skin->getChildByName("btnSkills");
	btnSkills->addTouchEventListener([](Ref *ref, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			ManagerUI::getInstance()->notify(ID_OBSERVER::SCENE_MAIN, TYPE_OBSERVER_SCENE_MAIN::SHOW_SKILLS);
		}
	});
}

void LayerLevels::updateNodeLevel(const int &index, Node *nodeLevel, DataLevel *dataLevel)
{
	auto cfgLevel = dataLevel->getCfgLevel();
	auto layout = (Layout *)nodeLevel->getChildByName("layout");
	
	auto spriteState = (Sprite *)nodeLevel->getChildByName("spriteState");
	spriteState->setVisible(dataLevel->getState() == TypeLevelState::PASSED);
	
	auto txtLevel = (Text *)nodeLevel->getChildByName("txtLevel");
	txtLevel->setString(STR_LEVEL_0 + Value(index + 1).asString() + STR_LEVEL_1);

	auto txtName = (Text *)nodeLevel->getChildByName("txtName");
	txtName->setString(cfgLevel.name);

	auto levelTargetNum = dataLevel->levelTargetNumGet();
	auto layoutStar = (Layout *)nodeLevel->getChildByName("layoutStar");
	auto isSpriteNullptr = false;
	auto widthSpriteStar = 0.0f;
	for (auto i = 0; i < levelTargetNum; i++)
	{
		auto spriteStar = (Sprite *)layoutStar->getChildByName("spriteStar" + Value(i).asInt());
		if (spriteStar == nullptr)
		{
			spriteStar = Sprite::create();
			spriteStar->setName("spriteStar" + Value(i).asInt());
			layoutStar->addChild(spriteStar);
			isSpriteNullptr = true;
		}
		
		auto isComolete = dataLevel->levelTargetIsComplete(i);
		auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(isComolete ? RES_IMAGES_MAIN_LEVELS_XING_PNG : RES_IMAGES_MAIN_LEVELS_XING_KONG_PNG);
		spriteStar->setSpriteFrame(spriteFrame);

		auto width = spriteStar->getContentSize().width;
		if (isSpriteNullptr && (widthSpriteStar == 0.0f || width > widthSpriteStar))
		{
			widthSpriteStar = width;
		}
	}
	if (widthSpriteStar != 0.0f)
	{
		widthSpriteStar += 5.0f;
		auto size = layoutStar->getContentSize();
		auto postion = Vec2((size.width - widthSpriteStar * (levelTargetNum - 1)) * 0.5f, size.height * 0.5f);
		for (auto i = 0; i < levelTargetNum; i++)
		{
			auto spriteStar = (Sprite *)layoutStar->getChildByName("spriteStar" + Value(i).asInt());
			spriteStar->setPosition(postion);
			postion += Vec2(widthSpriteStar, 0.0f);
		}
	}
	
	auto btn = (Button *)nodeLevel->getChildByName("btn");
	if (dataLevel->getState() != TypeLevelState::LOCK)
	{
		btn->setTouchEnabled(true);
		btn->setUserData((void *)cfgLevel.id);
		btn->addTouchEventListener(CC_CALLBACK_2(LayerLevels::onTouchBtnLv, this));
	}
	else
	{
		btn->setTouchEnabled(false);
	}
}

void LayerLevels::onTouchBtnLv(Ref *ref, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		auto btn = (Button *)ref;
		auto idLevel = (int)btn->getUserData();
		ManagerData::getInstance()->getHandleDataLevels()->setLevelCurrent(idLevel);
		ManagerUI::getInstance()->notify(ID_OBSERVER::SCENE_MAIN, TYPE_OBSERVER_SCENE_MAIN::SHOW_BATTLE);
	}
}
