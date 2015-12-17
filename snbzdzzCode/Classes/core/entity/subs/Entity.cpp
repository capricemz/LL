#include "Entity.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"
#include "data/data/ManagerData.h"
#include "ui/ManagerUI.h"
#include "../ManagerEntity.h"
#include "core/grid/ManagerGrid.h"
#include "data/define/DefinesString.h"

using namespace CocosDenshion;

Entity::Entity() : _dataEntity(nullptr), _skin(nullptr), _isRunAppearOver(true), _isRunDisappearOver(true), _isDoActionOver(true), _isTurnOver(true)
{
}

Entity::~Entity()
{
	_dataEntity = nullptr;
	_skin = nullptr;
}

bool Entity::init()
{
	auto isInit = false;
	do
	{
		CC_BREAK_IF(!Node::init());

		updateSkin();

		isInit = true;
	} while (0);
	return isInit;
}

void Entity::updateSkin()
{
	setDataEntity();

	auto cfgEntity = _dataEntity->getCfgEntity();
	setPosition(cfgEntity.xPic, cfgEntity.yPic);
	
	auto breakTakesNum = _dataEntity->getAttribute(IdAttribute::ENTITY_BREAK_TAKES_NUM);
	auto urlPic = breakTakesNum > 0 ? cfgEntity.urlPicEntityBreak : cfgEntity.urlPicEntity;
	if (_skin == nullptr)
	{
		_skin = Sprite::create(urlPic);
		setMyScale();
		addChild(_skin);
	}
	else
	{
		auto texture = Director::getInstance()->getTextureCache()->getTextureForKey(urlPic);
		_skin->setTexture(texture);
	}
}

void Entity::runAppear(const function<void()> &func /*= nullptr*/)
{
	_isRunAppearOver = false;

	setVisible(true);

	auto postionBegan = getPostionAppearDisAppear();
	_skin->setPosition(postionBegan);

	Vector<FiniteTimeAction *> vecActions;

	auto actionMove = EaseCircleActionOut::create(MoveTo::create(0.5f, Vec2::ZERO));
	vecActions.pushBack(actionMove);

	auto actionCallFunc = CallFunc::create([func, this]()
	{
		_isRunAppearOver = true;
		if (func != nullptr)
		{
			func();
		}
	});
	vecActions.pushBack(actionCallFunc);

	_skin->runAction(Sequence::create(vecActions));
}

void Entity::runDisAppear(const function<void()> &func /*= nullptr*/)
{
	_isRunDisappearOver = false;

	Vector<FiniteTimeAction *> vecActions;

	auto postionEnd = getPostionAppearDisAppear();
	auto actionMove = EaseCircleActionIn::create(MoveTo::create(0.5f, postionEnd));
	vecActions.pushBack(actionMove);

	auto actionCallFunc = CallFunc::create([func, this]()
	{
		_isRunDisappearOver = true;
		_skin->setPosition(Vec2::ZERO);
		setVisible(false);
		if (func != nullptr)
		{
			func();
		}
	});
	vecActions.pushBack(actionCallFunc);

	_skin->runAction(Sequence::create(vecActions));
}

