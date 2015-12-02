#pragma execution_character_set("utf-8")

#ifndef __UI_MAIN_SKILLS_LAYER_SKILLS_H__
#define __UI_MAIN_SKILLS_LAYER_SKILLS_H__

#include "cocos2d.h"
#include "ui/common/ILayerAppearDisappear.h"
#include "ui/UIWidget.h"
#include "ui/UILayout.h"
#include "data/config/ManagerCfgDefines.h"

USING_NS_CC;
using namespace ui;

class LayerSkills : public Layer, public ILayerAppearDisappear
{
public:
	CREATE_FUNC(LayerSkills);

public:
	LayerSkills();
	~LayerSkills();

	virtual bool init();

	virtual Layer *getThis();
	virtual void afterRunAppear();
	virtual void afterRunDisappear();
	virtual void dealRemoveFromParent();
	
private:
	void createSkin();
	void updateLayoutBtns();
	void onTouchBtnMaid(Ref *ref, Widget::TouchEventType type);
	void updateLayoutSkillItems();
	void updateLayoutSKillItem(Layout *layoutSkillItem, const bool &isGet, const DataSkillInfo &dataSkillInfo);
	void onTouchBtnSkill(Ref *ref, Widget::TouchEventType type, const DataSkillInfo &dataSkillInfo);
	
private:
	Layer *_skin;

	int _idEntityCurrent;
	
};

#endif