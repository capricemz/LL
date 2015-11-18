#pragma execution_character_set("utf-8")

#ifndef __DATA_DATA_MANAGER_DATA_H__
#define __DATA_DATA_MANAGER_DATA_H__

#include "cocos2d.h"
#include "../define/DefinesValue.h"
#include "../config/ManagerCfgDefines.h"

USING_NS_CC;
using namespace std;

//时间数据处理类
class HandleDataTime
{
	public:
		HandleDataTime() : _timeLast(0), _timeNow(0) {}
		~HandleDataTime();

		void dataFileInit();
		void dataFileGet();
		void dataFileSet();

	public:
		double timeLastGet() const { return _timeLast; }
		void timeLastSet(double val) { _timeLast = val; }
		double timeNowGet() const { return _timeNow; }
		void timeNowSet(double val) { _timeNow = val; }

		bool isTimeLastNeedReset() const { return _timeNow - _timeLast >= TIME_LAST_SAVE_INTERVAL; }

	private:
		const string USER_DEFAULT_KEY_DT = "dataTime";//时刻数据,上一时刻，行动力恢复时刻，饱食度消耗时刻

		double _timeLast;//上一时刻
		double _timeNow;//当前时刻

};
//格子数据类
class DataGrid : public Ref
{
	public:
		CREATE_FUNC(DataGrid);

	public:
		DataGrid();
		~DataGrid();

		virtual bool init();

		CfgSkill getCfgSkill();

		bool isBasicAttributeExist();
		bool isDamageAttributeExist();
		bool isUnblockableExist();
		bool isQuickExist();

		void updateSkillEffect();
	
	public:
		int getId() const//唯一id
		{
			return _id;
		}
		void setId(int val)//唯一id
		{
			_id = val;
		}
		int getIndexGrid() const
		{
			return _indexGrid;
		}
		void setIndexGrid(int val)
		{
			_indexGrid = val;
		}
		int getIdSkill() const
		{
			return _idSkill;
		}
		void setIdSkill(int val)
		{
			_idSkill = val;
		}
		int getIndexSkill() const
		{
			return _indexSkill;
		}
		void setIndexSkill(int val)
		{
			_indexSkill = val;
		}
		map<IdAttribute, int> getDicAttribute()
		{
			return _dicAttribute;
		}
		int getAttribute(const IdAttribute &idAttribute);
		void setAttribute(const IdAttribute &idAttribute, const int &value);//idAttribute 元素id, value 新值
		void addAttribute(const IdAttribute &idAttribute, const int &value);//idAttribute 元素id, value 正值增加，负值减少
		map<IdAttribute, string> getDicAttributeCondition()
		{
			return _dicAttributeCondition;
		}
		string getAttributeCondition(const IdAttribute &idAttribute);
		void setAttributeCondition(const IdAttribute &idAttribute, const string &value);//idAttribute 元素id, value 新值
		void addAttributeCondition(const IdAttribute &idAttribute, const string &value);//idAttribute 元素id, value 正值增加，负值减少
		DataGrid * getDataGridNext() const
		{
			return _dataGridNext;
		}
		void setDataGridNext(DataGrid * val)
		{
			_dataGridNext = val;
		}
		
	private:
		int _id;
		int _indexGrid;
		int _idSkill;
		int _indexSkill;
		map<IdAttribute, int> _dicAttribute;
		map<IdAttribute, string> _dicAttributeCondition;
		DataGrid *_dataGridNext;
		
};
//格子数据处理类
class HandleDataGrid
{
	public:
		HandleDataGrid();
		~HandleDataGrid();

		DataGrid * getDataGrid();
		
	public:
		int getIndexGridBattle();
		void resetIndexGridBattle(){ _indexGridBattle = 0; }
		bool isRoundOver() { return _indexGridBattle == GRID_SELECTED_MAX; }//回合是否结束
		
	private:
		int _idDataGridNow;

		int _indexGridBattle;
		
};
//实体数据类
class DataEntity : public Ref
{
	public:
		CREATE_FUNC(DataEntity);

	public:
		DataEntity();
		~DataEntity();

		virtual bool init();

		CfgEntity getCfgEntity();

		void updateAttribute();
		void updateSkillGroup();

	public:
		int getIdEntity() const
		{
			return _idEntity;
		}
		void setIdEntity(int val)
		{
			_idEntity = val;
		}
		
		int getIndex() const
		{
			return _index;
		}
		void setIndex(int val)
		{
			_index = val;
		}
		
		map<IdAttribute, int> getDicAttribute()
		{
			return _dicAttribute;
		}
		int getAttribute(IdAttribute idAttribute);
		void setAttribute(IdAttribute idAttribute, int value);//idAttribute 元素id, value 新值
		void addAttribute(IdAttribute idAttribute, int value);//idAttribute 元素id, value 正值增加，负值减少
		bool getIsAlive();

		vector<int> vecSkillActiveInfoGet();//获取技能信息
		void vecSkillActiveInUse2UseOver();//加使用的牌放入弃牌库
		bool vecSkillActiveIsAllUse();//是否取完牌库
		void vecSkillActiveSort(const bool &isAll = false);//洗牌
		vector<vector<int>> getVecSkillPassive()
		{
			return _vecSkillPassive;
		}
		vector<vector<int>> getVecSkillRandom()//vector:0idSkill1index2num3odds
		{
			return _vecSkillRandom;
		}
		/*设置技能
		idSkill 技能表id
		index 技能表index
		num 数量*/
		void setSkill(const string &skillInfo);
		void vecSkillClear();

