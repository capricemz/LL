#pragma execution_character_set("utf-8")

#include "ManagerData.h"
#include "../config/ManagerCfg.h"

DataGrid::DataGrid() :
	_id(0),
	_indexGrid(0),
	_idSkill(0),
	_indexSkill(0),
	_dicAttribute({}),
	_dicAttributeCondition({}),
	_dataGridNext(nullptr)
{
}

DataGrid::~DataGrid()
{
	_dicAttribute.clear();
	_dicAttributeCondition.clear();
	_dataGridNext = nullptr;
}

bool DataGrid::init()
{
	auto isInit = false;
	do 
	{
		isInit = true;
	} while (0);
	return isInit;
}

CfgSkill DataGrid::getCfgSkill()
{
	auto cfgSkill = ManagerCfg::getInstance()->getDicDicCfgSkill()[_idSkill][_indexSkill];
	return cfgSkill;
}

bool DataGrid::isBasicAttributeExist()
{
	return getAttribute(IdAttribute::GRID_DAMAGE_PHYSICAL) > 0 || getAttribute(IdAttribute::GRID_BLOCK_PHYSICAL) > 0 || getAttribute(IdAttribute::GRID_DAMAGE_MAGIC) > 0 || getAttribute(IdAttribute::GRID_BLOCK_MAGIC) > 0;
}

bool DataGrid::isDamageAttributeExist()
{
	return getAttribute(IdAttribute::GRID_DAMAGE_PHYSICAL) > 0 || getAttribute(IdAttribute::GRID_DAMAGE_MAGIC) > 0;
}

bool DataGrid::isUnblockableExist()
{
	return getAttribute(IdAttribute::GRID_UNBLOCKABLE) > 0;
}

bool DataGrid::isQuickExist()
{
	return getAttribute(IdAttribute::GRID_QUICK) > 0;
}

void DataGrid::updateSkillEffect()
{
	auto cfgSkill = getCfgSkill();
	auto vecEffect = UtilString::split(cfgSkill.effect, "|");
	for (auto varEffect : vecEffect)
	{
		auto vec = UtilString::split(varEffect, ":");
		auto size = (int)vec.size();
		auto idAttribute = (IdAttribute)Value(vec[0]).asInt();
		if (idAttribute < IdAttribute::GRID_ATTRIBUTE_LAST)
		{
			auto value = size > 1 ? Value(vec[1]).asInt() : 1;
			setAttribute(idAttribute, value);
		}
		else
		{
			CCASSERT(size > 1, "HandleDataGrid::getDataGrid vec.size <= 1");
			setAttributeCondition(idAttribute, vec[1]);
		}
	}
}

int DataGrid::getAttribute(const IdAttribute &idAttribute)
{
	if (_dicAttribute.find(idAttribute) == _dicAttribute.end())
	{
		return 0;
	}
	else
	{
		return _dicAttribute[idAttribute];
	}
}

void DataGrid::setAttribute(const IdAttribute &idAttribute, const int &value)
{
	if (_dicAttribute.find(idAttribute) == _dicAttribute.end())
	{
		if (value != 0)
		{
			_dicAttribute.insert(std::make_pair(idAttribute, value));
		}
	}
	else
	{
		if (value == 0)
		{
			_dicAttribute.erase(idAttribute);
		}
		else
		{
			_dicAttribute[idAttribute] = value;
		}
	}
}

void DataGrid::addAttribute(const IdAttribute &idAttribute, const int &value)
{
	if (value == 0)
	{
		return;
	}
	if (_dicAttribute.find(idAttribute) == _dicAttribute.end())
	{
		_dicAttribute.insert(std::make_pair(idAttribute, value));
	}
	else
	{
		_dicAttribute[idAttribute] += value;
	}
}

std::string DataGrid::getAttributeCondition(const IdAttribute &idAttribute)
{
	if (_dicAttributeCondition.find(idAttribute) == _dicAttributeCondition.end())
	{
		return "";
	}
	else
	{
		return _dicAttributeCondition[idAttribute];
	}
}

void DataGrid::setAttributeCondition(const IdAttribute &idAttribute, const string &value)
{
	if (_dicAttributeCondition.find(idAttribute) == _dicAttributeCondition.end())
	{
		if (value != "")
		{
			_dicAttributeCondition.insert(std::make_pair(idAttribute, value));
		}
	}
	else
	{
		if (value == "")
		{
			_dicAttributeCondition.erase(idAttribute);
		}
		else
		{
			_dicAttributeCondition[idAttribute] = value;
		}
	}
}

void DataGrid::addAttributeCondition(const IdAttribute &idAttribute, const string &value)
{
	if (value == "")
	{
		return;
	}
	if (_dicAttributeCondition.find(idAttribute) == _dicAttributeCondition.end())
	{
		_dicAttributeCondition.insert(std::make_pair(idAttribute, value));
	}
	else
	{
		_dicAttributeCondition[idAttribute] += "+" + value;
	}
}

HandleDataGrid::HandleDataGrid() : _idDataGridNow(0), _indexGridBattle(0)
{
}

HandleDataGrid::~HandleDataGrid()
{
}

DataGrid * HandleDataGrid::getDataGrid()
{
	auto dataGrid = DataGrid::create();
	dataGrid->setId(_idDataGridNow++);
	return dataGrid;
}

int HandleDataGrid::getIndexGridBattle()
{
	auto indexGridBattle = _indexGridBattle;
	_indexGridBattle++;
	if (_indexGridBattle >= GRID_SELECTED_MAX)
	{
		_indexGridBattle = GRID_SELECTED_MAX;
	}
	return indexGridBattle;
}
