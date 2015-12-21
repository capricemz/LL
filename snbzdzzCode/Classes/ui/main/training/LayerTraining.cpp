#pragma execution_character_set("utf-8")

#include "LayerTraining.h"
#include "data/define/DefinesRes.h"
#include "data/data/ManagerData.h"
#include "data/config/ManagerCfg.h"
#include "../battle/NodeHead.h"
#include "ui/ManagerUI.h"
#include "common/util/UtilRandom.h"

LayerTraining::LayerTraining() : _skin(nullptr), _uiEntity(nullptr)
{
}

LayerTraining::~LayerTraining()
{
	_skin = nullptr;
	_uiEntity = nullptr;
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

void LayerTraining::updateSkin()
{
	updateLayoutTraining();
	updateLayoutSelect();
	updateLayoutEntity();
	updateLayoutCount();
	updateLayoutBtns();
}

void LayerTraining::createSkin()
{
	_skin = (Layer *)CSLoader::createNode(RES_MODULES_MAIN_LAYER_TRAINING_CSB);
	addChild(_skin);

	updateSkin();

	initLayoutBtns();
}

void LayerTraining::updateLayoutTraining()
{
	auto handleDataTraining = ManagerData::getInstance()->getHandleDataTraining();
	auto indexCurrent = handleDataTraining->getIndexCurrent();

	auto layout = (Layout *)_skin->getChildByName("layoutTraining");
	auto barPrecent = (LoadingBar *)layout->getChildByName("barPrecent");
	auto txtPrecentValue = (Text *)layout->getChildByName("txtPrecentValue");
	auto layoutLv = (Layout *)layout->getChildByName("layoutLv");

	auto handleDataIncome = ManagerData::getInstance()->getHandleDataIncome();
	auto dt = handleDataIncome->getDataTrainingInfo(indexCurrent);

	if (dt == nullptr)
	{
		barPrecent->setPercent(0.0f);
		txtPrecentValue->setString("0/100");
		layoutLv->setVisible(false);
		return;
	}

	auto idEntity = dt->getIdEntity();
	auto precent = dt->getValuePrecent();

	auto managerCfg = ManagerCfg::getInstance();
	auto cfgEntity = managerCfg->getDicCfgEntity().at(idEntity);
	auto cfgTraining = managerCfg->getDicCfgTraining().at(cfgEntity.idTraining);

	barPrecent->setPercent((float)precent);
	txtPrecentValue->setString(Value(precent).asString() + "/100");

	layoutLv->removeAllChildren();
	auto interval = 8.0f;
	for (auto i = 0; i < cfgTraining.limitMax; i++)
	{
		auto isFull = i < dt->getValueLv();

		auto sprite = Sprite::createWithSpriteFrameName(isFull ? RES_IMAGES_MAIN_LEVELS_XING_PNG : RES_IMAGES_MAIN_LEVELS_XING_KONG_PNG);
		auto size = sprite->getContentSize();
		auto scale = size.width > size.height ? sizeTrainingLv.width / size.width : sizeTrainingLv.height / size.height;
		sprite->setScale(scale);

		auto postion = Vec2(sizeTrainingLv.width * 0.5f, sizeTrainingLv.height * 0.5f);


		auto children = layoutLv->getChildren();
		if (children.size() > 0)
		{
			auto spriteLast = children.at(children.size() - 1);
			postion = spriteLast->getPosition();
			postion = Vec2(postion.x + sizeTrainingLv.width + interval, postion.y);
		}
		sprite->setPosition(postion);
		layoutLv->addChild(sprite);
	}
}

void LayerTraining::updateLayoutSelect()
{
	auto handleDataTraining = ManagerData::getInstance()->getHandleDataTraining();
	auto indexCurrent = handleDataTraining->getIndexCurrent();

	auto layout = (Layout *)_skin->getChildByName("layoutSelect");
	auto listBtns = (ListView *)layout->getChildByName("listBtns");
	auto layoutLv = (Layout *)layout->getChildByName("layoutLv");
	auto txtPrecentValue = (Text *)layout->getChildByName("txtPrecentValue");

	auto handleDataIncome = ManagerData::getInstance()->getHandleDataIncome();
	auto vecDt = handleDataIncome->getVecDataTrainingInfo();
	auto dt = handleDataIncome->getDataTrainingInfo(indexCurrent);

	if (dt == nullptr)
	{
		listBtns->setVisible(false);
		layoutLv->setVisible(false);
		txtPrecentValue->setVisible(false);
		return;
	}

	auto idEntity = dt->getIdEntity();
	auto precent = dt->getValuePrecent();

	auto managerCfg = ManagerCfg::getInstance();
	auto cfgEntity = managerCfg->getDicCfgEntity().at(idEntity);
	auto cfgTraining = managerCfg->getDicCfgTraining().at(cfgEntity.idTraining);
	
	listBtns->removeAllChildren();
	auto interval = 10.0f;
	auto length = (int)vecDt.size();
	for (auto i = 0; i < length; i++)
	{
		auto dt = vecDt.at(i);
		auto nodeHead = NodeHead::create();
		nodeHead->setName("nodeHead" + Value(i).asString());
		nodeHead->updateSkin(TypeNodeHead::MIDDLE, true, dt->getIdEntity());
		auto size = nodeHead->getLayoutBg()->getContentSize();

		auto postion = Vec2(size.width * 0.5f, size.height);

		auto children = listBtns->getChildren();
		if (children.size() > 0)
		{
			auto nodeLast = children.at(children.size() - 1);
			postion = nodeLast->getPosition();
			postion = Vec2(postion.x + size.width + interval, postion.y);
		}

		nodeHead->setPosition(postion);
		listBtns->addChild(nodeHead);
	}

	layoutLv->removeAllChildren();
	interval = 8.0f;
	for (auto i = 0; i < cfgTraining.limitMax; i++)
	{
		auto isFull = i < dt->getValueLv();

		auto sprite = Sprite::createWithSpriteFrameName(isFull ? RES_IMAGES_MAIN_LEVELS_XING_PNG : RES_IMAGES_MAIN_LEVELS_XING_KONG_PNG);
		auto size = sprite->getContentSize();
		auto scale = size.width > size.height ? sizeTrainingLv.width / size.width : sizeTrainingLv.height / size.height;
		sprite->setScale(scale);

		auto postion = Vec2(sizeTrainingLv.width * 0.5f, sizeTrainingLv.height * 0.5f);

		auto children = layoutLv->getChildren();
		if (children.size() > 0)
		{
			auto spriteLast = children.at(children.size() - 1);
			postion = spriteLast->getPosition();
			postion = Vec2(postion.x + sizeTrainingLv.width + interval, postion.y);
		}
		sprite->setPosition(postion);
		layoutLv->addChild(sprite);
	}

	txtPrecentValue->setString(Value(precent).asString() + "/100");
}

void LayerTraining::updateLayoutEntity()
{
	auto handleDataTraining = ManagerData::getInstance()->getHandleDataTraining();
	auto indexCurrent = handleDataTraining->getIndexCurrent();

	auto layout = (Layout *)_skin->getChildByName("layoutEntity");
	auto spriteName = (Sprite *)layout->getChildByName("spriteName");

	auto handleDataIncome = ManagerData::getInstance()->getHandleDataIncome();
	auto dt = handleDataIncome->getDataTrainingInfo(indexCurrent);

	if (dt == nullptr)
	{
		if (_uiEntity != nullptr)
		{
			_uiEntity->setVisible(false);
		}
		spriteName->setVisible(false);
		return;
	}

	auto idEntity = dt->getIdEntity();

	if (_uiEntity == nullptr)
	{
		auto size = layout->getContentSize();
		_uiEntity = UIEntity::create();
		_uiEntity->setPosition(Vec2(size.width * 0.5f, size.height *0.5f));
		layout->addChild(_uiEntity);

		spriteName->setLocalZOrder(1);
	}

	_uiEntity->updateSkin(idEntity, 1.0f);

	auto cfgEntity = ManagerCfg::getInstance()->getDicCfgEntity()[idEntity];
	auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cfgEntity.urlPicName);
	spriteName->setSpriteFrame(spriteFrame);
	
}

