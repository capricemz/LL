#pragma execution_character_set("utf-8")

#include "ManagerData.h"
#include "../config/ManagerCfg.h"

HandleDataGrade::HandleDataGrade() : _idGradeLast(0)
{
}

HandleDataGrade::~HandleDataGrade()
{
}

void HandleDataGrade::setIdGradeLast()
{
	_idGradeLast = getIdGrade() - 1;
}

CfgGrade HandleDataGrade::getCfgGradeLast()
{
	auto dicCfgGrade = ManagerCfg::getInstance()->getDicCfgGrade();
	return dicCfgGrade[_idGradeLast];
}

bool HandleDataGrade::getIsGradeUp()//获取是否等级提升
{
	auto idGrade = getIdGrade();
	return idGrade > _idGradeLast + 1;
}

bool HandleDataGrade::getIsGradeMax()
{
	auto handleDatIncome = ManagerData::getInstance()->getHandleDataIncome();
	auto value = handleDatIncome->getThing(IdThing::EXP);//当前经验
	auto managerCfg = ManagerCfg::getInstance();
	auto dicCfgGrade = managerCfg->getDicCfgGrade();
	auto id = 1000;
	auto isMax = false;
	while (true)
	{
		if (dicCfgGrade.find(id) == dicCfgGrade.end())
		{
			isMax = true;
			break;
		}

		auto cfgGradeTemp = dicCfgGrade[id];

		if (value < cfgGradeTemp.exp)
		{
			break;
		}

		id++;
	}//获取当前等级配置
	return isMax;
}

int HandleDataGrade::getIdGrade()
{
	auto handleDatIncome = ManagerData::getInstance()->getHandleDataIncome();
	auto value = handleDatIncome->getThing(IdThing::EXP);//当前经验
	auto managerCfg = ManagerCfg::getInstance();
	auto dicCfgGrade = managerCfg->getDicCfgGrade();
	auto id = 1000;
	while (true)
	{
		if (dicCfgGrade.find(id) == dicCfgGrade.end())
		{
			break;
		}

		auto cfgGradeTemp = dicCfgGrade[id];

		if (value < cfgGradeTemp.exp)
		{
			break;
		}

		id++;
	}//获取当前等级配置
	return id;
}

int HandleDataGrade::getGrade()
{
	auto handleDatIncome = ManagerData::getInstance()->getHandleDataIncome();
	auto value = handleDatIncome->getThing(IdThing::EXP);//当前经验
	auto managerCfg = ManagerCfg::getInstance();
	auto dicCfgGrade = managerCfg->getDicCfgGrade();
	auto id = 1000;
	auto grade = 1;
	while (true)
	{
		if (dicCfgGrade.find(id) == dicCfgGrade.end())
		{
			break;
		}

		auto cfgGradeTemp = dicCfgGrade[id];

		if (value < cfgGradeTemp.exp)
		{
			break;
		}

		grade = cfgGradeTemp.index;

		id++;
	}//获取当前等级配置
	return grade;
}

string HandleDataGrade::getGradeEffect()
{
	auto handleDatIncome = ManagerData::getInstance()->getHandleDataIncome();
	auto value = handleDatIncome->getThing(IdThing::EXP);//当前经验
	auto managerCfg = ManagerCfg::getInstance();
	auto dicCfgGrade = managerCfg->getDicCfgGrade();
	auto id = 1000;
	string effect = "";
	while (true)
	{
		if (dicCfgGrade.find(id) == dicCfgGrade.end())
		{
			break;
		}

		auto cfgGradeTemp = dicCfgGrade[id];

		if (value < cfgGradeTemp.exp)
		{
			break;
		}

		effect = cfgGradeTemp.effect;

		id++;
	}//获取当前等级配置
	return effect;
}

int HandleDataGrade::getGradeExpNow()
{
	auto handleDatIncome = ManagerData::getInstance()->getHandleDataIncome();
	auto value = handleDatIncome->getThing(IdThing::EXP);//当前经验
	auto managerCfg = ManagerCfg::getInstance();
	auto dicCfgGrade = managerCfg->getDicCfgGrade();
	auto id = 1000;
	auto exp = 0;
	while (true)
	{
		if (dicCfgGrade.find(id) == dicCfgGrade.end())
		{
			break;
		}

		auto cfgGradeTemp = dicCfgGrade[id];

		if (value < cfgGradeTemp.exp)
		{
			break;
		}

		exp = value - cfgGradeTemp.exp;

		id++;
	}//获取当前等级配置
	return exp;
}

int HandleDataGrade::getGradeExpNeed()
{
	auto handleDatIncome = ManagerData::getInstance()->getHandleDataIncome();
	auto value = handleDatIncome->getThing(IdThing::EXP);//当前经验
	auto managerCfg = ManagerCfg::getInstance();
	auto dicCfgGrade = managerCfg->getDicCfgGrade();
	auto id = 1000;
	auto exp = 0;
	while (true)
	{
		if (dicCfgGrade.find(id) == dicCfgGrade.end())
		{
			exp = 0;
			break;
		}

		auto cfgGradeTemp = dicCfgGrade[id];

		if (value < cfgGradeTemp.exp)
		{
			exp = cfgGradeTemp.exp - exp;
			break;
		}

		exp = cfgGradeTemp.exp;

		id++;
	}//获取当前等级配置
	return exp;
}
