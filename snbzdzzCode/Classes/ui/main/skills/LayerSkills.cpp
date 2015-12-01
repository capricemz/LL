#pragma execution_character_set("utf-8")

#include "LayerSkills.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CCComExtensionData.h"
#include "data/define/DefinesRes.h"
#include "ui/ManagerUI.h"
#include "data/data/ManagerData.h"

using namespace ui;

LayerSkills::LayerSkills() : _skin(nullptr)
{
}

LayerSkills::~LayerSkills()
{
	_skin = nullptr;
}

bool LayerSkills::init()
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

Layer * LayerSkills::getThis()
{
	return this;
}

void LayerSkills::afterRunAppear()
{
}

void LayerSkills::afterRunDisappear()
{
}

void LayerSkills::dealRemoveFromParent()
{
	if (getParent())
	{
		removeFromParent();
	}
}

void LayerSkills::createSkin()
{
	_skin = (Layer *)CSLoader::createNode(RES_MODULES_MAIN_LAYER_SKILLS_CSB);
	addChild(_skin);

	auto btn = (Button *)_skin->getChildByName("btnBack");
	btn->addTouchEventListener([](Ref *ref, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			ManagerUI::getInstance()->notify(ID_OBSERVER::SCENE_MAIN, TYPE_OBSERVER_SCENE_MAIN::SHOW_LEVELS);
		}
	});
	
	updateLayoutBtns();

	updateLayoutSkillItems(DATA_UNLOCK_INIT_MAID);
}

void LayerSkills::updateLayoutBtns()
{
	auto layoutBtns = (Layout *)_skin->getChildByName("layoutBtns");
	auto index = 0;
	while (true)
	{
		auto btn = (Button *)layoutBtns->getChildByName("btn" + Value(index).asString());
		if (btn == nullptr)
		{
			break;
		}
		//在代码里面先获取到button，getComponent()，并把获取的对象强转为Cocos Studio::ComExtensionData* 指针，再调用getCustomProperty()
		cocostudio::ComExtensionData* data = dynamic_cast<cocostudio::ComExtensionData*>(btn->getComponent("ComExtensionData"));
		auto idEntity = Value(data->getCustomProperty()).asInt();
		auto isUnlock = ManagerData::getInstance()->getHandleDataUnlock()->getIsUnlockMaid(idEntity);
		if (isUnlock)
		{
			btn->setTouchEnabled(true);
			btn->addTouchEventListener(CC_CALLBACK_2(LayerSkills::onTouchBtnMaid, this));
		}
		else
		{
			btn->setTouchEnabled(false);
		}
		index++;
	}
}

void LayerSkills::onTouchBtnMaid(Ref *ref, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		auto btn = (Button *)ref;
		cocostudio::ComExtensionData* data = dynamic_cast<cocostudio::ComExtensionData*>(btn->getComponent("ComExtensionData"));
		auto idEntity = Value(data->getCustomProperty()).asInt();
		updateLayoutSkillItems(idEntity);
	}
}

void LayerSkills::updateLayoutSkillItems(const int &idEntity)
{
	auto layoutSkillItems = (Layout *)_skin->getChildByName("layoutSkillItems");
	auto vecdataEntityMaid = ManagerData::getInstance()->getHandleDataEntity()->getVecDataEntityMaid();
	DataEntity *dataEntity = nullptr;
	for (auto var : vecdataEntityMaid)
	{
		if (var->getIdEntity() == idEntity)
		{
			dataEntity = var;
			break;
		}
	}
	CCASSERT(dataEntity != nullptr, "LayerSkills::updateLayoutSkillItems idEntity wrong");
	auto index = 0;
	while (true)
	{
		auto layoutSkillItem = (Layout *)layoutSkillItems->getChildByName("layoutSkillItem" + Value(index).asString());
		if (layoutSkillItem == nullptr)
		{
			break;
		}
		auto txt = (Text *)layoutSkillItem->getChildByName("txt");
		auto btn = (Button *)layoutSkillItem->getChildByName("btn");

		auto vec = dataEntity->vecSkillActiveInfoGet();
		auto vecSkillNeedUnlock = dataEntity->getVecSkillNeedUnlock();
		if ((int)vecSkillNeedUnlock.size() > index)
		{
			auto vecInfo = vecSkillNeedUnlock[index];
			txt->setString("");
			btn->setTouchEnabled(true);
			auto idSkill = (int)btn->getUserData();
			if (idSkill == 0)
			{
				btn->addTouchEventListener(CC_CALLBACK_2(LayerSkills::onTouchBtnSkill, this));
			}
			btn->setUserData((void *)vecInfo);
		}
		else
		{
			txt->setString("");
			btn->setTouchEnabled(false);
		}
		
		index++;
	}
}

void LayerSkills::onTouchBtnSkill(Ref *ref, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		auto btn = (Button *)ref;
		auto idSkill = (int)btn->getUserData();

	}
}
