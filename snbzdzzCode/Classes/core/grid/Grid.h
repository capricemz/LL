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

	void createDataGrid();//�ͷžɵ�DataGrid�����µ�DataGrid
	void createDataGridSkill(const bool &isMst);
	void setDataGrid(DataGrid *dataGrid);
	void updateSkinAttribute();

	Layout *getLayoutTouch();
	
	/*������ʾ���ݣ���ʾ���ơ���ҡ�ʯͷ�����顢�����*/
	void updateContent(const bool &isBack);
	/*�ƶ�
	postion ��ʵλ�� ȫ������
	isBack �Ƿ�Ϊ��ʾ����
	scaleBegan ��ʼ����
	scaleEnd �յ�����
	offsetEnd �յ�ƫ�� Vec2::ZERO��ʾ�ƶ������λ��
	func ��������ʱ����*/
	void moveFrom(const Vec2 &postion, const bool &isBack, const float &scaleBegan, const float &scaleEnd, const Vec2 & offsetEnd, const function<void()> &func = nullptr);
	/*��ת
	func ��������ʱ����*/
	void turn(const function<void()> &func = nullptr);
	/*�ӵ�
	psotion �յ�λ�� ȫ������
	angleEnd ��ֹת���Ƕ�
	func ��������ʱ����*/
	void throwTo(const Vec2 &postion, const float &angleEnd, const function<void ()> &func = nullptr);
	/*���ż���Ч��������Ʒ����
	func ��������ʱ����*/
	void playSpecialSthGenerate(const function<void()> &func = nullptr);
	/*����������Ʒʹ��
	func ��������ʱ����*/
	void playSpecialSthBeUse(const function<void()> &func = nullptr);
	/*�Ƿ��ܹ�����ѡ��*/
	bool isCanMoveOver() const;
	void scaleBig(const bool &isAlignTop = true, CallFunc *funcOver = nullptr);
	void scaleSmall(CallFunc *funcOver = nullptr);
	/*����skin*/
	void resetSkin();
	/*����������Ʒ*/
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
	
	bool getIsCard();//�Ƿ�Ϊ����
	bool getIsNotCard();
	
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