#pragma execution_character_set("utf-8")

#include "LayerTraining.h"
#include "data/define/DefinesRes.h"
#include "../guild/UIEntity.h"
#include "data/data/ManagerData.h"

LayerTraining::LayerTraining() : _skin(nullptr)
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
	auto dataIncome = ManagerData::getInstance()->getHandleDataIncome()->getDataIncome();
	auto idEntity = dataIncome->getVecIdEntityCatched().at(index);

	auto layout = (Layout *)_skin->getChildByName("layoutContent");
	auto size = layout->getContentSize();

	auto uiEntity = UIEntity::create();
	uiEntity->updateSkin(idEntity, 1.0f);
	uiEntity->setPosition(Vec2(size.width * 0.5f, size.height *0.5f));
	layout->addChild(uiEntity);
}

void LayerTraining::createSkin()
{
	_skin = (Layer *)CSLoader::createNode(RES_MODULES_MAIN_LAYER_TRAINING_CSB);
	addChild(_skin);

	updateSkin(0);

	auto btn = (Button *)_skin->getChildByName("btn0");
	btn->addTouchEventListener(CC_CALLBACK_2(LayerTraining::onTouchBtn, this));
	btn->setUserData((void *)TypeTrianing::WAY0);

	btn = (Button *)_skin->getChildByName("btn1");
	btn->addTouchEventListener(CC_CALLBACK_2(LayerTraining::onTouchBtn, this));
	btn->setUserData((void *)TypeTrianing::WAY1);

	btn = (Button *)_skin->getChildByName("btn2");
	btn->addTouchEventListener(CC_CALLBACK_2(LayerTraining::onTouchBtn, this));
	btn->setUserData((void *)TypeTrianing::WAY2);

	btn = (Button *)_skin->getChildByName("btn3");
	btn->addTouchEventListener(CC_CALLBACK_2(LayerTraining::onTouchBtn, this));
	btn->setUserData((void *)TypeTrianing::WAY3);
}

void LayerTraining::onTouchBtn(Ref *ref, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		auto btn = (Button *)ref;
		auto typeTrianing = (TypeTrianing)(int)btn->getUserData();

	}
}
