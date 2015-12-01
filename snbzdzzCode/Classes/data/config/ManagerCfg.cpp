#pragma execution_character_set("utf-8")

#include "ManagerCfg.h"

static ManagerCfg *_instance = nullptr;//静态成员变量的定义

ManagerCfg * ManagerCfg::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new ManagerCfg();
	}
	return _instance;
}

void ManagerCfg::destroyInstance()
{
	CC_SAFE_DELETE(_instance);
}

ManagerCfg::ManagerCfg() : 
	_typeLoadState(TypeLoadState::UNLOAD),
	_dicCfgAttribute({}),
	_dicDicCfgSkill({}),
	_dicDicDicCfgSkillGroup({}),
	_dicVecCfgSkillGroupTypeArgs({}),
	_dicCfgEntity({}),
	_dicCfgLevels({}),
	_dicDicCfgPlot({}),
	_dicDicCfgTargetAward({}),
	_dicDicCfgGuide({})
{
}

ManagerCfg::~ManagerCfg()
{
	_dicCfgAttribute.clear();
	_dicDicCfgSkill.clear();
	_dicDicDicCfgSkillGroup.clear();
	_dicVecCfgSkillGroupTypeArgs.clear();
	_dicCfgEntity.clear();
	_dicCfgLevels.clear();
	_dicDicCfgPlot.clear();
	_dicDicCfgTargetAward.clear();
	_dicDicCfgGuide.clear();
}

void ManagerCfg::loadConfigs()
{
	if (_typeLoadState != TypeLoadState::UNLOAD)
	{
		return;
	}
	_typeLoadState = TypeLoadState::LOADING;
	thread thread(&ManagerCfg::threadDeal, this);
	thread.detach();
}

void ManagerCfg::threadDeal()
{
	doLoad("attribute.cfg", CC_CALLBACK_1(ManagerCfg::assignCfgAttribute, this));
	doLoad("skill.cfg", CC_CALLBACK_1(ManagerCfg::assignCfgSkill, this));
	doLoad("skillGroup.cfg", CC_CALLBACK_1(ManagerCfg::assignCfgSkillGroup, this));
	assignCfgSkillGroupTypeArgs();
	doLoad("entity.cfg", CC_CALLBACK_1(ManagerCfg::assignCfgEntity,this));
	doLoad("levels.cfg", CC_CALLBACK_1(ManagerCfg::assignCfgLevels, this));
	doLoad("levelTargets.cfg", CC_CALLBACK_1(ManagerCfg::assignCfgLevelTargets, this));
	doLoad("plot.cfg", CC_CALLBACK_1(ManagerCfg::assignCfgPlot, this));
	doLoad("targetAward.cfg", CC_CALLBACK_1(ManagerCfg::assignCfgTargetAward, this));
	doLoad("guide.cfg", CC_CALLBACK_1(ManagerCfg::assignCfgGuide, this));
	_typeLoadState = TypeLoadState::LOADED;
}

void ManagerCfg::doLoad(const string &fileName, function<void(const VectorString &)> func)
{
	/*auto strCfg = readFileByName(fileName);*/
	auto strCfg = FileUtils::getInstance()->getStringFromFile(fileName);
	string delim = "[data]";
	strCfg = strCfg.substr(strCfg.find(delim) + delim.length(), strCfg.length());
	delim = "\r\n";
	auto vecCfg = UtilString::split(strCfg, delim);
	delim = "\t";
	for (auto strItem : vecCfg)
	{
		if (strItem == "")
		{
			continue;
		}
		auto vecItem = UtilString::split(strItem, delim);
		func(vecItem);
	}
}

std::string ManagerCfg::readFileByName(const string &fileName)
{
	auto fullPath = FileUtils::getInstance()->fullPathForFilename(fileName);

	log("loadPath = %s", fullPath.c_str());

	if (fullPath.length() <= 0)
	{
		return nullptr;
	}
	auto file = fopen(fullPath.c_str(), "r");//创建一个文件指针
	if (!file)
	{
		log("file doesn't exist.");
		return nullptr;
	}
	char *buf;//要获取的字符串
	int len;//获取的长度
	fseek(file, 0, SEEK_END);//移到尾部
	len = ftell(file);//提取长度
	rewind(file);//回归原位
	//分配buf空间
	buf = (char *)malloc(sizeof(char) * len + 1);
	if (!buf)
	{
		log("malloc space is not enough.");
		return nullptr;
	}
	//读取文件
	int rlen = fread(buf, sizeof(char), len, file);//读取进的buf，单位大小，长度，文件指针
	buf[rlen] = '\0';
	/*log("has read Length = %d", rlen);
	log("has read content = %s", buf);*/

	string result = buf;
	fclose(file);
	free(buf);
	return result;
}

