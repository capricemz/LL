#include "ManagerData.h"
#include "common/util/UtilString.h"
#include "../config/ManagerCfg.h"

DataTrainingInfo::DataTrainingInfo() : _idEntity(0), _valueLv(0), _valuePrecent(0), _isClothed(false)
{
}

DataTrainingInfo::~DataTrainingInfo()
{
}

bool DataTrainingInfo::init()
{
	auto isInit = false;
	do
	{

		isInit = true;
	} while (0);
	return isInit;
}

HandleDataIncome::HandleDataIncome() : _isDataFileInit(false), _dicThing({}), _vecDataTrainingInfo({})
{
}

HandleDataIncome::~HandleDataIncome()
{
	_dicThing.clear();
	_vecDataTrainingInfo.clear();
}

void HandleDataIncome::dataFileInit()
{
	if (!_isDataFileInit)
	{
		_isDataFileInit = true;
		/*auto userDefault = UserDefault::getInstance();
		auto key = ManagerData::getInstance()->getUserDefaultKey(USER_DEFAULT_KEY_DI);
		userDefault->setStringForKey(key.c_str(), "");//写入初始数据
		userDefault->flush();//设置完一定要调用flush，才能从缓冲写入io*/
		setThing(IdThing::TRAINING, TRAINING_NUM_MAX);
		dataFileSet();
	}
}

void HandleDataIncome::dataFileGet()
{
	auto userDefault = UserDefault::getInstance();
	auto key = ManagerData::getInstance()->getUserDefaultKey(USER_DEFAULT_KEY_DI);
	auto strData = userDefault->getStringForKey(key.c_str());
	if (strData == "")
	{
		return;
	}
	auto vecInfo = UtilString::split(strData, "|");

	auto vecInfoThing = UtilString::split(vecInfo[0], ":");
	auto length = (int)vecInfoThing.size();
	for (auto i = 0; i < length; i++)
	{
		if (i % LENGTH_INFO_THING == LENGTH_INFO_THING - 1)
		{
			auto idThing = (IdThing)Value(vecInfoThing[i - 1]).asInt();
			auto value = Value(vecInfoThing[i]).asInt();
			setThing(idThing, value);
		}
	}

	if ((int)vecInfo.size() <= 1)
	{
		return;
	}

	auto vecInfoCatchMst = UtilString::split(vecInfo[1], ":");
	length = (int)vecInfoCatchMst.size();
	for (auto i = 0; i < length; i++)
	{
		if (i % LENGTH_INFO_CATCH_MST == LENGTH_INFO_CATCH_MST - 1)
		{
			auto idEntity = Value(vecInfoCatchMst[i - 3]).asInt();
			auto valueLv = Value(vecInfoCatchMst[i - 2]).asInt();
			auto valuePrecent = Value(vecInfoCatchMst[i - 1]).asInt();
			auto isClothed = Value(vecInfoCatchMst[i]).asInt() != 0;

			pushVecDataTrainingInfo(idEntity, valueLv, valuePrecent, isClothed);
		}
	}
}

void HandleDataIncome::dataFileSet()
{
	string strData = "";
	auto isFirst = true;
	for (auto var : _dicThing)
	{
		strData += (isFirst ? "" : ":") + Value((int)var.first).asString() + ":" + Value(var.second).asString();
		isFirst = false;
	}

	auto length = (int)_vecDataTrainingInfo.size();
	for (auto i = 0; i < length; i++)
	{
		auto dt = _vecDataTrainingInfo.at(i);
		strData += (i == 0 ? (strData == "" ? "" : "|") : ":") + 
			Value(dt->getIdEntity()).asString() + ":" + 
			Value(dt->getValueLv()).asString() + ":" + 
			Value(dt->getValuePrecent()).asString() + ":" + 
			Value(dt->getIsClothed() ? 1 : 0).asString();
	}
	
	auto userDefault = UserDefault::getInstance();
	auto key = ManagerData::getInstance()->getUserDefaultKey(USER_DEFAULT_KEY_DI);
	userDefault->setStringForKey(key.c_str(), strData);//修改存档
	userDefault->flush();
}

int HandleDataIncome::getThing(const IdThing &idThing)
{
	if (_dicThing.find(idThing) == _dicThing.end())
	{
		return 0;
	}
	else
	{
		return _dicThing[idThing];
	}
}

bool HandleDataIncome::getThingEnough(const IdThing &idThing, const int &valueNeed)
{
	auto value = getThing(idThing);
	return value >= valueNeed;
}

void HandleDataIncome::setThing(const IdThing &idThing, const int &value)
{
	if (_dicThing.find(idThing) == _dicThing.end())//若无该值
	{
		if (value != 0)
		{
			_dicThing.insert(std::make_pair(idThing, value));
		}
	}
	else
	{
		if (value == 0)
		{
			_dicThing.erase(idThing);
		}
		else
		{
			_dicThing[idThing] = value;
		}
	}
}

void HandleDataIncome::addThingBefore(const IdThing &idThing, const int &value)
{
	if (idThing == IdThing::EXP)
	{
	}
}

void HandleDataIncome::addThing(const IdThing &idThing, const int &value)
{
	if (value == 0)
	{
		return;
	}
	addThingBefore(idThing, value);
	setThing(idThing, getThing(idThing) + value);
	addThingAfter(idThing, value);
}

void HandleDataIncome::addThingAfter(const IdThing &idThing, const int &value)
{
	if (idThing == IdThing::EXP)
	{
		auto handleDataGrade = ManagerData::getInstance()->getHandleDataGrade();
		auto isGradeUp = handleDataGrade->getIsGradeUp();
		if (isGradeUp)
		{
			auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
			handleDataEntity->updateAttributeGrade();
		}
	}
	else if (idThing == IdThing::TRAINING)
	{
		auto valueTemp = getThing(IdThing::TRAINING);
		if (valueTemp > TRAINING_NUM_MAX)
		{
			setThing(IdThing::TRAINING, TRAINING_NUM_MAX);
		}
	}
}

DataTrainingInfo * HandleDataIncome::getDataTrainingInfo(const int &index)
{
	if ((int)_vecDataTrainingInfo.size() > index)
	{
		return _vecDataTrainingInfo.at(index);
	}
	return nullptr;
}

void HandleDataIncome::pushVecDataTrainingInfo(const int &idEntity, const int &valueLv, const int &valuePrecent, const bool &isClothed)
{
	auto dt = DataTrainingInfo::create();
	dt->setIdEntity(idEntity);
	dt->setValueLv(valueLv);
	dt->setValuePrecent(valuePrecent);
	dt->setIsClothed(isClothed);
	_vecDataTrainingInfo.pushBack(dt);
}

void HandleDataIncome::earseVecDataTrainingInfo(int index)
{
	if ((int)_vecDataTrainingInfo.size() > index)
	{
		_vecDataTrainingInfo.erase(index);
	}
}
