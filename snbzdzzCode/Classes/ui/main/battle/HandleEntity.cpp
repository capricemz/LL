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

	auto managerEntity = ManagerEntity::getInstance();

	for (int i = 0; i < 2; i++)
	{
		auto isMst = i < 1;
		auto layout = (Layout *)_skin->getChildByName(isMst ? "layoutMst" : "layoutMaid");
		//
		auto scenery = Scenery::create();
		scenery->setName("scenery");
		scenery->updateSkin(isMst);
		layout->addChild(scenery);
		isMst ? managerEntity->setSceneryMst(scenery) : managerEntity->setSceneryMaid(scenery);
		//
		auto entity = isMst ? (Entity *)Monster::create() : (Entity *)Maid::create();
		entity->setName("entity");
		entity->setVisible(false);
		layout->addChild(entity);
		isMst ? managerEntity->setMonster((Monster *)entity) : managerEntity->setMaid((Maid *)entity);
		//
		/*setTxtHpOrEnergy(entity, isMst, true);
		setTxtHpOrEnergy(entity, isMst, false);*/
	}
}

void HandleEntity::resetSkin()
{
	for (int i = 0; i < 2; i++)
	{
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
		/*updateTxtHpOrEnergy(true);*/
	}
	else if (type == TYPE_OBSERVER_HANDLE_ENTITY::UPDATE_ENERGY)
	{
		/*updateTxtHpOrEnergy(false);*/
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
				ManagerUI::getInstance()->notify(ID_OBSERVER::LAYER_BATTLE, TYPE_OBSERVER_LAYER_BATTLE::SHOW_APPEAR_GRID_SELECTED_MST);
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
		auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
		handleDataEntity->resetDataEntityAttributeTemp();
		handleDataEntity->dealVecSkillActiveInUse2UseOverMaid();
		auto isRoundOver = ManagerData::getInstance()->getHandleDataGrid()->isRoundOver();
		if (!isRoundOver)
		{
			ManagerUI::getInstance()->notify(ID_OBSERVER::HANDLE_GRID, TYPE_OBSERVER_HANDLE_GRID::RUN_GRID_MOVE_AND_THROW);
		}
		else//若回合结束
		{
			auto indexTo = 0;
			auto isSkillNeedSwitchEntity = handleDataEntity->getIsSkillNeedSwitchEntity(indexTo);
			if (isSkillNeedSwitchEntity)
			{
				ManagerUI::getInstance()->notify(ID_OBSERVER::HANDLE_HEAD, TYPE_OBSERVER_HANDLE_HEAD::SWITCH_NODE_HEAD_TO, true, indexTo);//参数：是怪物，切换目标
			}
			else
			{
				dealRoundOver();
			}
		}
	}
}

void HandleEntity::dealRoundOver(const bool &isForce /*= false*/)
{
	ManagerData::getInstance()->getHandleDataGrid()->resetIndexGridBattle();
	auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
	handleDataEntity->addRound();
	handleDataEntity->dealDataEntitySkillSort(isForce);

	auto managerUI = ManagerUI::getInstance();
	managerUI->notify(ID_OBSERVER::LAYER_BATTLE, TYPE_OBSERVER_LAYER_BATTLE::RESET_SKIN);
	managerUI->notify(ID_OBSERVER::LAYER_BATTLE, TYPE_OBSERVER_LAYER_BATTLE::SHOW_APPEAR_GRID_SELECTED_MST);
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
