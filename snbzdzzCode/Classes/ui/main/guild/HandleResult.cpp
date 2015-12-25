#pragma execution_character_set("utf-8")

#include "HandleResult.h"

HandleResult::HandleResult() : _skin(nullptr)
{
}

HandleResult::~HandleResult()
{
	_skin = nullptr;
}

bool HandleResult::init()
{
	auto isInit = false;
	do
	{

		isInit = true;
	} while (0);
	return isInit;
}

void HandleResult::setSkin(Layout *skin)
{
	_skin = skin;

}
