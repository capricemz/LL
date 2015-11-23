#pragma execution_character_set("utf-8")

#include "HandleGrid.h"
#include "ui/ManagerUI.h"
#include "core/grid/Grid.h"
#include "core/grid/ManagerGrid.h"

HandleGrid::HandleGrid() : _skin(nullptr)
{
}

HandleGrid::~HandleGrid()
{
	ManagerUI::getInstance()->detach(this);
	_skin = nullptr;
}

bool HandleGrid::init()
{
	auto isInit = false;
	do
	{
		idObserverSet(ID_OBSERVER::HANDLE_GRID);
		ManagerUI::getInstance()->attach(this);

		isInit = true;
	} while (0);
	return isInit;
}

void HandleGrid::setSkin(Layout *skin)
{
	_skin = skin;
	for (int i = 0; i < GRID_SELECTED_MAX * 2; i++)//隔间选中格子
	{
		auto isMst = i < GRID_SELECTED_MAX;
		auto index = i % GRID_SELECTED_MAX;

		auto postion = ManagerData::getInstance()->getHandleDataGrid()->postionGridSelectedGet(isMst, index);
		auto name = isMst ? "gridSelectedMst" + Value(index).asString() : "gridSelectedMaid" + Value(index).asString();

		auto grid = Grid::create();
		grid->setIndexGrid(index);
		isMst ? grid->createDataGrid() : nullptr;
		isMst ? grid->createDataGridSkill(true) : nullptr;
		grid->setPosition(postion);
		grid->setName(name);
		grid->setVisible(false);
		_skin->addChild(grid);

		auto managerGrid = ManagerGrid::getInstance();
		isMst ? managerGrid->insertGridMstSelected(index, grid) : managerGrid->insertGridMaidSelected(index, grid);
	}
	for (auto i = 0; i < 2; i++)//构建战斗格子
	{
		auto isMst = i < 1;
		auto grid = Grid::create();
		grid->setIndexGrid(i);
		grid->setPosition(vecPostionGridBattle[i]);
		grid->setName(isMst ? "gridBattleMst" : "gridBattleMaid");
		grid->setVisible(false);
		_skin->addChild(grid);
		ManagerGrid::getInstance()->insertGridBattle(i, grid);
	}
}

void HandleGrid::updateBySubject(va_list values)
{
	auto type = va_arg(values, TYPE_OBSERVER_HANDLE_GRID);
	if (type == TYPE_OBSERVER_HANDLE_GRID::RUN_ACTION_GRID_SELECTED_MOVE_FROM_SELECT)
	{
		auto indexGridSelected = va_arg(values, int);
		auto indexGridSelect = va_arg(values, int);
		runActionGridSelectedMaidMoveFromSelect(indexGridSelected, indexGridSelect);
	}
	else if (type == TYPE_OBSERVER_HANDLE_GRID::RUN_GRID_MOVE_AND_THROW)
	{
		runGridMoveAndThrow();
	}
	else if (type == TYPE_OBSERVER_HANDLE_GRID::UPDATE_GRID)
	{
		auto idDataGrid = va_arg(values, int);
		updateGrid(idDataGrid);
	}
}

void HandleGrid::showAppearGridSelectedMst(const Vec2 &postion)
{
	runActionGridSelectedMstMoveFrom(postion, nullptr, CC_CALLBACK_0(HandleGrid::runActionGridSelectedMstTurn, this, nullptr, []()
	{
		ManagerUI::getInstance()->notify(ID_OBSERVER::LAYER_BATTLE, TYPE_OBSERVER_LAYER_BATTLE::SHOW_LAYER_GRID_SELECT);
	}));
}

void HandleGrid::runActionGridSelectedMaidMoveFromSelect(const int &indexGridSelected, const int &indexGridSelect)
{
	auto gridSelect = (Grid *)ManagerGrid::getInstance()->getDicGridMaidSelect().at(indexGridSelect);
	auto postion = gridSelect->getLayoutTouch()->getWorldPosition();
	Grid *grid = (Grid *)_skin->getChildByName("gridSelectedMaid" + Value(indexGridSelected).asString());
	grid->moveFrom(postion, false, 1.0f, 1.0f, Vec2::ZERO, nullptr);
}

void HandleGrid::resetSkin()
{
	for (int i = 0; i < GRID_SELECTED_MAX * 2; i++)
	{
		auto isMst = i < GRID_SELECTED_MAX;
		auto index = i % GRID_SELECTED_MAX;
		auto grid = _skin->getChildByName(isMst ? "gridSelectedMst" + Value(index).asString() : "gridSelectedMaid" + Value(index).asString());
		grid->setVisible(false);
	}
	for (int i = 0; i < 2; i++)
	{
		auto isMst = i < 1;
		auto grid = (Grid *)_skin->getChildByName(isMst ? "gridBattleMst" : "gridBattleMaid");
		grid->setVisible(false);
	}
}