void ManagerCfg::assignCfgAttribute(const VectorString &vecItem)
{
	CfgAttribute cfg;
	cfg.id = Value(vecItem[0]).asInt();
	auto nameTemp = vecItem[1];
	auto isFind = nameTemp.find("//") != string::npos;
	cfg.desc = isFind ? UtilString::split(nameTemp, "//")[0] : nameTemp;
	cfg.urlPic = vecItem[2];
	auto typeTemp = vecItem[3];
	isFind = typeTemp.find("//") != string::npos;
	typeTemp = isFind ? UtilString::split(typeTemp, "//")[0] : typeTemp;
	cfg.type = (TypeAttribute)Value(typeTemp).asInt();
	cfg.args = vecItem[4];
	_dicCfgAttribute[cfg.id] = cfg;
}

void ManagerCfg::assignCfgSkill(const VectorString &vecItem)
{
	CfgSkill cfg;
	cfg.id = Value(vecItem[0]).asInt();
	cfg.index = Value(vecItem[1]).asInt();
	cfg.name = vecItem[2];
	cfg.type = (TypeSkill)Value(vecItem[3]).asInt();
	cfg.effect = vecItem[4];
	cfg.unlock = vecItem[5];
	cfg.desc = vecItem[6];
	_dicDicCfgSkill[cfg.id][cfg.index] = cfg;
}

void ManagerCfg::assignCfgSkillGroup(const VectorString &vecItem)
{
	CfgSkillGroup cfg;
	cfg.id = Value(vecItem[0]).asInt();
	cfg.typeArgs = vecItem[1];
	cfg.index = Value(vecItem[2]).asInt();
	cfg.skills = vecItem[3];
	_dicDicDicCfgSkillGroup[cfg.id][cfg.typeArgs][cfg.index] = cfg;
}

void ManagerCfg::assignCfgSkillGroupTypeArgs()
{
	function<void(const string &typeStr, int &hpPercent, int &energyValue)> dealHpPercentEnergyValue = [](const string &typeStr, int &hpPercent, int &energyValue)
	{
		auto vecFront = UtilString::split(typeStr, "|");
		for (auto var : vecFront)
		{
			auto vecFont = UtilString::split(var, ":");
			TypeSkillGroup type = (TypeSkillGroup)Value(vecFont[0]).asInt();
			if (type == TypeSkillGroup::HP_PERCENT)
			{
				hpPercent = Value(vecFont[1]).asInt();
			}
			else if (type == TypeSkillGroup::ENERGY_VALUE)
			{
				energyValue = Value(vecFont[1]).asInt();
			}
		}
	};
	for (auto var : _dicDicDicCfgSkillGroup)
	{
		auto dicDicCfgSkillGroup = var.second;
		VectorString vecCfgSkillGroupTypeArgs;
		for (auto var : dicDicCfgSkillGroup)
		{
			vecCfgSkillGroupTypeArgs.push_back(var.first);
		}
		auto length = (int)vecCfgSkillGroupTypeArgs.size();
		for (auto i = 0; i < length - 1; i++)
		{
			auto isSwap = false;
			for (auto j = length - 1; j > i; j--)
			{
				auto typeFront = vecCfgSkillGroupTypeArgs[j - 1];
				auto hpPercentFront = INT32_MAX;
				auto energyValueFront = 0;
				dealHpPercentEnergyValue(typeFront, hpPercentFront, energyValueFront);
				auto typeBehind = vecCfgSkillGroupTypeArgs[j];
				auto hpPercentBehind = INT32_MAX;
				auto energyValueBehind = 0;
				dealHpPercentEnergyValue(typeBehind, hpPercentBehind, energyValueBehind);
				auto isNeedSwap = hpPercentFront > hpPercentBehind || (hpPercentFront == hpPercentBehind && energyValueFront < energyValueBehind);
				if (isNeedSwap)
				{
					swap(vecCfgSkillGroupTypeArgs[j - 1], vecCfgSkillGroupTypeArgs[j]);
					isSwap = true;
				}
			}
			if (!isSwap)
			{
				break;
			}
		}
		_dicVecCfgSkillGroupTypeArgs[var.first] = vecCfgSkillGroupTypeArgs;
	}
}

