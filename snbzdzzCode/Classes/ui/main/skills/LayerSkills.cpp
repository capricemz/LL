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
#include "../battle/NodeHead.h"

using namespace ui;
using namespace cocostudio::timeline;

LayerSkills::LayerSkills() :
	_skin(nullptr),
	_uiEntity(nullptr),
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

void LayerSkills::updateSkin()
{
	updateLayoutBtns();
	updateLayoutMaid();
	updateLayoutSkillItems();
}

void LayerSkills::createSkin()
{
	_skin = (Layer *)CSLoader::createNode(RES_MODULES_MAIN_LAYER_SKILLS_CSB);
	addChild(_skin);

	auto actionTimeline = CSLoader::createTimeline(RES_MODULES_MAIN_LAYER_SKILLS_CSB);
	actionTimeline->play(animationHided, false);
	_skin->runAction(actionTimeline);

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
		auto layout = (Layout *)layoutBtns->getChildByName("layout" + Value(index).asString());
		if (layout == nullptr)
		{
			break;
		}
		//在代码里面先获取到button，getComponent()，并把获取的对象强转为Cocos Studio::ComExtensionData* 指针，再调用getCustomProperty()
		cocostudio::ComExtensionData* data = dynamic_cast<cocostudio::ComExtensionData*>(layout->getComponent("ComExtensionData"));
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

			auto nodeHead = NodeHead::create();
			nodeHead->setName("nodeHead" + Value(index).asString());
			nodeHead->updateSkin(TypeNodeHead::MIDDLE, false, idEntity);
			nodeHead->setPosition(layout->getPosition());
			nodeHead->getLayoutBg()->setTouchEnabled(true);
			nodeHead->getLayoutBg()->addTouchEventListener(CC_CALLBACK_2(LayerSkills::onTouchBtnMaid, this));
			nodeHead->getLayoutBg()->setUserData((void *)idEntity);
			layoutBtns->addChild(nodeHead);
		}

		auto nodeHead = (NodeHead *)layoutBtns->getChildByName("nodeHead" + Value(index).asString());
		nodeHead->updateSpriteIcon();
		nodeHead->updateSpriteState();
		
		index++;
	}
}