void LayerTraining::updateLayoutCount()
{
	auto handleDataIncome = ManagerData::getInstance()->getHandleDataIncome();
	auto value = handleDataIncome->getThing(IdThing::TRAINING);

	auto layout = (Layout *)_skin->getChildByName("layoutCount");
	auto txtCountValue = (Text *)layout->getChildByName("txtCountValue");
	txtCountValue->setString(Value(value).asString() + "/" + Value(TRAINING_NUM_MAX).asString());
}

void LayerTraining::initLayoutBtns()
{
	auto layout = (Layout *)_skin->getChildByName("layoutSelect");//选择容器
	auto listBtns = (ListView *)layout->getChildByName("listBtns");

	auto length = (int)listBtns->getChildrenCount();
	for (auto i = 0; i < length; i++)
	{
		auto node = (NodeHead *)listBtns->getChildByName("nodeHead" + Value(i).asString());
		auto layoutBg = node->getLayoutBg();
		layoutBg->setTouchEnabled(true);
		layoutBg->addTouchEventListener(CC_CALLBACK_2(LayerTraining::onTouchNodeHead, this));
		layoutBg->setUserData((void *)i);
	}

	layout = (Layout *)_skin->getChildByName("layoutTraining");//调教容器
	
	auto btn = (Button *)layout->getChildByName("btnBack");
	btn->addTouchEventListener(CC_CALLBACK_2(LayerTraining::onTouchBtnTrainingSelect, this));

	layout = (Layout *)_skin->getChildByName("layoutBtn0");//后宫出售调教按钮容器

	btn = (Button *)layout->getChildByName("btn0");
	btn->addTouchEventListener(CC_CALLBACK_2(LayerTraining::onTouchBtnSell, this));

	btn = (Button *)layout->getChildByName("btn1");
	btn->addTouchEventListener(CC_CALLBACK_2(LayerTraining::onTouchBtnSell, this));

	btn = (Button *)layout->getChildByName("btn2");
	btn->addTouchEventListener(CC_CALLBACK_2(LayerTraining::onTouchBtnTrainingSelect, this));

	layout = (Layout *)_skin->getChildByName("layoutBtn1");//调教方式按钮容器

	btn = (Button *)layout->getChildByName("btn0");
	btn->addTouchEventListener(CC_CALLBACK_2(LayerTraining::onTouchBtnWay, this));
	btn->setUserData((void *)TypeTrianing::WAY2);

	btn = (Button *)layout->getChildByName("btn1");
	btn->addTouchEventListener(CC_CALLBACK_2(LayerTraining::onTouchBtnWay, this));
	btn->setUserData((void *)TypeTrianing::WAY1);

	btn = (Button *)layout->getChildByName("btn2");
	btn->addTouchEventListener(CC_CALLBACK_2(LayerTraining::onTouchBtnWay, this));
	btn->setUserData((void *)TypeTrianing::WAY0);
}

