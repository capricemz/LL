#pragma execution_character_set("utf-8")

#ifndef __COMMON_UTIL_UTIL_STRING_H__
#define __COMMON_UTIL_UTIL_STRING_H__

#include "cocos2d.h"
#include <string>
#include <vector>

using namespace std;

typedef vector<string> VectorString;
typedef vector<int32_t> VectorInt32;

class UtilString
{
public:
	static int utf8CharLen(char firstByte);
	static int utf8Strlen(const char *str);
	static string utf8StrSub(const string &str, int startChar, int numChar);
	static VectorString split(const string &str, const string &delims = ",", uint32_t maxSplits = 0);
	static string combi(const VectorInt32 &ve, const string &delims);
	static void stringReplace(string &s1, const string &s2, const string &s3);

public:
	UtilString();
	~UtilString();
	
private:

};

#endif
