#pragma execution_character_set("utf-8")

#ifndef __UI_MAIN_BATTLE_CATCH_LAYER_CATCH_H__
#define __UI_MAIN_BATTLE_CATCH_LAYER_CATCH_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "data/define/DefinesValue.h"

USING_NS_CC;
using namespace ui;

class LayerCatch : public Layer
{
public:
	CREATE_FUNC(LayerCatch);

public:
	LayerCatch();
	~LayerCatch();

	virtual bool init();
	/*func 动作全部完成时回调*/
	void runAppearAction(const function<void()> &func = nullptr);
	
private:
	void createSkin();
	void addTouchEvent();

	void updateIndexRemain();//更新数据
	void getTypeSelectedMst();

	void doWait();//执行等待动画
	void doReach();//执行出动画
	void showResult();

	void onTouchBtnSelect(Ref *ref, Widget::TouchEventType type);
	void onTouchBtnResult(Ref *ref, Widget::TouchEventType type);
	
private:
	const string ANIMATION_WAIT = "animationWait";
	const string ANIMATION_RECH = "animationRech";
	const string ANIMATION_RESULT = "animationResult";

private:
	Layer *_skin;
	int _index;//第几个怪
	int _remain;//剩余捕获次数
	int _typeSelectedMaid;
	int _typeSelectedMst;
	bool _isSuccess;
	
};

#endif