void LayerSkills::updateLayoutMaid(const bool &isInit /*= false*/)
{
	auto handleDataSkill = ManagerData::getInstance()->getHandleDataSkill();
	auto idEntityCurrent = handleDataSkill->getIdEntityCurrent();

	auto layoutMaid = (Layout *)_skin->getChildByName("layoutMaid");
	auto size = layoutMaid->getContentSize();

	if (_uiEntity == nullptr)
	{
		auto spriteIcon = (Sprite *)layoutMaid->getChildByName("spriteIcon");
		_uiEntity = UIEntity::create();
		_uiEntity->setPosition(spriteIcon->getPosition());
		layoutMaid->addChild(_uiEntity, -1);
	}
	_uiEntity->updateSkin(idEntityCurrent, 1.0f);

	auto handleDataUnlock = ManagerData::getInstance()->getHandleDataUnlock();
	auto isBuy = handleDataUnlock->getIsBuyMaid(idEntityCurrent);
	auto isUnlock = handleDataUnlock->getIsUnlockMaid(idEntityCurrent);

	auto layoutInfo = (Layout *)layoutMaid->getChildByName("layoutInfo");
	if (isUnlock && !isBuy)
	{
		layoutInfo->setVisible(false);
	}
	else
	{
		layoutInfo->setVisible(true);
		auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
		auto vecDataEntityMaid = handleDataEntity->getVecDataEntityMaid();
		for (auto dataEntity : vecDataEntityMaid)
		{
			if (dataEntity->getIdEntity() == idEntityCurrent)
			{
				auto text = ManagerCfg::getInstance()->getDicCfgAttribute()[(int)IdAttribute::ENTITY_HP_MAX].desc;
				auto value = dataEntity->getAttribute(IdAttribute::ENTITY_HP_MAX);
				text += Value(value).asString();
				auto txt = (Text *)layoutInfo->getChildByName("txtAttribute0");
				txt->setString(text);

				text = "";
				txt = (Text *)layoutInfo->getChildByName("txtAttribute1");
				txt->setString(text);

				text = ManagerCfg::getInstance()->getDicCfgAttribute()[(int)IdAttribute::ENTITY_PHYSICAL_ATTACK].desc;
				value = dataEntity->getAttribute(IdAttribute::ENTITY_PHYSICAL_ATTACK);
				text += Value(value).asString();
				txt = (Text *)layoutInfo->getChildByName("txtAttribute2");
				txt->setString(text);

				text = ManagerCfg::getInstance()->getDicCfgAttribute()[(int)IdAttribute::ENTITY_MAGIC_ATTACK].desc;
				value = dataEntity->getAttribute(IdAttribute::ENTITY_MAGIC_ATTACK);
				text += Value(value).asString();
				txt = (Text *)layoutInfo->getChildByName("txtAttribute3");
				txt->setString(text);
				break;
			}
		}
	}

	auto btnGoldBuy = (Button *)layoutMaid->getChildByName("btnGoldBuy");
	btnGoldBuy->setVisible(isUnlock && !isBuy);
	if (btnGoldBuy->isVisible())
	{
		btnGoldBuy->addTouchEventListener(CC_CALLBACK_2(LayerSkills::onTouchBtnMaidBuy, this));
	}
	else
	{
		btnGoldBuy->addTouchEventListener(nullptr);
	}

	auto cfgEntity = ManagerCfg::getInstance()->getDicCfgEntity()[idEntityCurrent];
	auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cfgEntity.urlPicName);
	auto spriteName = (Sprite *)layoutMaid->getChildByName("spriteName");
	spriteName->setSpriteFrame(spriteFrame);

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

	btn = (Button *)layoutMaid->getChildByName("btnLove");
	if (isInit)
	{
		btn->addTouchEventListener(CC_CALLBACK_2(LayerSkills::onTouchSwitchMaidLove, this));
	}
	btn->setBright(isBuy);
	btn->setTouchEnabled(isBuy);
}

