#include "ManagerData.h"
#include "common\util\UtilString.h"

DataIncome::DataIncome() : _id(0), _gold(0), _vecIdEntityCatched({}), _vecValue({})
{
}

DataIncome::~DataIncome()
{
	_vecIdEntityCatched.clear();
	_vecValue.clear();
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
	string strData = Value(_gold).asString();
	/*strData += ":" + Value(_gold).asString();*/
	auto length = (int)_vecIdEntityCatched.size();
	if (length != 0)
	{
		for (auto i = 0; i < length; i++)
		{
			auto idEntityCatchedMst = _vecIdEntityCatched[i];
			strData += ":";
			strData += Value(idEntityCatchedMst).asString();
			strData += ":";
			strData += Value().asString();
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

HandleDataIncome::HandleDataIncome() : _isDataFileInit(false), _dataIncome(nullptr)
{
}

HandleDataIncome::~HandleDataIncome()
{
	CC_SAFE_RELEASE_NULL(_dataIncome);
}

void HandleDataIncome::dataFileInit()
{
	if (!_isDataFileInit)
	{
		_isDataFileInit = true;
		auto userDefault = UserDefault::getInstance();
		auto key = ManagerData::getInstance()->getUserDefaultKey(USER_DEFAULT_KEY_DI);
		userDefault->setStringForKey(key.c_str(), "0");//写入初始数据
		userDefault->flush();//设置完一定要调用flush，才能从缓冲写入io
		dataFileGet();
	}
}

void HandleDataIncome::dataFileGet()
{
	auto userDefault = UserDefault::getInstance();
	auto key = ManagerData::getInstance()->getUserDefaultKey(USER_DEFAULT_KEY_DI);
	auto strData = userDefault->getStringForKey(key.c_str());
	if (strData != "")
	{
		createDataIncome(strData);
	}
}

void HandleDataIncome::dataFileSet()
{
	string strData = _dataIncome->getStrData();
	auto userDefault = UserDefault::getInstance();
	auto key = ManagerData::getInstance()->getUserDefaultKey(USER_DEFAULT_KEY_DI);
	userDefault->setStringForKey(key.c_str(), strData);//修改存档
	userDefault->flush();
}

void HandleDataIncome::createDataIncome(string infos)
{
	CC_SAFE_RELEASE_NULL(_dataIncome);
	_dataIncome = DataIncome::create();
	CC_SAFE_RETAIN(_dataIncome);
	auto numDataOther = 1;
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
			_dataIncome->setGold(value);
		}
		else
		{
			if ((index - numDataOther) % numDataCatchedMst == 0)
			{
				_dataIncome->pushVecIdEntityCatched(value);
			}
			else
			{

			}
		}
		index++;
	}
}
