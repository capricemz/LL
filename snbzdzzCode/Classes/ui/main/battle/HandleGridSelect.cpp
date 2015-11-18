#pragma execution_character_set("utf-8")

#include "HandleGridSelect.h"
#include "data/define/DefinesValue.h"
#include "core/grid/Grid.h"
#include "ui/ManagerUI.h"
#include "core/grid/ManagerGrid.h"

HandleGridSelect::HandleGridSelect() : _skin(nullptr), _nodeCircleLine(nullptr)
{
}

HandleGridSelect::~HandleGridSelect()
{
	ManagerUI::getInstance()->detach(this);
	_skin = nullptr;
	_nodeCircleLine = nullptr;
}

bool HandleGridSelect::init()
{
	auto isInit = false;
	do 
	{
		idObserverSet(ID_OBSERVER::HANDLE_GRID_SELECT);
		ManagerUI::getInstance()->attach(this);

		isInit = true;
	} while (0);
	return isInit;
}

void HandleGridSelect::setSkin(Layout *skin)
{
	_skin = skin;
	for (int i = 0; i < 9; i++)
	{
		auto grid = Grid::create();
		grid->setIndexGrid(i);
		grid->createDataGrid();
		grid->setPosition(vecPostionGridSelect[i]);
		grid->setName("gridSelect" + Value(i).asString());
		grid->setVisible(false);
		grid->getLayoutTouch()->addTouchEventListener(CC_CALLBACK_2(HandleGridSelect::onGridLayoutTouch, this, grid->getIndexGrid()));
		_skin->addChild(grid);
		ManagerGrid::getInstance()->insertGridMaidSelect(i, grid);
	}

	_skin->addTouchEventListener([=](Ref *ref, Widget::TouchEventType type)
	{
		switch (type)
		{
		case Widget::TouchEventType::ENDED:
			/*ManagerUI::getInstance()->notify(ID_OBSERVER::SCENE_MAIN, TYPE_OBSERVER_SCENE_MAIN::RESET_SKIN);//for test
			ManagerUI::getInstance()->notify(ID_OBSERVER::SCENE_MAIN, TYPE_OBSERVER_SCENE_MAIN::START);//for test*/
			/*ManagerUI::getInstance()->notify(ID_OBSERVER::HANDLE_ENTITY);//for test*/
			ManagerUI::getInstance()->notify(ID_OBSERVER::SCENE_MAIN, TYPE_OBSERVER_SCENE_MAIN::SHOW_LEVELS);//for test
			break;
		default:
			break;
		}
	});
}

void HandleGridSelect::updateBySubject(va_list values)
{
	auto type = va_arg(values, TYPE_OBSERVER_HANDLE_GRID_SELECT);
	if (type == TYPE_OBSERVER_HANDLE_GRID_SELECT::RUN_MAID_GRID_MOVE_FROM_ACTION_ONE_BACK)
	{
		auto index = va_arg(values, int);
		/*auto funcOver = va_arg(values, CallFunc *);*/
		runMaidGridMoveFromAction(index/*, funcOver*/);
	}
	else if (type == TYPE_OBSERVER_HANDLE_GRID_SELECT::RUN_MAID_GRID_MOVE_FROM_ACTION_ALL_BACK)
	{
		/*auto funcOneOver = va_arg(values, function<void()>);*/
		/*auto funcAllOver = va_arg(values, function<void()>);*/
		runMaidGridMoveFromAction(/*funcOneOver, funcAllOver*/);
	}
	else if (type == TYPE_OBSERVER_HANDLE_GRID_SELECT::RUN_MAID_GRID_MOVE_FROM_ACTION_TAKE_BACK)
	{
		runMaidGridMoveFromActionTakeBack();
	}
	else if (type == TYPE_OBSERVER_HANDLE_GRID_SELECT::RUN_MAID_GRID_PLAY_SPECIAL_STH_GENERATE)
	{
		auto funcOver = va_arg(values, CallFunc *);
		runMaidGridPlaySpecialSthGenerate(nullptr, funcOver);
	}
	else if (type == TYPE_OBSERVER_HANDLE_GRID_SELECT::RUN_MAID_GRID_SCALE_BIG)
	{
		auto index = va_arg(values, int);
		auto funcOver = va_arg(values, CallFunc *);
		runMaidGridScaleBig(index, funcOver);
	}
	else if (type == TYPE_OBSERVER_HANDLE_GRID_SELECT::RUN_MAID_GRID_SCALE_SMALL)
	{
		auto index = va_arg(values, int);
		auto funcOver = va_arg(values, CallFunc *);
		runMaidGridScaleSmall(index, funcOver);
	}
}