void LayerSkills::updateLayoutSkillItems(const bool &isInit /*= false*/)
{
	auto handleDataSkill = ManagerData::getInstance()->getHandleDataSkill();
	auto idEntityCurrent = handleDataSkill->getIdEntityCurrent();

	auto vecdataEntityMaid = ManagerData::getInstance()->getHandleDataEntity()->getVecDataEntityMaid();
	DataEntity *dataEntity = nullptr;
	for (auto var : vecdataEntityMaid)
	{
		if (var->getIdEntity() == idEntityCurrent)
		{
			dataEntity = var;
			break;
		}
	}
	if (dataEntity == nullptr)
	{
		return;
	}

	auto layoutSkillItems = (Layout *)_skin->getChildByName("layoutSkillItems");
	auto layout = (Layout *)layoutSkillItems->getChildByName("layout");
	if (isInit)
	{
		/*layoutSkillItems->setTouchEnabled(true);
		layoutSkillItems->addTouchEventListener(CC_CALLBACK_2(LayerSkills::onTouchSwitchMaidSkill, this));*/
		auto btn = (Button *)layout->getChildByName("btnClose");
		btn->addTouchEventListener(CC_CALLBACK_2(LayerSkills::onTouchSwitchMaidSkill, this));

		btn = (Button *)layout->getChildByName("btnBase");
		btn->addTouchEventListener(CC_CALLBACK_2(LayerSkills::onTouchBtnSkill, this, TypeSkill::BASE));
		btn->setTouchEnabled(false);
		btn = (Button *)layout->getChildByName("btnSpecial");
		btn->addTouchEventListener(CC_CALLBACK_2(LayerSkills::onTouchBtnSkill, this, TypeSkill::SPECIAL));
		btn->setTouchEnabled(false);
		btn = (Button *)layout->getChildByName("btnEnergy");
		btn->addTouchEventListener(CC_CALLBACK_2(LayerSkills::onTouchBtnSkill, this, TypeSkill::ENERGY));
		btn->setTouchEnabled(false);
		btn = (Button *)layout->getChildByName("btnPassive");
		btn->addTouchEventListener(CC_CALLBACK_2(LayerSkills::onTouchBtnSkill, this, TypeSkill::PASSIVE));
		btn->setTouchEnabled(false);
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
	layout = (Layout *)layout->getChildByName("list")->getChildByName("layout");
	auto lengthVec = (int)vecDataSkillInfo.size();
	auto index = 0;
	while (true)
	{
		auto nodeSkillItem = (Layout *)layout->getChildByName("nodeSkillItem" + Value(index).asString());
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
	auto cfgSkill = ManagerCfg::getInstance()->getDicDicCfgSkill()[dataSkillInfo.idSkill][dataSkillInfo.indexSkill];

	auto layoutBg = (Layout *)nodeSkillItem->getChildByName("layoutBg");
	layoutBg->setTouchEnabled(false);

	auto spriteIcon = (Sprite *)nodeSkillItem->getChildByName("spriteIcon");
	auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cfgSkill.urlPic);
	spriteIcon->setSpriteFrame(spriteFrame);
	auto size = spriteFrame->getOriginalSizeInPixels();
	auto scale = size.width > size.height ? sizeSkillIcon.width / size.width : sizeSkillIcon.height / size.height;
	spriteIcon->setScale(scale);

	updateSkinAttribute(nodeSkillItem, cfgSkill);

	auto txt = (Text *)nodeSkillItem->getChildByName("txt");
	txt->setString(cfgSkill.desc);

	auto btn = (Button *)nodeSkillItem->getChildByName("btn");
	btn->addTouchEventListener(CC_CALLBACK_2(LayerSkills::onTouchBtnSkillBuy, this, dataSkillInfo));
	auto isSpecialOrPassive = cfgSkill.type == TypeSkill::SPECIAL || cfgSkill.type == TypeSkill::PASSIVE;
	btn->setVisible(isSpecialOrPassive);
	if (isSpecialOrPassive)
	{
		auto handleDataUnlock = ManagerData::getInstance()->getHandleDataUnlock();
		auto isUnlock = handleDataUnlock->getIsUnlockSkill(dataSkillInfo.idSkill, dataSkillInfo.indexSkill);
		if (!isUnlock)//若未解锁
		{
			btn->setBright(false);
		}
		else
		{
			btn->setBright(true);
			auto isBuy = handleDataUnlock->getIsBuySkill(dataSkillInfo.idSkill, dataSkillInfo.indexSkill);
			btn->setVisible(!isBuy);//若为购买，则显示按钮
		}
	}
}

void LayerSkills::updateSkinAttribute(Node *nodeSkillItem, const CfgSkill &cfgSkill)
{
	nodeSkillItem->getChildByName("layoutGridComplex")->removeAllChildren();
	nodeSkillItem->getChildByName("layoutGridBase1")->removeAllChildren();
	//
	auto count = 0;
	vector<int> countLineBefores = {};//到当前行为止的总数
	vector<float> lineWidths = {};
	vector<float> lineBottom = {};
	float interval = 1.0f;
	auto idAttributeLast = IdAttribute::GRID_DAMAGE_PHYSICAL;
	auto vec = UtilString::split(cfgSkill.effect, "|");
	for (auto var : vec)
	{
		auto vecInfo = UtilString::split(var, ":");
		auto idAttribute = (IdAttribute)Value(vecInfo[0]).asInt();
		auto value = Value(vecInfo[1]).asInt();

		auto cfgAttribute = ManagerCfg::getInstance()->getDicCfgAttribute()[(int)idAttribute];
		if (cfgAttribute.urlPic != "")
		{
			if (cfgAttribute.type == TypeAttribute::GRID_COMPLEX)
			{
				auto remainder = count % 3;
				if (remainder != 0 && value && idAttributeLast != idAttribute)//若余数不为0且有属性值且与之前属性不同
				{
					count += 3 - remainder;//换行显示
				}
				idAttributeLast = idAttribute;
				while (value--)
				{
					auto sprite = Sprite::createWithSpriteFrameName(cfgAttribute.urlPic);
					nodeSkillItem->getChildByName("layoutGridComplex")->addChild(sprite);
					auto line = count / 3;
					auto nodeHeight = sprite->getContentSize().height;
					auto nodeWidth = sprite->getContentSize().width;
					auto countLineBeforeLast = line > 0 ? countLineBefores[line - 1] : 0;
					if ((int)countLineBefores.size() < line + 1)
					{
						countLineBefores.push_back(1 + countLineBeforeLast);
					}
					else
					{
						countLineBefores[line]++;
					}
					auto lineTopLast = line > 0 ? lineBottom[line - 1] : 0.0f;
					if ((int)lineBottom.size() < line + 1)
					{
						lineBottom.push_back(nodeHeight + lineTopLast);
					}
					else if (lineBottom[line] < nodeHeight + lineTopLast)
					{
						lineBottom[line] = nodeHeight;
					}
					if ((int)lineWidths.size() < line + 1)
					{
						lineWidths.push_back(nodeWidth);
					}
					else
					{
						lineWidths[line] += nodeWidth;
					}
					count++;
				}
			}
			else if (cfgAttribute.type == TypeAttribute::GRID_BASE)
			{
				auto sprite = Sprite::createWithSpriteFrameName(cfgAttribute.urlPic);
				Layout *layoutGridBase = nullptr;
				auto isUnblockableOrQuick = cfgAttribute.id == (int)IdAttribute::GRID_UNBLOCKABLE || cfgAttribute.id == (int)IdAttribute::GRID_QUICK;
				if (isUnblockableOrQuick)
				{
					layoutGridBase = (Layout *)nodeSkillItem->getChildByName("layoutGridBase1");
					auto children = layoutGridBase->getChildren();
					auto size = sprite->getContentSize();
					auto postion = Vec2(size.width * 0.5f, size.height * 0.5f);
					if (children.size() > 0)
					{
						auto spriteLast = children.at(children.size() - 1);
						postion = spriteLast->getPosition();
						postion = Vec2(postion.x + spriteLast->getContentSize().width + interval, postion.y);
					}
					sprite->setPosition(postion);
					layoutGridBase->addChild(sprite);
				}
			}
		}
	}
	//
	auto isMiddle = false;
	auto isBottomRight = true;
	auto xPostion = 0.0f;
	auto yPostion = 0.0f;
	count = 0;
	auto children = nodeSkillItem->getChildByName("layoutGridComplex")->getChildren();
	for (auto line = 0; line < (int)countLineBefores.size();)
	{
		auto countLineBefore = countLineBefores[line];
		if (count == 0 || count == countLineBefore)
		{
			if (count != 0)
			{
				line++;
			}
			if (isMiddle)
			{
				xPostion = nodeSkillItem->getChildByName("layoutGridComplex")->getContentSize().width / 2.0f - lineWidths[line] / 2.0f;//行居中行起始x位置
				yPostion = nodeSkillItem->getChildByName("layoutGridComplex")->getContentSize().height / 2.0f + lineBottom[lineBottom.size() - 1] / 2.0f - (line > 0 ? lineBottom[line - 1] : 0.0f);//行居中对齐行y位置
			}
			else if (isBottomRight)
			{
				xPostion = nodeSkillItem->getChildByName("layoutGridComplex")->getContentSize().width;//行右对齐行起始x位置
				yPostion = lineBottom[lineBottom.size() - 1] / 2.0f - (line > 0 ? lineBottom[line - 1] : 0.0f);//行右对齐行y位置
			}
		}
		if (isMiddle)
		{
			auto node = (Node *)children.at(count);
			xPostion += node->getContentSize().width / 2.0f;
			node->setPositionX(xPostion);
			xPostion += node->getContentSize().width / 2.0f;
			node->setPositionY(yPostion + node->getContentSize().height / 2.0f);
		}
		else if (isBottomRight)
		{
			auto node = (Node *)children.at(count);
			xPostion -= node->getContentSize().width / 2.0f;
			node->setPositionX(xPostion);
			xPostion -= node->getContentSize().width / 2.0f;
			node->setPositionY(yPostion/* + node->getContentSize().height / 2.0f*/);
		}

		count++;
		if (count >= (int)children.size())
		{
			break;
		}
	}
	//
	auto layoutAttribute = (Layout *)nodeSkillItem->getChildByName("layoutAttribute");
	layoutAttribute->setTouchEnabled(false);
	layoutAttribute->removeAllChildren();
	interval = 8.0f;
	for (auto var : vec)
	{
		auto vecInfo = UtilString::split(var, ":");
		auto idAttribute = Value(vecInfo[0]).asInt();
		auto value = Value(vecInfo[1]).asInt();

		auto cfgAttribute = ManagerCfg::getInstance()->getDicCfgAttribute()[(int)idAttribute];
		if (cfgAttribute.urlPic != "")
		{
			if (cfgAttribute.type == TypeAttribute::GRID_BASE)
			{
				auto isUnblockableOrQuick = cfgAttribute.id == (int)IdAttribute::GRID_UNBLOCKABLE || cfgAttribute.id == (int)IdAttribute::GRID_QUICK;
				if (!isUnblockableOrQuick)
				{
					auto sprite = Sprite::createWithSpriteFrameName(cfgAttribute.urlPic);
					auto size = sprite->getContentSize();
					auto scale = size.width > size.height ? sizeSkillAttribute.width / size.width : sizeSkillAttribute.height / size.height;
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

					auto txt = Text::create(Value(value).asString(), RES_FONTS_KTJT, 30);
					txt->enableOutline(Color4B::BLACK);
					txt->setPosition(Vec2(postion.x, postion.y));
					layoutAttribute->addChild(txt);
				}
			}
		}
	}
}

void LayerSkills::onTouchBtnMaid(Ref *ref, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		auto layout = (Layout *)ref;
		auto idEntity = (int)layout->getUserData();
		auto handleDataSkill = ManagerData::getInstance()->getHandleDataSkill();
		auto idEntityCurrent = handleDataSkill->getIdEntityCurrent();

		if (idEntityCurrent == idEntity)
		{
			return;
		}
		handleDataSkill->setIdEntityCurrent(idEntity);
		updateLayoutMaid();
		updateLayoutSkillItems();
	}
}

