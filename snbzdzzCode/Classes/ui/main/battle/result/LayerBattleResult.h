#pragma execution_character_set("utf-8")

#ifndef __UI_MAIN_BATTLE_RESULT_LAYER_BATTLE_RESULT_H__
#define __UI_MAIN_BATTLE_RESULT_LAYER_BATTLE_RESULT_H__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class LayerBattleResult : public Layer
{
public:
	CREATE_FUNC(LayerBattleResult);

public:
	LayerBattleResult();
	~LayerBattleResult();

	virtual bool init();
	void updateSkin(const bool &isWin);
	/*func 动作全部完成时回调*/
	void runAppearAction(const function<void()> &func = nullptr);

private:
	void createSkin();

private:
	Layer *_skin;

};

#endif