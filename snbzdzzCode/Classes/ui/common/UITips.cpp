#pragma execution_character_set("utf-8")

#include "UITips.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "data/config/ManagerCfg.h"
#include "data/define/DefinesValue.h"
#include "data/define/DefinesRes.h"
#include "data/define/DefinesString.h"

using namespace ui;

UITips::UITips()
{
}

UITips::~UITips()
{
}

void UITips::show(const TypeTips &type, const Vec2 &postion, const int &id)
{
	if (type == TypeTips::ERRORS || type == TypeTips::THING_UNLOCK || type == TypeTips::MONSTER)//直接弹出且持续一段时间后自动消失
	{
		hide();
		auto actionCallFunc = CallFunc::create(CC_CALLBACK_0(UITips::showCallFunc, this, type, postion, id));
		auto actionDelay = DelayTime::create(type == TypeTips::THING_UNLOCK || type == TypeTips::MONSTER ? 3.0f : 1.0f);
		auto actionCallFunc1 = CallFunc::create(CC_CALLBACK_0(UITips::hide, this));
		runAction(Sequence::create(actionCallFunc, actionDelay, actionCallFunc1, nullptr));
	}
	else
	{
		auto actionDelay = DelayTime::create(0.2f);
		auto actionCallFunc = CallFunc::create(CC_CALLBACK_0(UITips::showCallFunc, this, type, postion, id));
		runAction(Sequence::create(actionDelay, actionCallFunc, nullptr));
	}
}

void UITips::showCallFunc(const TypeTips &type, const Vec2 &postion, const int &id)
{
	/*auto node = CSLoader::createNode(UI_COMMON_TIPS);
	switch (type)
	{
	default:
	case TypeTips::THING:
	case TypeTips::THING_UNLOCK:
		createTipThing(node, postion, id);
		break;
	case TypeTips::MONSTER:
		createTipMonster(node, postion, id);
		break;
	case TypeTips::SKILL:
		createTipSkill(node, postion, id);
		break;
	case TypeTips::TARGET_AWARD:
		createTipTargetAward(node, postion, id);
		break;
	case TypeTips::ERRORS:
		createTipErrors(node, postion, id);
		break;
	}*/
}

void UITips::createTipThing(Node *node, const Vec2 &postion, const int &idThing)
{
	/*auto skin = (Layout *)node->getChildByName("tipThing");
	auto bg = (ImageView *)skin->getChildByName("bg");
	auto txtName = (Text *)skin->getChildByName("txtName");
	auto txtType = (Text *)skin->getChildByName("txtType");
	auto txtDesc = (Text *)skin->getChildByName("txtDesc");
	//
	auto isLeftOut = postion.x - skin->getContentSize().width * skin->getAnchorPoint().x < 0;
	auto isDownOut = postion.y - skin->getContentSize().height * skin->getAnchorPoint().y < 0;
	if (isLeftOut && !isDownOut)
	{
		bg->setScaleX(-1);
		skin->setAnchorPoint(Vec2(0.15f, 1.0f));
	}
	else if (isLeftOut && isDownOut)
	{
		bg->setScaleX(-1);
		bg->setScaleY(-1);
		skin->setAnchorPoint(Vec2(0.15f, 0.0f));
		txtName->setPositionY(txtName->getPositionY() + 20.0f);
		txtType->setPositionY(txtType->getPositionY() + 20.0f);
		txtDesc->setPositionY(txtDesc->getPositionY() + 20.0f);
	}
	else if (!isLeftOut && isDownOut)
	{
		bg->setScaleY(-1);
		skin->setAnchorPoint(Vec2(0.85f, 0.0f));
		txtName->setPositionY(txtName->getPositionY() + 20.0f);
		txtType->setPositionY(txtType->getPositionY() + 20.0f);
		txtDesc->setPositionY(txtDesc->getPositionY() + 20.0f);
	}
	//
	skin->setName("skin");
	skin->removeFromParentAndCleanup(false);
	skin->setPosition(postion);
	addChild(skin);
	//
	auto cfgThing = ManagerCfg::getInstance()->dicCfgThingGet()[idThing];
	//
	txtName->setString(cfgThing.name);
	//
	if (cfgThing.type == TypeThing::INGREDIENTS)
	{
		txtType->setString(vecThingDouble[cfgThing.typeSub]);
	}
	else if (cfgThing.type == TypeThing::UNLOCK)
	{
		txtType->setString(STR_FOOD_UNLOCK);
	}
	else
	{
		txtType->setString("");
	}
	//
	txtDesc->setString(cfgThing.desc);*/
}