void LayerTraining::updateLayoutBtns()
{
	auto handleDataTraining = ManagerData::getInstance()->getHandleDataTraining();
	auto indexCurrent = handleDataTraining->getIndexCurrent();

	auto layoutTraining = (Layout *)_skin->getChildByName("layoutTraining");
	auto layoutBtn0 = (Layout *)_skin->getChildByName("layoutBtn0");//后宫出售调教按钮容器
	auto layoutBtn1 = (Layout *)_skin->getChildByName("layoutBtn1");//调教方式按钮容器

	auto handleDataIncome = ManagerData::getInstance()->getHandleDataIncome();
	auto vecDt = handleDataIncome->getVecDataTrainingInfo();
	auto dt = handleDataIncome->getDataTrainingInfo(indexCurrent);

	if (dt == nullptr)
	{
		layoutBtn0->setVisible(false);
		layoutBtn1->setVisible(false);
		return;
	}

	auto idEntity = dt->getIdEntity();
	auto valueLv = dt->getValueLv();
	
	auto managerCfg = ManagerCfg::getInstance();
	auto cfgEntity = managerCfg->getDicCfgEntity().at(idEntity);
	auto cfgTraining = managerCfg->getDicCfgTraining().at(cfgEntity.idTraining);

	auto valueHave = handleDataIncome->getThing((IdThing)cfgTraining.way0CostIdThing);
	auto valueCost = cfgTraining.way0CostValue;
	auto valueWay0 = (int)valueHave / valueCost;
	valueHave = handleDataIncome->getThing((IdThing)cfgTraining.way1CostIdThing);
	valueCost = cfgTraining.way1CostValue;
	auto valueWay1 = (int)valueHave / valueCost;
	valueHave = handleDataIncome->getThing((IdThing)cfgTraining.way2CostIdThing);
	valueCost = cfgTraining.way2CostValue;
	auto valueWay2 = (int)valueHave / valueCost;

	auto isLvMax = valueLv >= TRAINING_NUM_MAX;

	layoutBtn0->setVisible(!layoutTraining->isVisible());

	auto btn = (Button *)layoutBtn0->getChildByName("btn0");//后宫按钮
	btn->setBright(isLvMax);
	btn->setTouchEnabled(isLvMax);

	layoutBtn1->setVisible(layoutTraining->isVisible());

	btn = (Button *)layoutBtn1->getChildByName("btn0");
	btn->setBright(!isLvMax);
	btn->setTouchEnabled(!isLvMax);
	auto txt = (Text *)btn->getChildByName("txtCount");
	txt->setString("X" + Value(valueWay2).asString());

	btn = (Button *)layoutBtn1->getChildByName("btn1");
	btn->setBright(!isLvMax);
	btn->setTouchEnabled(!isLvMax);
	txt = (Text *)btn->getChildByName("txtCount");
	txt->setString("X" + Value(valueWay1).asString());

	btn = (Button *)layoutBtn1->getChildByName("btn2");
	btn->setBright(!isLvMax);
	btn->setTouchEnabled(!isLvMax);
	txt = (Text *)btn->getChildByName("txtCount");
	txt->setString("X" + Value(valueWay0).asString());
}

