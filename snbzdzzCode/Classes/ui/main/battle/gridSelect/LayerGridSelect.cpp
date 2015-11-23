#pragma execution_character_set("utf-8")

#include "LayerGridSelect.h"
#include "data/define/DefinesValue.h"
#include "core/grid/Grid.h"
#include "ui/ManagerUI.h"
#include "core/grid/ManagerGrid.h"
#include "data/define/DefinesRes.h"
#include "common/shake/Shake.h"

LayerGridSelect::LayerGridSelect() : _skin(nullptr), _nodeCircleLine(nullptr)
{
}

LayerGridSelect::~LayerGridSelect()
{
	ManagerUI::getInstance()->detach(this);
	_skin = nullptr;
	_nodeCircleLine = nullptr;
}

bool LayerGridSelect::init()
{
	auto isInit = false;
	do 
	{
		CC_BREAK_IF(!Node::init());

		idObserverSet(ID_OBSERVER::LAYER_GRID_SELECT);
		ManagerUI::getInstance()->attach(this);

		createSkin();

		isInit = true;
	} while (0);
	return isInit;
}

void LayerGridSelect::updateBySubject(va_list values)
{
	auto type = va_arg(values, TYPE_OBSERVER_LAYER_GRID_SELECT);
	if (type == TYPE_OBSERVER_LAYER_GRID_SELECT::RUN_MAID_GRID_MOVE_FROM_ACTION_ONE_BACK)
	{
		auto index = va_arg(values, int);
		runActionGridSelectMoveFromSelectedOne(index);
	}
	else if (type == TYPE_OBSERVER_LAYER_GRID_SELECT::RUN_MAID_GRID_MOVE_FROM_ACTION_ALL_BACK)
	{
		runActionGridSelectMoveFromSelectedAll();
	}
	else if (type == TYPE_OBSERVER_LAYER_GRID_SELECT::RUN_MAID_GRID_MOVE_FROM_ACTION_TAKE_BACK)
	{
		runMaidGridMoveFromActionTakeBack();
	}
	else if (type == TYPE_OBSERVER_LAYER_GRID_SELECT::RUN_MAID_GRID_PLAY_SPECIAL_STH_GENERATE)
	{
		auto funcOver = va_arg(values, CallFunc *);
		runMaidGridPlaySpecialSthGenerate(nullptr, funcOver);
	}
	else if (type == TYPE_OBSERVER_LAYER_GRID_SELECT::RUN_MAID_GRID_SCALE_BIG)
	{
		auto index = va_arg(values, int);
		auto funcOver = va_arg(values, CallFunc *);
		runMaidGridScaleBig(index, funcOver);
	}
	else if (type == TYPE_OBSERVER_LAYER_GRID_SELECT::RUN_MAID_GRID_SCALE_SMALL)
	{
		auto index = va_arg(values, int);
		auto funcOver = va_arg(values, CallFunc *);
		runMaidGridScaleSmall(index, funcOver);
	}
}

void LayerGridSelect::runAppearAction()
{
	auto d = 0.4f;
	_skin->setVisible(true);
	_skin->setOpacity(0.0f);
	_skin->setScale(10.0f);

	auto actionSpawn = Spawn::createWithTwoActions(EaseCubicActionIn::create(FadeIn::create(d)), EaseCubicActionIn::create(ScaleTo::create(d, 1.0f)));

	auto durationShake = 0.4f;
	auto actionShake = Spawn::createWithTwoActions(DelayTime::create(durationShake), CallFunc::create([this, durationShake]()
	{
		auto node = getParent()->getParent();
		node->runAction(Shake::create(durationShake, 1.5f));
	}));
	
	auto actionCallFunc = CallFunc::create([this]()
	{
		runSkillRandom();
	});

	_skin->runAction(Sequence::create(actionSpawn, actionShake, actionCallFunc, nullptr));
}

void LayerGridSelect::runSkillRandom()
{
	ManagerData::getInstance()->getHandleDataEntity()->dealSkillRandom([]()
	{
		ManagerUI::getInstance()->notify(ID_OBSERVER::LAYER_BATTLE, TYPE_OBSERVER_LAYER_BATTLE::SHOW_APPEAR_GRID_SELECT_MAID);
	});
}

void LayerGridSelect::showAppearGridSelectMaid(const Vec2 &postion)
{
	runActionGridSelectMaidMoveFrom(postion, nullptr, CC_CALLBACK_0(LayerGridSelect::runActionGridSelectMaidTurn, this, nullptr, nullptr));
}

void LayerGridSelect::runDisappearAction()
{
	auto d = 0.4f;

	auto actionScale = EaseCubicActionIn::create(ScaleTo::create(d, 0.0f));

	auto actionCallFunc = CallFunc::create([this]()
	{
		_skin->setVisible(false);
		_skin->setScale(1.0f);
		ManagerUI::getInstance()->notify(ID_OBSERVER::HANDLE_GRID, TYPE_OBSERVER_HANDLE_GRID::RUN_GRID_MOVE_AND_THROW);
	});

	_skin->runAction(Sequence::create(actionScale, actionCallFunc, nullptr));
}

