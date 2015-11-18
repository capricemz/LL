#pragma execution_character_set("utf-8")

#ifndef __UI_MAIN_BATTLE_HANDLE_GRID_SELECTED_H__
#define __UI_MAIN_BATTLE_HANDLE_GRID_SELECTED_H__

#include "cocos2d.h"
#include "ui/UILayout.h"
#include "common/observer/Observer.h"

USING_NS_CC;
using namespace ui;
using namespace std;

class HandleGridSelected : public Ref, public Observer
{
public:
	CREATE_FUNC(HandleGridSelected);

public:
	HandleGridSelected();
	~HandleGridSelected();

	virtual bool init();

	void setSkin(Layout *skin);
	
	virtual void updateBySubject(va_list values);

	void runGridMoveAction(CallFunc *callFuncAllOver = nullptr);//���и��Ӵ���ʾ���ɵ�ѡ������
	
	void resetSkin();

private:
	void funcOverGridSelectedGridMove();
	void updateGrid(const int &idDataGrid);//ˢ�¸�����ʾ

private:
	Layout *_skin;

};

#endif