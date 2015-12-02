#pragma execution_character_set("utf-8")

#include "LayerSkills.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CCComExtensionData.h"
#include "data/define/DefinesRes.h"
#include "ui/ManagerUI.h"
#include "data/data/ManagerData.h"
#include "data/config/ManagerCfg.h"
#include "data/define/DefinesString.h"

using namespace ui;

LayerSkills::LayerSkills() : _skin(nullptr), _idEntityCurrent(DATA_UNLOCK_INIT_MAID)
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

	updateLayoutSkillItems();
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
		auto cfgEntity = ManagerCfg::getInstance()->getDicCfgEntity()[idEntity];
		btn->setTitleText(cfgEntity.name);
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
		_idEntityCurrent = Value(data->getCustomProperty()).asInt();
		updateLayoutSkillItems();
	}
}

void LayerSkills::updateLayoutSkillItems()
{
	auto layoutSkillItems = (Layout *)_skin->getChildByName("layoutSkillItems");
	auto vecdataEntityMaid = ManagerData::getInstance()->getHandleDataEntity()->getVecDataEntityMaid();
	DataEntity *dataEntity = nullptr;
	for (auto var : vecdataEntityMaid)
	{
		if (var->getIdEntity() == _idEntityCurrent)
		{
			dataEntity = var;
			break;
		}
	}
	CCASSERT(dataEntity != nullptr, "LayerSkills::updateLayoutSkillItems _idEntityCurrent wrong");
	auto vecSkillActiveNeedUnlock = dataEntity->getVecSkillActiveNeedUnlock();
	auto lengthVecSkillActiveNeedUnlock = (int)vecSkillActiveNeedUnlock.size();
	auto vecSkillPassive = dataEntity->getVecSkillPassive();

	auto index = 0;
	while (true)
	{
		auto layoutSkillItem = (Layout *)layoutSkillItems->getChildByName("layoutSkillItem" + Value(index).asString());
		if (layoutSkillItem == nullptr)
		{
			break;
		}

		if (lengthVecSkillActiveNeedUnlock > index)
		{
			auto dataSkillInfo = vecSkillActiveNeedUnlock[index];
			updateLayoutSKillItem(layoutSkillItem, true, dataSkillInfo);
		}
		else if ((int)vecSkillPassive.size() > index - lengthVecSkillActiveNeedUnlock)
		{
			auto dataSkillInfo = vecSkillPassive[index - lengthVecSkillActiveNeedUnlock];
			updateLayoutSKillItem(layoutSkillItem, true, dataSkillInfo);
		}
		else
		{
			updateLayoutSKillItem(layoutSkillItem, false, {});
		}

		index++;
	}
}

void LayerSkills::updateLayoutSKillItem(Layout *layoutSkillItem, const bool &isGet, const DataSkillInfo &dataSkillInfo)
{
	auto txt = (Text *)layoutSkillItem->getChildByName("txt");
	auto btn = (Button *)layoutSkillItem->getChildByName("btn");
	btn->addTouchEventListener(CC_CALLBACK_2(LayerSkills::onTouchBtnSkill, this, dataSkillInfo));

	if (isGet)
	{
		auto cfgSkill = ManagerCfg::getInstance()->getDicDicCfgSkill()[dataSkillInfo.id][dataSkillInfo.index];
		txt->setString(cfgSkill.desc);

		btn->setVisible(true);
		auto handleDataUnlock = ManagerData::getInstance()->getHandleDataUnlock();
		auto isUnlock = handleDataUnlock->getIsUnlockSkill(dataSkillInfo.id, dataSkillInfo.index);
		if (!isUnlock)//若未解锁
		{
			btn->setTitleText("button");
			btn->setTouchEnabled(true);
		}
		else
		{
			btn->setTitleText(STR_FILLED);
			btn->setTouchEnabled(false);
		}
	}
	else
	{
		txt->setString("");
		btn->setVisible(false);
	}
}

void LayerSkills::onTouchBtnSkill(Ref *ref, Widget::TouchEventType type, const DataSkillInfo &dataSkillInfo)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		auto id = dataSkillInfo.id;
		auto index = dataSkillInfo.index;

		if (true)
		{
			auto handleDataUnlock = ManagerData::getInstance()->getHandleDataUnlock();
			handleDataUnlock->setIsUnlockSkill(id, index);
			handleDataUnlock->dataFileSet();
			auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
			handleDataEntity->getDataEntityMaid()->updateSkillGroup();
			updateLayoutSkillItems();
		}
	}
}
