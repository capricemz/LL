#pragma execution_character_set("utf-8")

#include "LayerGridShow.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "data/define/DefinesRes.h"
#include "data/define/DefinesValue.h"
#include "core/grid/Grid.h"
#include "ui/ManagerUI.h"
#include "core/grid/ManagerGrid.h"

using namespace ui;

LayerGridShow::LayerGridShow() : _skin(nullptr)
{
}

LayerGridShow::~LayerGridShow()
{
	ManagerGrid::getInstance()->clearDicGridMstShow();
	ManagerGrid::getInstance()->clearDicGridMaidShow();
	ManagerUI::getInstance()->detach(this);
	_skin = nullptr;
}

bool LayerGridShow::init()
{
	auto isInit = false;
	do 
	{
		CC_BREAK_IF(!Layer::init());

		idObserverSet(ID_OBSERVER::LAYER_GRID_SHOW);
		ManagerUI::getInstance()->attach(this);

		createSkin();

		isInit = true;
	} while (0);
	return isInit;
}

void LayerGridShow::updateBySubject(va_list values)
{
	auto type = va_arg(values, TYPE_OBSERVER_LAYER_GRID_SHOW);
	if (type == TYPE_OBSERVER_LAYER_GRID_SHOW::RUN_MAID_GRID_MOVE_FROM_ACTION)
	{
		auto index = va_arg(values, int);
		auto postion = va_arg(values, Vec2);
		/*auto func = va_arg(values, function<void()>);*/
		runMaidGridMoveFromAction(index, postion, nullptr);
	}
	else if (type == TYPE_OBSERVER_LAYER_GRID_SHOW::HIDE_BG)
	{
		hideBg();
	}
}

void LayerGridShow::runAppearAction(const function<void()> &func/* = nullptr*/)
{
	auto d = 0.4f;
	_skin->setVisible(true);
	_skin->setOpacity(0.0f);
	_skin->setScale(10.0f);

	auto actionSpawn = Spawn::createWithTwoActions(EaseCubicActionIn::create(FadeIn::create(d)), EaseCubicActionIn::create(ScaleTo::create(d, 1.0f)));
	auto actionCallFunc = CallFunc::create([func]()
	{
		if (func != nullptr)
		{
			func();
		}
	});
	_skin->runAction(Sequence::create(actionSpawn, actionCallFunc, nullptr));
}

void LayerGridShow::runSkillRandom(const function<void()> &func/* = nullptr*/)
{
	ManagerData::getInstance()->getHandleDataEntity()->dealSkillRandom(func);
}

void LayerGridShow::runMstGridMoveFromAction(const Vec2 &postion, const function<void()> &funcOneOver /*= nullptr*/, const function<void()> &funcAllOver /*= nullptr*/)
{
	Vector<FiniteTimeAction *> vecActions;
	for (int i = 0; i < 4; i++)
	{
		auto actionCallFunc = CallFunc::create([=]()
		{
			Grid *grid = (Grid *)_skin->getChildByName("gridMst" + Value(i).asString());
			grid->moveFrom(postion, true, 0.5f, 0.5f, Vec2(37.5f, 37.5f), funcOneOver);
		});
		vecActions.pushBack(actionCallFunc);
		auto actionDelay = DelayTime::create(0.2f);
		vecActions.pushBack(actionDelay);
	}
	auto actionCallFuncAllOver = CallFunc::create([=]()
	{
		if (funcAllOver != nullptr)
		{
			funcAllOver();
		}
	});
	vecActions.pushBack(actionCallFuncAllOver);
	runAction(Sequence::create(vecActions));
}

void LayerGridShow::runMstGridTurnAction(const function<void()> &funcOneOver /*= nullptr*/, const function<void()> &funcAllOver /*= nullptr*/)
{
	Vector<FiniteTimeAction *> vecActions;
	for (int i = 0; i < 4; i++)
	{
		auto actionCallFunc = CallFunc::create([=]()
		{
			Grid *grid = (Grid *)_skin->getChildByName("gridMst" + Value(i).asString());
			grid->turn(funcOneOver);
		});
		vecActions.pushBack(actionCallFunc);
		auto actionDelay = DelayTime::create(0.1f);
		vecActions.pushBack(actionDelay);
	}
	auto actionCallFuncAllOver = CallFunc::create([=]()
	{
		if (funcAllOver != nullptr)
		{
			funcAllOver();
		}
	});
	vecActions.pushBack(actionCallFuncAllOver);
	runAction(Sequence::create(vecActions));
}

void LayerGridShow::runMaidGridMoveFromAction(const int &indexMaidGrid, const Vec2 &postion, const function<void()> &funcOver /*= nullptr*/)
{
	Grid *grid = (Grid *)_skin->getChildByName("gridMaid" + Value(indexMaidGrid).asString());
	grid->moveFrom(postion, false, 1.0f, 1.0f, Vec2::ZERO, funcOver);
}

void LayerGridShow::createSkin()
{
	_skin = (Layer *)CSLoader::createNode(RES_MODULES_MAIN_LAYER_GRID_SHOW_CSB);
	_skin->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_skin->setPosition(187.0f, 720.0f);
	_skin->setVisible(false);
	addChild(_skin);

	for (int i = 0; i < 8; i++)
	{
		auto isMstGrid = i < 4;
		auto index = i % 4;
		auto grid = Grid::create();
		grid->setIndexGrid(index);
		isMstGrid ? grid->createDataGrid() : nullptr;
		isMstGrid ? grid->createDataGridSkill(true) : nullptr;
		grid->setPosition(isMstGrid ? vecPostionGridShowMst[index] : vecPostionGridShowMaid[index]);
		grid->setName(isMstGrid ? "gridMst" + Value(index).asString() : "gridMaid" + Value(index).asString());
		grid->setVisible(false);
		_skin->addChild(grid);
		auto managerGrid = ManagerGrid::getInstance();
		isMstGrid ? managerGrid->insertGridMstShow(index, grid) : managerGrid->insertGridMaidShow(index, grid);
	}
}

void LayerGridShow::hideBg()
{
	auto children = _skin->getChildren();
	for (auto var : children)
	{
		if (var->getName().find("grid") == string::npos)
		{
			var->setVisible(false);
		}
	}
}