void LayerSkills::onTouchBtnMaidBuy(Ref *ref, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		auto handleDataSkill = ManagerData::getInstance()->getHandleDataSkill();
		auto idEntityCurrent = handleDataSkill->getIdEntityCurrent();

		auto cfgEntity = ManagerCfg::getInstance()->getDicCfgEntity()[idEntityCurrent];
		auto handleDataIncome = ManagerData::getInstance()->getHandleDataIncome();
		auto isThingEnough = handleDataIncome->getThingEnough(IdThing::GOLD, cfgEntity.cost);
		if (!isThingEnough)
		{
			log("`````````` LayerSkills::onTouchBtnMaidBuy gold is not enough");
			return;
		}

		handleDataIncome->addThing(IdThing::GOLD, -cfgEntity.cost);
		handleDataIncome->dataFileSet();
		log("`````````` LayerSkills::onTouchBtnMaidBuy cost:%d,remain:%d", cfgEntity.cost, handleDataIncome->getThing(IdThing::GOLD));
		auto handleDataUnlock = ManagerData::getInstance()->getHandleDataUnlock();
		handleDataUnlock->setIsBuyMaid(idEntityCurrent);
		handleDataUnlock->dataFileSet();
		auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
		handleDataEntity->createDataEntityMaid(idEntityCurrent);//构建女仆数据
		updateSkin();
	}
}

