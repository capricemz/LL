#pragma execution_character_set("utf-8")

#ifndef __CORE_ENTITY_SUBS_CENERY_H__
#define __CORE_ENTITY_SUBS_CENERY_H__

#include "cocos2d.h"
#include "ui/common/SpriteBlur.h"

USING_NS_CC;

class Scenery : public Node
{
public:
	CREATE_FUNC(Scenery);

public:
	Scenery();
	~Scenery();

	virtual bool init();

	void updateSkin(const bool &isMst);

	void runEffect();
	void stopEffect();
	
public:
	bool getIsMst() const
	{
		return _isMst;
	}
	
private:
	Sprite *_skin;

	SpriteBlur *_skinBlur;

	bool _isMst;
	
};

#endif