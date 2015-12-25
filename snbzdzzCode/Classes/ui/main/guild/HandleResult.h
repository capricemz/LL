#pragma execution_character_set("utf-8")

#ifndef __UI_MAIN_GUILD_HANDLE_RESULT_H__
#define __UI_MAIN_GUILD_HANDLE_RESULT_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

class HandleResult : public Ref
{
public:
	CREATE_FUNC(HandleResult);

public:
	HandleResult();
	~HandleResult();
	
	virtual bool init();

	void setSkin(Layout *skin);

public:
	Layout * getSkin() const
	{
		return _skin;
	}

private:
	Layout *_skin;

};

#endif