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

	/*func 动作全部完成时回调*/
	void runAppearAction(const function<void()> &func = nullptr);
	/*func 动作全部完成时回调*/
	void runSkillRandom(const function<void()> &func = nullptr);
	/*postion 全局位置
	funcOneOver 一个格子动作完成时调用
	funcAllOver 动作全部完成时回调*/
	void runMstGridMoveFromAction(const Vec2 &postion, const function<void()> &funcOneOver = nullptr, const function<void()> &funcAllOver = nullptr);
	/*funcOneOver 一个格子动作完成时调用
	funcAllOver 动作全部完成时回调*/
	void runMstGridTurnAction(const function<void()> &funcOneOver = nullptr, const function<void()> &funcAllOver = nullptr);
	/*indexMaidGrid 女仆格子编号
	postion 全局位置
	funcOver 一个格子动作完成时调用*/
	void runMaidGridMoveFromAction(const int &indexMaidGrid, const Vec2 &postion, const function<void()> &funcOver = nullptr);

private:
	void createSkin();
	void hideBg();
	
private:
	Layer *_skin;

};

#endif