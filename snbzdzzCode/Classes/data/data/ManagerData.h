#pragma execution_character_set("utf-8")

#ifndef __DATA_DATA_MANAGER_DATA_H__
#define __DATA_DATA_MANAGER_DATA_H__

#include "cocos2d.h"
#include "../define/DefinesValue.h"
#include "../config/ManagerCfgDefines.h"

USING_NS_CC;
using namespace std;

//ʱ�����ݴ�����
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
		const string USER_DEFAULT_KEY_DT = "dataTime";//ʱ������,��һʱ�̣��ж����ָ�ʱ�̣���ʳ������ʱ��
		bool _isDataFileInit;

		double _timeLast;//��һʱ��
		double _timeNow;//��ǰʱ��

};
//����������
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
		int getId() const//Ψһid
		{
			return _id;
		}
		void setId(int val)//Ψһid
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
		void setAttribute(const IdAttribute &idAttribute, const int &value);//idAttribute Ԫ��id, value ��ֵ
		void addAttribute(const IdAttribute &idAttribute, const int &value);//idAttribute Ԫ��id, value ��ֵ���ӣ���ֵ����
		map<IdAttribute, string> getDicAttributeCondition()
		{
			return _dicAttributeCondition;
		}
		string getAttributeCondition(const IdAttribute &idAttribute);
		void setAttributeCondition(const IdAttribute &idAttribute, const string &value);//idAttribute Ԫ��id, value ��ֵ
		void addAttributeCondition(const IdAttribute &idAttribute, const string &value);//idAttribute Ԫ��id, value ��ֵ���ӣ���ֵ����
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
//�������ݴ�����
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
		bool isRoundOver() { return _indexGridBattle == GRID_SELECTED_MAX; }//�غ��Ƿ����
		
	private:
		vector<Vec2> _vecPostionGridSelectedMaid;
		vector<Vec2> _vecPostionGridSelectedMst;

		int _idDataGridNow;//���ӵ�Ψһid

		int _indexGridBattle;
		
};
//ʵ��������
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
		void setAttribute(IdAttribute idAttribute, int value);//idAttribute Ԫ��id, value ��ֵ
		void addAttribute(IdAttribute idAttribute, int value);//idAttribute Ԫ��id, value ��ֵ���ӣ���ֵ����
		bool getIsAlive();

		DataSkillInfo &vecSkillActiveInfoGet();//��ȡ������Ϣ
		void vecSkillActiveInUse2UseOver();//��ʹ�õ��Ʒ������ƿ�
		bool vecSkillActiveIsAllUse();//�Ƿ�ȡ���ƿ�
		void vecSkillActiveSort(const bool &isAll = false);//ϴ��
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
		/*���ü���
		idSkill ���ܱ�id
		index ���ܱ�index
		num ����*/
		void setSkill(DataSkillInfo &dataSkillInfo);
		void vecSkillClear();

		int getRound() const//��ȡ��ǰ�غ���
		{
			return _round;
		}
		void setRound(int val)//���õ�ǰ�غ���
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

		int _round;//�غ���
		
};
//ʵ�����ݴ�����
class HandleDataEntity
{
	public:
		HandleDataEntity();
		~HandleDataEntity();

		void dataFileInit();//����
		void dataFileGet();//����
		void dataFileSet();//����
		
		void resetDataEntityMaid();//��ʼ�ؿ�ʱ������Ů�����ݣ��罫Ů��Ѫ��������
		void createDataEntityMaid();
		void createDataEntityMaid(const int &idEntity);
		void createDataEntityMst();//���ݵ�ǰ�ؿ���������DataEntity
		void vecSkillActiveSortMaid();//Ů��ϴ��

		void dealSkillRandom(const function<void()> &func = nullptr);

		void resetDataEntityAttributeTemp();//����ʵ��ս�������ʱ����

		void dealVecSkillActiveInUse2UseOverMaid();//�����ж���������
		void dealDataEntitySkillSort(const bool &isForce = false);//����غϽ�������
		void dealBattleOver();//����ս����������
		
	public:
		Vector<DataEntity *> &getVecDataEntityMst()
		{
			return _vecDataEntityMst;
		}
		DataEntity * getDataEntityMst() const//��ȡ��ǰ����DataEntity
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
		DataEntity * getDataEntityMaid() const//��ȡ��ǰŮ��DataEntity
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

		int getRoundTotal() const//��ȡ��ǰ�ܻغ���
		{
			return _roundTotal;
		}
		void addRound();
		void resetRound();

		bool getIsSkillNeedSwitchMst(int &indexTo);

	private:
		DataEntity * createDataEntity(const int &idEntity);
		
	private:
		const string USER_DEFAULT_KEY_DE = "dataEntity";//ʵ������
		bool _isDataFileInit;

