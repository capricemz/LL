#pragma execution_character_set("utf-8")

#ifndef __UI_MAIN_TRAINING_LAYER_TRAINING_H__
#define __UI_MAIN_TRAINING_LAYER_TRAINING_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "ui/common/ILayerAppearDisappear.h"

USING_NS_CC;
using namespace ui;

class LayerTraining : public Layer, public ILayerAppearDisappear
{
public:
	CREATE_FUNC(LayerTraining);

public:
	LayerTraining();
	~LayerTraining();
	
	virtual bool init();
	
	virtual Layer *getThis();
	virtual void afterRunAppear();
	virtual void afterRunDisappear();
	virtual void dealRemoveFromParent();
	
	void updateSkin(const int &index);
	
private:
	void createSkin();
	void onTouchBtn(Ref *ref, Widget::TouchEventType type);
	
private:
	Layer *_skin;
	int _indexCurrent;
	
};

#endif