void UITips::createTipMonster(Node *node, const Vec2 &postion, const int &idRegion)
{
	/*auto skin = (Layout *)node->getChildByName("tipMonster");
	auto bg = (ImageView *)skin->getChildByName("bg");
	auto txtName = (Text *)skin->getChildByName("txtName");
	auto txtDesc1 = (Text *)skin->getChildByName("txtDesc1");
	auto txtDesc2 = (Text *)skin->getChildByName("txtDesc2");
	auto txtDesc3 = (Text *)skin->getChildByName("txtDesc3");
	//
	auto isLeftOut = postion.x - skin->getContentSize().width * skin->getAnchorPoint().x < 0;
	auto isDownOut = postion.y - skin->getContentSize().height * skin->getAnchorPoint().y < 0;
	if (isLeftOut && !isDownOut)
	{
		bg->setScaleX(-1);
		skin->setAnchorPoint(Vec2(0.15f, 1.0f));
	}
	else if (isLeftOut && isDownOut)
	{
		bg->setScaleX(-1);
		bg->setScaleY(-1);
		skin->setAnchorPoint(Vec2(0.15f, 0.0f));
		txtName->setPositionY(txtName->getPositionY() + 20.0f);
		txtDesc1->setPositionY(txtDesc1->getPositionY() + 20.0f);
		txtDesc2->setPositionY(txtDesc2->getPositionY() + 20.0f);
		txtDesc3->setPositionY(txtDesc3->getPositionY() + 20.0f);
	}
	else if (!isLeftOut && isDownOut)
	{
		bg->setScaleY(-1);
		skin->setAnchorPoint(Vec2(0.85f, 0.0f));
		txtName->setPositionY(txtName->getPositionY() + 20.0f);
		txtDesc1->setPositionY(txtDesc1->getPositionY() + 20.0f);
		txtDesc2->setPositionY(txtDesc2->getPositionY() + 20.0f);
		txtDesc3->setPositionY(txtDesc3->getPositionY() + 20.0f);
	}
	//
	skin->setName("skin");
	skin->removeFromParentAndCleanup(false);
	skin->setPosition(postion);
	addChild(skin);
	//
	auto cfgRegion = ManagerCfg::getInstance()->dicCfgRegionGet()[idRegion];
	//
	auto vec = UtilString::split(cfgRegion.desc, "|");
	txtName->setString(vec.size() > 0 ? vec[0] : "");
	txtDesc1->setString(vec.size() > 1 ? vec[1] : "");
	txtDesc2->setString(vec.size() > 2 ? vec[2] : "");
	txtDesc3->setString(vec.size() > 3 ? vec[3] : "");*/
}

void UITips::createTipSkill(Node *node, const Vec2 &postion, const int &idDataEntityAttr)
{
	/*auto skin = (ImageView *)node->getChildByName("tipSkill");
	skin->setName("skin");
	skin->removeFromParentAndCleanup(false);
	skin->setPosition(postion);
	addChild(skin);
	//
	auto txtAtk = (Text *)skin->getChildByName("txtAtk");
	txtAtk->setString(STR_GONGJI_XIAOGUOWU);
	auto txtDef = (Text *)skin->getChildByName("txtDef");
	txtDef->setString(STR_BEIJI_XIAOGUOWU);
	auto txtCtk = (Text *)skin->getChildByName("txtCtk");
	txtCtk->setString(STR_FANGJI_XIAOGUOWU);
	auto dataEntityAttr = ManagerData::getInstance()->dicDataEntityAttrGet()[idDataEntityAttr];
	for (auto var : dataEntityAttr.skill)
	{
		auto cfgThing = ManagerCfg::getInstance()->dicCfgThingGet()[Value(UtilString::split(var.second, ";")[0]).asInt()];
		auto iter = cfgThing.argsSkill.begin();
		if (iter == cfgThing.argsSkill.end())
		{
			continue;
		}
		auto cfgSkill = ManagerCfg::getInstance()->dicCfgSkillGet()[iter->first];
		if (var.first == TypeSkillTime::ATK)
		{
			txtAtk->setString(STR_GONGJI_XIAOGUO + cfgSkill.desc);
		}
		else if (var.first == TypeSkillTime::DEF)
		{
			txtDef->setString(STR_BEIJI_XIAOGUO + cfgSkill.desc);
		}
		else if (var.first == TypeSkillTime::CTK)
		{
			txtCtk->setString(STR_FANGJI_XIAOGUO + cfgSkill.desc);
		}
	}*/
}

