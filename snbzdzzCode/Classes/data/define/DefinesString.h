#pragma execution_character_set("utf-8")

#ifndef __DATA_DEFINE_DEFINES_STRING_H__
#define __DATA_DEFINE_DEFINES_STRING_H__

#include <vector>
#include <string>
#include "DefinesValue.h"

using namespace std;

static const vector<string> vecError =
{
	"食材不够，无法烹饪~‘(*>o<*)′", "目标未达成，无法领取~‘(*>o<*)′", "体力不足，无法传送~‘(*>o<*)′", "暂未解锁，不能烹饪~‘(*>o<*)′", "行动力不足，无法前进~‘(*>o<*)′",
	"没有可以前往的道路~‘(*>o<*)′", "饱食度已满，不能烹饪~‘(*>o<*)′,", "属性已满，不能烹饪~‘(*>o<*)′", "BOSS接客中，请稍候~‘(*>o<*)′"
};

static const string STR_WU = "无";
static const string STR_REMAIN = "剩余";
static const string STR_COUNT = "次";
static const string STR_BATTLE_VICTORY = "战斗胜利";
static const string STR_BATTLE_DEFEAT = "战斗失败";

static const string STR_HP = "HP";
static const string STR_EP = "EP";

static const string STR_BREAK = "破衣";
static const string STR_DEAD = "角色死亡";

static const string STR_LEVEL_0 = "第";
static const string STR_LEVEL_1 = "关";

/*static const string STR_UNLOCK = "未解锁";
static const string STR_BUY = "购买";
static const string STR_FILLED = "已满";*/

static const string STR_LEVEL_TARGET = "怪物|女仆|出场&x回合内|总回合&x回合内|大于|小于";

static const string STR_COMMA = "，";

static const map<TypeLevelTarget, string> DIC_STR_BY_LEVEL_TARGET_TYPE =
{
	{ TypeLevelTarget::HP_MST, "&a血量&b&x%" },
	{ TypeLevelTarget::HP_MAID, "&a血量&b&x%" },
	{ TypeLevelTarget::PASS, "通关" },
	{ TypeLevelTarget::KILL, "击杀&x次" },
	{ TypeLevelTarget::BREAK, "破衣&x次" },
	{ TypeLevelTarget::GOLD, "获得金币&x次" },
	{ TypeLevelTarget::STONE, "击碎石头&x次" },
	{ TypeLevelTarget::ICE, "融化冰块&x次" },
	{ TypeLevelTarget::TRAP, "解除陷阱&x次" }
};

static const vector<string> STR_LEVEL_TARGET_AWARD_TIP = 
{
	"",
	"一星奖励",
	"二星奖励",
	"三星奖励"
};

#endif