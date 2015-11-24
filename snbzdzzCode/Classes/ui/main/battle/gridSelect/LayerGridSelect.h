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
	/*显示出现动画,随后调用处理随机技能*/
	void runAppearAction();
	/*处理随机技能，随后调用显示女仆选择格子出现动画*/
	void runSkillRandom();
	/*显示女仆选择格子出现动画*/
	void showAppearGridSelectMaid(const Vec2 &postion);
	/*显示消失动画，随后调用战斗格子动画*/
	void runDisappearAction();
	/*funcOneOver 一个格子动作完成时调用
	funcAllOver 动作全部完成时回调*/
	void runMaidGridPlaySpecialSthGenerate(const function<void()> &funcOneOver = nullptr, CallFunc *funcAllOver = nullptr);

	void runMaidGridScaleBig(const int &indexMaidGrid, CallFunc *funcOver = nullptr);
	void runMaidGridScaleSmall(const int &indexMaidGrid, CallFunc *funcOver = nullptr);

private:
	void createSkin();

	void onGridLayoutTouch(Ref *ref, Widget::TouchEventType type, const int &indexGrid);
	/*postion 起始位置
	funcOneOver 一个格子动作完成时调用
	funcAllOver 动作全部完成时回调*/
	void runActionGridSelectMaidMoveFrom(const Vec2 &postion, const function<void()> &funcOneOver = nullptr, const function<void()> &funcAllOver = nullptr);
	/*funcOneOver 一个格子动作完成时调用
	funcAllOver 动作全部完成时回调*/
	void runActionGridSelectMaidTurn(const function<void()> &funcOneOver = nullptr, const function<void()> &funcAllOver = nullptr);
	/*indexMaidGrid 女仆格子编号
	postion 起始位置
	funcOver 格子动作完成时调用*/
	void runActionGridSelectMoveFromSelectedOne(const int &indexMaidGrid, const function<void()> &funcOver = nullptr);
	/*funcOver 格子动作完成时调用*/
	void runActionGridSelectMoveFromSelectedAll(const function<void()> &funcOneOver = nullptr, const function<void()> &funcAllOver = nullptr);

	void runMaidGridMoveFromActionTakeBack(const function<void()> &funcOneOver = nullptr, const function<void()> &funcAllOver = nullptr);
	
private:
	Layer *_skin;
	NodeCircleLine *_nodeCircleLine;

};

#endif