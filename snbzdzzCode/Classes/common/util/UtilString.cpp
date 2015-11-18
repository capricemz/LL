#pragma execution_character_set("utf-8")

#include "UtilString.h"

const unsigned char kFirstBitMask = 128; // 1000000
const unsigned char kSecondBitMask = 64; // 0100000
const unsigned char kThirdBitMask = 32; // 0010000
const unsigned char kFourthBitMask = 16; // 0001000
const unsigned char kFifthBitMask = 8; // 0000100

int UtilString::utf8CharLen(char firstByte)
{
	std::string::difference_type offset = 1;

	if (firstByte & kFirstBitMask) // This means the first byte has a value greater than 127, and so is beyond the ASCII range.
	{
		if (firstByte & kThirdBitMask) // This means that the first byte has a value greater than 224, and so it must be at least a three-octet code point.
		{
			if (firstByte & kFourthBitMask) // This means that the first byte has a value greater than 240, and so it must be a four-octet code point.
				offset = 4;
			else
				offset = 3;
		}
		else
		{
			offset = 2;
		}
	}
	return offset;
}

int UtilString::utf8Strlen(const char *str)
{
	if (str == nullptr)
	{
		return 0;
	}

	int byteLength = static_cast<int>(strlen(str));

	int length = 0;

	int index = 0;
	while (index < byteLength)
	{
		char ch = str[index];

		length++;

		index++;

		if (index >= byteLength)
		{
			break;
		}

		if (ch & 0x80)
		{
			ch <<= 1;
			while (ch & 0x80)
			{
				index++;
				ch <<= 1;
			}
		}
	}

	return length;
}

string UtilString::utf8StrSub(const string &str, int startChar, int numChar)
{
	if (str == "")
	{
		return "";
	}

	int startIndex = 0;
	while (startChar > 0)
	{
		startIndex += utf8CharLen(str[startIndex]);
		startChar--;
	}

	int currentIndex = startIndex;
	int strLength = str.size();
	while (numChar > 0 && currentIndex <= strLength)
	{
		currentIndex += utf8CharLen(str[currentIndex]);
		numChar--;
	}
	return str.substr(startChar, currentIndex - startChar);
}

VectorString UtilString::split(const string &str, const string &delim /* =  */, uint32_t maxSplits /* = 0 */)
{
	VectorString ret;

	uint32_t numSplits = 0;

	size_t start = 0;
	size_t pos = 0;
	do
	{
		pos = str.find_first_of(delim, start);
		if (pos == start)
		{
			ret.push_back("");
			start = pos + 1;
		}
		else if (pos == string::npos || (maxSplits && numSplits == maxSplits))
		{
			ret.push_back(str.substr(start));
			break;
		}
		else
		{
			ret.push_back(str.substr(start, pos - start));
			start = pos + 1;
		}

		++numSplits;

	} while (pos != string::npos);

	return ret;
}

string UtilString::combi(const VectorInt32 &ve, const string &delim)
{
	string str = "";
	VectorInt32::const_iterator it = ve.begin();
	if (it != ve.end())
	{
		char buff[20] = {};
		string tempStr = "";
		sprintf(buff, "%d", *it);
		tempStr = buff;
		str += tempStr;
		it++;
	}

	for (; it != ve.end(); ++it)
	{
		char buff[20] = {};
		string tempStr = "";
		sprintf(buff, "%d", *it);
		tempStr = buff;
		str += ":";
		str += tempStr;
	}

	return str;
}
//s:Ä¿±ê×Ö·û´®  search:ÐèÒªÌæ»»µÄ×Ö·û´® replace:Ìæ»»³ÉµÄ×Ö·û´®
void UtilString::stringReplace(std::string &s, const std::string &search, const std::string &replace)
{
	const size_t psize = search.size();
	const size_t nsize = replace.size();

	for (size_t pos = s.find(search, 0); pos != std::string::npos; pos = s.find(search, pos + nsize))
	{
		s.replace(pos, psize, replace);
	}
}

UtilString::UtilString()
{
}

UtilString::~UtilString()
{
}
