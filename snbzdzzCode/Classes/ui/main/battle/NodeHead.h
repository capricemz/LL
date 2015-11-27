#pragma execution_character_set("utf-8")

#ifndef __UI_MAIN_BATTLE_NODE_HEAD_H__
#define __UI_MAIN_BATTLE_NODE_HEAD_H__

#include "cocos2d.h"
#include "data/data/ManagerData.h"
#include "ui/UILayout.h"

USING_NS_CC;
using namespace ui;

class NodeHead : public Node
{
public:
	CREATE_FUNC(NodeHead);
	
public:
	NodeHead();
	~NodeHead();

	virtual bool init();

	void createSkin();
	void setInfo(const bool &isMst, const int &indexDataEntity);

	void updateAll();
	void updateSpriteIcon();
	void updateBarHp();
	void updateSpriteJob();

	/*�ƶ�
	postion ��ʵλ�� ȫ������
	isBack �Ƿ�Ϊ��ʾ����
	scaleBegan ��ʼ����
	scaleEnd �յ�����
	offsetEnd �յ�ƫ�� Vec2::ZERO��ʾ�ƶ������λ��
	func ��������ʱ����*/
	void moveFrom(const Vec2 &postion, const bool &isBack, const float &scaleBegan, const float &scaleEnd, const Vec2 & offsetEnd, const function<void()> &func = nullptr);
	
	NodeHead *clone();
	
public:
	bool getIsMst() const
	{
		return _isMst;
	}
	int getIndexDataEntity() const
	{
		return _indexDataEntity;
	}

	Layout *getLayoutBg()
	{
		return (Layout *)_skin->getChildByName("layoutBg");
	}

	DataEntity *getDataEntity();

private:
	Node *_skin;
	bool _isMst;
	int _indexDataEntity;
	
};

#endif