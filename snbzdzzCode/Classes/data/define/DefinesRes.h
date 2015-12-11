#pragma execution_character_set("utf-8")

#ifndef __DATA_DEFINE_DEFINES_RES_H__
#define __DATA_DEFINE_DEFINES_RES_H__

#include <string>

using namespace std;

static const string RES_FONTS_KTJT = "fonts/ktjt.ttf";

static const string RES_MODULES_COMMON_PLIST_COMMON_PLIST = "modules/common/PlistCommon.plist";
static const string RES_MODULES_COMMON_NODE_BUBBLE_CSB = "modules/common/NodeBubble.csb";

static const string RES_MODULES_WELCOME_SCENE_WELCOME_CSB = "modules/welcome/SceneWelcome.csb";

static const string RES_MODULES_PLOT_SCENE_PLOT_CSB = "modules/plot/ScenePlot.csb";

static const string RES_MODULES_MAIN_PLIST_MAIN_PLIST = "modules/main/PlistMain.plist";
static const string RES_MODULES_MAIN_PLIST_MAID_HEAD_PLIST = "modules/main/PlistMaidHead.plist";
static const string RES_MODULES_MAIN_PLIST_MAID_NAME_PLIST = "modules/main/PlistMaidName.plist";
static const string RES_MODULES_MAIN_SCENE_MAIN_CSB = "modules/main/SceneMain.csb";

static const string RES_MODULES_MAIN_LAYER_GUILD_CSB = "modules/main/LayerGuild.csb";
static const string RES_MODULES_MAIN_LAYER_TRAINING_CSB = "modules/main/LayerTraining.csb";
static const string RES_MODULES_MAIN_LAYER_LEVELS_CSB = "modules/main/LayerLevels.csb";
static const string RES_MODULES_MAIN_LAYER_MAID_SELECT_CSB = "modules/main/LayerMaidSelect.csb";
static const string RES_MODULES_MAIN_LAYER_SKILLS_CSB = "modules/main/LayerSkills.csb";
static const string RES_MODULES_MAIN_LAYER_BATTLE_CSB = "modules/main/LayerBattle.csb";
static const string RES_MODULES_MAIN_LAYER_GRID_SELECT_CSB = "modules/main/LayerGridSelect.csb";
static const string RES_MODULES_MAIN_LAYER_GRID_SHOW_CSB = "modules/main/LayerGridShow.csb";
static const string RES_MODULES_MAIN_LAYER_BATTLE_RESULT_CSB = "modules/main/LayerBattleResult.csb";
static const string RES_MODULES_MAIN_LAYER_CATCH_CSB = "modules/main/LayerCatch.csb";

static const string RES_MODULES_MAIN_NODE_GRID_CSB = "modules/main/NodeGrid.csb";
static const string RES_MODULES_MAIN_NODE_HEAD_CSB = "modules/main/NodeHead.csb";

static const string RES_IMAGES_MAIN_MAID_UNLOCK_PNG = "images/girl/not_unlock.png";
static const string RES_IMAGES_MAIN_MAID_BUY_PNG = "images/girl/buy.png";

static const string RES_IMAGES_MAIN_CIRCLE_LINE_POINT_PNG = "images/battle/lianxian_dian.png";
static const string RES_IMAGES_MAIN_CIRCLE_LINE_CIRCLE_PNG = "images/battle/lianxian_quan.png";
static const string RES_IMAGES_MAIN_CIRCLE_LINE_LINE_PNG = "images/battle/lianxian_xian.png";

static const vector<string> RES_IMAGES_MAIN_SRP_PNG_VEC =
{
	"",
	"images/battle/scissors.jpg",
	"images/battle/rock.jpg",
	"images/battle/paper.jpg"
};

static const string RES_IMAGES_MAIN_LEVELS_XING_PNG = "images/levels/xing.png";
static const string RES_IMAGES_MAIN_LEVELS_XING_KONG_PNG = "images/levels/xingKong.png";

static const vector<string> RES_IMAGES_COMMON_TYPE_JOB_PNG_VEC = 
{ 
	"", 
	"images/common/typeJobRogue.png",
	"images/common/typeJobWarrior.png", 
	"images/common/typeJobMage.png", 
	"images/common/typeJobTreat.png", 
	"images/common/typeJobTank.png", 
	"images/common/typeJobArcher.png" 
};

static const string SOUND_EFFECT_SYSTEM_BTN_0_MP3 = "effect/systemBtn0.mp3";//音效系统按钮0
static const string SOUND_EFFECT_SYSTEM_BTN_1_MP3 = "effect/systemBtn1.mp3";//音效系统按钮1

#endif