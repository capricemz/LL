#pragma execution_character_set("utf-8")

#ifndef __DATA_CONFIG_MANAGER_CFG_DEFINES_H__
#define __DATA_CONFIG_MANAGER_CFG_DEFINES_H__

#include <string>
#include "../define/DefinesValue.h"

using namespace std;

struct CfgAttribute//属性
{
	int id;//标志
	string desc;//描述
	string urlPic;//图片路径
	TypeAttribute type;//类型
	string args;//参数
};
typedef map<int32_t, CfgAttribute> DicCfgAttribute;
//
struct CfgSkill//指令
{
	int id;//标志
	int index;//排序
	string name;//名称
	TypeSkill type;//类型
	string effect;//效果
	int buyCost;//购买花费
	string desc;//描述
};
typedef map<int32_t, map<int32_t, CfgSkill>> DicDicCfgSkill;
//
struct DataSkillInfo
{
	int id;
	int index;
	int num;
	int odds;
};
struct CfgSkillGroup//指令组
{
	int id;//标志
	string typeArgs;//条件 类型(1血量百分比2能量值3总回合4回合):参数
	int index;//排序
	vector<DataSkillInfo> skills;//技能标志
};
typedef map<int32_t, map<string, map<int32_t, CfgSkillGroup>>> DicDicDicCfgSkillGroup;
typedef map<int32_t, vector<string>> DicVecCfgSkillGroupTypeArgs;
//
struct CfgEntity
{
	int id;//标志
	string name;//名称
	TypeEntity type;//类型 1女仆2怪物
	TypeJob typeJob;//职业 1盗贼2战士3法师4治疗5坦克6弓手
	vector<string> vecUrlPic;//图片
	int xPic;//图片x
	int yPic;//图片y
	string attribute;//属性 101生命上限103能量上限104物理攻击105魔法攻击106金币收益
	int idSkillGroup;//技能组id
	int idTraining;//训练id
	int cost;//购买消耗
};
typedef map<int32_t, CfgEntity> DicCfgEntity;
//
struct CfgLevel//关卡
{
	int id;//标志
	string name;//名称
	vector<string> vecUrlPic;//图片路径
	string msts;//怪物配置
	int roundLimit;//回合限制
	bool isRoundLimitWin;//是否回合限制获胜
	vector<int> targets;//目标
	vector<int> unlockLevels;//解锁关卡
	vector<vector<int>> unlockSkills;//解锁技能
	vector<int> unlockMaids;//解锁女仆
	map<IdThing, int> award;//奖励 类型:值
};
typedef map<int32_t, CfgLevel> DicCfgLevels;
//
struct CfgLevelTarget
{
	int id;//标志
	string desc;//描述
	TypeLevelTarget type;//类型
	int args;//参数
	int roundLimitMst;//怪物回合限制
	int roundLimitMaid;//女仆回合限制
	int roundLimitTotal;//总回合限制
	map<IdThing, int> award;//奖励 类型:值
};
typedef map<int32_t, CfgLevelTarget> DicCfgLevelTargets;
//
struct CfgTraining
{
	int id;//标志
	int limitMax;//星数上限
	int valueLvBase;//基础价格
	int valueLvAdd;//每星加价
	int valueLvFull;//满星加价
	int valueOther;//换装加价
	int costWay0;//扰痒消耗(金币)
	int costWay1;//刷牙消耗(道具)
	int costWay2;//换装消耗(道具)
	string urlPic;//换装图片
	vector<vector<string>> vecVecDesc;//文本
	vector<vector<string>> vecVecAnimation;//动画
};
typedef map<int32_t, CfgTraining> DicCfgTraining;
struct CfgThing
{
	int id;//标志
	string name;//名称
	string urlPic;//图片路径
	string desc;//描述
};
typedef map<int32_t, CfgThing> DicCfgThing;
//
struct CfgPlot
{
	int id;//标志
	int index;//排序
	string textPlot;//文字
	string urlPic;//图片
	float time;//单字时间（毫秒）
};
typedef map<int32_t, map<int32_t, CfgPlot>> DicDicCfgPlot;
//
struct CfgTargetAward 
{
	int id;//标志
	int target;//目标
	int award;//奖励
	int num;//数量
	string desc;//描述
	int idNext;//下一项标志
};
typedef map<int32_t, CfgTargetAward> DicCfgTargetAward;
//
//
struct CfgGuide
{
	int id;//标志
	string dirName;//目标（编辑器中节点名称）
	string desc;//描述
	int idRegion;//条件（region.cfg标志）
	int idNext;//下一项标志
};
typedef map<int32_t, CfgGuide> DicCfgGuide;
//
#endif