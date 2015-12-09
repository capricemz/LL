#pragma execution_character_set("utf-8")

#ifndef __UI_COMMON_UI_BUBBLE_H__
#define __UI_COMMON_UI_BUBBLE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;
using namespace std;

class UIBubble : public Node
{
public:
	CREATE_FUNC(UIBubble);
	
public:
	UIBubble();
	~UIBubble();
	
	virtual bool init();
	/*根据对齐点刷新背景*/
	virtual void setAnchorPoint(const Vec2& point);
	/*响应点击处理*/
	void show(
		const int &idPlot,
		const int &index,
		const function<void()> funcOverAppear,
		const function<void()> funcOverDisappear,
		const bool &isTxtShowImmediately = false,
		const bool &isAppearImmediately = false,
		const bool &isDisappearImmediately = false);
	
private:
	void runAppear();
	void runDisappear();

	void playPlot();
	void updateNodeBubbleTxt(float dt);
	
private:
	Node *_skin;

	int _idPlot;
	int _index;
	function<void()> _funcOverAppear;
	function<void()> _funcOverDisappear;
	bool _isTxtShowImmediately;
	bool _isAppearImmediately;
	bool _isDisappearImmediately;
	
	int _numWordShow;

	bool _isAppear;

};

#endif