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
		userDefault->setStringForKey(USER_DEFAULT_KEY_DT.c_str(), "");//写入初始数据
		userDefault->flush();//设置完一定要调用flush，才能从缓冲写入io
	}
}

void HandleDataTime::dataFileGet()
{
	auto userDefault = UserDefault::getInstance();
	auto strDataTimeData = userDefault->getStringForKey(USER_DEFAULT_KEY_DT.c_str());
	if (strDataTimeData != "")
	{
		auto vec = UtilString::split(strDataTimeData, ":");
		_timeLast = Value(vec[0]).asDouble();
	}
}

void HandleDataTime::dataFileSet()
{
	auto userDefault = UserDefault::getInstance();
	/*log("`````````````````````ManagerData::dataTimeDataFileSet timeLast:%s", Value(timeLast).asString().c_str());*/
	string strDataTimeData = Value(_timeLast).asString()/* + ":" + Value(_timeApRst).asString() + ":" + Value(_timeFeedCost).asString()*/;
	userDefault->setStringForKey(USER_DEFAULT_KEY_DT.c_str(), strDataTimeData);//修改存档
	userDefault->flush();
}
