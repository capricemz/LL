#pragma execution_character_set("utf-8")

#include "HandleEntity.h"
#include "data/define/DefinesValue.h"
#include "core/grid/Grid.h"
#include "ui/ManagerUI.h"
#include "core/grid/ManagerGrid.h"
#include "core/entity/subs/Entity.h"
#include "core/entity/subs/Maid.h"
#include "core/entity/subs/Monster.h"
#include "core/entity/ManagerEntity.h"
#include "data/define/DefinesRes.h"

HandleEntity::HandleEntity() : _skin(nullptr)
{
}

HandleEntity::~HandleEntity()
{
	ManagerUI::getInstance()->detach(this);
	_skin = nullptr;
}

bool HandleEntity::init()
{
	auto isInit = false;
	do 
	{
		idObserverSet(ID_OBSERVER::HANDLE_ENTITY);
		ManagerUI::getInstance()->attach(this);

		isInit = true;
	} while (0);
	return isInit;
}

void HandleEntity::setSkin(Layout *skin)
{
	_skin = skin;

	for (int i = 0; i < 2; i++)
	{
		auto isMst = i < 1;
		//
		auto grid = Grid::create();
		grid->setIndexGrid(i);
		grid->setPosition(vecPostionGridBattle[i]);
		grid->setName(isMst ? "gridBattleMst" : "gridBattleMaid");
		grid->setVisible(false);
		_skin->addChild(grid);
		ManagerGrid::getInstance()->insertGridBattle(i, grid);
		//
		auto layout = (Layout *)_skin->getChildByName("layoutEntityBattle")->getChildByName(isMst ? "layoutMstEB" : "layoutMaidEB");
		auto entity = isMst ? (Entity *)Monster::create() : (Entity *)Maid::create();
		entity->setName("entity");
		entity->setVisible(false);
		layout->addChild(entity);
		auto managerEntity = ManagerEntity::getInstance();
		isMst ? managerEntity->setMonster((Monster *)entity) : managerEntity->setMaid((Maid *)entity);
		//
		setTxtHpOrEnergy(entity, isMst, true);
		setTxtHpOrEnergy(entity, isMst, false);
	}
}

void HandleEntity::resetSkin()
{
	for (int i = 0; i < 2; i++)
	{
		auto isMst = i < 1;
		auto grid = (Grid *)_skin->getChildByName(isMst ? "gridBattleMst" : "gridBattleMaid");
		grid->setVisible(false);

		/*auto managerEntity = ManagerEntity::getInstance();
		auto entity = isMst ? (Entity *)managerEntity->getMonster() : (Entity *)managerEntity->getMaid();
		entity->setVisible(false);*/
	}
}

void HandleEntity::updateBySubject(va_list values)
{
	auto type = va_arg(values, TYPE_OBSERVER_HANDLE_ENTITY);
	if (type == TYPE_OBSERVER_HANDLE_ENTITY::RUN_ENTITY_APPEAR)
	{
		runEntityAppear();
	}
	else if (type == TYPE_OBSERVER_HANDLE_ENTITY::RUN_GRID_MOVE_AND_THROW)
	{
		runGridMoveAndThrow();
	}
	else if (type == TYPE_OBSERVER_HANDLE_ENTITY::RUN_ENTITY_ACTION)
	{
		runEntityAction();
	}
	else if (type == TYPE_OBSERVER_HANDLE_ENTITY::DEAL_ROUND_OVER)
	{
		auto isForce = va_arg(values, bool);
		dealRoundOver(isForce);
	}
	else if (type == TYPE_OBSERVER_HANDLE_ENTITY::UPDATE_HP)
	{
		updateTxtHpOrEnergy(true);
	}
	else if (type == TYPE_OBSERVER_HANDLE_ENTITY::UPDATE_ENERGY)
	{
		updateTxtHpOrEnergy(false);
	}
}

