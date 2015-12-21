#pragma execution_character_set("utf-8")

#ifndef __UI_MAIN_BATTLE_RESULT_LAYER_BATTLE_RESULT_H__
#define __UI_MAIN_BATTLE_RESULT_LAYER_BATTLE_RESULT_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

using namespace std;
USING_NS_CC;
using namespace ui;

class LayerBattleResult : public Layer
{
public:
	CREATE_FUNC(LayerBattleResult);

public:
	LayerBattleResult();
	~LayerBattleResult();

	virtual bool init();
	/*func ����ȫ�����ʱ�ص�*/
	void runAppearAction(const function<void()> &func = nullptr);

private:
	void createSkin();
	
	void updateLayoutVictory();
	void updateLayoutDefeat();

	void onTouchContinue(Ref *ref, Widget::TouchEventType type);

	void updateLayoutStar();
	void updateLayoutDrop();
	void playAnimationVictory();

private:
	Layer *_skin;
	bool _isActionRunning;

};

#endif