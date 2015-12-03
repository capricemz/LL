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
		HandleDataTime() : _isDataFileInit(false), _timeLast(0), _timeNow(0) {}
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
		bool _isDataFileInit;

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
		Vec2 postionGridSelectedGet(const bool &isMst, const int &index) const;
		void postionGridSelectedPush(const bool &isMst, const Vec2 &val);
		int getIndexGridBattle();
		void resetIndexGridBattle(){ _indexGridBattle = 0; }
		bool isRoundOver() { return _indexGridBattle == GRID_SELECTED_MAX; }//回合是否结束
		
	private:
		vector<Vec2> _vecPostionGridSelectedMaid;
		vector<Vec2> _vecPostionGridSelectedMst;

		int _idDataGridNow;//格子的唯一id

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
		void updateAttributeSkillPassive();

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

		DataSkillInfo &vecSkillActiveInfoGet();//获取技能信息
		void vecSkillActiveInUse2UseOver();//加使用的牌放入弃牌库
		bool vecSkillActiveIsAllUse();//是否取完牌库
		void vecSkillActiveSort(const bool &isAll = false);//洗牌
		vector<DataSkillInfo> &getVecSkillPassive()
		{
			return _vecSkillPassive;
		}
		vector<DataSkillInfo> &getVecSkillRandom()//
		{
			return _vecSkillRandom;
		}
		vector<DataSkillInfo> &getVecSkillActiveNeedBuy()
		{
			return _vecSkillActiveNeedBuy;
		}
		/*设置技能
		idSkill 技能表id
		index 技能表index
		num 数量*/
		void setSkill(DataSkillInfo &dataSkillInfo);
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
		vector<DataSkillInfo> _vecSkillActiveNeedBuy;
		vector<DataSkillInfo> _vecSkillActive;
		vector<DataSkillInfo> _vecSkillActiveInUse;
		vector<DataSkillInfo> _vecSkillActiveUseOver;
		vector<DataSkillInfo> _vecSkillPassive;
		vector<DataSkillInfo> _vecSkillRandom;

		int _round;//回合数
		
};
//实体数据处理类
class HandleDataEntity
{
	public:
		HandleDataEntity();
		~HandleDataEntity();

		void dataFileInit();//备用
		void dataFileGet();//备用
		void dataFileSet();//备用
		
		void resetDataEntityMaid();//开始关卡时，重置女仆数据，如将女仆血量补满等
		void createDataEntityMaid();
		void createDataEntityMaid(const int &idEntity);
		void createDataEntityMst();//根据当前关卡构建怪物DataEntity
		void vecSkillActiveSortMaid();//女仆洗牌

		void dealSkillRandom(const function<void()> &func = nullptr);

		void resetDataEntityAttributeTemp();//重置实体战斗结果临时属性

		void dealVecSkillActiveInUse2UseOverMaid();//处理行动结束数据
		void dealDataEntitySkillSort(const bool &isForce = false);//处理回合结束数据
		void dealBattleOver();//处理战斗结束数据
		
	public:
		Vector<DataEntity *> &getVecDataEntityMst()
		{
			return _vecDataEntityMst;
		}
		DataEntity * getDataEntityMst() const//获取当前怪物DataEntity
		{
			return _vecDataEntityMst.at(_indexMst);
		}
		void swapVecDataEntityMst(const int &index0, const int &index1)
		{
			_vecDataEntityMst.swap(index0, index1);
		}
		void clearVecDataEntityMst()
		{
			_vecDataEntityMst.clear();
		}
		Vector<DataEntity *> &getVecDataEntityMaid()
		{
			return _vecDataEntityMaid;
		}
		DataEntity * getDataEntityMaid() const//获取当前女仆DataEntity
		{
			return _vecDataEntityMaid.at(_indexMaid);
		}
		void swapVecDataEntityMaid(const int &index0, const int &index1)
		{
			_vecDataEntityMaid.swap(index0, index1);
		}

		int getLengthVecDataEntity(const bool &isMst);

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
		void addRound();
		void resetRound();

		bool getIsSkillNeedSwitchMst(int &indexTo);

	private:
		DataEntity * createDataEntity(const int &idEntity);
		
	private:
		const string USER_DEFAULT_KEY_DE = "dataEntity";//实体数据
		bool _isDataFileInit;

		Vector<DataEntity *> _vecDataEntityMst;
		Vector<DataEntity *> _vecDataEntityMaid;
		int _indexMst;//当前战斗怪物
		int _indexMaid;//当前战斗女仆

