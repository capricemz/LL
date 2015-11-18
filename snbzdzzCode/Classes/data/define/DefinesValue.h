#pragma execution_character_set("utf-8")

#ifndef __DATA_DEFINE_DEFINES_VALUE_H__
#define __DATA_DEFINE_DEFINES_VALUE_H__

#include <vector>
#include "math/Vec2.h"

USING_NS_CC;
using namespace std;

static const int TIME_LAST_SAVE_INTERVAL = 300;
static const int TIME_OFF_LINE_MAX = 172800;

static const int GRID_SELECT_MAX = 9;
static const int GRID_SELECTED_MAX = 4;
static const int ENTITY_BATTLE_MAX = 3;

static const vector<Vec2> vecPostionGridSelect =
{
	Vec2(60.0f, 396.0f), Vec2(187.0f, 396.0f), Vec2(314.0f, 396.0f),
	Vec2(60.0f, 238.0f), Vec2(187.0f, 238.0f), Vec2(314.0f, 238.0f),
	Vec2(60.0f, 80.0f), Vec2(187.0f, 80.0f), Vec2(314.0f, 80.0f)
};

static const vector<Vec2> vecPostionGridShowMst =
{
	Vec2(80.0f, 259.0f), Vec2(202.0f, 259.0f), Vec2(324.0f, 259.0f), Vec2(446.0f, 259.0f)
};

static const vector<Vec2> vecPostionGridShowMaid =
{
	Vec2(194.0f, 80.0f), Vec2(316.0f, 80.0f), Vec2(438.0f, 80.0f), Vec2(560.0f, 80.0f)
};

static const vector<Vec2> vecPostionGridSelectedMaid =
{
	Vec2(218.0f, 40.0f), Vec2(157.0f, 40.0f), Vec2(96.0f, 40.0f), Vec2(35.0f, 40.0f)
};

static const vector<Vec2> vecPostionGridSelectedMst =
{
	Vec2(422.0f, 40.0f), Vec2(483.0f, 40.0f), Vec2(544.0f, 40.0f), Vec2(605.0f, 40.0f)
};

static const vector<Vec2> vecPostionGridBattle =
{
	Vec2(480.0f, 260.0f), Vec2(160.0f, 260.0f), Vec2(320.0f, 260.0f)
};

enum class TypeLoadState
{
	UNLOAD,//未加载
	LOADING,//加载中
	LOADED//加载完成
};

enum class IdAttribute
{
	ENTITY_HP = 100,//血量
	ENTITY_HP_MAX,//血量上限
	ENTITY_ENERGY,//能量
	ENTITY_ENERGY_MAX,//能量上限
	ENTITY_PHYSICAL_ATTACK,//物理攻击
	ENTITY_MAGIC_ATTACK,//魔法攻击
	ENTITY_GOLD_GENERATE,//生成宝箱
	ENTITY_GOLD_INCOME,//金币收益
	ENTITY_STONE_GENERATE,//生成石头
	ENTITY_STONE_CRUSHED,//击碎石头
	ENTITY_ICE_GENERATE,//生成冰块
	ENTITY_ICE_MELTING,//融化冰块
	ENTITY_TRAP_GENERATE,//生成陷阱
	ENTITY_TRAP_DISARM,//解除陷阱
	ENTITY_SWITCH,//切换角色

	ENTITY_QUICK = 150,//快速攻击
	ENTITY_DAMAGE_CASE,//造成伤害
	ENTITY_DAMAGE_TAKES,//受到伤害
	ENTITY_RESTORE_HP,//恢复生命
	ENTITY_COST_HP,//消耗生命
	ENTITY_RESTORE_ENERGY,//恢复能量
	ENTITY_COST_ENERGY,//消耗能量
	ENTITY_RESTORE_HP_ALL,//全体恢复生命
	ENTITY_COST_HP_ALL,//全体消耗生命
	ENTITY_DAMAGE_CASE_EXTRA,//额外造成伤害
	ENTITY_DAMAGE_TAKES_EXTRA,//额外受到伤害

