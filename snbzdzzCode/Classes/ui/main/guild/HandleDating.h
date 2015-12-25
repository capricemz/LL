#pragma execution_character_set("utf-8")

#ifndef __UI_MAIN_GUILD_HANDLE_DATING_H__
#define __UI_MAIN_GUILD_HANDLE_DATING_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

class HandleDating : public Ref
{
public:
	CREATE_FUNC(HandleDating);

public:
	HandleDating();
	~HandleDating();

	virtual bool init();

	void setSkin(Layout *skin);

public:
	Layout * getSkin() const
	{
		return _skin;
	}

private:
	void createRegion();
	void createBtn();

private:
	Layout *_skin;

};

#endif