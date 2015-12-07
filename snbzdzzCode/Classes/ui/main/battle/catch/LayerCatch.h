#pragma execution_character_set("utf-8")

#ifndef __UI_MAIN_BATTLE_CATCH_LAYER_CATCH_H__
#define __UI_MAIN_BATTLE_CATCH_LAYER_CATCH_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "data/define/DefinesValue.h"

USING_NS_CC;
using namespace ui;

class LayerCatch : public Layer
{
public:
	CREATE_FUNC(LayerCatch);

public:
	LayerCatch();
	~LayerCatch();

	virtual bool init();
	/*func ����ȫ�����ʱ�ص�*/
	void runAppearAction(const function<void()> &func = nullptr);
	
private:
	void createSkin();
	void onTouchBtn(Ref *ref, Widget::TouchEventType type);
	void doWait();//ִ�еȴ�����
	void doReach();//ִ�г�����
	void showResult();
	void updateIndexRemain();//��������
	void updateInfo();//ˢ����ʾ��Ϣ
	void setBtnVisible(const bool &value);

private:
	Layer *_skin;
	int _index;//�ڼ�����
	int _remain;//ʣ�ಶ�����
	int _typeSelectedMst;
	int _typeSelectedMaid;
	
};

#endif