#pragma execution_character_set("utf-8")

#ifndef __UI_MAIN_BATTLE_RESULT_LAYER_GRADE_UP_H__
#define __UI_MAIN_BATTLE_RESULT_LAYER_GRADE_UP_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;
using namespace std;

class LayerGradeUp : public Layer
{
public:
	CREATE_FUNC(LayerGradeUp);

public:
	LayerGradeUp();
	~LayerGradeUp();

	virtual bool init();
	/*func 动作全部完成时回调*/
	void runAppearAction(const function<void()> &func = nullptr);

private:
	void createSkin();
	
	void updateSpriteGradeUp();
	void updateLayoutInfoGrade();
	void updateNodeHead();
	void updateLayoutInfoMaid();

	void onTouchContinue(Ref *ref, Widget::TouchEventType type);
	
private:
	Layer *_skin;
	bool _isAppearing;

};

#endif