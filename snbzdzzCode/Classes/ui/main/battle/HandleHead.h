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
	/*切换头像到下一个*/
	void switchNodeHeadTo(const bool &isMst, const int &indexTo);
	void onTouchMoveHead(Ref *ref, Widget::TouchEventType type, const bool &isMst);
	
	void resetSkin();

private:
	void updateNodeHeadHp(const bool &isMst, const int &indexNodeHead);
	void updateBarEnergy(const bool &isMst);
	
	void switchLayoutHeadMaidTouchable(const bool &isTouchEnabled);
	void nodeHeadScalePostionGet(const int &index, const bool &isMst, float &scale, Vec2 &postion, const float &xOffset = 0.0f);
	void moveNodeHead(const bool &isMst, const float &xOffset);//移动NodeHead位置
	void dealNodeHeadTemp(const bool &isMst, const bool &isLeft);
	void dealOverMoveNodeHead(const bool &isMst, const bool &isActive);//移动NodeHead结束时处理判断
	void showWordsDrift(const bool &isMst, const int &indexNodeHead, const int &valueChange, const IdAttribute &idAttributeBeChange, const Color4B &color, const float &duration);

private:
	Layout *_skin;
	Vector<NodeHead *> _vecNodeHeadMst;
	Vector<NodeHead *> _vecNodeHeadMaid;

	float _xPostionMoveTouchLast;
	float _dictanceMoved;

	int _indexNodeHeadTempMst;
	int _indexNodeHeadTempMaid;
	
};

#endif