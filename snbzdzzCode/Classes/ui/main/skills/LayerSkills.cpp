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

LayerSkills::LayerSkills() :
	_skin(nullptr),
	_uiEntity(nullptr),
	_idEntityCurrent(DATA_UNLOCK_INIT_MAID),
	_vecShowIdEntity({}),
	_typeSkill(TypeSkill::BASE)
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
	updateLayoutBtns();
	updateLayoutMaid();
	updateLayoutSkillItems();
}

void LayerSkills::createSkin()
{
	_skin = (Layer *)CSLoader::createNode(RES_MODULES_MAIN_LAYER_SKILLS_CSB);
	addChild(_skin);

	updateLayoutBtns(true);

	updateLayoutMaid(true);

	updateLayoutSkillItems(true);
}

void LayerSkills::updateLayoutBtns(const bool &isInit /*= false*/)
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
		
		auto handleDataUnlock = ManagerData::getInstance()->getHandleDataUnlock();
		auto isBuy = handleDataUnlock->getIsBuyMaid(idEntity);
		auto isUnlock = handleDataUnlock->getIsUnlockMaid(idEntity);
		
		if (isInit)
		{
			if ((isBuy || (isUnlock && !isBuy)))//若已购买或解锁且未购买
			{
				_vecShowIdEntity.push_back(idEntity);
			}
			btn->addTouchEventListener(CC_CALLBACK_2(LayerSkills::onTouchBtnMaid, this));
		}

		btn->setBright(isUnlock);
		btn->setTouchEnabled(isUnlock);
		
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

void LayerSkills::updateLayoutMaid(const bool &isInit /*= false*/)
{
	auto layoutMaid = (Layout *)_skin->getChildByName("layoutMaid");
	auto size = layoutMaid->getContentSize();

	if (_uiEntity == nullptr)
	{
		_uiEntity = UIEntity::create();
		_uiEntity->setPosition(Vec2(size.width * 0.5f, size.height *0.5f));
		layoutMaid->addChild(_uiEntity, -1);
	}
	_uiEntity->updateSkin(_idEntityCurrent, 1.0f);
	_uiEntity->getLayoutBg()->addTouchEventListener(CC_CALLBACK_2(LayerSkills::onTouchBtnMaidBuy, this));

	auto handleDataUnlock = ManagerData::getInstance()->getHandleDataUnlock();
	auto isBuy = handleDataUnlock->getIsBuyMaid(_idEntityCurrent);
	auto isUnlock = handleDataUnlock->getIsUnlockMaid(_idEntityCurrent);

	auto spriteBuyTip = (Sprite *)layoutMaid->getChildByName("spriteBuyTip");
	spriteBuyTip->setVisible(isUnlock && !isBuy);

	auto cfgEntity = ManagerCfg::getInstance()->getDicCfgEntity()[_idEntityCurrent];
	auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cfgEntity.urlPicName);
	auto spriteNameBg = (Sprite *)layoutMaid->getChildByName("spriteNameBg");
	spriteNameBg->setSpriteFrame(spriteFrame);

	auto btn = (Button *)layoutMaid->getChildByName("btnPrev");
	if (isInit)
	{
		btn->addTouchEventListener(CC_CALLBACK_2(LayerSkills::onTouchBtnPrev, this));
	}
	btn->setBright(_vecShowIdEntity.size() > 1);
	btn->setTouchEnabled(_vecShowIdEntity.size() > 1);

	btn = (Button *)layoutMaid->getChildByName("btnNext");
	if (isInit)
	{
		btn->addTouchEventListener(CC_CALLBACK_2(LayerSkills::onTouchBtnNext, this));
	}
	btn->setBright(_vecShowIdEntity.size() > 1);
	btn->setTouchEnabled(_vecShowIdEntity.size() > 1);

	btn = (Button *)layoutMaid->getChildByName("btnSkill");
	if (isInit)
	{
		btn->addTouchEventListener(CC_CALLBACK_2(LayerSkills::onTouchSwitchMaidSkill, this));
	}
	btn->setBright(isBuy);
	btn->setTouchEnabled(isBuy);
}

