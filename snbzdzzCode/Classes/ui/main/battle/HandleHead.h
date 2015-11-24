#pragma execution_character_set("utf-8")

#ifndef __UI_MAIN_BATTLE_HANDLE_HEAD_ICON_H__
#define __UI_MAIN_BATTLE_HANDLE_HEAD_ICON_H__

#include "cocos2d.h"
#include "ui/UILayout.h"
#include "common/observer/Observer.h"
#include "data/data/ManagerData.h"
#include "NodeHead.h"

USING_NS_CC;
using namespace ui;

class HandleHead : public Ref, public Observer
{
public:
	CREATE_FUNC(HandleHead);

public:
	HandleHead();
	~HandleHead();

	virtual bool init();

	virtual void updateBySubject(va_list values);

	void setSkin(Layout *skin);
	/*type 0女仆，1怪物
	index 第几个*/
	Vec2 getPostionHeadIcon(const int &type, const int &index);
	/*切换头像*/
	void switchHead();
	void onTouchMoveHead(Ref *ref, Widget::TouchEventType type, const bool &isMst);
	
	void resetSkin();

private:
	void updateBarHp(const bool &isMst, const int &indexNodeHead);
	void updateBarEnergy(const bool &isMst);
	
private:
	Layout *_skin;
	Vector<NodeHead *> _vecNodeHeadMst;
	Vector<NodeHead *> _vecNodeHeadMaid;

	Vec2 _postionMoveBegan;

};

#endif