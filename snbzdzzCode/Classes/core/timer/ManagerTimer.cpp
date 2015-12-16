#include "ManagerTimer.h"
#include "common/util/UtilDate.h"

static ManagerTimer *_instance = nullptr;

ManagerTimer * ManagerTimer::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new ManagerTimer();
	}
	return _instance;
}

void ManagerTimer::destroyInstance()
{
	CC_SAFE_DELETE(_instance);
}

ManagerTimer::~ManagerTimer()
{
	Director::getInstance()->getScheduler()->unschedule(schedule_selector(ManagerTimer::updateCustom), this);
}

void ManagerTimer::timerStartDeal()
{
	dataTimeOffLineDeal();
	//
	Director::getInstance()->getScheduler()->schedule(schedule_selector(ManagerTimer::updateCustom), this, 1.0f, false);//1秒刷新一次
}

void ManagerTimer::timerForegroundDeal()
{
	if (_isBackground)
	{
		_isBackground = false;
		dataTimeOffLineDeal();
	}
}

void ManagerTimer::timerBackgroundDeal()
{
	if (!_isBackground)
	{
		_isBackground = true;
		timeLastReset();
	}
}

void ManagerTimer::dataTimeOffLineDeal()
{
	auto handleDataTime = ManagerData::getInstance()->getHandleDataTime();
	auto handleDataIncome = ManagerData::getInstance()->getHandleDataIncome();
	//
	auto timeNow = UtilDate::getSecond();
	handleDataTime->timeNowSet(timeNow);
	//
	double timeOffLineModifyActionPoint = 0;
	double timeOffLineModifyFeedCost = 0;
	auto timeLast = handleDataTime->timeLastGet();
	if (timeLast > 0)
	{
		auto timeOffLine = timeNow - timeLast;
		/*log("`````````````````````timeOffLine:%s,_timeNow:%s,_timeLast:%s", Value(timeOffLine).asString().c_str(), Value(_timeNow).asString().c_str(), Value(_timeLast).asString().c_str());*/
		if (timeOffLine > 0)
		{
			timeOffLine = timeOffLine > TIME_OFF_LINE_MAX ? TIME_OFF_LINE_MAX : timeOffLine;

			auto count = int(timeOffLine / TRAINING_NUM_RST_INTERVAL);
			handleDataIncome->addTrainingNum(TRAINING_NUM_RST_VALUE * count);

			timeOffLineModifyActionPoint = (timeOffLine - Value(TRAINING_NUM_RST_INTERVAL * count).asDouble());

			/*count = int(timeOffLine / FEED_COST_INTERVAL);
			managerData->onAllEntityFeedChange(count * FEED_COST_VALUE);//离线饱食度
			timeOffLineModifyFeedCost = (timeOffLine - Value(FEED_COST_INTERVAL * count).asDouble());

			count = int(timeOffLine / TIME_OFF_LINE_DROP_INTERVAL);
			managerData->onTimeOffLineDrop(count);

			managerData->timeOffLineSet(timeOffLine);

			managerData->notify(ID_OBSERVER_LAYER_MAP, (void *)DATA_LAYER_MAP_OFF_LINE_DROP);*/
		}
	}
	//
	handleDataTime->timeLastSet(timeNow);
	handleDataTime->dataFileSet();
}

void ManagerTimer::updateCustom(float dt)
{
	auto handleDataTime = ManagerData::getInstance()->getHandleDataTime();
	auto handleDataIncome = ManagerData::getInstance()->getHandleDataIncome();

	auto second = UtilDate::getSecond();
	/*log("``````````````````````_timeNow:%e,second:%e,d:%e", _timeNow, second, _timeNow - second);*/

	auto timeNow = handleDataTime->timeNowGet() + Value(dt).asDouble();
	handleDataTime->timeNowSet(timeNow);

	if (handleDataTime->isTimeLastNeedReset())//每隔3分钟保存一次上一时刻数据
	{
		timeLastReset();
		ManagerData::getInstance()->dataFileAllSet();
	}
	//
	if (timeNow > handleDataTime->getTimeTrainingNumRst())
	{
		handleDataTime->setTimeTrainingNumRst(timeNow + TRAINING_NUM_RST_INTERVAL);
		handleDataTime->dataFileSet();
		handleDataIncome->addTrainingNum(TRAINING_NUM_RST_VALUE);
	}
	/*if (timeNow > managerData->timeFeedCostGet())
	{
		managerData->timeFeedCostSet(timeNow + FEED_COST_INTERVAL);
		managerData->dataTimeDataFileSet();
		managerData->onAllEntityFeedChange(FEED_COST_VALUE);
	}
	for (auto var : managerData->dicTimeFlushRegionGet())
	{
		if (var.second > 0 && timeNow > var.second)
		{
			managerData->dicTimeFlushRegionSet(var.first, 0);
		}
	}*/
}

void ManagerTimer::timeLastReset()
{
	auto handleDataTime = ManagerData::getInstance()->getHandleDataTime();
	auto timeNow = handleDataTime->timeNowGet();
	handleDataTime->timeLastSet(timeNow);
	/*log("`````````````````````ManagerTimer::timeLastDeal timeLast:%s", Value(_timeLast).asString().c_str());*/
	handleDataTime->dataFileSet();
}