void HandleGridSelect::runMaidGridMoveFromAction(const Vec2 &postion, const function<void()> &funcOneOver /*= nullptr*/, const function<void()> &funcAllOver /*= nullptr*/)
{
	Vector<FiniteTimeAction *> vecActions;
	for (int i = 0; i < 9; i++)
	{
		Grid *grid = (Grid *)_skin->getChildByName("gridSelect" + Value(i).asString());
		if (!grid->isVisible())
		{
			auto actionCallFunc = CallFunc::create([grid, postion, funcOneOver]()
			{
				grid->createDataGrid();
				grid->createDataGridSkill(false);
				grid->moveFrom(postion, true, 0.5f, 0.5f, Vec2(37.5f, 37.5f), funcOneOver);
				grid->setIsNeedTurn(true);
			});
			vecActions.pushBack(actionCallFunc);
			auto actionDelay = DelayTime::create(0.2f);
			vecActions.pushBack(actionDelay);
		}
	}
	auto actionCallFuncAllOver = CallFunc::create([=]()
	{
		if (funcAllOver != nullptr)
		{
			funcAllOver();
		}
	});
	vecActions.pushBack(actionCallFuncAllOver);
	_skin->runAction(Sequence::create(vecActions));
}

void HandleGridSelect::runMaidGridMoveFromAction(const int &indexMaidGrid, const function<void()> &funcOver /*= nullptr*/)
{
	auto managerGrid = ManagerGrid::getInstance();
	auto vecDataGrid = managerGrid->getVecDataGridMaidSelected();
	auto gridMaidShow = (Grid *)managerGrid->getDicGridMaidShow().at(vecDataGrid.size() - 1);
	gridMaidShow->setVisible(false);
	auto postion = gridMaidShow->getLayoutTouch()->getWorldPosition();
	Grid *grid = (Grid *)_skin->getChildByName("gridSelect" + Value(indexMaidGrid).asString());
	grid->moveFrom(postion, false, 1.0f, 1.0f, Vec2::ZERO, funcOver);
}

void HandleGridSelect::runMaidGridMoveFromAction(const function<void()> &funcOneOver /*= nullptr*/, const function<void()> &funcAllOver /*= nullptr*/)
{
	Vector<FiniteTimeAction *> vecActions;
	auto managerGrid = ManagerGrid::getInstance();
	auto vecDataGrid = managerGrid->getVecDataGridMaidSelected();
	for (int i = vecDataGrid.size() - 1; i >= 0; i--)
	{
		auto gridMaidShow = (Grid *)managerGrid->getDicGridMaidShow().at(i);
		if (gridMaidShow->isVisible())
		{
			auto dataGrid = vecDataGrid.at(i);
			auto actionCallFunc = CallFunc::create([gridMaidShow, managerGrid, dataGrid, funcOneOver]()
			{
				gridMaidShow->setVisible(false);
				auto postion = gridMaidShow->getLayoutTouch()->getWorldPosition();
				auto gridMaidSelect = (Grid *)managerGrid->getDicGridMaidSelect().at(dataGrid->getIndexGrid());
				gridMaidSelect->moveFrom(postion, false, 1.0f, 1.0f, Vec2::ZERO, funcOneOver);
			});
			vecActions.pushBack(actionCallFunc);
			auto actionDelay = DelayTime::create(0.2f);
			vecActions.pushBack(actionDelay);
		}
	}
	auto actionCallFuncAllOver = CallFunc::create([=]()
	{
		if (funcAllOver != nullptr)
		{
			funcAllOver();
		}
	});
	vecActions.pushBack(actionCallFuncAllOver);
	_skin->runAction(Sequence::create(vecActions));
}

void HandleGridSelect::runMaidGridTurnAction(const function<void()> &funcOneOver /*= nullptr*/, const function<void()> &funcAllOver /*= nullptr*/)
{
	Vector<FiniteTimeAction *> vecActions;
	for (int i = 0; i < 9; i++)
	{
		Grid *grid = (Grid *)_skin->getChildByName("gridSelect" + Value(i).asString());
		if (grid->getIsNeedTurn())
		{
			auto actionCallFunc = CallFunc::create([grid, funcOneOver]()
			{
				grid->turn(funcOneOver);
				grid->setIsNeedTurn(false);
			});
			vecActions.pushBack(actionCallFunc);
			auto actionDelay = DelayTime::create(0.1f);
			vecActions.pushBack(actionDelay);
		}
	}
	auto actionCallFuncAllOver = CallFunc::create([=]()
	{
		if (funcAllOver != nullptr)
		{
			funcAllOver();
		}
	});
	vecActions.pushBack(actionCallFuncAllOver);
	_skin->runAction(Sequence::create(vecActions));
}