void LayerSkills::onTouchBtnPrev(Ref *ref, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		auto handleDataSkill = ManagerData::getInstance()->getHandleDataSkill();
		auto idEntityCurrent = handleDataSkill->getIdEntityCurrent();

		auto iter = find(_vecShowIdEntity.begin(), _vecShowIdEntity.end(), idEntityCurrent);
		auto index = 0;
		if (iter != _vecShowIdEntity.begin())
		{
			index = (iter - 1) - _vecShowIdEntity.begin();
		}
		else
		{
			index = _vecShowIdEntity.size() - 1;
		}
		handleDataSkill->setIdEntityCurrent(_vecShowIdEntity[index]);
		updateLayoutMaid();
		updateLayoutSkillItems();
	}
}

void LayerSkills::onTouchBtnNext(Ref *ref, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		auto handleDataSkill = ManagerData::getInstance()->getHandleDataSkill();
		auto idEntityCurrent = handleDataSkill->getIdEntityCurrent();

		auto iter = find(_vecShowIdEntity.begin(), _vecShowIdEntity.end(), idEntityCurrent);
		auto index = 0;
		if (iter != _vecShowIdEntity.begin() + _vecShowIdEntity.size() - 1)
		{
			index = (iter + 1) - _vecShowIdEntity.begin();
		}
		else
		{
			index = 0;
		}
		handleDataSkill->setIdEntityCurrent(_vecShowIdEntity[index]);
		updateLayoutMaid();
		updateLayoutSkillItems();
	}
}

