#pragma execution_character_set("utf-8")

#include "ManagerData.h"
#include "../config/ManagerCfg.h"

HandleDataGrade::HandleDataGrade() : _idGradeLast(ID_GRADE_FIRST)
{
}

HandleDataGrade::~HandleDataGrade()
{
}

void HandleDataGrade::setIdGradeLast()
{
	_idGradeLast = getIdGrade();
}

CfgGrade HandleDataGrade::getCfgGradeLast()
{
	auto dicCfgGrade = ManagerCfg::getInstance()->getDicCfgGrade();
	return dicCfgGrade[_idGradeLast];
}

bool HandleDataGrade::getIsGradeUp()//��ȡ�Ƿ�ȼ�����
{
	auto idGrade = getIdGrade();
	return idGrade > _idGradeLast;
}

bool HandleDataGrade::getIsGradeMax()
{
	auto handleDatIncome = ManagerData::getInstance()->getHandleDataIncome();
	auto value = handleDatIncome->getThing(IdThing::EXP);//��ǰ����
	auto managerCfg = ManagerCfg::getInstance();
	auto dicCfgGrade = managerCfg->getDicCfgGrade();
	auto id = ID_GRADE_FIRST;
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
	}//��ȡ��ǰ�ȼ�����
	return isMax;
}

int HandleDataGrade::getIdGrade()
{
	auto handleDatIncome = ManagerData::getInstance()->getHandleDataIncome();
	auto value = handleDatIncome->getThing(IdThing::EXP);//��ǰ����
	auto managerCfg = ManagerCfg::getInstance();
	auto dicCfgGrade = managerCfg->getDicCfgGrade();
	auto id = ID_GRADE_FIRST;
	auto idGrade = 0;
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
		idGrade = cfgGradeTemp.id;
		id++;
	}//��ȡ��ǰ�ȼ�����
	return idGrade;
}

int HandleDataGrade::getGrade()
{
	auto handleDatIncome = ManagerData::getInstance()->getHandleDataIncome();
	auto value = handleDatIncome->getThing(IdThing::EXP);//��ǰ����
	auto managerCfg = ManagerCfg::getInstance();
	auto dicCfgGrade = managerCfg->getDicCfgGrade();
	auto id = ID_GRADE_FIRST;
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
	}//��ȡ��ǰ�ȼ�����
	return grade;
}

string HandleDataGrade::getGradeEffect()
{
	auto handleDatIncome = ManagerData::getInstance()->getHandleDataIncome();
	auto value = handleDatIncome->getThing(IdThing::EXP);//��ǰ����
	auto managerCfg = ManagerCfg::getInstance();
	auto dicCfgGrade = managerCfg->getDicCfgGrade();
	auto id = ID_GRADE_FIRST;
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
	}//��ȡ��ǰ�ȼ�����
	return effect;
}

int HandleDataGrade::getGradeExpNow()
{
	auto handleDatIncome = ManagerData::getInstance()->getHandleDataIncome();
	auto value = handleDatIncome->getThing(IdThing::EXP);//��ǰ����
	auto managerCfg = ManagerCfg::getInstance();
	auto dicCfgGrade = managerCfg->getDicCfgGrade();
	auto id = ID_GRADE_FIRST;
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
	}//��ȡ��ǰ�ȼ�����
	return exp;
}

int HandleDataGrade::getGradeExpNeed()
{
	auto handleDatIncome = ManagerData::getInstance()->getHandleDataIncome();
	auto value = handleDatIncome->getThing(IdThing::EXP);//��ǰ����
	auto managerCfg = ManagerCfg::getInstance();
	auto dicCfgGrade = managerCfg->getDicCfgGrade();
	auto id = ID_GRADE_FIRST;
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
	}//��ȡ��ǰ�ȼ�����
	return exp;
}
