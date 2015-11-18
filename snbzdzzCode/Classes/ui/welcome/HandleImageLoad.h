#pragma execution_character_set("utf-8")

#ifndef __UI_WELCOME_HANDLE_IMAGE_LOAD__
#define __UI_WELCOME_HANDLE_IMAGE_LOAD__

#include "cocos2d.h"
#include <string>
#include "data/define/DefinesValue.h"

USING_NS_CC;
using namespace std;

class HandleImageLoad : public Ref
{
public:
	CREATE_FUNC(HandleImageLoad);

public:
	HandleImageLoad();
	~HandleImageLoad();

	virtual bool init();

	void loadImages();

public:
	TypeLoadState getTypeLoadState() const 
	{
		return _typeLoadState;
	}

private:
	/*º”‘ÿplistªÚpng
	fileName *.plistªÚ*.png*/
	void imageAsyncLoad(const string &fileName);

	void imageAsyncCallback(Texture2D *texture, const string &fileName);

private:
	TypeLoadState _typeLoadState;
	map<string, bool> _dicUrlLoaded;
	int _numPlistNeedLoad;
};

#endif