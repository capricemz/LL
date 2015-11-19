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
		const string USER_DEFAULT_KEY_DT = "dataTime";//ʱ������,��һʱ�̣��ж����ָ�ʱ�̣���ʳ������ʱ��

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
		int getIndexGridBattle();
		void resetIndexGridBattle(){ _indexGridBattle = 0; }
		bool isRoundOver() { return _indexGridBattle == GRID_SELECTED_MAX; }//�غ��Ƿ����
		
	private:
		int _idDataGridNow;

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

		vector<int> vecSkillActiveInfoGet();//��ȡ������Ϣ
		void vecSkillActiveInUse2UseOver();//��ʹ�õ��Ʒ������ƿ�
		bool vecSkillActiveIsAllUse();//�Ƿ�ȡ���ƿ�
		void vecSkillActiveSort(const bool &isAll = false);//ϴ��
		vector<vector<int>> getVecSkillPassive()
		{
			return _vecSkillPassive;
		}
		vector<vector<int>> getVecSkillRandom()//vector:0idSkill1index2num3odds
		{
			return _vecSkillRandom;
		}
		/*���ü���
		idSkill ���ܱ�id
		index ���ܱ�index
		num ����*/
		void setSkill(const string &skillInfo);
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
		vector<vector<int>> _vecSkillActive;//vector:0idSkill1index2num3odds
		vector<vector<int>> _vecSkillActiveInUse;//vector:0idSkill1index2num3odds
		vector<vector<int>> _vecSkillActiveUseOver;//vector:0idSkill1index2num3odds
		vector<vector<int>> _vecSkillPassive;//vector:0idSkill1index2num3odds
		vector<vector<int>> _vecSkillRandom;//vector:0idSkill1index2num3odds

		int _round;//�غ���
		
};
//ʵ�����ݴ�����
class HandleDataEntity
{
	public:
		HandleDataEntity();
		~HandleDataEntity();

		void dataFileInit();
		void dataFileGet();
		void dataFileSet();
		
		void setDataEntityMaidHpFull();//��ʼ�ؿ��ǽ�Ů��Ѫ������
		void createDataEntityMst();//���ݵ�ǰ�ؿ���������DataEntity
		void vecSkillActiveSortMaid();//Ů��ϴ��

		void dealSkillRandom(const function<void()> &func = nullptr);

		void dealTurnOver();//�����ж���������
		void dealRoundOver(const bool &isForce = false);//����غϽ�������
		void dealBattleOver();//����ս����������
		
	public:
		Vector<DataEntity *> getVecDataEntityMst() const
		{
			return _vecDataEntityMst;
		}
		DataEntity * getDataEntityMst() const//��ȡ��ǰ����DataEntity
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
		DataEntity * getDataEntityMaid() const//��ȡ��ǰŮ��DataEntity
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

		int getRoundTotal() const//��ȡ��ǰ�ܻغ���
		{
			return _roundTotal;
		}
		void setRoundTotal(int val)//���õ�ǰ�ܻغ���
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
		void createDataEntityMaid(const vector<string> &vecIdEntity);
		
	private:
		const string USER_DEFAULT_KEY_DE = "dataEntity";//ʵ������

		Vector<DataEntity *> _vecDataEntityMst;
		Vector<DataEntity *> _vecDataEntityMaid;
		int _indexMst;//��ǰս������
		int _indexMaid;//��ǰս��Ů��

		int _roundTotal;//�ܻغ���
		
};
//�ؿ���
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
//�ؿ����ݴ�����
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
		const string USER_DEFAULT_KEY_DL = "dataLevels";//�ؿ�����
		
		int _levelCurrent;//��ǰ�ؿ�
		
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
		HandleDataGrid * getHandleDataGrid() { return _handleDataGrid; }
		HandleDataEntity * getHandleDataEntity() { return _handleDataEntity; }
		HandleDataLevels * getHandleDataLevels() { return _handleDataLevels; }

	private:
		const string USER_DEFAULT_KEY_ISFE = "isSaveFileExist";//�����ļ��Ƿ����

	private:
		HandleDataTime *_handleDataTime;//ʱ�����ݴ���
		HandleDataGrid *_handleDataGrid;//�������ݴ���
		HandleDataEntity *_handleDataEntity;//ʵ�����ݴ���
		HandleDataLevels *_handleDataLevels;//�ؿ����ݴ���

};

#endif