#pragma execution_character_set("utf-8")

#include "HandleBg.h"
#include "data/data/ManagerData.h"

HandleBg::HandleBg()
{
}

HandleBg::~HandleBg()
{
}

bool HandleBg::init()
{
	auto isInit = false;
	do
	{

		isInit = true;
	} while (0);
	return isInit;
}

void HandleBg::setSkin(Layout *skin)
{
	_skin = skin;

	auto length = 6;
	for (auto i = 0; i < length; i++)
	{
		auto isMst = i < (length / 2);
		auto index = i % (length / 2);
		auto sprite = (Sprite *)_skin->getChildByName(isMst ? "spriteMst" + Value(index).asString() : "spriteMaid" + Value(index).asString());
		auto postion = sprite->getPosition();
		ManagerData::getInstance()->getHandleDataGrid()->postionGridSelectedPush(isMst, postion);
	}

	//²¥·ÅÌØÐ§
	auto spriteVs = (Sprite *)_skin->getChildByName("spriteVs");
	spriteVs->setVisible(false);

	auto actionDelay = DelayTime::create(0.4f);
	auto actionCallFunc = CallFunc::create(CC_CALLBACK_0(HandleBg::updateTxtRound, this));
	spriteVs->runAction(Sequence::createWithTwoActions(actionDelay, actionCallFunc));

	auto txt = (Text *)_skin->getChildByName("txtRound0");
	txt->setVisible(false);
	txt = (Text *)_skin->getChildByName("txtRound1");
	txt->setVisible(false);
	txt = (Text *)_skin->getChildByName("txtRound");
	txt->setVisible(false);
}

void HandleBg::updateTxtRound()
{
	auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
	auto round = handleDataEntity->getRoundTotal();
	auto handleDataLevels = ManagerData::getInstance()->getHandleDataLevels();
	auto cfgLevel = handleDataLevels->getDataLevelCurrent()->getCfgLevel();
	auto roundLimit = cfgLevel.roundLimit;

	auto txt = (Text *)_skin->getChildByName("txtRound0");
	txt->setString(Value(round).asString());
	txt->setVisible(true);

	txt = (Text *)_skin->getChildByName("txtRound1");
	txt->setString(Value(roundLimit).asString());
	txt->setVisible(true);

	txt = (Text *)_skin->getChildByName("txtRound");
	txt->setVisible(true);
}
