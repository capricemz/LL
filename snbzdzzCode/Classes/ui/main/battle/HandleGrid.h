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
	/*显示怪物选中格子出现动画, 随后调用添加格子选择层
	postion 全局位置*/
	void showAppearGridSelectedMst(const Vec2 &postion);
	/*显示女仆格子从格子选择移动到格子选中的动画*/
	void runActionGridSelectedMaidMoveFromSelect(const int &indexGridSelected, const int &indexGridSelect);
	
	void resetSkin();
	
private:
	/*postion 全局位置
	funcOneOver 一个格子动作完成时调用
	funcAllOver 动作全部完成时回调*/
	void runActionGridSelectedMstMoveFrom(const Vec2 &postion, const function<void()> &funcOneOver = nullptr, const function<void()> &funcAllOver = nullptr);
	/*funcOneOver 一个格子动作完成时调用
	funcAllOver 动作全部完成时回调*/
	void runActionGridSelectedMstTurn(const function<void()> &funcOneOver = nullptr, const function<void()> &funcAllOver = nullptr);

	void runGridMoveAndThrow();//轮开始执行
	void gridMoveFrom(const int &indexGrid);
	void gridMoveFromOver(Grid *grid, const bool &isMst);
	void gridThrowToOrPlayOver(Grid *grid, const bool &isMst);

	void updateGrid(const int &idDataGrid);//刷新格子显示
	
private:
	Layout *_skin;

};

#endif