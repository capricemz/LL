#ifndef __UI_MAIN_GUILD_LAYER_GUILD_H__
#define __UI_MAIN_GUILD_LAYER_GUILD_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "ui/common/ILayerAppearDisappear.h"
#include "HandleSelect.h"
#include "HandleDating.h"
#include "HandleResult.h"
#include "common/observer/Observer.h"

USING_NS_CC;
using namespace ui;

class LayerGuild : public Layer, public ILayerAppearDisappear, public Observer
{
public:
	CREATE_FUNC(LayerGuild);

public:
	LayerGuild();
	~LayerGuild();
	
	virtual void updateBySubject(va_list values);

	virtual bool init();
	
	virtual Layer *getThis();
	virtual void afterRunAppear();
	virtual void afterRunDisappear();
	virtual void dealRemoveFromParent();
	
private:
	void createSkin();

	void switchLayout(const TYPE_OBSERVER_LAYER_GUILD &typeLayout);

private:
	Layer *_skin;

	Node *_nodeNow;
	HandleSelect *_handleSelect;
	HandleDating *_handleDating;
	HandleResult *_handleResult;
	
};

#endif