void LayerSkills::updateLayoutSkillItems(const bool &isInit /*= false*/)
{
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

	auto layoutSkillItems = (Layout *)_skin->getChildByName("layoutSkillItems");
	if (isInit)
	{
		layoutSkillItems->setTouchEnabled(true);
		layoutSkillItems->addTouchEventListener(CC_CALLBACK_2(LayerSkills::onTouchSwitchMaidSkill, this));
		auto btn = (Button *)layoutSkillItems->getChildByName("btnBase");
		btn->addTouchEventListener(CC_CALLBACK_2(LayerSkills::onTouchBtnSkill, this, TypeSkill::BASE));
		btn = (Button *)layoutSkillItems->getChildByName("btnSpecial");
		btn->addTouchEventListener(CC_CALLBACK_2(LayerSkills::onTouchBtnSkill, this, TypeSkill::SPECIAL));
		btn = (Button *)layoutSkillItems->getChildByName("btnEnergy");
		btn->addTouchEventListener(CC_CALLBACK_2(LayerSkills::onTouchBtnSkill, this, TypeSkill::ENERGY));
		btn = (Button *)layoutSkillItems->getChildByName("btnPassive");
		btn->addTouchEventListener(CC_CALLBACK_2(LayerSkills::onTouchBtnSkill, this, TypeSkill::PASSIVE));
	}


	vector<DataSkillInfo> vecDataSkillInfo;
	if (_typeSkill == TypeSkill::BASE)
	{
		vecDataSkillInfo = dataEntity->getVecSkillBase();
	}
	else if (_typeSkill == TypeSkill::SPECIAL)
	{
		vecDataSkillInfo = dataEntity->getVecSkillSpecial();
	}
	else if (_typeSkill == TypeSkill::ENERGY)
	{
		vecDataSkillInfo = dataEntity->getVecSkillEnergy();
	}
	else if (_typeSkill == TypeSkill::PASSIVE)
	{
		vecDataSkillInfo = dataEntity->getVecSkillPassive();
	}
	auto lengthVec = (int)vecDataSkillInfo.size();
	auto index = 0;
	while (true)
	{
		auto nodeSkillItem = (Layout *)layoutSkillItems->getChildByName("nodeSkillItem" + Value(index).asString());
		if (nodeSkillItem == nullptr)
		{
			break;
		}

		if (lengthVec > index)
		{
			auto dataSkillInfo = vecDataSkillInfo[index];
			updateLayoutSKillItem(nodeSkillItem, true, dataSkillInfo, isInit);
		}
		else
		{
			updateLayoutSKillItem(nodeSkillItem, false, {}, isInit);
		}

		index++;
	}
}

