#pragma execution_character_set("utf-8")

#ifndef __DATA_DEFINE_DEFINES_STRING_H__
#define __DATA_DEFINE_DEFINES_STRING_H__

#include <vector>
#include <string>

using namespace std;

static const vector<string> vecError =
{
	"食材不够，无法烹饪~‘(*>o<*)′", "目标未达成，无法领取~‘(*>o<*)′", "体力不足，无法传送~‘(*>o<*)′", "暂未解锁，不能烹饪~‘(*>o<*)′", "行动力不足，无法前进~‘(*>o<*)′",
	"没有可以前往的道路~‘(*>o<*)′", "饱食度已满，不能烹饪~‘(*>o<*)′,", "属性已满，不能烹饪~‘(*>o<*)′", "BOSS接客中，请稍候~‘(*>o<*)′"
};

static const string STR_WU = "无";
static const string STR_BATTLE_VICTORY = "战斗胜利";
static const string STR_BATTLE_DEFEAT = "战斗失败";

static const string STR_HP = "HP";
static const string STR_EP = "EP";

static const string STR_DEAD = "角色死亡";

static const string STR_LEVEL_0 = "第";
static const string STR_LEVEL_1 = "关";

#endif