	GRID_DAMAGE_PHYSICAL = 200,//物理伤害
	GRID_DAMAGE_MAGIC,//魔法伤害
	GRID_DAMAGE_ANY,//任意伤害
	GRID_BLOCK_PHYSICAL,//物理抵挡
	GRID_BLOCK_MAGIC,//魔法抵挡
	GRID_BLOCK_ANY,//任意抵挡
	GRID_UNBLOCKABLE,//不可抵挡
	GRID_QUICK,//快速攻击
	GRID_RESTORE_HP,//恢复生命
	GRID_COST_HP,//消耗生命
	GRID_RESTORE_HP_CANCEL,//取消恢复生命
	GRID_COST_HP_CANCEL,//取消消耗生命
	GRID_RESTORE_ENERGY,//恢复能量
	GRID_COST_ENERGY,//消耗能量
	GRID_RESTORE_ENERGY_CANCEL,//取消恢复能量
	GRID_COST_ENERGY_CANCEL,//取消消耗能量
	GRID_RESTORE_HP_ALL,//全体恢复生命
	GRID_COST_HP_ALL,//全体消耗生命
	GRID_BLOCK_ALL,//抵挡所有伤害
	GRID_DAMAGE_PHYSICAL_EXTRA,//额外物理伤害
	GRID_DAMAGE_MAGIC_EXTRA,//额外魔法伤害

	GRID_ATTRIBUTE_LAST = 299,//标志最后一个格子属性位

	GRID_PHYSICAL_DAMAGE_SUCCESS = 300,//物理伤害成功
	GRID_PHYSICAL_DAMAGE_FAILED,//物理伤害失败
	GRID_PHYSICAL_BLOCK_SUCCESS,//物理抵挡成功
	GRID_PHYSICAL_BLOCK_FAILED,//物理抵挡失败
	GRID_MAGIC_DAMAGE_SUCCESS,//魔法伤害成功
	GRID_MAGIC_DAMAGE_FAILED,//魔法伤害失败
	GRID_MAGIC_BLOCK_SUCCESS,//魔法抵挡成功
	GRID_MAGIC_BLOCK_FAILED,//魔法抵挡失败
	GRID_ANY_DAMAGE_SUCCESS,//任意伤害成功
	GRID_ANY_DAMAGE_FAILED,//任意伤害失败
	GRID_ANY_BLOCK_SUCCESS,//任意抵挡成功
	GRID_ANY_BLOCK_FAILED,//任意抵挡失败
	GRID_N_PHYSICAL_DAMAGE,//造成n点物理伤害//n为0表示每点
	GRID_N_PHYSICAL_TAKES,//受到n点物理伤害//n为0表示每点
	GRID_N_PHYSICAL_BLOCK,//抵挡n点物理伤害//n为0表示每点
	GRID_N_MAGIC_DAMAGE,//造成n点魔法伤害//n为0表示每点
	GRID_N_MAGIC_TAKES,//受到n点魔法伤害//n为0表示每点
	GRID_N_MAGIC_BLOCK,//抵挡n点魔法抵挡//n为0表示每点
	GRID_N_ANY_DAMAGE,//造成n点任意伤害//n为0表示每点
	GRID_N_ANY_TAKES,//受到n点任意伤害//n为0表示每点
	GRID_N_ANY_BLOCK,//抵挡n点任意伤害//n为0表示每点
	GRID_OWN_UNBLOCKABLE,//拥有不可抵挡
	GRID_TAKEN_UNBLOCKABLE,//受到不可抵挡
	GRID_OWN_QUICK,//拥有快速攻击
	GRID_TAKEN_QUICK,//受到快速攻击
	GRID_CERTAINLY,//一定触发
	GRID_UNOWN_UNBLOCKABLE,//不拥有不可抵挡
	GRID_UNTAKEN_UNBLOCKABLE,//不受到不可抵挡
	GRID_UNOWN_QUICK,//不拥有快速攻击
	GRID_UNTAKEN_QUICK,//不受到快速攻击