void LayerTraining::onTouchNodeHead(Ref *ref, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		auto btn = (Button *)ref;
		auto index = (int)btn->getUserData();
		auto handleDataTraining = ManagerData::getInstance()->getHandleDataTraining();
		auto indexCurrent = handleDataTraining->getIndexCurrent();

		if (indexCurrent != index)
		{
			return;
		}
		handleDataTraining->setIndexCurrent(index);
		updateSkin();
	}
}

void LayerTraining::onTouchBtnTrainingSelect(Ref *ref, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		auto layoutTraining = (Layout *)_skin->getChildByName("layoutTraining");
		auto layoutSelect = (Layout *)_skin->getChildByName("layoutSelect");
		auto node = layoutTraining->isVisible() ? layoutTraining : layoutSelect;
		auto nodeNew = layoutTraining->isVisible() ? layoutSelect : layoutTraining;
		nodeNew->setVisible(true);
		auto funcOverNode = [node, this]()
		{
			node->setVisible(false);
			updateLayoutBtns();
		};
		ManagerUI::getInstance()->switchTwoNode(node, nodeNew, funcOverNode);
	}
}

void LayerTraining::onTouchBtnSell(Ref *ref, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		auto btn = (Button *)ref;

		auto handleDataTraining = ManagerData::getInstance()->getHandleDataTraining();
		auto indexCurrent = handleDataTraining->getIndexCurrent();
		auto handleDataIncome = ManagerData::getInstance()->getHandleDataIncome();
		auto vecDt = handleDataIncome->getVecDataTrainingInfo();
		auto dt = handleDataIncome->getDataTrainingInfo(indexCurrent);
		auto idEntity = dt->getIdEntity();
		auto valueLv = dt->getValueLv();
		auto isClothed = dt->getIsClothed();

		auto managerCfg = ManagerCfg::getInstance();
		auto cfgEntity = managerCfg->getDicCfgEntity().at(idEntity);
		auto cfgTraining = managerCfg->getDicCfgTraining().at(cfgEntity.idTraining);

		auto value = cfgTraining.valueLvBase;
		value += valueLv * cfgTraining.valueLvAdd;
		value += valueLv >= TRAINING_NUM_MAX ? cfgTraining.valueLvFull : 0;
		value += isClothed ? cfgTraining.valueOther : 0;

		handleDataIncome->addThing(IdThing::GOLD, value);
		handleDataIncome->earseVecDataTrainingInfo(indexCurrent);
		handleDataIncome->dataFileSet();
		updateSkin();
	}
}

