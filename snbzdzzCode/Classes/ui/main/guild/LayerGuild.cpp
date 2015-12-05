#include "LayerGuild.h"
#include "data/define/DefinesRes.h"

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

void LayerGuild::createSkin()
{
	_skin = (Layer *)CSLoader::createNode(RES_MODULES_MAIN_LAYER_GUILD_CSB);
	addChild(_skin);


}
