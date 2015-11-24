#pragma execution_character_set("utf-8")

#ifndef __UI_MAIN_BATTLE_NODE_HEAD_H__
#define __UI_MAIN_BATTLE_NODE_HEAD_H__

#include "cocos2d.h"
#include "data/data/ManagerData.h"

USING_NS_CC;

class NodeHead : public Node
{
public:
	CREATE_FUNC(NodeHead);

public:
	NodeHead();
	~NodeHead();

	virtual bool init();

	void createSkin();
	void setSkin(Node *skin);

	void updateAll();
	void updateSpriteIcon();
	void updateBarHp();
	void updateSpriteJob();

	/*移动
	postion 其实位置 全局坐标
	isBack 是否为显示背面
	scaleBegan 起始缩放
	scaleEnd 终点缩放
	offsetEnd 终点偏移 Vec2::ZERO表示移动到添加位置
	func 动作结束时调用*/
	void moveFrom(const Vec2 &postion, const bool &isBack, const float &scaleBegan, const float &scaleEnd, const Vec2 & offsetEnd, const function<void()> &func = nullptr);

public:
	bool getIsMst() const
	{
		return _isMst;
	}
	void setIsMst(bool val)
	{
		_isMst = val;
	}
	int getIndexDataEntity() const
	{
		return _indexDataEntity;
	}
	void setIndexDataEntity(int val)
	{
		_indexDataEntity = val;
	}

private:
	Node *_skin;
	bool _isMst;
	int _indexDataEntity;
	
};

#endif