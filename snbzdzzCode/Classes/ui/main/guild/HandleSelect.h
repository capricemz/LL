#pragma execution_character_set("utf-8")

#ifndef __UI_MAIN_GUILD_HANDLE_SELECT_H__
#define __UI_MAIN_GUILD_HANDLE_SELECT_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

class HandleSelect : public Ref
{
public:
	CREATE_FUNC(HandleSelect);

public:
	HandleSelect();
	~HandleSelect();

	virtual bool init();

	void setSkin(Layout *skin);
public:
	Layout * getSkin() const
	{
		return _skin;
	}

private:
	void createPageSelectItem();
	Layer *createSelectItem();
	void createTxtCount();//约会次数

private:
	Layout *_skin;
	
};

#endif