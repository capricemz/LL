#pragma execution_character_set("utf-8")

#ifndef __DATA_CONFIG_MANAGER_CFG_DEFINES_H__
#define __DATA_CONFIG_MANAGER_CFG_DEFINES_H__

#include <string>
#include "../define/DefinesValue.h"

using namespace std;

//
struct CfgLevels//关卡
{
	int id;//标志
	string name;//名称
	string urlPic;//图片路径
	string msts;//怪物配置
};
typedef map<int32_t, CfgLevels> DicCfgLevels;
//
struct CfgAttribute//属性
{
	int id;//标志
	string name;//名称
	string urlPic;//图片路径
};
typedef map<int32_t, CfgAttribute> DicCfgAttribute;
//
struct CfgSkill//指令
{
	int id;//标志
	int sort;//排序
	string name;//名称
	TypeSkill type;//类型
	string effect;//效果
	string unlock;//解锁
	string desc;//描述
};
typedef map<int32_t, map<int32_t, CfgSkill>> DicDicCfgSkill;
//
struct CfgSkillGroup//指令组
{
	int id;//标志
	string typeArgs;//条件 类型(1血量百分比2能量值3总回合4回合):参数
	int index;//排序
	string skills;//技能标志 idSkill:indexSkill:num:odds
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
	string urlPic;//图片
	int xPic;//图片x
	int yPic;//图片y
	string attribute;//属性 101生命上限103能量上限104物理攻击105魔法攻击106金币收益
	string skills;//技能
	int skillGroup;//技能组
};
typedef map<int32_t, CfgEntity> DicCfgEntity;
//
struct CfgPlot
{
	int id;//标志
	int sort;//排序
	string textPlot;//文字
	string urlPic;//图片
	float time;//时间（秒）
	int pos;//位置（地图剧情时：0左，1右；战斗剧情时：0-4站位）
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