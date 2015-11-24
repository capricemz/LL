#pragma execution_character_set("utf-8")

#ifndef __UI_MAIN_BATTLE_GRID_SELECT_LAYER_GRID_SELECT_H__
#define __UI_MAIN_BATTLE_GRID_SELECT_LAYER_GRID_SELECT_H__

#include "cocos2d.h"
#include "ui/UILayout.h"
#include "NodeCircleLine.h"
#include "common/observer/Observer.h"

USING_NS_CC;
using namespace ui;
using namespace std;

class LayerGridSelect : public Layer, public Observer
{
public:
	CREATE_FUNC(LayerGridSelect);

public:
	LayerGridSelect();
	~LayerGridSelect();

	virtual bool init();

	virtual void updateBySubject(va_list values);
	/*��ʾ���ֶ���,�����ô����������*/
	void runAppearAction();
	/*����������ܣ���������ʾŮ��ѡ����ӳ��ֶ���*/
	void runSkillRandom();
	/*��ʾŮ��ѡ����ӳ��ֶ���*/
	void showAppearGridSelectMaid(const Vec2 &postion);
	/*��ʾ��ʧ������������ս�����Ӷ���*/
	void runDisappearAction();
	/*funcOneOver һ�����Ӷ������ʱ����
	funcAllOver ����ȫ�����ʱ�ص�*/
	void runMaidGridPlaySpecialSthGenerate(const function<void()> &funcOneOver = nullptr, CallFunc *funcAllOver = nullptr);

	void runMaidGridScaleBig(const int &indexMaidGrid, CallFunc *funcOver = nullptr);
	void runMaidGridScaleSmall(const int &indexMaidGrid, CallFunc *funcOver = nullptr);

private:
	void createSkin();

	void onGridLayoutTouch(Ref *ref, Widget::TouchEventType type, const int &indexGrid);
	/*postion ��ʼλ��
	funcOneOver һ�����Ӷ������ʱ����
	funcAllOver ����ȫ�����ʱ�ص�*/
	void runActionGridSelectMaidMoveFrom(const Vec2 &postion, const function<void()> &funcOneOver = nullptr, const function<void()> &funcAllOver = nullptr);
	/*funcOneOver һ�����Ӷ������ʱ����
	funcAllOver ����ȫ�����ʱ�ص�*/
	void runActionGridSelectMaidTurn(const function<void()> &funcOneOver = nullptr, const function<void()> &funcAllOver = nullptr);
	/*indexMaidGrid Ů�͸��ӱ��
	postion ��ʼλ��
	funcOver ���Ӷ������ʱ����*/
	void runActionGridSelectMoveFromSelectedOne(const int &indexMaidGrid, const function<void()> &funcOver = nullptr);
	/*funcOver ���Ӷ������ʱ����*/
	void runActionGridSelectMoveFromSelectedAll(const function<void()> &funcOneOver = nullptr, const function<void()> &funcAllOver = nullptr);

	void runMaidGridMoveFromActionTakeBack(const function<void()> &funcOneOver = nullptr, const function<void()> &funcAllOver = nullptr);
	
private:
	Layer *_skin;
	NodeCircleLine *_nodeCircleLine;

};

#endif