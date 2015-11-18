#pragma execution_character_set("utf-8")

#ifndef __UI_WELCOME_SCENE_WELCOME_H__
#define __UI_WELCOME_SCENE_WELCOME_H__

#include "cocos2d.h"
#include "HandleImageLoad.h"

USING_NS_CC;

class SceneWelcome : public Scene
{
public:
	CREATE_FUNC(SceneWelcome);

public:
	SceneWelcome();
	~SceneWelcome();

	virtual bool init();

	void handleLoading(Sprite *spriteLoading);

private:
	void createSkin();

	void handleLoadSound();

private:
	HandleImageLoad * _handleImageLoad;

};

#endif