void HandleGridSelect::runMaidGridPlaySpecialSthGenerate(const function<void()> &funcOneOver /*= nullptr*/, CallFunc *funcAllOver /*= nullptr*/)
{
	Vector<FiniteTimeAction *> vecActions;
	for (int i = 0; i < 9; i++)
	{
		Grid *grid = (Grid *)_skin->getChildByName("gridSelect" + Value(i).asString());
		if (grid->getIsNotCard() && !grid->isVisible())//非牌且已被使用即不可见
		{
			auto actionCallFunc = CallFunc::create([grid, funcOneOver]()
			{
				grid->playSpecialSthGenerate(funcOneOver);
			});
			vecActions.pushBack(actionCallFunc);
			auto actionDelay = DelayTime::create(0.2f);
			vecActions.pushBack(actionDelay);
		}
	}
	vecActions.pushBack(funcAllOver);
	_skin->runAction(Sequence::create(vecActions));
}

void HandleGridSelect::runMaidGridScaleBig(const int &indexMaidGrid, CallFunc *funcOver /*= nullptr*/)
{
	Grid *grid = (Grid *)_skin->getChildByName("gridSelect" + Value(indexMaidGrid).asString());
	if (grid->getIsCanScaleBig())
	{
		grid->scaleBig(false, funcOver);
	}
	else
	{
		if (funcOver != nullptr)
		{
			funcOver->execute();
		}
	}
}

void HandleGridSelect::runMaidGridScaleSmall(const int &indexMaidGrid, CallFunc *funcOver /*= nullptr*/)
{
	Grid *grid = (Grid *)_skin->getChildByName("gridSelect" + Value(indexMaidGrid).asString());
	if (grid->getIsCanScaleSmall())
	{
		grid->scaleSmall(funcOver);
	}
	else
	{
		if (funcOver != nullptr)
		{
			funcOver->execute();
		}
	}
}

void HandleGridSelect::onGridLayoutTouch(Ref *ref, Widget::TouchEventType type, const int &indexGrid)
{
	auto layoutTouch = (Layout *)ref;
	auto postionLayoutWorld = layoutTouch->getWorldPosition();
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		_nodeCircleLine = NodeCircleLine::create();
		_skin->addChild(_nodeCircleLine, 1);
		_nodeCircleLine->onTouchBegan(indexGrid, postionLayoutWorld, layoutTouch->getTouchBeganPosition());
		break;
	case Widget::TouchEventType::MOVED:
		_nodeCircleLine->onTouchMoved(layoutTouch->getTouchMovePosition());
		break;
	case Widget::TouchEventType::ENDED:
	case Widget::TouchEventType::CANCELED:
		_nodeCircleLine->onTouchEndedCanceled();
		_nodeCircleLine = nullptr;
		break;
	}
}

void HandleGridSelect::runMaidGridMoveFromActionTakeBack(const function<void()> &funcOneOver /*= nullptr*/, const function<void()> &funcAllOver /*= nullptr*/)
{
	for (int i = 0; i < 9; i++)
	{
		auto grid = (Grid *)_skin->getChildByName("gridSelect" + Value(i).asString());
		grid->setVisible(false);
	}
	/*Vector<FiniteTimeAction *> vecActions;
	for (int i = 0; i < 9; i++)
	{
		Grid *grid = (Grid *)_skin->getChildByName("gridSelect" + Value(i).asString());
		if (grid->isVisible())
		{
			auto actionCallFunc = CallFunc::create([grid, postion, funcOneOver]()
			{
				grid->createDataGrid(false);
				grid->moveFrom(postion, true, 0.5f, 0.5f, Vec2(37.5f, 37.5f), funcOneOver);
				grid->setIsNeedTurn(true);
			});
			vecActions.pushBack(actionCallFunc);
			auto actionDelay = DelayTime::create(0.2f);
			vecActions.pushBack(actionDelay);
		}
	}
	auto actionCallFuncAllOver = CallFunc::create([=]()
	{
		if (funcAllOver != nullptr)
		{
			funcAllOver();
		}
	});
	vecActions.pushBack(actionCallFuncAllOver);
	_skin->runAction(Sequence::create(vecActions));*/
}
