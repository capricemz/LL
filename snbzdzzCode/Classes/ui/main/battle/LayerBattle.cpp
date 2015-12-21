#pragma execution_character_set("utf-8")

#include "LayerBattle.h"
#include "cocostudio/CocoStudio.h"
#include "data/define/DefinesRes.h"
#include "data/define/DefinesValue.h"
#include "ui/ManagerUI.h"
#include "common/shake/Shake.h"
#include "core/entity/ManagerEntity.h"
#include "result/LayerBattleResult.h"
#include "catch/LayerCatch.h"

LayerBattle::LayerBattle() : 
	_skin(nullptr),
	_handleEntity(nullptr),
	_handleBg(nullptr),
	_handleHead(nullptr),
	_handleGrid(nullptr),
	_layerGridSelect(nullptr)/*,
	_layerGridShow(nullptr),*/
{
}

LayerBattle::~LayerBattle()
{
	ManagerUI::getInstance()->detach(this);
	_skin = nullptr;
	CC_SAFE_RELEASE_NULL(_handleEntity);
	CC_SAFE_RELEASE_NULL(_handleBg);
	CC_SAFE_RELEASE_NULL(_handleHead);
	CC_SAFE_RELEASE_NULL(_handleGrid);

	_layerGridSelect = nullptr;
	/*_layerGridShow = nullptr;*/
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
	if (type == TYPE_OBSERVER_LAYER_BATTLE::SHOW_APPEAR_GRID_SELECTED_MST)
	{
		showAppearGridSelectedMst();
	}
	else if (type == TYPE_OBSERVER_LAYER_BATTLE::SHOW_LAYER_GRID_SELECT)
	{
		if (_layerGridSelect == nullptr)
		{
			_layerGridSelect = LayerGridSelect::create();
			auto layoutGrid = (Layout *)_skin->getChildByName("layoutGrid");
			layoutGrid->addChild(_layerGridSelect);
		}
		_layerGridSelect->runAppearAction();
	}
	else if (type == TYPE_OBSERVER_LAYER_BATTLE::SHOW_APPEAR_GRID_SELECT_MAID)
	{
		showAppearGridSelectMaid();
	}
	else if (type == TYPE_OBSERVER_LAYER_BATTLE::HIDE_LAYER_GRID_SELECT)
	{
		if (_layerGridSelect != nullptr && _layerGridSelect->getParent())
		{
			_layerGridSelect->runDisappearAction();
		}
	}
	else if (type == TYPE_OBSERVER_LAYER_BATTLE::UPDATE_TXT_ROUND)
	{
		_handleBg->updateTxtRound();
	}
	else if (type == TYPE_OBSERVER_LAYER_BATTLE::SHOW_LAYER_CATCH)
	{
		auto layerCatch = LayerCatch::create();
		addChild(layerCatch);
		layerCatch->runAppearAction(nullptr);
	}
	else if (type == TYPE_OBSERVER_LAYER_BATTLE::SHOW_LAYER_BATTLE_RESULT)
	{
		auto layerBattleResult = LayerBattleResult::create();
		addChild(layerBattleResult);
		layerBattleResult->runAppearAction(nullptr);
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

void LayerBattle::showAppearGridSelectedMst()
{
	auto indexMst = ManagerData::getInstance()->getHandleDataEntity()->getIndexMst();
	auto postion = getPostionHeadIcon(1, /*indexMst*/0);
	_handleGrid->showAppearGridSelectedMst(postion);
}

void LayerBattle::showAppearGridSelectMaid()
{
	if (_layerGridSelect == nullptr)
	{
		return;
	}
	auto indexMaid = ManagerData::getInstance()->getHandleDataEntity()->getIndexMaid();
	auto postion = getPostionHeadIcon(0, /*indexMaid*/0);
	_layerGridSelect->showAppearGridSelectMaid(postion);
}

Vec2 LayerBattle::getPostionHeadIcon(const int &type, const int &index)
{
	return _handleHead->getPostionHeadIcon(type, index);
}

void LayerBattle::createData()
{
	auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
	handleDataEntity->resetDataEntityMaid();
	handleDataEntity->vecSkillActiveSortMaid();
}

void LayerBattle::createSkin()
{
	_skin = (Layer *)CSLoader::createNode(RES_MODULES_MAIN_LAYER_BATTLE_CSB);
	addChild(_skin);

	auto layoutEntity = (Layout *)_skin->getChildByName("layoutEntity");
	_handleEntity = HandleEntity::create();
	_handleEntity->retain();
	_handleEntity->setSkin(layoutEntity);

	auto layoutBg = (Layout *)_skin->getChildByName("layoutBg");
	_handleBg = HandleBg::create();
	_handleBg->retain();
	_handleBg->setSkin(layoutBg);

	auto layoutHead = (Layout *)_skin->getChildByName("layoutHead");
	_handleHead = HandleHead::create();
	_handleHead->retain();
	_handleHead->setSkin(layoutHead);

	auto layoutGrid = (Layout *)_skin->getChildByName("layoutGrid");
	_handleGrid = HandleGrid::create();
	_handleGrid->retain();
	_handleGrid->setSkin(layoutGrid);
}

void LayerBattle::resetSkin()
{
	_handleEntity->resetSkin();
	_handleHead->resetSkin();
	_handleGrid->resetSkin();
	/*_layerGridSelect->resetSkin();*///不用统一清理
}
