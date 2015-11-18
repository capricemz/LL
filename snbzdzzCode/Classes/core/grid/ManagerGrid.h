#pragma execution_character_set("utf-8")

#ifndef __CORE_GRID_MANAGER_GRID_H__
#define __CORE_GRID_MANAGER_GRID_H__

#include "cocos2d.h"
#include "Grid.h"
#include "data/data/ManagerData.h"

USING_NS_CC;

class ManagerGrid
{
public:
	static ManagerGrid * getInstance();
	static void destoryInstance();

public:
	~ManagerGrid();

	void setAroundGridCanMoveOver(const int &indexGrid);
	bool getIsGridMoveOut(const int &index, const Vec2 &postionTouchMove, Vec2 &postionLayoutWorldMoveOver);
	bool getIsGridMoveToLast(int &indexLast, const float &rotation, const Vec2 &positionBegan);
	bool getIsGridMoveOver(const Vec2 &postionTouchMove, Vec2 &postionLayoutWorldMoveOver, int &indexGridMoveOver);
	
	void linkDataGridSelected();

	void dealBattle();
	
public:
	Map<int, Grid *> getDicGridMaidSelect() const { return _dicGridMaidSelect; }
	void insertGridMaidSelect(const int &idGrid, Grid *grid) { _dicGridMaidSelect.insert(idGrid, grid); }

	Map<int, Grid *> getDicGridMstShow() const { return _dicGridMstShow; }
	void insertGridMstShow(const int &idGrid, Grid *grid) { _dicGridMstShow.insert(idGrid, grid); }
	void clearDicGridMstShow() { _dicGridMstShow.clear(); };

	Map<int, Grid *> getDicGridMaidShow() const { return _dicGridMaidShow; }
	void insertGridMaidShow(const int &idGrid, Grid *grid) { _dicGridMaidShow.insert(idGrid, grid); }
	void clearDicGridMaidShow() { _dicGridMaidShow.clear(); };

	Map<int, Grid *> getDicGridMstSelected() const { return _dicGridMstSelected; }
	void insertGridMstSelected(const int &idGrid, Grid *grid) { _dicGridMstSelected.insert(idGrid, grid); }

	Map<int, Grid *> getDicGridMaidSelected() const { return _dicGridMaidSelected; }
	void insertGridMaidSelected(const int &idGrid, Grid *grid) { _dicGridMaidSelected.insert(idGrid, grid); }

	Map<int, Grid *> getDicGridBattle() const { return _dicGridBattle; }
	void insertGridBattle(const int &idGrid, Grid *grid) { _dicGridBattle.insert(idGrid, grid); }

	Vector<DataGrid *> getVecDataGridMaidSelected() const { return _vecDataGridMaidSelected; }
	void pushDataGridMaidSelected(DataGrid *dataGrid) { _vecDataGridMaidSelected.pushBack(dataGrid); }
	void popDataGridMaidSelected() { _vecDataGridMaidSelected.popBack(); }
	void clearVecDataGridMaidSelected() { _vecDataGridMaidSelected.clear(); }
	bool getIsVecDataGridMaidSelectedFull() const { return _vecDataGridMaidSelected.size() == GRID_SELECTED_MAX; }
	
private:
	void dealQuick(DataGrid *dataGridCase, DataGrid *dataGridTakes, DataEntity *dataEntityCase, DataEntity *dataEntityTakes);
	void dealDamage(DataGrid *dataGridCase, DataGrid *dataGridTakes, DataEntity *dataEntityCase, DataEntity *dataEntityTakes);
	void dealRestoreCostHp(DataGrid *dataGrid, DataEntity *dataEntity);
	void dealRestoreCostEnergy(DataGrid *dataGrid, DataEntity *dataEntity);
	void dealDamageAttributeCondition(DataGrid *dataGridCase, DataGrid *dataGridTakes, const int &damagePhysical, const int &damageMagic, DataEntity *dataEntityCase, DataEntity *dataEntityTakes);
	void dealAttributeCondition(DataGrid *dataGridCase, const IdAttribute &idAttribute, DataGrid *dataGridTakes, DataEntity *dataEntity, const int &value2Count = -1, const int &value2Judge = -1);
	void dealEffectiveEach(vector<string> &args, const int &value2Count);
	/*处理n个回合后生效效果
	dataGridCase 造成效果格子
	round 第n回合后
	args 剩余参数*/
	void dealEffectiveRound(DataGrid *dataGridCase, const int &round, const vector<string> &args);
	/*处理之后持续n个回合效果
	dataGridCase 造成效果格子
	round 持续n回合数
	args 剩余参数*/
	void dealEffectiveRoundCount(DataGrid *dataGridCase, const int &round, const vector<string> &args);
	/*处理效果
	dataGrid 造成效果格子
	args 剩余参数*/
	void dealEffective(DataGrid *dataGrid, const vector<string> &args);		
	
private:
	Map<int, Grid *> _dicGridMaidSelect;
	Map<int, Grid *> _dicGridMstShow;
	Map<int, Grid *> _dicGridMaidShow;
	Map<int, Grid *> _dicGridMstSelected;
	Map<int, Grid *> _dicGridMaidSelected;
	Map<int, Grid *> _dicGridBattle;
	Vector<DataGrid *> _vecDataGridMaidSelected;
	
};

#endif