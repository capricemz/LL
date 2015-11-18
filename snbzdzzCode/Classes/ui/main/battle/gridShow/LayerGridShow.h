#pragma execution_character_set("utf-8")

#ifndef __UI_MAIN_SELECTED_LAYER_SELECTED_H__
#define __UI_MAIN_SELECTED_LAYER_SELECTED_H__

#include "cocos2d.h"
#include "common/observer/Observer.h"

USING_NS_CC;

using namespace std;

class LayerGridShow : public Layer, public Observer
{
public:
	CREATE_FUNC(LayerGridShow);

public:
	LayerGridShow();
	~LayerGridShow();

	virtual bool init();

	virtual void updateBySubject(va_list values);

	/*func ����ȫ�����ʱ�ص�*/
	void runAppearAction(const function<void()> &func = nullptr);
	/*func ����ȫ�����ʱ�ص�*/
	void runSkillRandom(const function<void()> &func = nullptr);
	/*postion ȫ��λ��
	funcOneOver һ�����Ӷ������ʱ����
	funcAllOver ����ȫ�����ʱ�ص�*/
	void runMstGridMoveFromAction(const Vec2 &postion, const function<void()> &funcOneOver = nullptr, const function<void()> &funcAllOver = nullptr);
	/*funcOneOver һ�����Ӷ������ʱ����
	funcAllOver ����ȫ�����ʱ�ص�*/
	void runMstGridTurnAction(const function<void()> &funcOneOver = nullptr, const function<void()> &funcAllOver = nullptr);
	/*indexMaidGrid Ů�͸��ӱ��
	postion ȫ��λ��
	funcOver һ�����Ӷ������ʱ����*/
	void runMaidGridMoveFromAction(const int &indexMaidGrid, const Vec2 &postion, const function<void()> &funcOver = nullptr);

private:
	void createSkin();
	void hideBg();
	
private:
	Layer *_skin;

};

#endif