		int getRound() const//获取当前回合数
		{
			return _round;
		}
		void setRound(int val)//设置当前回合数
		{
			_round = val;
		}
		void addRound()
		{
			_round++;
		}
		void resetRound()
		{
			_round = 0;
		}
		
	private:
		int _idEntity;//idEntity
		int _index;
		map<IdAttribute, int> _dicAttribute;//idAttribute value
		vector<vector<int>> _vecSkillActive;//vector:0idSkill1index2num3odds
		vector<vector<int>> _vecSkillActiveInUse;//vector:0idSkill1index2num3odds
		vector<vector<int>> _vecSkillActiveUseOver;//vector:0idSkill1index2num3odds
		vector<vector<int>> _vecSkillPassive;//vector:0idSkill1index2num3odds
		vector<vector<int>> _vecSkillRandom;//vector:0idSkill1index2num3odds

		int _round;//回合数
		
};
//实体数据处理类
class HandleDataEntity
{
	public:
		HandleDataEntity();
		~HandleDataEntity();

		void dataFileInit();
		void dataFileGet();
		void dataFileSet();
		
		void setDataEntityMaidHpFull();//开始关卡是将女仆血量补满
		void createDataEntityMst();//根据当前关卡构建怪物DataEntity
		void vecSkillActiveSortMaid();//女仆洗牌

		void dealSkillRandom(const function<void()> &func = nullptr);

		void dealTurnOver();//处理行动结束数据
		void dealRoundOver(const bool &isForce = false);//处理回合结束数据
		void dealBattleOver();//处理战斗结束数据
		
	public:
		Vector<DataEntity *> getVecDataEntityMst() const
		{
			return _vecDataEntityMst;
		}
		DataEntity * getDataEntityMst() const//获取当前怪物DataEntity
		{
			return _vecDataEntityMst.at(_indexMst);
		}
		void clearVecDataEntityMst()
		{
			_vecDataEntityMst.clear();
		}
		Vector<DataEntity *> getVecDataEntityMaid() const
		{
			return _vecDataEntityMaid;
		}
		DataEntity * getDataEntityMaid() const//获取当前女仆DataEntity
		{
			return _vecDataEntityMaid.at(_indexMaid);
		}

		int getIndexMst() const
		{
			return _indexMst;
		}
		void setIndexMst(int val)
		{
			_indexMst = val;
		}
		void resetIndexMst()
		{
			_indexMst = 0;
		}
		bool isAllMstDead();

		int getIndexMaid() const
		{
			return _indexMaid;
		}
		void setIndexMaid(int val)
		{
			_indexMaid = val;
		}
		void resetIndexMaid()
		{
			_indexMaid = 0;
		}
		bool isAllMaidDead();

		int getRoundTotal() const//获取当前总回合数
		{
			return _roundTotal;
		}
		void setRoundTotal(int val)//设置当前总回合数
		{
			_roundTotal = val;
		}
		void addRoundTotal()
		{
			_roundTotal++;
		}
		void resetRoundTotal()
		{
			_roundTotal = 0;
		}

		bool getIsSkillNeedSwitchEntity(int &indexTo);

	private:
		DataEntity * createDataEntity(const int &idEntity);
		void createDataEntityMaid();
		
	private:
		const string USER_DEFAULT_KEY_DE = "dataEntity";//实体数据

		Vector<DataEntity *> _vecDataEntityMst;
		Vector<DataEntity *> _vecDataEntityMaid;
		int _indexMst;//当前战斗怪物
		int _indexMaid;//当前战斗女仆

		int _roundTotal;//总回合数
		
};
//关卡类
class DataLevels : public Ref
{
	public:
		CREATE_FUNC(DataLevels);
		
	public:
		DataLevels();
		~DataLevels();
		
		virtual bool init();
		
	private:
		
};
//关卡数据处理类
class HandleDataLevels
{
	public:
		HandleDataLevels();
		~HandleDataLevels();
		
		void dataFileInit();
		void dataFileGet();
		void dataFileSet();

	public:
		int getLevelCurrent() const
		{
			return _levelCurrent;
		}
		void setLevelCurrent(int val)
		{
			_levelCurrent = val;
		}
		
	private:
		const string USER_DEFAULT_KEY_DL = "dataLevels";//关卡数据
		
		int _levelCurrent;//当前关卡
		
};
//数据类
class ManagerData
{
	public:
		static ManagerData *getInstance();
		static void destroyInstance();

	public:
		virtual ~ManagerData();
		void setSaveFileExist();//设置数据存在
		bool isSaveFileExist();//判断存档是否存在
		void dataFileGet();
		void dataFileSet();//保存所有数据

	private:
		ManagerData();
		void initHandleDatas();

	public:
		HandleDataTime * getHandleDataTime() { return _handleDataTime; }
		HandleDataGrid * getHandleDataGrid() { return _handleDataGrid; }
		HandleDataEntity * getHandleDataEntity() { return _handleDataEntity; }
		HandleDataLevels * getHandleDataLevels() { return _handleDataLevels; }

	private:
		const string USER_DEFAULT_KEY_ISFE = "isSaveFileExist";//储存文件是否存在

	private:
		HandleDataTime *_handleDataTime;//时间数据处理
		HandleDataGrid *_handleDataGrid;//格子数据处理
		HandleDataEntity *_handleDataEntity;//实体数据处理
		HandleDataLevels *_handleDataLevels;//关卡数据处理

};

#endif