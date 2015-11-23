#pragma execution_character_set("utf-8")

#ifndef __UI_MAIN_BATTLE_HANDLE_HEAD_ICON_H__
#define __UI_MAIN_BATTLE_HANDLE_HEAD_ICON_H__

#include "cocos2d.h"
#include "ui/UILayout.h"

USING_NS_CC;
using namespace ui;

class HandleHead : public Ref
{
public:
	CREATE_FUNC(HandleHead);

public:
	HandleHead();
	~HandleHead();

	virtual bool init();

	void setSkin(Layout *skin);
	/*type 0女仆，1怪物
	index 第几个*/
	Vec2 getPostionHeadIcon(const int &type, const int &index);
	
	void resetSkin();

private:
	Layout *_skin;

};

#endif