#pragma execution_character_set("utf-8")

#ifndef __UI_MANAGER_UI_H__
#define __UI_MANAGER_UI_H__

#include "cocos2d.h"
#include "data/define/DefinesValue.h"
#include "common/observer/Observer.h"
#include "common/ILayerAppearDisappear.h"
#include "ui/UILayout.h"

USING_NS_CC;
using namespace ui;

class ManagerUI : public Subject
{
public:
	static ManagerUI * getInstance();
	static void destroyInstance();

public:
	~ManagerUI();
	void createLayout(Scene *scene);

	void addKeyEvent(Scene *scene);//添加返回及其他按键时间
	void replaceScene(TypeScene type);
	void runLayerAppearDisappear(ILayerAppearDisappear *layerNew);
	void switchTwoNode(Node *node, Node *nodeNew, function<void()> funcOverNode = nullptr, function<void()> funcOverNodeNew = nullptr);
	/*显示飘字
	parent 父对象
	postion 相对父对象原点位置
	words 文字
	color 颜色
	duration 持续时间*/
	void showWordsDrift(Node *parent, const Vec2 &postion, const string &words, const Color4B &color, const float &duration);
	/*显示气泡
	parent 父对象
	postion 相对父对象原点位置
	anchor 对齐点
	idPlot 剧情id
	index 顺序
	funcOverAppear 显示完成回调
	funcOverDisappear 消失完成回调
	isTxtShowImmediately 是否立即显示文本
	isAppearImmediately 是否立即显示
	isDisappearImmediately 是否立即消失*/
	void showBubble(
		Node *parent,
		const Vec2 &anchor,
		const Vec2 &postion,
		const int &idPlot,
		const int &index,
		const function<void()> funcOverAppear,
		const function<void()> funcOverDisappear,
		const bool &isTxtShowImmediately = false,
		const bool &isAppearImmediately = false,
		const bool &isDisappearImmediately = false);
	/*显示剧情
	target 目标对象
	anchor 对齐点
	postion 目标对象世界位置
	idPlot 剧情id
	index 顺序
	funcOverAppear 显示完成回调
	funcOverDisappear 消失完成回调
	isTxtShowImmediately 是否立即显示文本
	isAppearImmediately 是否立即显示
	isDisappearImmediately 是否立即消失*/
	void showPlot(Node *target,
		const Vec2 &anchor,
		const Vec2 &postion,
		const int &idPlot,
		const int &index,
		const function<void()> funcOverAppear,
		const function<void()> funcOverDisappear,
		const bool &isTxtShowImmediately = false,
		const bool &isAppearImmediately = false,
		const bool &isDisappearImmediately = false);

public:
	TYPE_OBSERVER_SCENE_MAIN getTypeLayerRunning() const { return _typeLayerRunning; }
	void setTypeLayerRunning(TYPE_OBSERVER_SCENE_MAIN val) { _typeLayerRunning = val; }
	ILayerAppearDisappear * getLayerRunning() const { return _layerRunning; }
	void setLayerRunning(ILayerAppearDisappear * val) { _layerRunning = val; }

private:
	ManagerUI();
	
private:
	TypeScene _typeSceneRunning;
	TYPE_OBSERVER_SCENE_MAIN _typeLayerRunning;
	ILayerAppearDisappear *_layerRunning;

	Layout *_layoutPlot;

};

#endif