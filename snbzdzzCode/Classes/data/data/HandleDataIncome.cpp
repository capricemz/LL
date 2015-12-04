#include "ManagerData.h"
#include "common\util\UtilString.h"

DataIncome::DataIncome() : _id(0), _gold(0), _vecIdEntityCatched({})
{
}

DataIncome::~DataIncome()
{
	_vecIdEntityCatched.clear();
}

bool DataIncome::init()
{
	auto isInit = false;
	do 
	{

		isInit = true;
	} while (0);
	return isInit;
}

string DataIncome::getStrData()
{
	string strData = Value(_id).asString();
	strData += ":" + Value(_gold).asString();
	auto length = (int)_vecIdEntityCatched.size();
	if (length != 0)
	{
		strData += ":";
		for (auto i = 0; i < length; i++)
		{
			auto idEntityCatchedMst = _vecIdEntityCatched[i];
			strData += Value(idEntityCatchedMst).asString() + ":";
			strData += ":";//TODO
		}
	}
	return strData;
}

bool DataIncome::isGoldEnoughGet(const int & value)
{
	return _gold >= value;
}

void DataIncome::costGold(const int & value)
{
	_gold -= value;
}

HandleDataIncome::HandleDataIncome() : _isDataFileInit(false), _dicDataIncome({})
{
}

HandleDataIncome::~HandleDataIncome()
{
}

void HandleDataIncome::dataFileInit()
{
	if (!_isDataFileInit)
	{
		_isDataFileInit = true;
		auto userDefault = UserDefault::getInstance();
		userDefault->setStringForKey(USER_DEFAULT_KEY_DI.c_str(), DATA_UNLOCK_INIT_INCOME);//写入初始数据
		userDefault->flush();//设置完一定要调用flush，才能从缓冲写入io
		dataFileGet();
	}
}

void HandleDataIncome::dataFileGet()
{
	auto userDefault = UserDefault::getInstance();
	auto strData = userDefault->getStringForKey(USER_DEFAULT_KEY_DI.c_str());
	if (strData != "")
	{
		auto vecData = UtilString::split(strData, "|");
		auto length = (int)vecData.size();
		for (auto i = 0; i < length; i++)
		{
			createDataIncome(vecData[i]);
		}
	}
}

void HandleDataIncome::dataFileSet()
{
	string strData = "";
	auto userDefault = UserDefault::getInstance();
	for (auto var : _dicDataIncome)
	{
		auto dataIncome = var.second;
		auto str = dataIncome->getStrData();
		strData += (strData != "" ? "|" : "") + str;
	}
	userDefault->setStringForKey(USER_DEFAULT_KEY_DI.c_str(), strData);//修改存档
	userDefault->flush();
}

void HandleDataIncome::createDataIncome(string infos)
{
	if (infos == "")
	{
		return;
	}
	auto data = DataIncome::create();
	auto numDataOther = 2;
	auto numDataCatchedMst = 2;

	auto vecInfo = UtilString::split(infos, ":");
	auto length = (int)vecInfo.size();
	auto index = 0;
	while (index != length)
	{
		auto value = Value(vecInfo[0]).asInt();
		vecInfo.erase(vecInfo.begin());
		if (index == 0)
		{
			data->setId(value);
		}
		else if (index == 1)
		{
			data->setGold(value);
		}
		else
		{
			if ((index - numDataOther) % numDataCatchedMst == 0)
			{
				data->pushVecIdEntityCatched(value);
			}
			else
			{

			}
		}
		index++;
	}
	_dicDataIncome.insert(data->getId(), data);
}