void HandleEntity::runEntityAppear()
{
	for (int i = 0; i < 2; i++)
	{
		auto isMst = i < 1;
		auto managerEntity = ManagerEntity::getInstance();
		auto entity = isMst ? (Entity *)managerEntity->getMonster() : (Entity *)managerEntity->getMaid();
		entity->runAppear([]()
		{
			auto isAppearAll = ManagerEntity::getInstance()->isRunAppearOverAll();
			if (isAppearAll)
			{
				ManagerUI::getInstance()->notify(ID_OBSERVER::LAYER_BATTLE, TYPE_OBSERVER_LAYER_BATTLE::SHOW_LAYER_GRID_SHOW);
			}
		});
	}
}

void HandleEntity::setTxtHpOrEnergy(Entity *entity, const bool &isMst, const bool &isHp)
{
	IdAttribute idAttribute;
	string name = "";
	if (isHp)
	{
		idAttribute = IdAttribute::ENTITY_HP;
		name = "txtHp";
	}
	else
	{
		idAttribute = IdAttribute::ENTITY_ENERGY;
		name = "txtEnergy";
	}
	auto value = entity->getDataEntity()->getAttribute(idAttribute);
	auto text = isMst ? Value(value).asString() + "X" : "X" + Value(value).asString();
	auto txt = (Text *)_skin->getChildByName(isMst ? "layoutMstBar" : "layoutMaidBar")->getChildByName(name);
	txt->setString(text);
}

void HandleEntity::runGridMoveAndThrow()
{
	auto indexGrid = ManagerData::getInstance()->getHandleDataGrid()->getIndexGridBattle();
	/*log("``````````HandleEntity::executeGrid indexGrid:%d", indexGrid);*/
	gridMoveFrom(indexGrid);
}

void HandleEntity::gridMoveFrom(const int &indexGrid)
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
		grid->moveFrom(postion, false, 0.5f, 1.0f, Vec2::ZERO, CC_CALLBACK_0(HandleEntity::gridMoveFromOver, this, grid, isMst));
	}
}

void HandleEntity::gridMoveFromOver(Grid *grid, const bool &isMst)
{
	if (grid->getIsCard())
	{
		runBackgroundEffect();//播放实体背景特效
		auto postion = grid->getParent()->convertToWorldSpace(vecPostionGridBattle[2]);
		grid->throwTo(postion, isMst ? -60.0f : 60.0f, CC_CALLBACK_0(HandleEntity::gridThrowToOrPlayOver, this, grid, isMst));
	}
	else
	{
		grid->playSpecialSthBeUse(CC_CALLBACK_0(HandleEntity::gridThrowToOrPlayOver, this, grid, isMst));
	}
}

void HandleEntity::runBackgroundEffect()
{

}

void HandleEntity::gridThrowToOrPlayOver(Grid *grid, const bool &isMst)
{
	grid->resetSkin();
	grid->setVisible(false);

	if (!isMst)
	{
		ManagerGrid::getInstance()->dealBattle();
	}
}

