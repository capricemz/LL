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

	void addKeyEvent(Scene *scene);//��ӷ��ؼ���������ʱ��
	void replaceScene(TypeScene type);
	void runLayerAppearDisappear(ILayerAppearDisappear *layerNew);
	void switchTwoNode(Node *node, Node *nodeNew, function<void()> funcOverNode = nullptr, function<void()> funcOverNodeNew = nullptr);
	/*��ʾƮ��
	parent ������
	postion ��Ը�����ԭ��λ��
	words ����
	color ��ɫ
	duration ����ʱ��*/
	void showWordsDrift(Node *parent, const Vec2 &postion, const string &words, const Color4B &color, const float &duration);
	/*��ʾ����
	parent ������
	postion ��Ը�����ԭ��λ��
	anchor �����
	idPlot ����id
	index ˳��
	funcOverAppear ��ʾ��ɻص�
	funcOverDisappear ��ʧ��ɻص�
	isTxtShowImmediately �Ƿ�������ʾ�ı�
	isAppearImmediately �Ƿ�������ʾ
	isDisappearImmediately �Ƿ�������ʧ*/
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
	/*��ʾ����
	target Ŀ�����
	anchor �����
	postion Ŀ���������λ��
	idPlot ����id
	index ˳��
	funcOverAppear ��ʾ��ɻص�
	funcOverDisappear ��ʧ��ɻص�
	isTxtShowImmediately �Ƿ�������ʾ�ı�
	isAppearImmediately �Ƿ�������ʾ
	isDisappearImmediately �Ƿ�������ʧ*/
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