#include <iostream>
#include "UtilRandom.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

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
����[0,1)֮��ĸ��������
*/
float UtilRandom::random()
{
	return (float)rand() / (float)RAND_MAX;
}
/*
��valueֵΪ���ĵ�����ò��������
@param value ���ĵ���
@param wave ����ֵ,ֵΪ0ʱʹ��GOLDE_RATIO_Y��Ϊwaveֵ����
@return ���������
*/
float UtilRandom::randomWave( float value, float wave )
{
	auto r = random();
	return value * (1 - wave + 2 * wave * r);
}
/*
��valueMinֵ��valueMaxֵ֮�������ֵ
@param valueMin �������ֵ
@param valueMax �������ֵ
@return ���ֵ
*/
float UtilRandom::randomBewteen( float valueMin, float valueMax )
{
	auto r = random();
	r = valueMin + (valueMax - valueMin) * r;
	return r == valueMax ? r - 0.0001f : r;
}
/*
����probabilityDistribution�����еĸ��ʷֲ�������ֵ
@param probabilityDistribution
@return ���ֵ
*/
int UtilRandom::randomPitchUpon( vector<float> probabilityDistribution )
{
	/*int i,l = probabilityDistribution.size();
	for (i=0;i<l;i++) 
	{
		if(i > 0)
		{
			probabilityDistribution[i] = probabilityDistribution[i] + probabilityDistribution[i-1];
		}
	}
	try
	{
		if(probabilityDistribution[i-1] != 1)
		{
			log("total probability is not one");
		}
	}
	catch (exception * ex)
	{
		delete ex;
	}
	for (i=0;i<l;i++) 
	{
		auto r = random();
		if(r < probabilityDistribution[i])
		{
			break;
		}
	}
	return i;*/
	return 0;
}