void LayerSkills::updateLayoutSKillItem(Node *nodeSkillItem, const bool &isExsit, const DataSkillInfo &dataSkillInfo, const bool &isInit /*= false*/)
{
	nodeSkillItem->setVisible(isExsit);

	if (!isExsit)
	{
		return;
	}
	auto cfgSkill = ManagerCfg::getInstance()->getDicDicCfgSkill()[dataSkillInfo.id][dataSkillInfo.index];

	auto spriteIcon = (Sprite *)nodeSkillItem->getChildByName("spriteIcon");
	auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cfgSkill.urlPic);
	spriteIcon->setSpriteFrame(spriteFrame);
	auto sizeOriginal = spriteFrame->getOriginalSizeInPixels();
	auto scale = sizeOriginal.width > sizeOriginal.height ? sizeSkillIcon.width / sizeOriginal.width : sizeSkillIcon.height / sizeOriginal.height;
	spriteIcon->setScale(scale);

	auto layoutAttribute = (Layout *)nodeSkillItem->getChildByName("layoutAttribute");
	layoutAttribute->setTouchEnabled(false);
	layoutAttribute->removeAllChildren();
	auto vec = UtilString::split(cfgSkill.effect, "|");
	auto interval = 8.0f;
	for (auto var : vec)
	{
		auto vecInfo = UtilString::split(var, ":");
		auto idAttribute = Value(vecInfo[0]).asInt();
		auto value = Value(vecInfo[1]).asInt();

		auto cfgAttribute = ManagerCfg::getInstance()->getDicCfgAttribute()[(int)idAttribute];
		if (cfgAttribute.urlPic != "")
		{
			auto sprite = Sprite::createWithSpriteFrameName(cfgAttribute.urlPic);
			auto sizeOriginal = spriteFrame->getOriginalSizeInPixels();
			auto scale = sizeOriginal.width > sizeOriginal.height ? sizeSkillAttribute.width / sizeOriginal.width : sizeSkillAttribute.height / sizeOriginal.height;
			sprite->setScale(scale);
			
			auto postion = Vec2(sizeSkillAttribute.width * 0.5f, sizeSkillAttribute.height * 0.5f);

			auto children = layoutAttribute->getChildren();
			if (children.size() > 0)
			{
				auto spriteLast = children.at(children.size() - 1);
				postion = spriteLast->getPosition();
				postion = Vec2(postion.x + sizeSkillAttribute.width + interval, postion.y);
			}
			sprite->setPosition(postion);
			layoutAttribute->addChild(sprite);

			auto isUnblockableOrQuick = cfgAttribute.id == (int)IdAttribute::GRID_UNBLOCKABLE || cfgAttribute.id == (int)IdAttribute::GRID_QUICK;
			if (!isUnblockableOrQuick)
			{
				auto txt = Text::create(Value(value).asString(), RES_FONTS_KTJT, 30);
				txt->enableOutline(Color4B::BLACK);
				txt->setPosition(Vec2(postion.x, postion.y));
				layoutAttribute->addChild(txt);
			}
		}
	}

	auto txt = (Text *)nodeSkillItem->getChildByName("txt");
	txt->setString(cfgSkill.desc);

	auto btn = (Button *)nodeSkillItem->getChildByName("btn");
	btn->addTouchEventListener(CC_CALLBACK_2(LayerSkills::onTouchBtnSkillBuy, this, dataSkillInfo));
	auto isSpecialOrPassive = cfgSkill.type == TypeSkill::SPECIAL || cfgSkill.type == TypeSkill::PASSIVE;
	btn->setVisible(isSpecialOrPassive);
	if (isSpecialOrPassive)
	{
		auto handleDataUnlock = ManagerData::getInstance()->getHandleDataUnlock();
		auto isUnlock = handleDataUnlock->getIsUnlockSkill(dataSkillInfo.id, dataSkillInfo.index);
		if (!isUnlock)//若未解锁
		{
			btn->setBright(false);
		}
		else
		{
			btn->setBright(true);
			auto isBuy = handleDataUnlock->getIsBuySkill(dataSkillInfo.id, dataSkillInfo.index);
			btn->setVisible(!isBuy);//若为购买，则显示按钮
		}
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

void LayerSkills::onTouchBtnMaidBuy(Ref *ref, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		auto cfgEntity = ManagerCfg::getInstance()->getDicCfgEntity()[_idEntityCurrent];
		auto handleDataIncome = ManagerData::getInstance()->getHandleDataIncome();
		if (handleDataIncome->getThingEnough(IdThing::GOLD, cfgEntity.cost))
		{
			handleDataIncome->addThing(IdThing::GOLD, -cfgEntity.cost);
			auto handleDataUnlock = ManagerData::getInstance()->getHandleDataUnlock();
			handleDataUnlock->setIsBuyMaid(_idEntityCurrent);
			handleDataUnlock->dataFileSet();
			updateSkin(_idEntityCurrent);
		}
	}
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
		if (iter != _vecShowIdEntity.end() - 1)
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

void LayerSkills::onTouchSwitchMaidSkill(Ref *ref, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		//显示动画
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
}

void LayerSkills::onTouchBtnSkill(Ref *ref, Widget::TouchEventType type, const TypeSkill &typeSkill)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		_typeSkill = typeSkill;
		updateLayoutSkillItems();
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
