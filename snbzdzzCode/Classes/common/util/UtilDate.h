#pragma execution_character_set("utf-8")

#ifndef __COMMON_UTIL_UTIL_DATE_H__
#define __COMMON_UTIL_UTIL_DATE_H__

#include "cocos2d.h"

USING_NS_CC;

class UtilDate
{
public:
	//格式化时间返回
	static std::string getCurrentTime(const char *format);
	//获取系统毫秒时间
	static double getMillSecond();
	//获取系统秒时间
	static double getSecond();
	//根据秒数获取时：分：秒格式字符
	static std::string timeFormat(double value, bool isHourShow = true, bool isMinuteShow = true);
	//将传入值填满两位
	static std::string fullDouble(int value);
	
private:

};

#endif