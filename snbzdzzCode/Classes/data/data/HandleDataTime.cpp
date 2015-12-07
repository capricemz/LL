#pragma execution_character_set("utf-8")

#include "ManagerData.h"
#include "common/util/UtilString.h"

HandleDataTime::~HandleDataTime()
{

}

void HandleDataTime::dataFileInit()
{
	if (!_isDataFileInit)
	{
		_isDataFileInit = true;
		auto userDefault = UserDefault::getInstance();
		auto key = ManagerData::getInstance()->getUserDefaultKey(USER_DEFAULT_KEY_DT);
		userDefault->setStringForKey(key.c_str(), "");//д���ʼ����
		userDefault->flush();//������һ��Ҫ����flush�����ܴӻ���д��io
	}
}

void HandleDataTime::dataFileGet()
{
	auto userDefault = UserDefault::getInstance();
	auto key = ManagerData::getInstance()->getUserDefaultKey(USER_DEFAULT_KEY_DT);
	auto strData = userDefault->getStringForKey(key.c_str());
	if (strData != "")
	{
		auto vec = UtilString::split(strData, ":");
		_timeLast = Value(vec[0]).asDouble();
	}
}

void HandleDataTime::dataFileSet()
{
	auto userDefault = UserDefault::getInstance();
	/*log("`````````````````````ManagerData::dataTimeDataFileSet timeLast:%s", Value(timeLast).asString().c_str());*/
	string strData = Value(_timeLast).asString()/* + ":" + Value(_timeApRst).asString() + ":" + Value(_timeFeedCost).asString()*/;
	auto key = ManagerData::getInstance()->getUserDefaultKey(USER_DEFAULT_KEY_DT);
	userDefault->setStringForKey(key.c_str(), strData);//�޸Ĵ浵
	userDefault->flush();
}