void Entity::doAction(const function<void()> &func /*= nullptr*/)
{
	_isDoActionOver = false;

	Vector<FiniteTimeAction *> vecActions;

	auto damageCase = _dataEntity->getAttribute(IdAttribute::ENTITY_DAMAGE_CASE);
	if (damageCase != 0)
	{
		auto psotionEnd = getPostionEndAttack();
		auto actionMoveTo = EaseBackIn::create(MoveTo::create(0.6f, psotionEnd));
		vecActions.pushBack(actionMoveTo);

		auto actionDelay = DelayTime::create(0.2f);
		vecActions.pushBack(actionDelay);

		auto actionMoveBack = EaseExponentialOut::create(MoveTo::create(0.6f, Vec2::ZERO));
		vecActions.pushBack(actionMoveBack);
	}

	auto costHp = _dataEntity->getAttribute(IdAttribute::ENTITY_COST_HP);
	if (costHp != 0)//若消耗生命
	{
		auto duration = 0.6f;
		auto actionDeal = CallFunc::create(CC_CALLBACK_0(Entity::dealResultValueChange, this, IdAttribute::ENTITY_COST_HP, false, IdAttribute::ENTITY_HP, Color4B::RED, duration));
		vecActions.pushBack(actionDeal);
		auto actionDelay = DelayTime::create(duration + 0.1f);
		vecActions.pushBack(actionDelay);
	}

	auto restoreHp = _dataEntity->getAttribute(IdAttribute::ENTITY_RESTORE_HP);
	if (restoreHp != 0)//若恢复生命
	{
		auto duration = 0.6f;
		auto actionDeal = CallFunc::create(CC_CALLBACK_0(Entity::dealResultValueChange, this, IdAttribute::ENTITY_RESTORE_HP, true, IdAttribute::ENTITY_HP, Color4B::GREEN, duration));
		vecActions.pushBack(actionDeal);
		auto actionDelay = DelayTime::create(duration + 0.1f);
		vecActions.pushBack(actionDelay);
	}

	auto costHpAll = _dataEntity->getAttribute(IdAttribute::ENTITY_COST_HP_ALL);
	if (costHpAll != 0)//若全体消耗生命
	{
		auto duration = 0.6f;
		auto actionDeal = CallFunc::create(CC_CALLBACK_0(Entity::dealResultValueChangeAll, this, IdAttribute::ENTITY_COST_HP_ALL, false, IdAttribute::ENTITY_HP, Color4B::RED, duration));
		vecActions.pushBack(actionDeal);
		auto actionDelay = DelayTime::create(duration + 0.1f);
		vecActions.pushBack(actionDelay);
	}

	auto restoreHpAll = _dataEntity->getAttribute(IdAttribute::ENTITY_RESTORE_HP_ALL);
	if (restoreHpAll != 0)//若全体恢复生命
	{
		auto duration = 0.6f;
		auto actionDeal = CallFunc::create(CC_CALLBACK_0(Entity::dealResultValueChangeAll, this, IdAttribute::ENTITY_RESTORE_HP_ALL, true, IdAttribute::ENTITY_HP, Color4B::GREEN, duration));
		vecActions.pushBack(actionDeal);
		auto actionDelay = DelayTime::create(duration + 0.1f);
		vecActions.pushBack(actionDelay);
	}

	auto costEnergy = _dataEntity->getAttribute(IdAttribute::ENTITY_COST_ENERGY);
	if (costEnergy != 0)//若消耗能量
	{
		auto duration = 0.6f;
		auto actionDeal = CallFunc::create(CC_CALLBACK_0(Entity::dealResultValueChange, this, IdAttribute::ENTITY_COST_ENERGY, false, IdAttribute::ENTITY_ENERGY, Color4B::GRAY, duration));
		vecActions.pushBack(actionDeal);
		auto actionDelay = DelayTime::create(duration + 0.1f);
		vecActions.pushBack(actionDelay);
	}

	auto restoreEnergy = _dataEntity->getAttribute(IdAttribute::ENTITY_RESTORE_ENERGY);
	if (restoreEnergy != 0)//若恢复能量
	{
		auto duration = 0.6f;
		auto actionDeal = CallFunc::create(CC_CALLBACK_0(Entity::dealResultValueChange, this, IdAttribute::ENTITY_RESTORE_ENERGY, true, IdAttribute::ENTITY_ENERGY, Color4B::YELLOW, duration));
		vecActions.pushBack(actionDeal);
		auto actionDelay = DelayTime::create(duration + 0.1f);
		vecActions.pushBack(actionDelay);
	}

	auto actionCallFunc = CallFunc::create([func, this]()
	{
		_isDoActionOver = true;
		if (func != nullptr)
		{
			func();
		}
	});
	vecActions.pushBack(actionCallFunc);

	_skin->runAction(Sequence::create(vecActions));
}

