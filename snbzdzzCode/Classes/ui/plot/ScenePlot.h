#pragma execution_character_set("utf-8")

#ifndef __UI_PLOT_SCENE_PLOT_H__
#define __UI_PLOT_SCENE_PLOT_H__

#include "cocos2d.h"

USING_NS_CC;

class ScenePlot : public Scene
{
public:
	CREATE_FUNC(ScenePlot);

public:
	ScenePlot();
	~ScenePlot();

	virtual bool init();

	void createSkin();

private:
	int _countClickCurr;//当前点击次数
	bool _isPlaying;//正在播放

};

#endif