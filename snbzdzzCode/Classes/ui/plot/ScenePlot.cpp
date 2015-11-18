#pragma execution_character_set("utf-8")

#include "ScenePlot.h"
#include "cocostudio/CocoStudio.h"
#include "data/define/DefinesRes.h"
#include "ui/ManagerUI.h"
#include "data/data/ManagerData.h"

using namespace ui;
using namespace cocostudio::timeline;

ScenePlot::ScenePlot() : _countClickCurr(0), _isPlaying(false)
{
}

ScenePlot::~ScenePlot()
{
}

bool ScenePlot::init()
{
	auto isInit = false;
	do 
	{
		CC_BREAK_IF(!Scene::init());

		ManagerUI::getInstance()->addKeyEvent(this);

		createSkin();

		isInit = true;
	} while (0);
	return isInit;
}

void ScenePlot::createSkin()
{
	auto skin = CSLoader::createNode(RES_MODULES_PLOT_SCENE_PLOT_CSB);
	addChild(skin);

	auto layoutBg = (Layout *)skin->getChildByName("layoutBg");
	layoutBg->addTouchEventListener([=](Ref *ref, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			ActionTimeline *actionTimeline = (ActionTimeline *)skin->getActionByTag(skin->getTag());
			if (actionTimeline == nullptr)
			{
				actionTimeline = CSLoader::createTimeline(RES_MODULES_PLOT_SCENE_PLOT_CSB);
				skin->runAction(actionTimeline);
			}

			auto animationName = "animation" + Value(_countClickCurr).asString();

			auto isAnimationInfoExists = actionTimeline->IsAnimationInfoExists(animationName);
			if (!isAnimationInfoExists)
			{
				ManagerData::getInstance()->setSaveFileExist();
				ManagerUI::getInstance()->replaceScene(TypeScene::MAIN);
				return;
			}

			if (_isPlaying)
			{
				return;
			}
			_isPlaying = true;

			actionTimeline->play(animationName, false);
			actionTimeline->setLastFrameCallFunc([=]()
			{
				_isPlaying = false;
			});

			_countClickCurr++;
		}
	});
}
