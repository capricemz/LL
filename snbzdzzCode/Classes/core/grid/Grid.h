#pragma execution_character_set("utf-8")

#ifndef __CORE_GRID_GRID_H__
#define __CORE_GRID_GRID_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "data/data/ManagerData.h"

USING_NS_CC;
using namespace ui;
using namespace std;

class Grid : public Node
{
public:
	CREATE_FUNC(Grid);

public:
	Grid();
	~Grid();

	virtual bool init();

	void createDataGrid();//释放旧的DataGrid构建新的DataGrid
	void createDataGridSkill(const bool &isMst);
	void setDataGrid(DataGrid *dataGrid);
	void updateSkinAttribute();

	Layout *getLayoutTouch();
	
	/*更新显示内容，显示卡牌、金币、石头、冰块、陷阱等*/
	void updateContent(const bool &isBack);
	/*移动
	postion 其实位置 全局坐标
	isBack 是否为显示背面
	scaleBegan 起始缩放
	scaleEnd 终点缩放
	offsetEnd 终点偏移 Vec2::ZERO表示移动到添加位置
	func 动作结束时调用*/
	void moveFrom(const Vec2 &postion, const bool &isBack, const float &scaleBegan, const float &scaleEnd, const Vec2 & offsetEnd, const function<void()> &func = nullptr);
	/*翻转
	func 动作结束时调用*/
	void turn(const function<void()> &func = nullptr);
	/*扔到
	psotion 终点位置 全局坐标
	angleEnd 终止转动角度
	func 动作结束时调用*/
	void throwTo(const Vec2 &postion, const float &angleEnd, const function<void ()> &func = nullptr);
	/*播放特殊格子生成
	func 动作结束时调用*/
	void playSpecialSthGenerate(const function<void()> &func = nullptr);
	/*获取特殊格子使用动画时间*/
	float durationPlaySpecialSthBeUse();
	/*播放特殊格子使用
	func 动作结束时调用*/
	void playSpecialSthBeUse(const function<void()> &func = nullptr);
	/*是否能够划过选中*/
	bool isCanMoveOver() const;
	void scaleBig(const bool &isAlignTop = true, CallFunc *funcOver = nullptr);
	void scaleSmall(CallFunc *funcOver = nullptr);
	/*重置skin*/
	void resetSkin();
	/*重置特殊物品*/
	void resetSpecialSth();
	
public:
	int getIndexGrid() const
	{
		return _indexGrid;
	}
	void setIndexGrid(int val)
	{
		_indexGrid = val;
	}

	DataGrid * getDataGrid() const
	{
		return _dataGrid;
	}

	void setIsCanMoveOver(bool val)
	{
		_isCanMoveOver = val;
	}

	bool getIsNeedTurn() const
	{
		return _isNeedTurn;
	}
	void setIsNeedTurn(bool val)
	{
		_isNeedTurn = val;
	}

	bool getIsCanScaleBig() const
	{
		return _isCanScaleBig;
	}

	bool getIsCanScaleSmall() const 
	{
		return _isCanScaleSmall;
	}
	
	bool getIsCard();//是否为卡牌
	bool getIsNotCard();//是否为特殊格子
	bool getIsIceMelting();//是否为播放冰块融化
	
private:
	void createSkin();
	
private:
	Node *_skin;
	int _indexGrid;
	DataGrid *_dataGrid;

	bool _isCanMoveOver;
	
	float _durationTurn;
	bool _isNeedTurn;
	bool _isCanScaleBig;
	bool _isCanScaleSmall;
	
};

#endif