void HandleGrid::runActionGridSelectedMstMoveFrom(const Vec2 &postion, const function<void()> &funcOneOver /*= nullptr*/, const function<void()> &funcAllOver /*= nullptr*/)
{
	Vector<FiniteTimeAction *> vecActions;
	for (int i = 0; i < GRID_SELECTED_MAX; i++)
	{
		auto actionCallFunc = CallFunc::create([=]()
		{
			Grid *grid = (Grid *)_skin->getChildByName("gridSelectedMst" + Value(i).asString());
			grid->moveFrom(postion, true, 0.5f, 0.5f, Vec2(37.5f, 37.5f), funcOneOver);
		});
		vecActions.pushBack(actionCallFunc);
		auto actionDelay = DelayTime::create(0.2f);
		vecActions.pushBack(actionDelay);
	}
	if (funcAllOver != nullptr)
	{
		auto actionCallFuncAllOver = CallFunc::create([=]()
		{
			funcAllOver();
		});
		vecActions.pushBack(actionCallFuncAllOver);
	}
	_skin->runAction(Sequence::create(vecActions));
}

void HandleGrid::runActionGridSelectedMstTurn(const function<void()> &funcOneOver /*= nullptr*/, const function<void()> &funcAllOver /*= nullptr*/)
{
	Vector<FiniteTimeAction *> vecActions;
	for (int i = 0; i < GRID_SELECTED_MAX; i++)
	{
		auto actionCallFunc = CallFunc::create([=]()
		{
			Grid *grid = (Grid *)_skin->getChildByName("gridSelectedMst" + Value(i).asString());
			grid->turn(funcOneOver);
		});
		vecActions.pushBack(actionCallFunc);
		auto actionDelay = DelayTime::create(0.1f);
		vecActions.pushBack(actionDelay);
	}
	if (funcAllOver != nullptr)
	{
		auto actionCallFuncAllOver = CallFunc::create([=]()
		{
			funcAllOver();
		});
		vecActions.pushBack(actionCallFuncAllOver);
	}
	_skin->runAction(Sequence::create(vecActions));
}

void HandleGrid::runGridMoveAndThrow()
{
	auto indexGrid = ManagerData::getInstance()->getHandleDataGrid()->getIndexGridBattle();
	/*log("``````````HandleEntity::executeGrid indexGrid:%d", indexGrid);*/
	gridMoveFrom(indexGrid);
}

void HandleGrid::gridMoveFrom(const int &indexGrid)
{
	for (int i = 0; i < 2; i++)
	{
		auto isMst = i < 1;
		auto managerGrid = ManagerGrid::getInstance();
		auto gridSelected = (Grid *)isMst ? managerGrid->getDicGridMstSelected().at(indexGrid) : managerGrid->getDicGridMaidSelected().at(indexGrid);
		gridSelected->setVisible(false);
		auto dataGrid = gridSelected->getDataGrid();
		auto postion = gridSelected->getLayoutTouch()->getWorldPosition();
		auto grid = (Grid *)_skin->getChildByName(isMst ? "gridBattleMst" : "gridBattleMaid");
		grid->setDataGrid(dataGrid);
		grid->moveFrom(postion, false, 0.5f, 1.0f, Vec2::ZERO, CC_CALLBACK_0(HandleGrid::gridMoveFromOver, this, grid, isMst));
	}
}

void HandleGrid::gridMoveFromOver(Grid *grid, const bool &isMst)
{
	if (grid->getIsCard())
	{
		ManagerUI::getInstance()->notify(ID_OBSERVER::HANDLE_ENTITY, TYPE_OBSERVER_HANDLE_ENTITY::RUN_BACKGROUND_EFFECT);//播放实体背景特效
		auto postion = grid->getParent()->convertToWorldSpace(vecPostionGridBattle[2]);
		grid->throwTo(postion, isMst ? 60.0f : -60.0f, CC_CALLBACK_0(HandleGrid::gridThrowToOrPlayOver, this, grid, isMst));
	}
	else
	{
		grid->playSpecialSthBeUse(CC_CALLBACK_0(HandleGrid::gridThrowToOrPlayOver, this, grid, isMst));
	}
}

void HandleGrid::gridThrowToOrPlayOver(Grid *grid, const bool &isMst)
{
	grid->resetSkin();
	grid->setVisible(false);

	if (!isMst)
	{
		ManagerGrid::getInstance()->dealBattle();
	}
}

void HandleGrid::updateGrid(const int &idDataGrid)
{
	for (int i = 0; i < GRID_SELECTED_MAX * 2; i++)
	{
		auto isMst = i < GRID_SELECTED_MAX;
		auto index = i % GRID_SELECTED_MAX;
		auto grid = (Grid *)_skin->getChildByName(isMst ? "gridSelectedMst" + Value(index).asString() : "gridSelectedMaid" + Value(index).asString());
		if (grid->getDataGrid()->getId() == idDataGrid)
		{
			grid->updateSkinAttribute();
			break;
		}
	}
}
