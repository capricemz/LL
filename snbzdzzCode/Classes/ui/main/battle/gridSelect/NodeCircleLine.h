#pragma execution_character_set("utf-8")

#ifndef __UI_MAIN_BATTLE_NODE_CIRCLE_LINE_H__
#define __UI_MAIN_BATTLE_NODE_CIRCLE_LINE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

class NodeCircleLine : public Node
{
public:
	CREATE_FUNC(NodeCircleLine);

public:
	NodeCircleLine();
	~NodeCircleLine();

	virtual bool init();

	void onTouchBegan(const int &indexGrid, const Vec2 &postionLayoutWorld, const Vec2 &postionTouchBegan);
	void onTouchMoved(const Vec2 &postionTouchMove);
	void onTouchEndedCanceled();

private:
	void drawCircleLinePoint(const Vec2 &postion);
	void clearCircleLinePoint();
	int getIndexLast();

private:
	int _indexCurrent;//��ǰ���еĸ���
	int _indexLast;//��һ�����еĸ���
	float _imageLineWidth;

};

#endif