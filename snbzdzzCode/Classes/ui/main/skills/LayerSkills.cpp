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
#include "../guild/UIEntity.h"

using namespace ui;

LayerSkills::LayerSkills() : _skin(nullptr), _idEntityCurrent(DATA_UNLOCK_INIT_MAID), _vecShowIdEntity({})
{
}

LayerSkills::~LayerSkills()
{
	_skin = nullptr;
	_vecShowIdEntity.clear();
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

void LayerSkills::updateSkin(const int &idEntity)
{
	_idEntityCurrent = idEntity;
	updateLayoutSkillItems();
}

void LayerSkills::createSkin()
{
	_skin = (Layer *)CSLoader::createNode(RES_MODULES_MAIN_LAYER_SKILLS_CSB);
	addChild(_skin);

	updateLayoutBtns();

	updateLayoutMaid();

	updateLayoutSkillItems();
}

void LayerSkills::updateLayoutBtns()
{
	auto isVecEmpty = _vecShowIdEntity.size() == 0;
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
		
		auto handleDataUnlock = ManagerData::getInstance()->getHandleDataUnlock();
		auto isBuy = handleDataUnlock->getIsBuyMaid(idEntity);
		auto isUnlock = handleDataUnlock->getIsUnlockMaid(idEntity);

		if (isVecEmpty && (isBuy || (isUnlock && !isBuy)))//若数据为空且，已购买或解锁且未购买
		{
			_vecShowIdEntity.push_back(idEntity);
		}

		btn->setBright(isUnlock);
		btn->setTouchEnabled(isUnlock);
		btn->addTouchEventListener(CC_CALLBACK_2(LayerSkills::onTouchBtnMaid, this));
		
		auto spriteLockState = (Sprite *)btn->getChildByName("spriteLockState");
		auto name = !isUnlock ? RES_IMAGES_MAIN_MAID_UNLOCK_PNG : (!isBuy ? RES_IMAGES_MAIN_MAID_BUY_PNG : "");
		if (name != "")
		{
			auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
			spriteLockState->setSpriteFrame(spriteFrame);
		}
		else
		{
			spriteLockState->setVisible(false);
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
		updateLayoutMaid();
		updateLayoutSkillItems();
	}
}

void LayerSkills::updateLayoutMaid()
{
	auto layoutMaid = (Layout *)_skin->getChildByName("layoutMaid");
	auto size = layoutMaid->getContentSize();

	auto uiEntity = UIEntity::create();
	uiEntity->updateSkin(_idEntityCurrent, 1.0f);
	uiEntity->setPosition(Vec2(size.width * 0.5f, size.height *0.5f));
	uiEntity->getLayoutBg()->addTouchEventListener([this](Ref *ref, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			auto cfgEntity = ManagerCfg::getInstance()->getDicCfgEntity()[_idEntityCurrent];
			auto handleDataIncome = ManagerData::getInstance()->getHandleDataIncome();
			if (handleDataIncome->getThingEnough(IdThing::GOLD, cfgEntity.cost))
			{
				handleDataIncome->addThing(IdThing::GOLD, cfgEntity.cost);
				auto handleDataUnlock = ManagerData::getInstance()->getHandleDataUnlock();
				handleDataUnlock->setIsBuyMaid(_idEntityCurrent);
			}
		}
	});
	layoutMaid->addChild(uiEntity, -1);

	auto handleDataUnlock = ManagerData::getInstance()->getHandleDataUnlock();
	auto isBuy = handleDataUnlock->getIsBuyMaid(_idEntityCurrent);
	auto isUnlock = handleDataUnlock->getIsUnlockMaid(_idEntityCurrent);

	auto spriteBuyTip = (Sprite *)layoutMaid->getChildByName("spriteBuyTip");
	spriteBuyTip->setVisible(isUnlock && !isBuy);

	auto cfgEntity = ManagerCfg::getInstance()->getDicCfgEntity()[_idEntityCurrent];
	auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cfgEntity.vecUrlPic[2]);
	auto spriteNameBg = (Sprite *)layoutMaid->getChildByName("spriteNameBg");
	spriteNameBg->setSpriteFrame(spriteFrame);

	auto btn = (Button *)layoutMaid->getChildByName("btnPrev");
	btn->addTouchEventListener(CC_CALLBACK_2(LayerSkills::onTouchBtnPrev, this));
	btn->setBright(_vecShowIdEntity.size() > 1);
	btn->setTouchEnabled(_vecShowIdEntity.size() > 1);
	
	btn = (Button *)layoutMaid->getChildByName("btnNext");
	btn->addTouchEventListener(CC_CALLBACK_2(LayerSkills::onTouchBtnNext, this));
	btn->setBright(_vecShowIdEntity.size() > 1);
	btn->setTouchEnabled(_vecShowIdEntity.size() > 1);
	
	btn = (Button *)layoutMaid->getChildByName("btnSkill");
	btn->addTouchEventListener(CC_CALLBACK_2(LayerSkills::onTouchBtnSkill, this));
}

void LayerSkills::onTouchBtnPrev(Ref *ref, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		auto iter = find(_vecShowIdEntity.begin(), _vecShowIdEntity.end(), _idEntityCurrent);
		auto index = 0;
		if (iter != _vecShowIdEntity.begin())
		{
			index = (iter - 1) - _vecShowIdEntity.begin();
		}
		else
		{
			index = _vecShowIdEntity.size() - 1;
		}
		_idEntityCurrent = _vecShowIdEntity[index];
		updateLayoutMaid();
		updateLayoutSkillItems();
	}
}

