#ifndef __UI_MAIN_SCENE_MAIN_H__
#define __UI_MAIN_SCENE_MAIN_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "common/observer/Observer.h"

USING_NS_CC;
using namespace ui;

class SceneMain : public Scene, public Observer
{
public:
	CREATE_FUNC(SceneMain);

public:
	SceneMain();
	~SceneMain();

	virtual bool init();

	virtual void updateBySubject(va_list values);
	void updateLayoutTop();
	
private:
	void createSkin();
	void switchLayer(const TYPE_OBSERVER_SCENE_MAIN &type);
	void onTouchTopBtn(Ref *ref, Widget::TouchEventType type);
	void onTouchBottomBtn(Ref *ref, Widget::TouchEventType type);
	void switchVisibleLayoutTop(const bool &isVisibe);
	void switchVisibleLayoutBottom(const bool &isVisibe);
	
private:
	Scene *_skin;

	bool _isLayoutTopVisible;
	bool _isLayoutBottomVisible;

};

#endif
