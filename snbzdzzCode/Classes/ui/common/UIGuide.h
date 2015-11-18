#pragma execution_character_set("utf-8")

#ifndef __UI_COMMON_UI_GUIDE_H__
#define __UI_COMMON_UI_GUIDE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace ui;

class UIGuide : public Node
{
public:
	CREATE_FUNC(UIGuide);

public:
	UIGuide();
	~UIGuide();

	virtual bool init();

	bool show();

	bool isShowed();

private:
	void onTouch(Ref *ref, Widget::TouchEventType type);
	void hide();

private:
	ClippingNode *_chipper = nullptr;
	Node *_target = nullptr;

	bool _isShowed = false;

};

#endif