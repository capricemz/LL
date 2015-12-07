#include "LayerGuild.h"
#include "data/define/DefinesRes.h"
#include "core/entity/subs/Entity.h"
#include "UIEntity.h"
#include "ui/ManagerUI.h"

LayerGuild::LayerGuild() : _skin(nullptr)
{
}

LayerGuild::~LayerGuild()
{
	_skin = nullptr;
}

bool LayerGuild::init()
{
	auto isInit = false;
	do
	{
		CC_BREAK_IF(!Layer::init());
		
		createSkin();

		isInit = true;
	} while (0);
	return isInit;
}

Layer * LayerGuild::getThis()
{
	return this;
}

void LayerGuild::afterRunAppear()
{
}

void LayerGuild::afterRunDisappear()
{
}

void LayerGuild::dealRemoveFromParent()
{
	if (getParent())
	{
		removeFromParent();
	}
}

void LayerGuild::createSkin()
{
	_skin = (Layer *)CSLoader::createNode(RES_MODULES_MAIN_LAYER_GUILD_CSB);
	addChild(_skin);

	auto layout = (Layout *)_skin->getChildByName("layoutEntity");

	for (int i = 0; i < 2; i++)
	{
		auto isMst = i < 1;
		//
		if (isMst)
		{

		}
		else
		{
			auto vecDataEntity = ManagerData::getInstance()->getHandleDataEntity()->getVecDataEntityMaid();
			auto postion = Vec2::ZERO;
			for (auto var : vecDataEntity)
			{
				auto idEntity = var->getIdEntity();

				auto uiEntity = UIEntity::create();
				uiEntity->updateSkin(idEntity);
				uiEntity->getLayoutBg()->addTouchEventListener([](Ref *ref, Widget::TouchEventType type)
				{
					if (type == Widget::TouchEventType::ENDED)
					{
						ManagerUI::getInstance()->notify(ID_OBSERVER::SCENE_MAIN, TYPE_OBSERVER_SCENE_MAIN::SHOW_SKILLS);
					}
				});
				layout->addChild(uiEntity);

				auto size = uiEntity->getLayoutBg()->getContentSize();
				if (postion == Vec2::ZERO)
				{
					postion = Vec2(size.width * 0.5f + 50.0f, size.height * 0.5f + 50.0f);
					uiEntity->setPosition(postion);
				}
				else
				{
					uiEntity->setPosition(postion);
				}
				postion += Vec2(size.width + 10.0f, 0.0f);
			}
		}
	}
}
