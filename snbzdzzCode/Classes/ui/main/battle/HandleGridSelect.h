#pragma execution_character_set("utf-8")

#ifndef __UI_MAIN_BATTLE_HANDLE_GRID_H__
#define __UI_MAIN_BATTLE_HANDLE_GRID_H__

#include "cocos2d.h"
#include "ui/UILayout.h"
#include "NodeCircleLine.h"
#include "common/observer/Observer.h"

USING_NS_CC;
using namespace ui;
using namespace std;

class HandleGridSelect : public Ref, public Observer
{
public:
	CREATE_FUNC(HandleGridSelect);

public:
	HandleGridSelect();
	~HandleGridSelect();

	virtual bool init();

	void setSkin(Layout *skin);

	virtual void updateBySubject(va_list values);
	/*postion 起始位置
	funcOneOver 一个格子动作完成时调用
	funcAllOver 动作全部完成时回调*/
	void runMaidGridMoveFromAction(const Vec2 &postion, const function<void()> &funcOneOver = nullptr, const function<void()> &funcAllOver = nullptr);
	/*indexMaidGrid 女仆格子编号
	postion 起始位置
	funcOver 格子动作完成时调用*/
	void runMaidGridMoveFromAction(const int &indexMaidGrid, const function<void()> &funcOver = nullptr);
	/*funcOver 格子动作完成时调用*/
	void runMaidGridMoveFromAction(const function<void()> &funcOneOver = nullptr, const function<void()> &funcAllOver = nullptr);
	/*funcOneOver 一个格子动作完成时调用
	funcAllOver 动作全部完成时回调*/
	void runMaidGridTurnAction(const function<void()> &funcOneOver = nullptr, const function<void()> &funcAllOver = nullptr);
	/*funcOneOver 一个格子动作完成时调用
	funcAllOver 动作全部完成时回调*/
	void runMaidGridPlaySpecialSthGenerate(const function<void()> &funcOneOver = nullptr, CallFunc *funcAllOver = nullptr);

	void runMaidGridScaleBig(const int &indexMaidGrid, CallFunc *funcOver = nullptr);
	void runMaidGridScaleSmall(const int &indexMaidGrid, CallFunc *funcOver = nullptr);

private:
	void onGridLayoutTouch(Ref *ref, Widget::TouchEventType type, const int &indexGrid);

	void runMaidGridMoveFromActionTakeBack(const function<void()> &funcOneOver = nullptr, const function<void()> &funcAllOver = nullptr);
	
private:
	Layout *_skin;
	NodeCircleLine *_nodeCircleLine;

};

#endif