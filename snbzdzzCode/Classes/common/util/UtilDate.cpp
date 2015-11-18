#pragma execution_character_set("utf-8")

#include "UtilDate.h"
#include <iostream>

using namespace std;

std::string UtilDate::getCurrentTime(const char* format)
{
	struct tm *tm;
	time_t timep;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	time(&timep);
#else
	struct timeval tv;
	gettimeofday(&tv, NULL);
	timep = tv.tv_sec;
#endif

	tm = localtime(&timep);
	int year = tm->tm_year + 1900;
	int month = tm->tm_mon + 1;
	int day = tm->tm_mday;
	int hour = tm->tm_hour;
	int minute = tm->tm_min;
	int second = tm->tm_sec;
	std::cout << "当前日期:" << year << "-" << month << "-" << day << std::endl;
	std::cout << "当前时间:" << hour << ":" << minute << ":" << second << std::endl;

	char currentTime[128];
	strftime(currentTime, 128, format, tm);

	log("CurrentTime %s", currentTime);

	return currentTime;
}

double UtilDate::getMillSecond()
{
	struct timeval tv;
	gettimeofday(&tv, nullptr);

	auto millSecond = (double)tv.tv_sec * 1000 + (double)tv.tv_usec / 1000;
	/*log("CurrentTime MillSecond %g", millSecond);*/

	return millSecond;
}

double UtilDate::getSecond()
{
	auto millSecond = getMillSecond();
	/*log("CurrentTime Second %g", millSecond / 1000);*/

	return millSecond / 1000;
}

std::string UtilDate::timeFormat(double value, bool isHourShow /*= true*/, bool isMinuteShow /*= true*/)
{
	int hour = value / 3600;
	value = value - hour * 3600;
	int minute = value / 60;
	int second = value - minute * 60;

	std::string str = "";
	str.append(isHourShow ? fullDouble(hour) : "");
	str.append(str != "" ? ":" : "");
	str.append(isMinuteShow || minute != 0 ? fullDouble(minute) : "");
	str.append(str != "" ? ":" : "");
	str.append(fullDouble(second));
	return str;
}

std::string UtilDate::fullDouble(int value)
{
	auto absValue = abs(value);
	if (absValue < 10)
	{
		return "0" + Value(absValue).asString();
	}
	else
	{
		return Value(absValue).asString();
	}
}
