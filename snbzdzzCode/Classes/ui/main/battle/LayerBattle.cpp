#pragma execution_character_set("utf-8")

#include "LayerBattle.h"
#include "cocostudio/CocoStudio.h"
#include "data/define/DefinesRes.h"
#include "data/define/DefinesValue.h"
#include "ui/ManagerUI.h"
#include "common/shake/Shake.h"
#include "core/entity/ManagerEntity.h"

LayerBattle::LayerBattle() : 
	_skin(nullptr),
	_handleEntity(nullptr),
	_handleGridSelected(nullptr),
	_handleHeadIcon(nullptr),
	_handleGridSelect(nullptr),
	_layerGridShow(nullptr),
	_layerBattleResult(nullptr)
{
}

LayerBattle::~LayerBattle()
{
	ManagerUI::getInstance()->detach(this);
	_skin = nullptr;
	CC_SAFE_RELEASE_NULL(_handleEntity);
	CC_SAFE_RELEASE_NULL(_handleGridSelected);
	CC_SAFE_RELEASE_NULL(_handleHeadIcon);
	CC_SAFE_RELEASE_NULL(_handleGridSelect);

	_layerGridShow = nullptr;
	_layerBattleResult = nullptr;
}

bool LayerBattle::init()
{
	auto isInit = false;
	do 
	{
		CC_BREAK_IF(!Layer::init());

		idObserverSet(ID_OBSERVER::LAYER_BATTLE);
		ManagerUI::getInstance()->attach(this);

		createData();

		createSkin();

		isInit = true;
	} while (0);
	return isInit;
}

void LayerBattle::updateBySubject(va_list values)
{
	auto type = va_arg(values, TYPE_OBSERVER_LAYER_BATTLE);
	if(type == TYPE_OBSERVER_LAYER_BATTLE::SHOW_LAYER_GRID_SHOW)
	{
		_layerGridShow = LayerGridShow::create();
		auto layoutGridSelect = (Layout *)_skin->getChildByName("layoutGridSelect");
		layoutGridSelect->addChild(_layerGridShow);
		_layerGridShow->runSkillRandom([this]()
		{
			_layerGridShow->runAppearAction(CC_CALLBACK_0(LayerBattle::funcAfterLayerGridShowRunAppearAction, this));
		});
	}
	else if (type == TYPE_OBSERVER_LAYER_BATTLE::CLOSE_LAYER_GRID_SHOW)
	{
		if (_layerGridShow != nullptr && _layerGridShow->getParent())
		{
			_layerGridShow->removeFromParent();
			_layerGridShow = nullptr;
		}
	}
	else if (type == TYPE_OBSERVER_LAYER_BATTLE::SHOW_LAYER_BATTLE_RESULT)
	{
		auto isWin = va_arg(values, bool);
		_layerBattleResult = LayerBattleResult::create();
		addChild(_layerBattleResult);
		_layerBattleResult->runAppearAction(isWin, nullptr);
	}
	else if(type == TYPE_OBSERVER_LAYER_BATTLE::RESET_SKIN)
	{
		resetSkin();
	}
}

Layer * LayerBattle::getThis()
{
	return this;
}

void LayerBattle::afterRunAppear()
{
	_handleEntity->runEntityAppear();
}

void LayerBattle::afterRunDisAppear()
{
}

void LayerBattle::dealRemoveFromParent()
{
	if (getParent())
	{
		removeFromParent();
	}
}

void LayerBattle::funcAfterLayerGridShowRunAppearAction()
{
	if (_layerGridShow == nullptr)
	{
		return;
	}
	auto actionCallFunc = CallFunc::create([this]()
	{
		auto indexMst = ManagerData::getInstance()->getHandleDataEntity()->getIndexMst();
		auto postion = getPostionHeadIcon(1, indexMst);
		_layerGridShow->runMstGridMoveFromAction(postion, nullptr, CC_CALLBACK_0(LayerBattle::funcAfterRunMstGridMoveFromAction, this));
	});
	runAction(Sequence::create(Shake::create(0.4f, 1.5f), actionCallFunc, nullptr));
}

void LayerBattle::funcAfterRunMstGridMoveFromAction()
{
	if (_layerGridShow == nullptr)
	{
		return;
	}
	auto actionCallFunc = CallFunc::create([this]()
	{
		_layerGridShow->runMstGridTurnAction(nullptr, CC_CALLBACK_0(LayerBattle::funcAfterRunMstGridTurnAction, this));
	});
	runAction(actionCallFunc);
}

void LayerBattle::funcAfterRunMstGridTurnAction()
{
	auto actionCallFunc = CallFunc::create([this]()
	{
		auto indexMaid = ManagerData::getInstance()->getHandleDataEntity()->getIndexMaid();
		runMaidGridMoveFromAction(indexMaid, nullptr, CC_CALLBACK_0(HandleGridSelect::runMaidGridTurnAction, _handleGridSelect, nullptr, nullptr));
	});
	runAction(actionCallFunc);
}

void LayerBattle::runMaidGridMoveFromAction(const int &indexMaid, const function<void()> &funcOneOver /*= nullptr*/, const function<void()> &funcAllOver /*= nullptr*/)
{
	auto postion = getPostionHeadIcon(0, indexMaid);
	_handleGridSelect->runMaidGridMoveFromAction(postion, funcOneOver, funcAllOver);
}

Vec2 LayerBattle::getPostionHeadIcon(const int &type, const int &index)
{
	return _handleHeadIcon->getPostionHeadIcon(type, index);
}

void LayerBattle::createData()
{
	auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
	handleDataEntity->setDataEntityMaidHpFull();
	handleDataEntity->vecSkillActiveSortMaid();
	handleDataEntity->createDataEntityMst();
}

void LayerBattle::createSkin()
{
	_skin = (Layer *)CSLoader::createNode(RES_MODULES_MAIN_LAYER_BATTLE_CSB);
	addChild(_skin);

	auto layoutEntity = (Layout *)_skin->getChildByName("layoutEntity");
	_handleEntity = HandleEntity::create();
	_handleEntity->retain();
	_handleEntity->setSkin(layoutEntity);

	auto layoutGridSelected = (Layout *)_skin->getChildByName("layoutGridSelected");
	_handleGridSelected = HandleGridSelected::create();
	_handleGridSelected->retain();
	_handleGridSelected->setSkin(layoutGridSelected);

	auto layoutHeadIcon = (Layout *)_skin->getChildByName("layoutHeadIcon");
	_handleHeadIcon = HandleHeadIcon::create();
	_handleHeadIcon->retain();
	_handleHeadIcon->setSkin(layoutHeadIcon);

	auto layoutGridSelect = (Layout *)_skin->getChildByName("layoutGridSelect");
	_handleGridSelect = HandleGridSelect::create();
	_handleGridSelect->retain();
	_handleGridSelect->setSkin(layoutGridSelect);
}

void LayerBattle::resetSkin()
{
	_handleEntity->resetSkin();
	_handleGridSelected->resetSkin();
	_handleHeadIcon->resetSkin();
	/*_handleGridSelect->resetSkin();*///不用统一清理
}