void LayerSkills::onTouchBtnNext(Ref *ref, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		auto iter = find(_vecShowIdEntity.begin(), _vecShowIdEntity.end(), _idEntityCurrent);
		auto index = 0;
		if (iter != _vecShowIdEntity.end())
		{
			index = (iter + 1) - _vecShowIdEntity.begin();
		}
		else
		{
			index = 0;
		}
		_idEntityCurrent = _vecShowIdEntity[index];
		updateLayoutMaid();
		updateLayoutSkillItems();
	}
}

void LayerSkills::onTouchBtnSkill(Ref *ref, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		//显示动画
		switchMaidSkill();
	}
}

void LayerSkills::switchMaidSkill()
{
	auto layoutMaid = (Layout *)_skin->getChildByName("layoutMaid");
	auto layoutSkillItems = (Layout *)_skin->getChildByName("layoutSkillItems");
	auto node = layoutMaid->isVisible() ? layoutMaid : layoutSkillItems;
	auto nodeNew = layoutMaid->isVisible() ? layoutSkillItems : layoutMaid;
	nodeNew->setVisible(true);
	auto funcOverNode = [node]()
	{
		node->setVisible(false);
	};
	ManagerUI::getInstance()->switchTwoNode(node, nodeNew, funcOverNode);
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
	auto vecSkillActiveNeedBuy = dataEntity->getVecSkillActiveNeedBuy();
	auto lengthVecSkillActiveNeedBuy = (int)vecSkillActiveNeedBuy.size();
	auto vecSkillPassive = dataEntity->getVecSkillPassive();

	auto index = 0;
	while (true)
	{
		auto layoutSkillItem = (Layout *)layoutSkillItems->getChildByName("layoutSkillItem" + Value(index).asString());
		if (layoutSkillItem == nullptr)
		{
			break;
		}

		if (lengthVecSkillActiveNeedBuy > index)
		{
			auto dataSkillInfo = vecSkillActiveNeedBuy[index];
			updateLayoutSKillItem(layoutSkillItem, true, dataSkillInfo);
		}
		else if ((int)vecSkillPassive.size() > index - lengthVecSkillActiveNeedBuy)
		{
			auto dataSkillInfo = vecSkillPassive[index - lengthVecSkillActiveNeedBuy];
			updateLayoutSKillItem(layoutSkillItem, true, dataSkillInfo);
		}
		else
		{
			updateLayoutSKillItem(layoutSkillItem, false, {});
		}

		index++;
	}
}

void LayerSkills::updateLayoutSKillItem(Layout *layoutSkillItem, const bool &isExsit, const DataSkillInfo &dataSkillInfo)
{
	auto txt = (Text *)layoutSkillItem->getChildByName("txt");
	auto btn = (Button *)layoutSkillItem->getChildByName("btn");
	btn->addTouchEventListener(CC_CALLBACK_2(LayerSkills::onTouchBtnSkillBuy, this, dataSkillInfo));

	if (isExsit)
	{
		auto cfgSkill = ManagerCfg::getInstance()->getDicDicCfgSkill()[dataSkillInfo.id][dataSkillInfo.index];
		txt->setString(cfgSkill.desc);

		btn->setVisible(true);
		auto handleDataUnlock = ManagerData::getInstance()->getHandleDataUnlock();
		auto isUnlock = handleDataUnlock->getIsUnlockSkill(dataSkillInfo.id, dataSkillInfo.index);
		if (!isUnlock)//若未解锁
		{
			btn->setTitleText(STR_UNLOCK);
			btn->setTouchEnabled(false);
		}
		else
		{
			auto isBuy = handleDataUnlock->getIsBuySkill(dataSkillInfo.id, dataSkillInfo.index);
			if (isBuy)//若已购买
			{
				btn->setTitleText(STR_FILLED);
				btn->setTouchEnabled(false);
			}
			else
			{
				btn->setTitleText(STR_BUY);
				btn->setTouchEnabled(true);
			}
		}
	}
	else
	{
		txt->setString("");
		btn->setVisible(false);
	}
}

void LayerSkills::onTouchBtnSkillBuy(Ref *ref, Widget::TouchEventType type, const DataSkillInfo &dataSkillInfo)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		auto id = dataSkillInfo.id;
		auto index = dataSkillInfo.index;

		auto managerData = ManagerData::getInstance();
		auto handleDataIncome = managerData->getHandleDataIncome();
		auto cfgSkill = ManagerCfg::getInstance()->getDicDicCfgSkill()[id][index];//需要花费的金币
		auto isThingEnough = handleDataIncome->getThingEnough(IdThing::GOLD, cfgSkill.buyCost);
		if (!isThingEnough)
		{
			log("`````````` LayerSkills::onTouchBtnSkill gold is not enough");
			return;
		}

		handleDataIncome->addThing(IdThing::GOLD, -cfgSkill.buyCost);
		log("`````````` LayerSkills::onTouchBtnSkill cost:%d,remain:%d", cfgSkill.buyCost, handleDataIncome->getThing(IdThing::GOLD));

		auto handleDataUnlock = managerData->getHandleDataUnlock();
		handleDataUnlock->setIsBuySkill(id, index);
		handleDataUnlock->dataFileSet();

		auto handleDataEntity = managerData->getHandleDataEntity();
		handleDataEntity->getDataEntityMaid()->updateSkillGroup();
		handleDataEntity->getDataEntityMaid()->updateAttributeSkillPassive();
		updateLayoutSkillItems();
	}
}
