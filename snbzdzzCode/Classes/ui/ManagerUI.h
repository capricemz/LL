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

	void addKeyEvent(Scene *scene);//��ӷ��ؼ���������ʱ��
	void replaceScene(TypeScene type);
	void runLayerAppearDisappear(ILayerAppearDisappear *layerNew);
	/*��ʾƮ��
	parent ������
	postion ��Ը�����ԭ��λ��
	words ����
	color ��ɫ
	duration ����ʱ��*/
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