#pragma execution_character_set("utf-8")

#ifndef __UI_COMMON_UI_ENTITY_H__
#define __UI_COMMON_UI_ENTITY_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

class UIEntity : public Node
{
public:
	CREATE_FUNC(UIEntity);

public:
	UIEntity();
	~UIEntity();

	virtual bool init();

	void updateSkin(const int &idEntity, const float &scale);

public:
	Layout *getLayoutBg()
	{
		return _layoutBg;
	}

private:
	int _idEntity;
	Sprite *_skin;
	Layout *_layoutBg;

};

#endif