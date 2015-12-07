#ifndef __UI_MAIN_GUILD_LAYER_GUILD_H__
#define __UI_MAIN_GUILD_LAYER_GUILD_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "ui/common/ILayerAppearDisappear.h"

USING_NS_CC;
using namespace ui;

class LayerGuild : public Layer, public ILayerAppearDisappear
{
public:
	CREATE_FUNC(LayerGuild);

public:
	LayerGuild();
	~LayerGuild();
	
	virtual bool init();
	
	virtual Layer *getThis();
	virtual void afterRunAppear();
	virtual void afterRunDisappear();
	virtual void dealRemoveFromParent();
	
private:
	void createSkin();
	
private:
	Layer *_skin;
	
};

#endif
