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

	/*func ����ȫ�����ʱ�ص�*/
	void runAppearAction(const bool &isWin, const function<void()> &func = nullptr);

private:
	void createSkin();

private:
	Layer *_skin;

};

#endif