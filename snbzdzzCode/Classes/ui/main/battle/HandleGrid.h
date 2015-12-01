#pragma execution_character_set("utf-8")

#ifndef __UI_MAIN_BATTLE_HANDLE_GRID_SELECTED_H__
#define __UI_MAIN_BATTLE_HANDLE_GRID_SELECTED_H__

#include "cocos2d.h"
#include "ui/UILayout.h"
#include "common/observer/Observer.h"
#include "core/grid/Grid.h"

USING_NS_CC;
using namespace ui;
using namespace std;

class HandleGrid : public Ref, public Observer
{
public:
	CREATE_FUNC(HandleGrid);

public:
	HandleGrid();
	~HandleGrid();

	virtual bool init();

	void setSkin(Layout *skin);
	
	virtual void updateBySubject(va_list values);
	/*��ʾ����ѡ�и��ӳ��ֶ���, ��������Ӹ���ѡ���
	postion ȫ��λ��*/
	void showAppearGridSelectedMst(const Vec2 &postion);
	/*��ʾŮ�͸��ӴӸ���ѡ���ƶ�������ѡ�еĶ���*/
	void runActionGridSelectedMaidMoveFromSelect(const int &indexGridSelected, const int &indexGridSelect);
	
	void resetSkin();
	
private:
	/*postion ȫ��λ��
	funcOneOver һ�����Ӷ������ʱ����
	funcAllOver ����ȫ�����ʱ�ص�*/
	void runActionGridSelectedMstMoveFrom(const Vec2 &postion, const function<void()> &funcOneOver = nullptr, const function<void()> &funcAllOver = nullptr);
	/*funcOneOver һ�����Ӷ������ʱ����
	funcAllOver ����ȫ�����ʱ�ص�*/
	void runActionGridSelectedMstTurn(const function<void()> &funcOneOver = nullptr, const function<void()> &funcAllOver = nullptr);

	void runGridMoveAndThrow();//�ֿ�ʼִ��
	void gridMoveFrom(const int &indexGrid);
	void gridMoveFromOver(Grid *grid, const bool &isMst);
	void gridSpecialOrDelayOver(Grid *grid, const bool &isMst);
	void gridThrowToOver(Grid *grid, const bool &isMst);

	void updateGrid(const int &idDataGrid);//ˢ�¸�����ʾ
	
private:
	Layout *_skin;

};

#endif