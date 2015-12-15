#pragma execution_character_set("utf-8")

#include "LayerTraining.h"
#include "data/define/DefinesRes.h"
#include "ui/common/UIEntity.h"
#include "data/data/ManagerData.h"
#include "data/config/ManagerCfg.h"

LayerTraining::LayerTraining() : _skin(nullptr), _indexCurrent(0)
{
}

LayerTraining::~LayerTraining()
{
	_skin = nullptr;
}

bool LayerTraining::init()
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

Layer * LayerTraining::getThis()
{
	return this;
}

void LayerTraining::afterRunAppear()
{
}

void LayerTraining::afterRunDisappear()
{
}

void LayerTraining::dealRemoveFromParent()
{
	if (getParent())
	{
		removeFromParent();
	}
}

void LayerTraining::updateSkin(const int &index)
{
	_indexCurrent = index;
	
	auto handleDataIncome = ManagerData::getInstance()->getHandleDataIncome();
	auto dt = handleDataIncome->getDataTrainingInfo(_indexCurrent);

	if (dt == nullptr)
	{
		return;
	}

	updateLayoutSelect();
	updateLayoutTraining();
	updateLayoutEntity();
	updateLayoutCount();
}

void LayerTraining::createSkin()
{
	_skin = (Layer *)CSLoader::createNode(RES_MODULES_MAIN_LAYER_TRAINING_CSB);
	addChild(_skin);

	updateSkin(0);

	updateLayoutBtns();
}

void LayerTraining::updateLayoutSelect()
{

}

void LayerTraining::updateLayoutTraining()
{
	
}

void LayerTraining::updateLayoutEntity()
{
	auto handleDataIncome = ManagerData::getInstance()->getHandleDataIncome();
	auto dt = handleDataIncome->getDataTrainingInfo(_indexCurrent);

	auto idEntity = dt->getIdEntity();

	auto layout = (Layout *)_skin->getChildByName("layoutEntity");
	auto size = layout->getContentSize();

	auto uiEntity = UIEntity::create();
	uiEntity->updateSkin(idEntity, 1.0f);
	uiEntity->setPosition(Vec2(size.width * 0.5f, size.height *0.5f));
	layout->addChild(uiEntity);

	auto cfgEntity = ManagerCfg::getInstance()->getDicCfgEntity()[idEntity];
	auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cfgEntity.urlPicName);
	auto spriteName = (Sprite *)layout->getChildByName("spriteName");
	spriteName->setSpriteFrame(spriteFrame);
}

void LayerTraining::updateLayoutCount()
{

}

void LayerTraining::updateLayoutBtns()
{
	auto layout = (Layout *)_skin->getChildByName("layoutBtn0");//后宫出售调教

	auto btn = (Button *)layout->getChildByName("btn0");
	btn->addTouchEventListener(CC_CALLBACK_2(LayerTraining::onTouchBtnSelect, this));
	btn->setUserData((void *)TypeTrianingSelect::STORE);

	btn = (Button *)_skin->getChildByName("btn1");
	btn->addTouchEventListener(CC_CALLBACK_2(LayerTraining::onTouchBtnSelect, this));
	btn->setUserData((void *)TypeTrianingSelect::SELL);

	btn = (Button *)_skin->getChildByName("btn2");
	btn->addTouchEventListener(CC_CALLBACK_2(LayerTraining::onTouchBtnSelect, this));
	btn->setUserData((void *)TypeTrianingSelect::TRIANING);

	layout = (Layout *)_skin->getChildByName("layoutBtn0");//后宫出售调教

	auto btn = (Button *)layout->getChildByName("btn0");
	btn->addTouchEventListener(CC_CALLBACK_2(LayerTraining::onTouchBtnWay, this));
	btn->setUserData((void *)TypeTrianing::WAY2);

	btn = (Button *)_skin->getChildByName("btn1");
	btn->addTouchEventListener(CC_CALLBACK_2(LayerTraining::onTouchBtnWay, this));
	btn->setUserData((void *)TypeTrianing::WAY1);

	btn = (Button *)_skin->getChildByName("btn2");
	btn->addTouchEventListener(CC_CALLBACK_2(LayerTraining::onTouchBtnWay, this));
	btn->setUserData((void *)TypeTrianing::WAY0);
}

void LayerTraining::onTouchBtnSelect(Ref *ref, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		auto btn = (Button *)ref;
		auto typeTrianingSelect = (TypeTrianingSelect)(int)btn->getUserData();

		auto handleDataIncome = ManagerData::getInstance()->getHandleDataIncome();
		auto dt = handleDataIncome->getDataTrainingInfo(_indexCurrent);

		if (typeTrianingSelect == TypeTrianingSelect::TRIANING)
		{

		}
		else if (typeTrianingSelect == TypeTrianingSelect::SELL)
		{

		}
		else if (typeTrianingSelect == TypeTrianingSelect::STORE)
		{

		}
	}
}

void LayerTraining::onTouchBtnWay(Ref *ref, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		auto btn = (Button *)ref;
		auto typeTrianing = (TypeTrianing)(int)btn->getUserData();

		auto handleDataIncome = ManagerData::getInstance()->getHandleDataIncome();
		auto dt = handleDataIncome->getDataTrainingInfo(_indexCurrent);

	}
}