void LayerGridSelect::runMaidGridPlaySpecialSthGenerate(const function<void()> &funcOneOver /*= nullptr*/, CallFunc *funcAllOver /*= nullptr*/)
{
	Vector<FiniteTimeAction *> vecActions;
	for (int i = 0; i < GRID_SELECT_MAX; i++)
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

void LayerGridSelect::runMaidGridScaleBig(const int &indexMaidGrid, CallFunc *funcOver /*= nullptr*/)
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

void LayerGridSelect::runMaidGridScaleSmall(const int &indexMaidGrid, CallFunc *funcOver /*= nullptr*/)
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

void LayerGridSelect::createSkin()
{
	auto size = Director::getInstance()->getVisibleSize();
	_skin = (Layer *)CSLoader::createNode(RES_MODULES_MAIN_LAYER_GRID_SELECT_CSB);
	_skin->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_skin->setPosition(size.width * 0.5f, size.height * 0.5f);
	_skin->setVisible(false);
	addChild(_skin);

	auto layout = (Layout *)_skin->getChildByName("layoutGridSelect");

	for (int i = 0; i < GRID_SELECT_MAX; i++)
	{
		auto sprite = (Sprite *)layout->getChildByName("spriteGridBg" + Value(i).asString());
		auto postion = sprite->getPosition();

		auto grid = Grid::create();
		grid->setIndexGrid(i);
		grid->createDataGrid();
		grid->setPosition(postion);
		grid->setName("gridSelect" + Value(i).asString());
		grid->setVisible(false);
		grid->getLayoutTouch()->addTouchEventListener(CC_CALLBACK_2(LayerGridSelect::onGridLayoutTouch, this, grid->getIndexGrid()));
		_skin->addChild(grid);
		ManagerGrid::getInstance()->insertGridMaidSelect(i, grid);
	}

	layout->addTouchEventListener([](Ref *ref, Widget::TouchEventType type)
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

void LayerGridSelect::onGridLayoutTouch(Ref *ref, Widget::TouchEventType type, const int &indexGrid)
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

void LayerGridSelect::runActionGridSelectMaidMoveFrom(const Vec2 &postion, const function<void()> &funcOneOver /*= nullptr*/, const function<void()> &funcAllOver /*= nullptr*/)
{
	Vector<FiniteTimeAction *> vecActions;
	for (int i = 0; i < GRID_SELECT_MAX; i++)
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

void LayerGridSelect::runActionGridSelectMaidTurn(const function<void()> &funcOneOver /*= nullptr*/, const function<void()> &funcAllOver /*= nullptr*/)
{
	Vector<FiniteTimeAction *> vecActions;
	for (int i = 0; i < GRID_SELECT_MAX; i++)
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

void LayerGridSelect::runActionGridSelectMoveFromSelectedOne(const int &indexMaidGrid, const function<void()> &funcOver /*= nullptr*/)
{
	auto managerGrid = ManagerGrid::getInstance();
	auto vecDataGrid = managerGrid->getVecDataGridMaidSelected();
	auto gridMaidSelected = (Grid *)managerGrid->getDicGridMaidSelected().at(vecDataGrid.size() - 1);
	gridMaidSelected->setVisible(false);
	auto postion = gridMaidSelected->getLayoutTouch()->getWorldPosition();
	Grid *grid = (Grid *)_skin->getChildByName("gridSelect" + Value(indexMaidGrid).asString());
	grid->moveFrom(postion, false, 1.0f, 1.0f, Vec2::ZERO, funcOver);
}

void LayerGridSelect::runActionGridSelectMoveFromSelectedAll(const function<void()> &funcOneOver /*= nullptr*/, const function<void()> &funcAllOver /*= nullptr*/)
{
	Vector<FiniteTimeAction *> vecActions;
	auto managerGrid = ManagerGrid::getInstance();
	auto vecDataGrid = managerGrid->getVecDataGridMaidSelected();
	for (int i = vecDataGrid.size() - 1; i >= 0; i--)
	{
		auto gridMaidSelected = (Grid *)managerGrid->getDicGridMaidSelected().at(i);
		if (gridMaidSelected->isVisible())
		{
			auto dataGrid = vecDataGrid.at(i);
			auto actionCallFunc = CallFunc::create([gridMaidSelected, managerGrid, dataGrid, funcOneOver]()
			{
				gridMaidSelected->setVisible(false);
				auto postion = gridMaidSelected->getLayoutTouch()->getWorldPosition();
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

void LayerGridSelect::runMaidGridMoveFromActionTakeBack(const function<void()> &funcOneOver /*= nullptr*/, const function<void()> &funcAllOver /*= nullptr*/)
{
	for (int i = 0; i < GRID_SELECT_MAX; i++)
	{
		auto grid = (Grid *)_skin->getChildByName("gridSelect" + Value(i).asString());
		grid->setVisible(false);
	}
	/*Vector<FiniteTimeAction *> vecActions;
	for (int i = 0; i < GRID_SELECT_MAX; i++)
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