void Entity::showEffect(const function<void()> &func /*= nullptr*/)
{
	Vector<FiniteTimeAction *> vecActions;

	auto damageTakes = _dataEntity->getAttribute(IdAttribute::ENTITY_DAMAGE_TAKES);
	if (damageTakes != 0)//若受到伤害
	{
		auto duration = 0.6f;
		auto actionDeal = CallFunc::create(CC_CALLBACK_0(Entity::dealResultValueChange, this, IdAttribute::ENTITY_DAMAGE_TAKES, false, IdAttribute::ENTITY_HP, Color4B::RED, duration));
		vecActions.pushBack(actionDeal);
		auto actionDelay = DelayTime::create(duration + 0.1f);
		vecActions.pushBack(actionDelay);
	}

	auto damageTakesExtra = _dataEntity->getAttribute(IdAttribute::ENTITY_DAMAGE_TAKES_EXTRA);
	if (damageTakesExtra != 0)//若受到额外伤害
	{
		auto duration = 0.6f;
		auto actionDeal = CallFunc::create(CC_CALLBACK_0(Entity::dealResultValueChange, this, IdAttribute::ENTITY_DAMAGE_TAKES_EXTRA, false, IdAttribute::ENTITY_HP, Color4B::RED, duration));
		vecActions.pushBack(actionDeal);
		auto actionDelay = DelayTime::create(duration + 0.1f);
		vecActions.pushBack(actionDelay);
	}

	auto breakTakes = _dataEntity->getAttribute(IdAttribute::ENTITY_BREAK_TAKES);
	if (breakTakes)
	{
		auto duration = 0.6f;
		auto actionDeal = CallFunc::create(CC_CALLBACK_0(Entity::dealBreakEffect, this, duration));
		vecActions.pushBack(actionDeal);
		auto actionDelay = DelayTime::create(duration + 0.1f);
		vecActions.pushBack(actionDelay);
		auto actionDeal1 = CallFunc::create(CC_CALLBACK_0(Entity::dealBreak, this));
		vecActions.pushBack(actionDeal1);
	}

	auto hpFinal = _dataEntity->getAttribute(IdAttribute::ENTITY_HP) - damageTakes - damageTakesExtra;
	if (hpFinal <= 0)
	{
		auto duration = 0.6f;
		auto actionDeal = CallFunc::create(CC_CALLBACK_0(Entity::dealDeadEffect, this, duration));
		vecActions.pushBack(actionDeal);
		auto actionDelay = DelayTime::create(duration + 0.1f);
		vecActions.pushBack(actionDelay);
		auto actionDeal1 = CallFunc::create(CC_CALLBACK_0(Entity::dealDead, this));
		vecActions.pushBack(actionDeal1);
	}
	else
	{
		auto actionCallFunc = CallFunc::create([func, this]()
		{
			_isTurnOver = true;
			if (func != nullptr)
			{
				func();
			}
		});
		vecActions.pushBack(actionCallFunc);
	}

	_skin->runAction(Sequence::create(vecActions));
}

void Entity::stopSkinAllActions()
{
	_skin->stopAllActions();
}

void Entity::switchEntity(const int &indexSwitchTo, bool &isSwitchSuccess, const function<void()> &func /*= nullptr*/)
{
	switchDataEntity(indexSwitchTo, isSwitchSuccess);
	if (!isSwitchSuccess)
	{
		return;
	}
	//
	runDisAppear([this, func]()
	{
		updateSkin();
		runAppear([this, func]()
		{
			auto isAppearAll = ManagerEntity::getInstance()->isRunAppearOverAll();
			if (isAppearAll)
			{
				auto managerUI = ManagerUI::getInstance();
				managerUI->notify(ID_OBSERVER::LAYER_GRID_SELECT, TYPE_OBSERVER_LAYER_GRID_SELECT::RUN_MAID_GRID_MOVE_FROM_ACTION_TAKE_BACK);
				/*managerUI->notify(ID_OBSERVER::HANDLE_ENTITY, TYPE_OBSERVER_HANDLE_ENTITY::UPDATE_HP);
				managerUI->notify(ID_OBSERVER::HANDLE_ENTITY, TYPE_OBSERVER_HANDLE_ENTITY::UPDATE_ENERGY);*/
				updateEnergy();
				if (func != nullptr)
				{
					func();
				}
			}
		});
	});
}