void LayerSkills::onTouchSwitchMaidSkill(Ref *ref, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		//显示动画
		auto actionTimeline = (ActionTimeline *)_skin->getActionByTag(_skin->getTag());
		auto currentFrame = actionTimeline->getCurrentFrame();
		if (currentFrame == actionTimeline->getAnimationInfo(animationHided).startIndex)
		{
			actionTimeline->play(animationShow, false);
			actionTimeline->setLastFrameCallFunc([actionTimeline, this]()
			{
				auto layoutSkillItems = (Layout *)_skin->getChildByName("layoutSkillItems");
				auto layout = (Layout *)layoutSkillItems->getChildByName("layout");
				auto btn = (Button *)layout->getChildByName("btnBase");
				btn->setTouchEnabled(true);
				btn = (Button *)layout->getChildByName("btnSpecial");
				btn->setTouchEnabled(true);
				btn = (Button *)layout->getChildByName("btnEnergy");
				btn->setTouchEnabled(true);
				btn = (Button *)layout->getChildByName("btnPassive");
				btn->setTouchEnabled(true);

				actionTimeline->play(animationShowed, false);
				actionTimeline->setLastFrameCallFunc(nullptr);
			});
		}
		else if (currentFrame == actionTimeline->getAnimationInfo(animationShowed).startIndex)
		{
			actionTimeline->play(animationHide, false);
			actionTimeline->setLastFrameCallFunc([actionTimeline, this]()
			{
				auto layoutSkillItems = (Layout *)_skin->getChildByName("layoutSkillItems");
				auto layout = (Layout *)layoutSkillItems->getChildByName("layout");
				auto btn = (Button *)layout->getChildByName("btnBase");
				btn->setTouchEnabled(false);
				btn = (Button *)layout->getChildByName("btnSpecial");
				btn->setTouchEnabled(false);
				btn = (Button *)layout->getChildByName("btnEnergy");
				btn->setTouchEnabled(false);
				btn = (Button *)layout->getChildByName("btnPassive");
				btn->setTouchEnabled(false);

				actionTimeline->play(animationHided, false);
				actionTimeline->setLastFrameCallFunc(nullptr);
			});
		}
	}
}

void LayerSkills::onTouchSwitchMaidLove(Ref *ref, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{

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
		auto id = dataSkillInfo.idSkill;
		auto index = dataSkillInfo.indexSkill;

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
		handleDataIncome->dataFileSet();
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
