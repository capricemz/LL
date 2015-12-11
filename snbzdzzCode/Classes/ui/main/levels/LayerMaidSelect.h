#pragma execution_character_set("utf-8")

#ifndef __UI_MAIN_LEVELS_LAYER_MAID_SELECT_H__
#define __UI_MAIN_LEVELS_LAYER_MAID_SELECT_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "ui/main/battle/NodeHead.h"

USING_NS_CC;
using namespace ui;

class LayerMaidSelect : public Layer
{
public:
	CREATE_FUNC(LayerMaidSelect);

public:
	LayerMaidSelect();
	~LayerMaidSelect();

	virtual bool init();

	void runAppear(const function<void()> &funcOver);
	
private:
	void createData();
	void createSkin();

	void ontTouchBack(Ref *ref, Widget::TouchEventType type);
	void runDisappear(const function<void()> &funcOver);

	void onTouchBtnEnter(Ref *ref, Widget::TouchEventType type);
	void onTouchNodeHead(Ref *ref, Widget::TouchEventType type, NodeHead *nodeHead);
	bool isMoveOverNodeHead(const Vec2 &postionTouchMove, int &indexDataEntityMoveOver);
	
private:
	Layer *_skin;
	Vector<NodeHead *> _vecNodeHead;
	Vec2 _postionDelta;//触摸起始点与中心点的距离
	
};

#endif