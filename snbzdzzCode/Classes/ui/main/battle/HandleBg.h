#pragma execution_character_set("utf-8")

#ifndef __UI_MAIN_BATTLE_HANDLE_BG_H__
#define __UI_MAIN_BATTLE_HANDLE_BG_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

class HandleBg : public Ref
{
public:
	CREATE_FUNC(HandleBg);

public:
	HandleBg();
	~HandleBg();

	virtual bool init();

	void setSkin(Layout *skin);
	void updateTxtRound();
	
private:
	Layout *_skin;
	
};

#endif