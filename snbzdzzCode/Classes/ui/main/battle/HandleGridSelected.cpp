#pragma execution_character_set("utf-8")

#include "HandleGridSelected.h"
#include "ui/ManagerUI.h"
#include "core/grid/Grid.h"
#include "core/grid/ManagerGrid.h"

HandleGridSelected::HandleGridSelected() : _skin(nullptr)
{
}

HandleGridSelected::~HandleGridSelected()
{
	ManagerUI::getInstance()->detach(this);
	_skin = nullptr;
}

bool HandleGridSelected::init()
{
	auto isInit = false;
	do
	{
		idObserverSet(ID_OBSERVER::HANDLE_GRID_SELECTED);
		ManagerUI::getInstance()->attach(this);

		isInit = true;
	} while (0);
	return isInit;
}

void HandleGridSelected::setSkin(Layout *skin)
{
	_skin = skin;
	_skin->setVisible(false);
	for (int i = 0; i < 8; i++)
	{
		auto isMst = i < 4;
		auto index = i % 4;
		auto grid = Grid::create();
		grid->setIndexGrid(index);
		grid->setPosition(isMst ? vecPostionGridSelectedMst[index] : vecPostionGridSelectedMaid[index]);
		grid->setName(isMst ? "gridMst" + Value(index).asString() : "gridMaid" + Value(index).asString());
		grid->setVisible(false);
		_skin->addChild(grid);
		auto managerGrid = ManagerGrid::getInstance();
		isMst ? managerGrid->insertGridMstSelected(index, grid) : managerGrid->insertGridMaidSelected(index, grid);
	}
}

void HandleGridSelected::updateBySubject(va_list values)
{
	auto type = va_arg(values, TYPE_OBSERVER_HANDLE_SELECTED);
	if (type == TYPE_OBSERVER_HANDLE_SELECTED::RUN_GRID_MOVE_ACTION)
	{
		_skin->setVisible(true);
		runGridMoveAction(CallFunc::create(CC_CALLBACK_0(HandleGridSelected::funcOverGridSelectedGridMove, this)));
	}
	else if (type == TYPE_OBSERVER_HANDLE_SELECTED::UPDATE_GRID)
	{
		auto idDataGrid = va_arg(values, int);
		updateGrid(idDataGrid);
	}
}

void HandleGridSelected::runGridMoveAction(CallFunc *callFuncAllOver /*= nullptr*/)
{
	auto managerGrid = ManagerGrid::getInstance();
	Vector<FiniteTimeAction *> vecActions;
	for (int i = 0; i < 8; i++)
	{
		auto actionCallFunc = CallFunc::create([=]()
		{
			auto isMst = i < 4;
			auto index = i % 4;
			auto gridShow = (Grid *)(isMst ? managerGrid->getDicGridMstShow() : managerGrid->getDicGridMaidShow()).at(index);
			gridShow->setVisible(false);
			auto dataGrid = gridShow->getDataGrid();
			auto postion = gridShow->getLayoutTouch()->getWorldPosition();
			auto gridSelected = (Grid *)(isMst ? managerGrid->getDicGridMstSelected() : managerGrid->getDicGridMaidSelected()).at(index);
			gridSelected->setDataGrid(dataGrid);
			gridSelected->moveFrom(postion, false, 1.0f, 0.5f, Vec2::ZERO, nullptr);
		});
		vecActions.pushBack(actionCallFunc);
		auto actionDelay = DelayTime::create(0.1f);
		vecActions.pushBack(actionDelay);
	}
	auto actionDelay = DelayTime::create(0.5f);
	vecActions.pushBack(actionDelay);
	vecActions.pushBack(callFuncAllOver);
	_skin->runAction(Sequence::create(vecActions));
}

void HandleGridSelected::resetSkin()
{
	for (int i = 0; i < 8; i++)
	{
		auto isMst = i < 4;
		auto index = i % 4;
		auto grid = _skin->getChildByName(isMst ? "gridMst" + Value(index).asString() : "gridMaid" + Value(index).asString());
		grid->setVisible(false);
	}
	_skin->setVisible(false);
}

void HandleGridSelected::funcOverGridSelectedGridMove()
{
	auto managerGrid = ManagerGrid::getInstance();
	managerGrid->clearVecDataGridMaidSelected();
	managerGrid->linkDataGridSelected();
	auto managerUI = ManagerUI::getInstance();
	managerUI->notify(ID_OBSERVER::LAYER_BATTLE, TYPE_OBSERVER_LAYER_BATTLE::CLOSE_LAYER_GRID_SHOW);
	managerUI->notify(ID_OBSERVER::HANDLE_ENTITY, TYPE_OBSERVER_HANDLE_ENTITY::RUN_GRID_MOVE_AND_THROW);
}

void HandleGridSelected::updateGrid(const int &idDataGrid)
{
	for (int i = 0; i < 8; i++)
	{
		auto isMst = i < 4;
		auto index = i % 4;
		auto grid = (Grid *)_skin->getChildByName(isMst ? "gridMst" + Value(index).asString() : "gridMaid" + Value(index).asString());
		if (grid->getDataGrid()->getId() == idDataGrid)
		{
			grid->updateSkinAttribute();
			break;
		}
	}
}
