#pragma execution_character_set("utf-8")

#include "HandleImageLoad.h"
#include "common/util/UtilString.h"
#include "data/define/DefinesRes.h"
#include "data/config/ManagerCfg.h"


HandleImageLoad::HandleImageLoad() : _typeLoadState(TypeLoadState::UNLOAD), _numPlistNeedLoad(0)
{
}

HandleImageLoad::~HandleImageLoad()
{
}

bool HandleImageLoad::init()
{
	auto isInit = false;
	do 
	{
		isInit = true;
	} while (0);
	return isInit;
}

void HandleImageLoad::loadImages()
{
	if (_typeLoadState != TypeLoadState::UNLOAD)
	{
		return;
	}
	_typeLoadState = TypeLoadState::LOADING;
	imageAsyncLoad(RES_MODULES_COMMON_PLIST_COMMON_PLIST);
	imageAsyncLoad(RES_MODULES_MAIN_PLIST_MAIN_PLIST);
	//¼ÓÔØ±³¾°Í¼Æ¬
	imageAsyncLoad(RES_IMAGES_MAIN_BG_BATTLE_BG1_PNG);
	//¼ÓÔØÊµÌåÍ¼Æ¬
	auto dicCfgEntity = ManagerCfg::getInstance()->getDicCfgEntity();
	for (auto var : dicCfgEntity)
	{
		auto cfgEntity = var.second;
		auto urlPic = cfgEntity.urlPic;
		if (_dicUrlLoaded.find(urlPic) == _dicUrlLoaded.end())
		{
			_dicUrlLoaded[urlPic] = true;
			imageAsyncLoad(urlPic);
		}
	}
}

void HandleImageLoad::imageAsyncLoad(const string &fileName)
{
	string fileNamePic = fileName;
	if (fileName.find(".png") == std::string::npos)
	{
		UtilString::stringReplace(fileNamePic, ".plist", ".png");
	}
	Director::getInstance()->getTextureCache()->addImageAsync(fileNamePic, CC_CALLBACK_1(HandleImageLoad::imageAsyncCallback, this, fileName));
	_numPlistNeedLoad++;
}

void HandleImageLoad::imageAsyncCallback(Texture2D *texture, const string &fileName)
{
	if(fileName.find(".png") == std::string::npos)
	{
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(fileName, texture);
	}
	_numPlistNeedLoad--;
	if (_numPlistNeedLoad <= 0)
	{
		_typeLoadState = TypeLoadState::LOADED;
		_dicUrlLoaded.clear();
	}
}
