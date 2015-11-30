#pragma execution_character_set("utf-8")

#ifndef __UI_MAIN_BATTLE_HANDLE_ENTITY_H__
#define __UI_MAIN_BATTLE_HANDLE_ENTITY_H__

#include "cocos2d.h"
#include "ui/UILayout.h"
#include "common/observer/Observer.h"
#include "core/grid/Grid.h"
#include "core/entity/subs/Entity.h"

USING_NS_CC;
using namespace ui;

class HandleEntity : public Ref, public Observer
{
public:
	CREATE_FUNC(HandleEntity);

public:
	HandleEntity();
	~HandleEntity();

	virtual bool init();

	void setSkin(Layout *skin);
	void resetSkin();

	virtual void updateBySubject(va_list values);
	void runEntityAppear();

private:
	void setTxtHpOrEnergy(Entity *entity, const bool &isMst, const bool &isHp);

	void runEntityAction();
	
	void dealTurnOver();//轮结束处理

	void dealRoundOver(const bool &isForce = false);//回合结束处理
	/*刷新血量
	type 0hp1energy*/
	void updateTxtHpOrEnergy(const bool &isHp);
	
private:
	Layout *_skin;

};

#endif