#pragma execution_character_set("utf-8")

#ifndef __UI_COMMON_UI_TIPS_H__
#define __UI_COMMON_UI_TIPS_H__

#include "cocos2d.h"
#include "data/define/DefinesValue.h"

USING_NS_CC;

class UITips : public Node
{
public:
	CREATE_FUNC(UITips);

public:
	UITips();
	~UITips();

	void show(const TypeTips &type, const Vec2 &postion, const int &id);
	bool isShowed();
	void hide();

private:
	void showCallFunc(const TypeTips &type, const Vec2 &postion, const int &id);
	void createTipThing(Node *node, const Vec2 &postion, const int &idThing);
	void createTipMonster(Node *node, const Vec2 &postion, const int &idRegion);
	void createTipSkill(Node *node, const Vec2 &postion, const int &idDataEntityAttr);
	void createTipTargetAward(Node *node, const Vec2 &postion, const int &idTargetAward);
	void createTipErrors(Node *node, const Vec2 &postion, const int &idError);

};

#endif