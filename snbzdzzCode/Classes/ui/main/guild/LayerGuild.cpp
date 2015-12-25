#include "LayerGuild.h"
#include "data/define/DefinesRes.h"
#include "ui/ManagerUI.h"

LayerGuild::LayerGuild() : _skin(nullptr), _nodeNow(nullptr), _handleSelect(nullptr), _handleDating(nullptr), _handleResult(nullptr)
{
}

LayerGuild::~LayerGuild()
{
	ManagerUI::getInstance()->detach(this);
	_skin = nullptr;
	_nodeNow = nullptr;
	CC_SAFE_RELEASE_NULL(_handleSelect);
	CC_SAFE_RELEASE_NULL(_handleDating);
	CC_SAFE_RELEASE_NULL(_handleResult);
}

void LayerGuild::updateBySubject(va_list values)
{
	auto type = va_arg(values, TYPE_OBSERVER_LAYER_GUILD);
	if (type == TYPE_OBSERVER_LAYER_GUILD::SWITCH_LAYOUT)
	{
		auto typeLayout = va_arg(values, TYPE_OBSERVER_LAYER_GUILD);
		switchLayout(typeLayout);
	}
}

bool LayerGuild::init()
{
	auto isInit = false;
	do
	{
		CC_BREAK_IF(!Layer::init());
		
		idObserverSet(ID_OBSERVER::LAYER_GUILD);
		ManagerUI::getInstance()->attach(this);

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

	auto layoutSelect = (Layout *)_skin->getChildByName("layoutSelect");
	layoutSelect->setVisible(true);
	_nodeNow = layoutSelect;
	_handleSelect = HandleSelect::create();
	_handleSelect->retain();
	_handleSelect->setSkin(layoutSelect);

	auto layoutDating = (Layout *)_skin->getChildByName("layoutDating");
	layoutDating->setVisible(false);
	_handleDating = HandleDating::create();
	_handleDating->retain();
	_handleDating->setSkin(layoutDating);

	auto layoutResult = (Layout *)_skin->getChildByName("layoutResult");
	layoutResult->setVisible(false);
	_handleResult = HandleResult::create();
	_handleResult->retain();
	_handleResult->setSkin(layoutResult);
}

void LayerGuild::switchLayout(const TYPE_OBSERVER_LAYER_GUILD &typeLayout)
{
	Node *nodeNew = nullptr;
	if (typeLayout == TYPE_OBSERVER_LAYER_GUILD::LAYOUT_SELECT)
	{
		nodeNew = _handleSelect->getSkin();
	}
	else if (typeLayout == TYPE_OBSERVER_LAYER_GUILD::LAYOUT_DATING)
	{
		nodeNew = _handleDating->getSkin();
	}
	else if (typeLayout == TYPE_OBSERVER_LAYER_GUILD::LAYOUT_RESULT)
	{
		nodeNew = _handleResult->getSkin();
	}
	ManagerUI::getInstance()->switchTwoNode(_nodeNow, nodeNew, nullptr, [this, nodeNew]()
	{
		_nodeNow->setVisible(false);
		_nodeNow = nodeNew;
		nodeNew->setVisible(true);
	});
}
