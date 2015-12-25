#pragma execution_character_set("utf-8")

#include "HandleDating.h"

HandleDating::HandleDating() : _skin(nullptr)
{
}

HandleDating::~HandleDating()
{
	_skin = nullptr;
}

bool HandleDating::init()
{
	auto isInit = false;
	do
	{
		isInit = true;
	} while (0);
	return isInit;
}

void HandleDating::setSkin(Layout *skin)
{
	_skin = skin;

	createRegion();
}

void HandleDating::createRegion()
{

}

void HandleDating::createBtn()
{

}
