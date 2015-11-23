#pragma execution_character_set("utf-8")

#include "HandleHead.h"
#include "ui/UILoadingBar.h"
#include "data/data/ManagerData.h"
#include "ui/ManagerUI.h"

HandleHead::HandleHead() : _skin(nullptr)
{
}

HandleHead::~HandleHead()
{
	ManagerUI::getInstance()->detach(this);
	_skin = nullptr;
}

bool HandleHead::init()
{
	auto isInit = false;
	do
	{
		idObserverSet(ID_OBSERVER::HANDLE_HEAD);
		ManagerUI::getInstance()->attach(this);

		isInit = true;
	} while (0);
	return isInit;
}

void HandleHead::updateBySubject(va_list values)
{
	auto type = va_arg(values, TYPE_OBSERVER_HANDLE_HEAD);
	if (type == TYPE_OBSERVER_HANDLE_HEAD::UPDATE_HP)
	{
		auto isMst = va_arg(values, bool);
		auto name = isMst ? "layoutMst0" : "layoutMaid0";
		auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
		auto dataEntity = isMst ? handleDataEntity->getDataEntityMst() : handleDataEntity->getDataEntityMaid();
		updateBarHp(name, dataEntity);
	}
	else if (type == TYPE_OBSERVER_HANDLE_HEAD::UPDATE_HP_ALL)
	{
		auto isMst = va_arg(values, bool);
		for (auto i = 0; i < ENTITY_BATTLE_MAX; i++)
		{
			auto name = isMst ? "layoutMst" : "layoutMaid" + Value(i).asString();
			auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
			auto dataEntity = isMst ? handleDataEntity->getVecDataEntityMst().at(i) : handleDataEntity->getVecDataEntityMaid().at(i);
			updateBarHp(name, dataEntity);
		}
	}
	else if (type == TYPE_OBSERVER_HANDLE_HEAD::UPDATE_ENERGY)
	{
		auto isMst = va_arg(values, bool);
		auto name = isMst ? "layoutEnergyMst" : "layoutEnergyMaid";
		auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
		auto dataEntity = isMst ? handleDataEntity->getDataEntityMst() : handleDataEntity->getDataEntityMaid();
		updateBarEnergy(name, dataEntity);
	}
}

void HandleHead::setSkin(Layout *skin)
{
	_skin = skin;
	for (int i = 0; i < 6; i++)
	{
		auto index = i % 3;
		auto isMst = i < 3;
		auto layout = (Layout *)_skin->getChildByName(isMst ? "layoutMst" + Value(index).asString() : "layoutMaid" + Value(index).asString());
		auto spriteIcon = (Sprite *)layout->getChildByName("spriteIcon");
	}
	for (size_t i = 0; i < 2; i++)
	{
		auto isMst = i < 1;
		auto name = isMst ? "layoutEnergyMst" : "layoutEnergyMaid";
		auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
		auto dataEntity = isMst ? handleDataEntity->getDataEntityMst() : handleDataEntity->getDataEntityMaid();
		updateBarEnergy(name,dataEntity);
	}
}

cocos2d::Vec2 HandleHead::getPostionHeadIcon(const int &type, const int &index)
{
	auto layoutMst = (Layout *)_skin->getChildByName((type == 0 ? "layoutMaid" : "layoutMst") + Value(index).asString());
	auto postion = layoutMst->getParent()->convertToWorldSpace(layoutMst->getPosition());
	return postion;
}

void HandleHead::resetSkin()
{
	for (int i = 0; i < 6; i++)
	{
		auto index = i % 3;
		auto layout = (Layout *)_skin->getChildByName(i < 3 ? "layoutMaid" + Value(index).asString() : "layoutMst" + Value(index).asString());
		auto spriteIcon = (Sprite *)layout->getChildByName("spriteIcon");
	}
}

void HandleHead::updateBarHp(const std::string &name, DataEntity *dataEntity)
{
	auto hp = dataEntity->getAttribute(IdAttribute::ENTITY_HP);
	auto hpMax = dataEntity->getAttribute(IdAttribute::ENTITY_HP_MAX);

	auto layout = (Layout *)_skin->getChildByName(name);
	auto bar = (LoadingBar *)layout->getChildByName("spriteHpBg")->getChildByName("barHp");
	bar->setPercent(((float)hp / (float)hpMax) * 100.0f);
}

void HandleHead::updateBarEnergy(const std::string &name, DataEntity *dataEntity)
{
	auto energy = dataEntity->getAttribute(IdAttribute::ENTITY_ENERGY);
	auto energyMax = dataEntity->getAttribute(IdAttribute::ENTITY_ENERGY_MAX);

	auto layout = (Layout *)_skin->getChildByName(name);
	auto bar = (LoadingBar *)layout->getChildByName("barEnergy");
	bar->setPercent(((float)energy / (float)energyMax) * 100.0f);
}
