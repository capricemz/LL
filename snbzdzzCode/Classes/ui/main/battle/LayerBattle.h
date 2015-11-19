#pragma execution_character_set("utf-8")

#ifndef __UI_MAIN_BATTLE_LAYER_BATTLE_H__
#define __UI_MAIN_BATTLE_LAYER_BATTLE_H__

#include "cocos2d.h"
#include "common/observer/Observer.h"
#include "ui/common/ILayerAppearDisappear.h"
#include "HandleEntity.h"
#include "HandleGridSelected.h"
#include "HandleHeadIcon.h"
#include "HandleGridSelect.h"
#include "gridShow/LayerGridShow.h"
#include "result/LayerBattleResult.h"

USING_NS_CC;
using namespace std;

class LayerBattle : public Layer, public Observer, public ILayerAppearDisappear
{
public:
	CREATE_FUNC(LayerBattle);

public:
	LayerBattle();
	~LayerBattle();

	virtual bool init();

	virtual void updateBySubject(va_list values);
	
	virtual Layer *getThis();
	virtual void afterRunAppear();
	virtual void afterRunDisAppear();
	virtual void dealRemoveFromParent();

	void funcAfterLayerGridShowRunAppearAction();
	void funcAfterRunMstGridMoveFromAction();
	void funcAfterRunMstGridTurnAction();
	/*indexMaid �ڼ���
	funcOneOver һ�����Ӷ������ʱ����
	funcAllOver ����ȫ�����ʱ�ص�*/
	void runMaidGridMoveFromAction(const int &indexMaid, const function<void()> &funcOneOver = nullptr, const function<void()> &funcAllOver = nullptr);
	/*type 0Ů�ͣ�1����
	index �ڼ���*/
	Vec2 getPostionHeadIcon(const int &type, const int &index);

private:
	void createData();
	void createSkin();
	void resetSkin();
	
private:
	Layer *_skin;
	HandleEntity *_handleEntity;
	HandleGridSelected *_handleGridSelected;
	HandleHeadIcon *_handleHeadIcon;
	HandleGridSelect *_handleGridSelect;

	LayerGridShow *_layerGridShow;
	LayerBattleResult *_layerBattleResult;

};

#endif