		int _roundTotal;//总回合数
		
};
//关卡类
class DataLevel : public Ref
{
	public:
		CREATE_FUNC(DataLevel);
		
	public:
		DataLevel();
		~DataLevel();
		
		virtual bool init();
		
		void assignCfgLevel(const int &idLevel);

		void dealLevelPassed();
		void dealLevelTarget();
		void setState();//设置状态
		void setVecTargetComplete();//根据完成数据设置完成状态
		
	public:
		int getId() const
		{
			return _id;
		}
		int getIndex() const
		{
			return _index;
		}
		void setIndex(const int &value)
		{
			_index = value;
		}
		CfgLevel getCfgLevel() const;
		TypeLevelState getState() const
		{
			return _state;
		}
		int levelTargetNumGet() const
		{
			return getCfgLevel().targets.size();
		}
		bool levelTargetIsComplete(const int &index) const
		{
			if ((int)_vecTargetComplete.size() <= index)
			{
				return false;
			}
			return _vecTargetComplete[index];
		}
		string getLevelTargetStr(const int &index) const;
		
	private:
		int _id;
		int _index;
		TypeLevelState _state;
		vector<bool> _vecTargetComplete;
		
};
//关卡数据处理类
class HandleDataLevels
{
	public:
		HandleDataLevels();
		~HandleDataLevels();
		
		void createDicDataLevel();

	public:
		int getLevelCurrent() const
		{
			return _levelCurrent;
		}
		void setLevelCurrent(int val)
		{
			_levelCurrent = val;
		}
		Map<int, DataLevel *> getDicDataLevel() const
		{
			return _dicDataLevel;
		}
		DataLevel *getDataLevelCurrent()
		{
			return _dicDataLevel.at(_levelCurrent);
		}//当前关卡
		
	private:
		Map<int, DataLevel *> _dicDataLevel;
		int _levelCurrent;//当前关卡
		
};
//处理解锁数据类
class HandleDataUnlock
{
public:
	HandleDataUnlock();
	~HandleDataUnlock();

	void dataFileInit();
	void dataFileGet();
	void dataFileSet();
	void createTypeUnlockOther();
	
	bool getIsUnlockMaid(const int &idEntity);
	void setIsUnlockMaid(const int &idEntity);
	bool getIsUnlockSkill(const int &idSkill, const int &indexSkill);
	void setIsUnlockSkill(const int &idSkill, const int &indexSkill);//indexSkill为-1时，解锁所有
	bool getIsBuySkill(const int &idSkill, const int &indexSkill);
	void setIsBuySkill(const int &idSkill, const int &indexSkill);
	bool getIsUnlockLevel(const int &idLevel);
	void setIsUnlockLevel(const int &idLevel);
	bool getIsPassedLevel(const int &idLevel);
	void setIsPassedLevel(const int &idLevel);
	bool getIsCompleteLevelTarget(const int &idLevel, const int &idLevelTarget);
	void setIsCompleteLevelTarget(const int &idLevel, const int &idLevelTarget);
	bool getIsUnlock(int index);
	void setIsUnlock(int index);
	
private:
	const string USER_DEFAULT_KEY_DU = "dataUnlock";//解锁数据
	bool _isDataFileInit;
	
	map<int, int> _dicTypeUnlockMaid;
	map<int, map<int, int>> _dicDicTypeUnlockSkill;
	map<int, map<int, int>> _dicDicTypeBuySkill;
	map<int, int> _dicTypeUnlockLevel;
	map<int, int> _dicTypePassedLevel;
	map<int, map<int, int>> _dicDicTypeCompleteLevelTarget;
	vector<int> _vecDataUnlock;
	
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
		HandleDataUnlock * getHandleDataUnlock() { return _handleDataUnlock; }
		HandleDataGrid * getHandleDataGrid() { return _handleDataGrid; }
		HandleDataEntity * getHandleDataEntity() { return _handleDataEntity; }
		HandleDataLevels * getHandleDataLevels() { return _handleDataLevels; }

	private:
		const string USER_DEFAULT_KEY_ISFE = "isSaveFileExist";//储存文件是否存在

	private:
		HandleDataTime *_handleDataTime;//时间数据处理
		HandleDataUnlock *_handleDataUnlock;
		HandleDataGrid *_handleDataGrid;//格子数据处理
		HandleDataEntity *_handleDataEntity;//实体数据处理
		HandleDataLevels *_handleDataLevels;//关卡数据处理

};

#endif