void HandleEntity::runEntityAction()
{
	auto managerEntity = ManagerEntity::getInstance();
	auto monster = managerEntity->getMonster();
	auto maid = managerEntity->getMaid();
	monster->setIsTurnOver(false);
	maid->setIsTurnOver(false);
	auto quickMst = monster->getDataEntity()->getAttribute(IdAttribute::ENTITY_QUICK);
	auto quickMaid = maid->getDataEntity()->getAttribute(IdAttribute::ENTITY_QUICK);
	auto quickMstOnly = quickMst != 0 && quickMaid == 0;
	auto quickMaidOnly = quickMst == 0 && quickMaid != 0;
	if (quickMstOnly || quickMaidOnly)//若仅怪物快速攻击或仅女仆快速攻击
	{
		auto entityQuick = quickMstOnly ? (Entity *)monster : (Entity *)maid;
		auto entityThen = quickMstOnly ? (Entity *)maid : (Entity *)monster;
		entityQuick->doAction([entityQuick, entityThen, this]()//先攻实体动作
		{
			entityThen->showEffect([entityQuick, entityThen, this]()//后续实体结果
			{
				entityThen->doAction([entityQuick, this]()//后续实体动作
				{
					entityQuick->showEffect([this]()//先攻实体结果
					{
						dealTurnOver();
					});
				});
			});
		});
	}
	else
	{
		for (auto i = 0; i < 2; i++)
		{
			auto isMst = i < 1;
			auto entityDoAction = isMst ? (Entity *)monster : (Entity *)maid;
			entityDoAction->doAction([this]()//动作
			{
				auto managerEntity = ManagerEntity::getInstance();
				auto isDoActoinOverAll = managerEntity->isDoActoinOverAll();
				if (isDoActoinOverAll)
				{
					for (auto i = 0; i < 2; i++)
					{
						auto isMst = i < 1;
						auto entityShowEffect = isMst ? (Entity *)managerEntity->getMonster() : (Entity *)managerEntity->getMaid();
						entityShowEffect->showEffect([this]()//结果
						{
							dealTurnOver();
						});
					}
				}
			});
		}
	}
}

void HandleEntity::dealTurnOver()
{
	auto isTurnAll = ManagerEntity::getInstance()->isTurnOverAll();
	if (isTurnAll)
	{
		auto isRoundOver = ManagerData::getInstance()->getHandleDataGrid()->isRoundOver();
		if (!isRoundOver)
		{
			ManagerData::getInstance()->getHandleDataEntity()->dealTurnOver();
			ManagerEntity::getInstance()->resetEntityAttributeTemp();
			runGridMoveAndThrow();
		}
		else//若回合结束
		{
			dealRoundOver();
		}
	}
}

void HandleEntity::dealRoundOver(const bool &isForce /*= false*/)
{
	auto func = []()
	{
		auto managerUI = ManagerUI::getInstance();
		managerUI->notify(ID_OBSERVER::LAYER_BATTLE, TYPE_OBSERVER_LAYER_BATTLE::RESET_SKIN);
		managerUI->notify(ID_OBSERVER::LAYER_BATTLE, TYPE_OBSERVER_LAYER_BATTLE::SHOW_LAYER_GRID_SHOW);
	};
	ManagerData::getInstance()->getHandleDataGrid()->resetIndexGridBattle();
	ManagerEntity::getInstance()->resetEntityAttributeTemp();
	auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
	handleDataEntity->dealRoundOver(isForce);
	auto indexTo = 0;
	auto isSkillNeedSwitchEntity = handleDataEntity->getIsSkillNeedSwitchEntity(indexTo);
	if (isSkillNeedSwitchEntity)
	{
		auto monster = ManagerEntity::getInstance()->getMonster();
		monster->switchEntity(indexTo, func);
	}
	else
	{
		func();
	}
}

void HandleEntity::updateTxtHpOrEnergy(const bool &isHp)
{
	IdAttribute idAttribute;
	string name = "";
	if (isHp)
	{
		idAttribute = IdAttribute::ENTITY_HP;
		name = "txtHp";
	}
	else
	{
		idAttribute = IdAttribute::ENTITY_ENERGY;
		name = "txtEnergy";
	}
	for (int i = 0; i < 2; i++)
	{
		auto isMst = i < 1;
		auto managerEntity = ManagerEntity::getInstance();
		auto entity = isMst ? (Entity *)managerEntity->getMonster() : (Entity *)managerEntity->getMaid();
		auto value = entity->getDataEntity()->getAttribute(idAttribute);
		auto text = isMst ? Value(value).asString() + "X" : "X" + Value(value).asString();
		auto txt = (Text *)_skin->getChildByName(isMst ? "layoutMstBar" : "layoutMaidBar")->getChildByName(name);
		txt->setString(text);
	}
}
