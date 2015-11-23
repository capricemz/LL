#ifndef __CORE_ENTITY_SUBS_ENTITY_H__
#define __CORE_ENTITY_SUBS_ENTITY_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "data/data/ManagerData.h"

USING_NS_CC;
using namespace ui;

class Entity : public Node
{
public:
	CREATE_FUNC(Entity);

public:
	Entity();
	~Entity();

	virtual bool init();

	void updateSkin();
	void runAppear(const function<void()> &func = nullptr);
	void runDisAppear(const function<void()> &func = nullptr);
	void doAction(const function<void()> &func = nullptr);
	void showEffect(const function<void()> &func = nullptr);

	void stopSkinAllActions();
	/*�л���ɫ
	indexSwitchTo Ҫ�л�����index ��ΪENTITY_BATTLE_MAXʱ���л�����һ��
	func �л���ɻص�*/
	void switchEntity(const int &indexSwitchTo, bool &isSwitchSuccess, const function<void()> &func = nullptr);

public:
	DataEntity *getDataEntity()
	{
		return _dataEntity;
	}
	bool getIsRunAppearOver() const
	{
		return _isRunAppearOver;
	}
	bool getIsRunDisappearOver() const
	{
		return _isRunDisappearOver;
	}
	bool getIsDoActionOver() const
	{
		return _isDoActionOver;
	}
	bool getIsTurnOver() const
	{
		return _isTurnOver;
	}
	void setIsTurnOver(bool val)
	{
		_isTurnOver = val;
	}

protected:
	virtual void setDataEntity() {}
	virtual Vec2 getPostionAppearDisAppear() { return Vec2::ZERO; }
	virtual Vec2 getPostionEndAttack() { return Vec2::ZERO; }
	virtual void updateHp() {}
	virtual void updateEnergy() {}
	virtual void dealDead();
	virtual void switchDataEntity(const int &indexSwitchTo, bool &isSwitchSuccess) {}

	
private:
	void dealResultValueChange(const IdAttribute &idAttributeGet, const bool &isPositive, const IdAttribute &idAttributeChange, const Color4B &color, const float &duration);
	void dealDeadEffect(const float &duration);
	
protected:
	DataEntity *_dataEntity;
	Sprite *_skin;

	bool _isRunAppearOver;
	bool _isRunDisappearOver;
	bool _isDoActionOver;
	bool _isTurnOver;
	
};

#endif