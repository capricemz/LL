#include <iostream>
#include "UtilRandom.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "base/ccMacros.h"
#include "base/CCValue.h"

using namespace std;

float UtilRandom::GOLDE_RATIO_X = (sqrt(5.0) - 1) * 0.5f;
float UtilRandom::GOLDE_RATIO_Y = (3 - sqrt(5.0)) * 0.5f;

UtilRandom::UtilRandom()
{
}


UtilRandom::~UtilRandom()
{
}

void UtilRandom::initRandomSeed()
{
	srand((unsigned)time(nullptr));
}

/*
生成[0,1)之间的浮点随机数
*/
float UtilRandom::random()
{
	return (float)rand() / (float)RAND_MAX;
}
/*
以value值为中心点数获得波动随机数
@param value 中心点数
@param wave 波动值,值为0时使用GOLDE_RATIO_Y作为wave值计算
@return 波动随机数
*/
float UtilRandom::randomWave( float value, float wave )
{
	auto r = random();
	return value * (1 - wave + 2 * wave * r);
}
/*
在valueMin值至valueMax值之间获得随机值
@param valueMin 随机下限值
@param valueMax 随机上限值
@return 随机值
*/
float UtilRandom::randomBewteen( float valueMin, float valueMax )
{
	auto r = random();
	return valueMin + (valueMax - valueMin) * r;
}
/*
根据probabilityDistribution数组中的概率分布获得随机值
@param probabilityDistribution
@return 随机值
*/
int UtilRandom::randomPitchUpon( vector<float> probabilityDistribution )
{
	int i,l = probabilityDistribution.size();
	for (i=0;i<l;i++) 
	{
		if(i > 0)
		{
			probabilityDistribution[i] = probabilityDistribution[i] + probabilityDistribution[i-1];
		}
	}

	CCASSERT(probabilityDistribution[i - 1] != 1.0f, "`````````` UtilRandom::randomPitchUpon total probability is not one");

	for (i=0;i<l;i++) 
	{
		auto r = random();
		if(r < probabilityDistribution[i])
		{
			break;
		}
	}
	return i;
}
