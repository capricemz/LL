#pragma execution_character_set("utf-8")

#ifndef __UI_COMMON_UI_CONFIRM_H__
#define __UI_COMMON_UI_CONFIRM_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "data/define/DefinesValue.h"

USING_NS_CC;
using namespace ui;

class UIConfirm : public Node
{
public:
	CREATE_FUNC(UIConfirm);

public:
	~UIConfirm()
	{
		_mask = nullptr;
	}

	void show(const TypeConfirms &type, std::string textAssgin, const std::function<void()> &confirmFunc);
	void hide();

	bool isShowed();

private:
	void onTouchConfirm(Ref *ref, Widget::TouchEventType type, const std::function<void()> &confirmFunc);
	void onTouchCancel(Ref *ref, Widget::TouchEventType type);

private:
	Layout *_mask = nullptr;

};

#endif