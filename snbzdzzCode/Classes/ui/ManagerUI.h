#pragma execution_character_set("utf-8")

#ifndef __UI_MANAGER_UI_H__
#define __UI_MANAGER_UI_H__

#include "cocos2d.h"
#include "data/define/DefinesValue.h"
#include "common/observer/Observer.h"
#include "common/ILayerAppearDisappear.h"

USING_NS_CC;

class ManagerUI : public Subject
{
public:
	static ManagerUI * getInstance();
	static void destroyInstance();

public:
	~ManagerUI();

	void addKeyEvent(Scene *scene);//添加返回及其他按键时间
	void replaceScene(TypeScene type);
	void runLayerAppearDisappear(ILayerAppearDisappear *layerNew);
	/*显示飘字
	parent 父对象
	postion 相对父对象原点位置
	words 文字
	color 颜色
	duration 持续时间*/
	void showWordsDrift(Node *parent, const Vec2 &postion, const string &words, const Color4B &color, const float &duration);

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

};

#endif