		Vector<DataEntity *> _vecDataEntityMst;
		Vector<DataEntity *> _vecDataEntityMaid;
		int _indexMst;//��ǰս������
		int _indexMaid;//��ǰս��Ů��

		int _roundTotal;//�ܻغ���
		
};
//�ؿ�������
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
		void setState();//����״̬
		void setVecTargetComplete();//������������������״̬
		
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
		void dealPassedIncome(const map<TypeAward, int> &award);
		
	private:
		int _id;
		int _index;
		TypeLevelState _state;
		vector<bool> _vecTargetComplete;
		
};
//�ؿ����ݴ�����
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
		}//��ǰ�ؿ�
		
	private:
		Map<int, DataLevel *> _dicDataLevel;
		int _levelCurrent;//��ǰ�ؿ�
		
};
//�������������
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
		void setIsUnlockSkill(const int &idSkill, const int &indexSkill);//indexSkillΪ-1ʱ����������
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
		const string USER_DEFAULT_KEY_DU = "dataUnlock";//��������
		bool _isDataFileInit;
	
		map<int, int> _dicTypeUnlockMaid;
		map<int, map<int, int>> _dicDicTypeUnlockSkill;
		map<int, map<int, int>> _dicDicTypeBuySkill;
		map<int, int> _dicTypeUnlockLevel;
		map<int, int> _dicTypePassedLevel;
		map<int, map<int, int>> _dicDicTypeCompleteLevelTarget;
		vector<int> _vecDataUnlock;
	
};
//����������
class DataIncome : public Ref
{
	public:
		CREATE_FUNC(DataIncome);
		
	public:
		DataIncome();
		~DataIncome();

		virtual bool init();

		string getStrData();

		bool isGoldEnoughGet(const int &value);//����Ƿ��㹻
		void costGold(const int &value);//���Ľ��
		
	public:
		int getId() const
		{
			return _id;
		}
		void setId(const int &val)
		{
			_id = val;
		}
		int getGold() const
		{
			return _gold;
		}
		void setGold(const int &val)
		{
			_gold = val;
		}
		void addGold(const int &val)
		{
			_gold += val;
		}
		vector<int> getVecIdEntityCatched() const
		{
			return _vecIdEntityCatched;
		}
		void pushVecIdEntityCatched(const int &val)
		{
			_vecIdEntityCatched.push_back(val);
		}
		void eraseVecIdEntityCatched(const int &val)
		{
			auto iter = find(_vecIdEntityCatched.begin(), _vecIdEntityCatched.end(), val);
			if (iter == _vecIdEntityCatched.end())
			{
				return;
			}
			_vecIdEntityCatched.erase(iter);
		}
		
	private:
		int _id;
		int _gold;
		vector<int> _vecIdEntityCatched;
		
};
//��������������
class HandleDataIncome
{
	public:
		HandleDataIncome();
		~HandleDataIncome();
		
		void dataFileInit();
		void dataFileGet();
		void dataFileSet();
		
		DataIncome * getDataIncome(const int &id) const
		{
			if (_dicDataIncome.find(id) == _dicDataIncome.end())
			{
				return nullptr;
			}
			return _dicDataIncome.at(id);
		}
		
	private:
		void createDataIncome(string infos);
		
	private:
		const string USER_DEFAULT_KEY_DI = "dataIncome";//��������
		bool _isDataFileInit;

		Map<int, DataIncome *> _dicDataIncome;

};
//������
class ManagerData
{
	public:
		static ManagerData *getInstance();
		static void destroyInstance();

	public:
		virtual ~ManagerData();
		void setSaveFileExist();//�������ݴ���
		bool isSaveFileExist();//�жϴ浵�Ƿ����
		void dataFileGet();
		void dataFileSet();//������������

	private:
		ManagerData();
		void initHandleDatas();

	public:
		HandleDataTime * getHandleDataTime() { return _handleDataTime; }
		HandleDataUnlock * getHandleDataUnlock() { return _handleDataUnlock; }
		HandleDataGrid * getHandleDataGrid() { return _handleDataGrid; }
		HandleDataEntity * getHandleDataEntity() { return _handleDataEntity; }
		HandleDataLevels * getHandleDataLevels() { return _handleDataLevels; }
		HandleDataIncome * getHandleDataIncome() { return _handleDataIncome; }

	private:
		const string USER_DEFAULT_KEY_ISFE = "isSaveFileExist";//�����ļ��Ƿ����

	private:
		HandleDataTime *_handleDataTime;//ʱ�����ݴ���
		HandleDataUnlock *_handleDataUnlock;
		HandleDataGrid *_handleDataGrid;//�������ݴ���
		HandleDataEntity *_handleDataEntity;//ʵ�����ݴ���
		HandleDataLevels *_handleDataLevels;//�ؿ����ݴ���
		HandleDataIncome *_handleDataIncome;//�������ݴ���

};

#endif