void Entity::dealResultValueChange(const IdAttribute &idAttributeChange, const bool &isPositive, const IdAttribute &idAttributeBeChange, const Color4B &color, const float &duration)
{
	//数据处理
	auto valueChange = _dataEntity->getAttribute(idAttributeChange);
	valueChange = isPositive ? valueChange : -valueChange;
	_dataEntity->addAttributeLimit(idAttributeBeChange, valueChange);
	//界面处理
	auto words = Value(valueChange).asString();
	if (idAttributeBeChange == IdAttribute::ENTITY_HP)
	{
		words = STR_HP + words;
		updateHp();//界面刷新
	}
	else if (idAttributeBeChange == IdAttribute::ENTITY_ENERGY)
	{
		words = STR_EP + words;
		updateEnergy();//界面刷新
	}
	auto managerUI = ManagerUI::getInstance();
	managerUI->showWordsDrift(getParent(), getPosition() + Vec2(0.0f, 100.0f), words, color, duration);
}

void Entity::dealResultValueChangeAll(const IdAttribute &idAttributeChange, const bool &isPositive, const IdAttribute &idAttributeBeChange, const Color4B &color, const float &duration)
{
	auto managerUI = ManagerUI::getInstance();

	auto valueChange = _dataEntity->getAttribute(idAttributeChange);

	auto vecDataEntityMaid = getVecDataEntity();
	auto length = (int)vecDataEntityMaid.size();
	for (auto i = 0; i < length; i++)
	{
		auto dataEntity = vecDataEntityMaid.at(i);
		auto valueMax = 0;
		if (idAttributeBeChange == IdAttribute::ENTITY_HP)
		{
			valueMax = dataEntity->getAttribute(IdAttribute::ENTITY_HP_MAX);
		}
		else if (idAttributeBeChange == IdAttribute::ENTITY_ENERGY)
		{
			valueMax = dataEntity->getAttribute(IdAttribute::ENTITY_ENERGY_MAX);
		}
		valueChange = valueChange * valueMax * 0.1f;
		valueChange = isPositive ? valueChange : -valueChange;
		dataEntity->addAttributeLimit(idAttributeBeChange, valueChange);
		//界面处理
		if (dataEntity == _dataEntity && valueChange != 0)
		{
			auto words = Value(valueChange).asString();
			if (idAttributeBeChange == IdAttribute::ENTITY_HP)
			{
				words = STR_HP + words;
			}
			else if (idAttributeBeChange == IdAttribute::ENTITY_ENERGY)
			{
				words = STR_EP + words;
			}
			managerUI->showWordsDrift(getParent(), getPosition() + Vec2(0.0f, 100.0f), words, color, duration);
		}
		managerUI->notify(ID_OBSERVER::HANDLE_HEAD, TYPE_OBSERVER_HANDLE_HEAD::SHOW_WORDS_DRIFT, false, i, valueChange, idAttributeBeChange, color, (double)duration);//界面刷新
	}
	if (idAttributeBeChange == IdAttribute::ENTITY_HP)
	{
		updateHpAll();
	}
}

void Entity::dealBreakEffect(const float &duration)
{
	//显示破衣效果
	auto managerUI = ManagerUI::getInstance();
	/*managerUI->notify(ID_OBSERVER::HANDLE_ENTITY, TYPE_OBSERVER_HANDLE_ENTITY::UPDATE_HP);*///界面刷新
	managerUI->showWordsDrift(getParent(), getPosition() + Vec2(0.0f, 100.0f), STR_BREAK, Color4B::RED, duration);
}

void Entity::dealBreak()
{
	auto cfgEntity = _dataEntity->getCfgEntity();
	auto breakTakes = _dataEntity->getAttribute(IdAttribute::ENTITY_BREAK_TAKES_NUM);
	auto urlPic = breakTakes > 0 ? cfgEntity.urlPicEntityBreak : cfgEntity.urlPicEntity;
	auto texture = Director::getInstance()->getTextureCache()->getTextureForKey(urlPic);
	_skin->setTexture(texture);
}

void Entity::dealDeadEffect(const float &duration)
{
	//显示死亡效果
	auto managerUI = ManagerUI::getInstance();
	/*managerUI->notify(ID_OBSERVER::HANDLE_ENTITY, TYPE_OBSERVER_HANDLE_ENTITY::UPDATE_HP);*///界面刷新
	managerUI->showWordsDrift(getParent(), getPosition() + Vec2(0.0f, 100.0f), STR_DEAD, Color4B::RED, duration);
}
