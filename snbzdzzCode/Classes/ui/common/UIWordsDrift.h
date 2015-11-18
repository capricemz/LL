#ifndef __UI_COMMON_UI_WORDS_DRIFT_H__
#define __UI_COMMON_UI_WORDS_DRIFT_H__

#include "cocos2d.h"
#include <string>

USING_NS_CC;
using namespace std;

class UIWordsDrift : public Node
{
public:
	CREATE_FUNC(UIWordsDrift);

public:
	UIWordsDrift();
	~UIWordsDrift();
	virtual bool init();
	void driftWords(const string &words, const Color4B &color, const float &duration);

};

#endif