	GRID_EFFECTIVE_ROUND = 400,//第n轮生效//n为0表示当前回合
	GRID_EFFECTIVE_ROUND_COUNT,//持续n个轮
	GIRD_EFFECTIVE_TO_OTHER,//对对方
	GRID_EFFECTIVE_EACH,//每点

	GRID_GOLD = 450,//宝箱
	GRID_STONE,//石头
	GRID_ICE,//冰块
	GRID_TRAP//陷阱
};

enum class TypeEntity
{
	NONE,
	MAID,//女仆
	MONSTER//怪物
};

enum class TypeJob
{
	NONE,
	ROGUE,//盗贼
	WARRIOR,//战士
	MAGE,//法师
	TREAT,//治疗
	TANK,//坦克
	ARCHER//弓手
};

enum class TypeSkill
{
	NONE,
	ACTIVE,//主动
	PASSIVE,//被动
	RANDOM//随机
};

enum class TypeSkillGroup
{
	NONE,
	HP_PERCENT,//血量百分比
	ENERGY_VALUE,//能量值
	ROUND_TOTAL,//总回合
	ROUND,//回合
};

enum class TypeConfirms
{
	MAP_TRANSFER,
	OFF_LINE_DROP,
	BUY_ACTION_POINT,
	BUY_CARRIAGE,
	BUY_MAID_CLOTHS
};

enum class TypeTips
{
	ERRORS,
	THING_UNLOCK,
	MONSTER,
	THING,
	SKILL,
	TARGET_AWARD
};

enum class TypeScene
{
	WELCOME,
	PLOT,
	MAIN,
};

enum class ID_OBSERVER
{
	SCENE_MAIN,
	LAYER_BATTLE,
	LAYER_GRID_SHOW,
	HANDLE_GRID_SELECT,
	HANDLE_GRID_SELECTED,
	HANDLE_ENTITY
};

enum class TYPE_OBSERVER_SCENE_MAIN
{
	SHOW_BATTLE,
	SHOW_LEVELS
};

enum class TYPE_OBSERVER_LAYER_BATTLE
{
	SHOW_LAYER_GRID_SHOW,//运行显示格子出现动作
	CLOSE_LAYER_GRID_SHOW,
	SHOW_LAYER_BATTLE_RESULT,
	RESET_SKIN
};

enum class TYPE_OBSERVER_LAYER_GRID_SHOW
{
	RUN_MAID_GRID_MOVE_FROM_ACTION,
	HIDE_BG,//隐藏展示背景
	CLOSE
};

enum class TYPE_OBSERVER_HANDLE_GRID_SELECT
{
	RUN_MAID_GRID_MOVE_FROM_ACTION_ONE_BACK,
	RUN_MAID_GRID_MOVE_FROM_ACTION_ALL_BACK,
	RUN_MAID_GRID_MOVE_FROM_ACTION_TAKE_BACK,
	RUN_MAID_GRID_PLAY_SPECIAL_STH_GENERATE,
	RUN_MAID_GRID_SCALE_BIG,
	RUN_MAID_GRID_SCALE_SMALL
};

enum class TYPE_OBSERVER_HANDLE_SELECTED
{
	RUN_GRID_MOVE_ACTION,
	UPDATE_GRID
};

enum class TYPE_OBSERVER_HANDLE_ENTITY
{
	RUN_ENTITY_APPEAR,
	RUN_GRID_MOVE_AND_THROW,//轮开始执行
	RUN_ENTITY_ACTION,
	DEAL_ROUND_OVER,
	UPDATE_HP,
	UPDATE_ENERGY
};

#endif