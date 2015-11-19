#pragma execution_character_set("utf-8")

#ifndef __UI_MAIN_LEVELS_LAYER_LEVELS_H__
#define __UI_MAIN_LEVELS_LAYER_LEVELS_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "ui/common/ILayerAppearDisappear.h"

USING_NS_CC;
using namespace ui;

class LayerLevels : public Layer, public ILayerAppearDisappear
{
public:
	CREATE_FUNC(LayerLevels);

public:
	LayerLevels();
	~LayerLevels();

	virtual bool init();

	virtual Layer *getThis();
	virtual void afterRunAppear();
	virtual void afterRunDisappear();
	virtual void dealRemoveFromParent();

private:
	void createSkin();
	void onTouchBtnLv(Ref *ref, Widget::TouchEventType type);

private:
	Layer *_skin;

};

#endif