void ManagerCfg::assignCfgEntity(const VectorString &vecItem)
{
	CfgEntity cfg;
	cfg.id = Value(vecItem[0]).asInt();
	cfg.name = vecItem[1];
	cfg.type = (TypeEntity)Value(vecItem[2]).asInt();
	cfg.typeJob = (TypeJob)Value(vecItem[3]).asInt();
	auto vecUrlPic = UtilString::split(vecItem[4], ":");
	cfg.vecUrlPic = vecUrlPic;
	auto vecStr = UtilString::split(vecItem[5], ":");
	cfg.xPic = Value(vecStr[0]).asInt();
	cfg.yPic = Value(vecStr[1]).asInt();
	cfg.attribute = vecItem[6];
	cfg.skillGroup = Value(vecItem[7]).asInt();
	_dicCfgEntity[cfg.id] = cfg;
}

void ManagerCfg::assignCfgLevels(const VectorString &vecItem)
{
	CfgLevel cfg;
	cfg.id = Value(vecItem[0]).asInt();
	auto nameTemp = vecItem[1];
	auto isFind = nameTemp.find("//") != string::npos;
	cfg.name = isFind ? UtilString::split(nameTemp, "//")[0] : nameTemp;
	auto vecUrlPic = UtilString::split(vecItem[2], ":");
	cfg.vecUrlPic = vecUrlPic;
	cfg.msts = vecItem[3];
	cfg.roundLimit = Value(vecItem[4]).asInt();
	cfg.isRoundLimitWin = Value(vecItem[5]).asBool();
	auto strTargets = vecItem[6];
	if (strTargets != "")
	{
		auto vec = UtilString::split(strTargets, ":");
		for (auto var : vec)
		{
			cfg.targets.push_back(Value(var).asInt());
		}
	}
	cfg.unlockLevel = Value(vecItem[7]).asInt();
	_dicCfgLevels[cfg.id] = cfg;
}

void ManagerCfg::assignCfgLevelTargets(const VectorString &vecItem)
{
	CfgLevelTarget cfg;
	cfg.id = Value(vecItem[0]).asInt();
	cfg.desc = vecItem[1];
	cfg.type = (TypeLevelTarget)Value(vecItem[2]).asInt();
	cfg.args = Value(vecItem[3]).asInt();
	cfg.roundLimitMst = Value(vecItem[4]).asInt();
	cfg.roundLimitMaid = Value(vecItem[5]).asInt();
	cfg.roundLimitTotal = Value(vecItem[6]).asInt();
	cfg.award = vecItem[7];
	_dicCfgLevelTargets[cfg.id] = cfg;
}

void ManagerCfg::assignCfgPlot(const VectorString &vecItem)
{
	CfgPlot cfg;
	cfg.id = Value(vecItem[0]).asInt();
	cfg.sort = Value(vecItem[1]).asInt();
	cfg.textPlot = vecItem[2];
	cfg.urlPic = vecItem[3];
	cfg.time = Value(vecItem[4]).asFloat();
	cfg.pos = Value(vecItem[5]).asInt();
	_dicDicCfgPlot[cfg.id][cfg.sort] = cfg;
}

void ManagerCfg::assignCfgTargetAward(const VectorString &vecItem)
{
	CfgTargetAward cfg;
	cfg.id = Value(vecItem[0]).asInt();
	cfg.target = Value(vecItem[1]).asInt();
	cfg.award = Value(vecItem[2]).asInt();
	cfg.num = Value(vecItem[3]).asInt();
	cfg.desc = vecItem[4];
	cfg.idNext = vecItem[5] == "" ? -1 : Value(vecItem[5]).asInt();
	_dicDicCfgTargetAward[cfg.id] = cfg;
}

void ManagerCfg::assignCfgGuide(const VectorString &vecItem)
{
	CfgGuide cfg;
	cfg.id = Value(vecItem[0]).asInt();
	cfg.dirName = vecItem[1];
	cfg.desc = vecItem[2];
	cfg.idRegion = Value(vecItem[3]).asInt();
	cfg.idNext = vecItem[4] == "" ? -1 : Value(vecItem[4]).asInt();
	_dicDicCfgGuide[cfg.id] = cfg;
}