void UITips::createTipTargetAward(Node *node, const Vec2 &postion, const int &idTargetAward)
{
	/*if (idTargetAward == -1)
	{
		return;
	}
	auto skin = (ImageView *)node->getChildByName("tipTargetAward");
	skin->setName("skin");
	skin->removeFromParentAndCleanup(false);
	skin->setPosition(postion);
	addChild(skin);
	//
	auto cfgTargetAward = ManagerCfg::getInstance()->dicCfgTargetAwardGet()[idTargetAward];
	auto cfgThing = ManagerCfg::getInstance()->dicCfgThingGet()[cfgTargetAward.award];
	//
	auto spriteIconBg = (Sprite *)skin->getChildByName("spriteIconBg");
	auto spriteIcon = (Sprite *)spriteIconBg->getChildByName("spriteIcon");
	if (!spriteIcon)
	{
		spriteIcon = Sprite::create();
		spriteIcon->setName("spriteIcon");
		spriteIcon->setPosition(spriteIconBg->getContentSize().width / 2.0f, spriteIconBg->getContentSize().height / 2.0f);
		spriteIconBg->addChild(spriteIcon);
	}
	auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(ICON_THING_ + cfgThing.urlPic);
	spriteIcon->setSpriteFrame(spriteFrame);
	auto sizeOriginal = spriteIcon->getContentSize();
	auto scale = sizeOriginal.width > sizeOriginal.height ? 64.0f / sizeOriginal.width : 64.0f / sizeOriginal.height;
	spriteIcon->setScale(scale);
	//
	auto txtDesc = (Text *)skin->getChildByName("txtDesc");
	txtDesc->setString(cfgTargetAward.desc);
	//
	auto txtNum = (Text *)skin->getChildByName("txtNum");
	txtNum->setString("x" + Value(cfgTargetAward.num).asString());*/
}

void UITips::createTipErrors(Node *node, const Vec2 &postion, const int &idError)
{
	auto skin = (Layout *)node->getChildByName("tipError");
	auto bg = (ImageView *)skin->getChildByName("bg");
	auto txtDesc = (Text *)skin->getChildByName("txtDesc");
	//
	auto isLeftOut = postion.x - skin->getContentSize().width * skin->getAnchorPoint().x < 0;
	auto isDownOut = postion.y - skin->getContentSize().height * skin->getAnchorPoint().y < 0;
	if (isLeftOut && !isDownOut)
	{
		bg->setScaleX(-1);
		skin->setAnchorPoint(Vec2(0.15f, 1.0f));
	}
	else if (isLeftOut && isDownOut)
	{
		bg->setScaleX(-1);
		bg->setScaleY(-1);
		skin->setAnchorPoint(Vec2(0.15f, 0.0f));
		txtDesc->setPositionY(txtDesc->getPositionY() + 20.0f);
	}
	else if (!isLeftOut && isDownOut)
	{
		bg->setScaleY(-1);
		skin->setAnchorPoint(Vec2(0.85f, 0.0f));
		txtDesc->setPositionY(txtDesc->getPositionY() + 20.0f);
	}
	skin->setName("skin");
	skin->removeFromParentAndCleanup(false);
	skin->setPosition(postion);
	addChild(skin);
	//
	txtDesc->setString(vecError[idError]);
}

bool UITips::isShowed()
{
	auto skin = getChildByName("skin");
	return skin != nullptr && skin->getParent() != nullptr;
}

void UITips::hide()
{
	stopAllActions();
	auto skin = getChildByName("skin");
	if (skin)
	{
		skin->removeFromParent();
	}
}
