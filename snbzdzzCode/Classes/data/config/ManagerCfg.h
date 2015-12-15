#pragma execution_character_set("utf-8")

#ifndef __DATA_CONFIG_MANAGER_CFG_H__
#define __DATA_CONFIG_MANAGER_CFG_H__

#include "cocos2d.h"
#include "common/util/UtilString.h"
#include "ManagerCfgDefines.h"
#include "../define/DefinesValue.h"

USING_NS_CC;

class ManagerCfg : public Node
{
public:
	static ManagerCfg *getInstance();//提供getInstance全局指针
	static void destroyInstance();
	
public:
	TypeLoadState getTypeLoadState() const
	{
		return _typeLoadState;
	}
	DicCfgAttribute getDicCfgAttribute() const
	{
		return _dicCfgAttribute;
	};
	DicDicCfgSkill getDicDicCfgSkill() const
	{
		return _dicDicCfgSkill;
	};
	DicDicDicCfgSkillGroup getDicDicDicCfgSkillGroup() const
	{
		return _dicDicDicCfgSkillGroup;
	};
	DicVecCfgSkillGroupTypeArgs getDicVecCfgSkillGroupTypeArgs() const
	{
		return _dicVecCfgSkillGroupTypeArgs;
	};
	DicCfgEntity getDicCfgEntity() const
	{
		return _dicCfgEntity;
	};
	DicCfgLevels getDicCfgLevels() const
	{
		return _dicCfgLevels;
	};
	DicCfgLevelTargets getDicCfgLevelTargets() const
	{
		return _dicCfgLevelTargets;
	};
	DicCfgGrade getDicCfgGrade() const
	{
		return _dicCfgGrade;
	};
	DicCfgTraining getDicCfgTraining() const
	{
		return _dicCfgTraining;
	}
	DicCfgThing getDicCfgThing() const
	{
		return _dicCfgThing;
	}
	DicDicCfgPlot getDicDicCfgPlot() const
	{
		return _dicDicCfgPlot;
	};
	DicCfgTargetAward getDicCfgTargetAward() const
	{
		return _dicDicCfgTargetAward;
	};
	DicCfgGuide getDicCfgGuide() const
	{
		return _dicDicCfgGuide;
	};
	
public:
	virtual ~ManagerCfg();
	void loadConfigs();
	
private:
	ManagerCfg();
	void threadDeal();
	void doLoad(const string &fileName, function<void(const VectorString &)> func);

	string readFileByName(const string &fileName);

	void assignCfgAttribute(const VectorString &vecItem);
	void assignCfgSkill(const VectorString &vecItem);
	void assignCfgSkillGroup(const VectorString &vecItem);
	void assignCfgSkillGroupTypeArgs();
	void assignCfgEntity(const VectorString &vecItem);
	void assignCfgLevels(const VectorString &vecItem);
	void assignCfgLevelTargets(const VectorString &vecItem);
	void assignCfgGrade(const VectorString &vecItem);
	void assignCfgTraining(const VectorString &vecItem);
	void assignCfgThing(const VectorString &vecItem);
	void assignCfgPlot(const VectorString &vecItem);
	void assignCfgTargetAward(const VectorString &vecItem);
	void assignCfgGuide(const VectorString &vecItem);
	
private:
	TypeLoadState _typeLoadState;
	
	DicCfgAttribute _dicCfgAttribute;
	DicDicCfgSkill _dicDicCfgSkill;
	DicDicDicCfgSkillGroup _dicDicDicCfgSkillGroup;
	DicVecCfgSkillGroupTypeArgs _dicVecCfgSkillGroupTypeArgs;
	DicCfgEntity _dicCfgEntity;
	DicCfgLevels _dicCfgLevels;
	DicCfgLevelTargets _dicCfgLevelTargets;
	DicCfgGrade _dicCfgGrade;
	DicCfgTraining _dicCfgTraining;
	DicCfgThing _dicCfgThing;
	DicDicCfgPlot _dicDicCfgPlot;
	DicCfgTargetAward _dicDicCfgTargetAward;
	DicCfgGuide _dicDicCfgGuide;
	
};

#endif