void LayerTraining::onTouchBtnWay(Ref *ref, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		auto btn = (Button *)ref;
		auto typeTrianing = (TypeTrianing)(int)btn->getUserData();

		auto handleDataTraining = ManagerData::getInstance()->getHandleDataTraining();
		auto indexCurrent = handleDataTraining->getIndexCurrent();
		auto handleDataIncome = ManagerData::getInstance()->getHandleDataIncome();
		auto dt = handleDataIncome->getDataTrainingInfo(indexCurrent);
		auto idEntity = dt->getIdEntity();

		auto managerCfg = ManagerCfg::getInstance();
		auto cfgEntity = managerCfg->getDicCfgEntity().at(idEntity);
		auto cfgTraining = managerCfg->getDicCfgTraining().at(cfgEntity.idTraining);

		IdThing wayCostIdThing = IdThing::THING_NONE;
		int wayCostValue = 0;
		int wayAddPrecent = 0;
		switch (typeTrianing)
		{
		case TypeTrianing::WAY0:
			wayCostIdThing = (IdThing)cfgTraining.way0CostIdThing;
			wayCostValue = cfgTraining.way0CostValue;
			wayAddPrecent = cfgTraining.way0AddPrecent;
			break;
		case TypeTrianing::WAY1:
			wayCostIdThing = (IdThing)cfgTraining.way1CostIdThing;
			wayCostValue = cfgTraining.way1CostValue;
			wayAddPrecent = cfgTraining.way1AddPrecent;
			break;
		case TypeTrianing::WAY2:
			wayCostIdThing = (IdThing)cfgTraining.way2CostIdThing;
			wayCostValue = cfgTraining.way2CostValue;
			wayAddPrecent = cfgTraining.way2AddPrecent;
			break;
		case TypeTrianing::NONE:
		default:
			break;
		}
		auto isRemain = handleDataIncome->getThingEnough(IdThing::TRAINING, 1);
		auto isEnough = handleDataIncome->getThingEnough(wayCostIdThing, wayCostValue);
		if (!isRemain)
		{
			log("LayerTraining::onTouchBtnWay remain not enough");
			return;
		}
		if (!isEnough)
		{
			log("LayerTraining::onTouchBtnWay gold not enough");
			return;
		}
		handleDataIncome->addThing(IdThing::GOLD, -wayCostValue);
		auto valuePrecent = dt->getValuePrecent();
		auto valuePrecentAdd = (int)UtilRandom::randomWave((float)wayAddPrecent);
		if (wayAddPrecent >= 100 || valuePrecent + valuePrecentAdd >= 100)
		{
			auto valueLv = dt->getValueLv();
			dt->setValueLv(++valueLv);
			dt->setValuePrecent(0);
		}
		else
		{
			dt->setValuePrecent(valuePrecent + valuePrecentAdd);
		}
		handleDataIncome->addThing(IdThing::TRAINING, -1);
		handleDataIncome->dataFileSet();
		updateSkin();
	}
}
