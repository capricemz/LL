#pragma execution_character_set("utf-8")

#include "HandleHead.h"
#include "ui/UILoadingBar.h"
#include "data/data/ManagerData.h"
#include "ui/ManagerUI.h"
#include "NodeHead.h"

HandleHead::HandleHead() : _skin(nullptr), _vecNodeHeadMst({}), _vecNodeHeadMaid({}), _xPostionBeganNodeHead(0.0f), _isInserted(false)
{
}

HandleHead::~HandleHead()
{
	ManagerUI::getInstance()->detach(this);
	_vecNodeHeadMaid.clear();
	_vecNodeHeadMst.clear();
	_skin = nullptr;
}

bool HandleHead::init()
{
	auto isInit = false;
	do
	{
		idObserverSet(ID_OBSERVER::HANDLE_HEAD);
		ManagerUI::getInstance()->attach(this);

		isInit = true;
	} while (0);
	return isInit;
}

void HandleHead::updateBySubject(va_list values)
{
	auto type = va_arg(values, TYPE_OBSERVER_HANDLE_HEAD);
	if (type == TYPE_OBSERVER_HANDLE_HEAD::UPDATE_HP)
	{
		auto isMst = va_arg(values, bool);
		updateBarHp(isMst, 0);
	}
	else if (type == TYPE_OBSERVER_HANDLE_HEAD::UPDATE_HP_ALL)
	{
		auto isMst = va_arg(values, bool);
		for (auto i = 0; i < ENTITY_BATTLE_MAX; i++)
		{
			updateBarHp(isMst, i);
		}
	}
	else if (type == TYPE_OBSERVER_HANDLE_HEAD::UPDATE_ENERGY)
	{
		auto isMst = va_arg(values, bool);
		updateBarEnergy(isMst);
	}
}

void HandleHead::setSkin(Layout *skin)
{
	_skin = skin;

	for (int i = 0; i < 6; i++)
	{
		auto index = i % 3;
		auto isMst = i < 3;

		auto layout = (Layout *)_skin->getChildByName(isMst ? "layoutHeadMst" : "layoutHeadMaid");
		layout->addTouchEventListener(CC_CALLBACK_2(HandleHead::onTouchMoveHead, this, isMst));//添加头像拖动事件

		auto nodeHead = NodeHead::create();
		nodeHead->setInfo(isMst, index);
		layout->addChild(nodeHead);
		
		auto scale = 0.0f;
		auto postion = Vec2::ZERO;
		auto nodeHeadLast = index == 0 ? nullptr : (isMst ? _vecNodeHeadMst.at(_vecNodeHeadMst.size() - 1) : _vecNodeHeadMaid.at(_vecNodeHeadMaid.size() - 1));
		nodeHeadScalePostionGet(false, index, nodeHead, nodeHeadLast, scale, postion);
		nodeHead->setScale(scale);
		nodeHead->setPosition(postion);

		nodeHead->updateAll();
		
		isMst ? _vecNodeHeadMst.pushBack(nodeHead) : _vecNodeHeadMaid.pushBack(nodeHead);
	}
	
	for (size_t i = 0; i < 2; i++)
	{
		auto isMst = i < 1;
		updateBarEnergy(isMst);
	}
}

cocos2d::Vec2 HandleHead::getPostionHeadIcon(const int &type, const int &index)
{
	auto isMst = type == 1;
	auto vec = isMst ? _vecNodeHeadMst : _vecNodeHeadMaid;
	CCASSERT(vec.size() > index, "HandleHead::getPostionHeadIcon vec.size() <= index");
	auto nodeHead = vec.at(index);
	auto postion = nodeHead->convertToWorldSpace(nodeHead->getLayoutBg()->getPosition());
	return postion;
}

void HandleHead::switchHead()
{

}

void HandleHead::onTouchMoveHead(Ref *ref, Widget::TouchEventType type, const bool &isMst)
{
	auto layout = (Layout *)ref;
	if (type == Widget::TouchEventType::BEGAN)
	{
		recordPostionBegan(isMst);
	}
	else if (type == Widget::TouchEventType::MOVED)
	{
		auto touchBeganPostion = layout->getTouchBeganPosition();
		auto touchMovePostion = layout->getTouchMovePosition();
		auto offset = touchMovePostion - touchBeganPostion;
		moveNodeHead(isMst, offset);
	}
	else
	{
		auto touchBeganPostion = layout->getTouchBeganPosition();
		auto touchEndPostion = layout->getTouchEndPosition();
		auto offsetOver = touchEndPostion - touchBeganPostion;
		dealOverMoveNodeHead(offsetOver);
	}
}

void HandleHead::resetSkin()
{
	for (int i = 0; i < 6; i++)
	{
		auto index = i % 3;
	}
}

void HandleHead::updateBarHp(const bool &isMst, const int &indexNodeHead)
{
	auto vecNodeHead = isMst ? _vecNodeHeadMst : _vecNodeHeadMaid;
	if (vecNodeHead.size() > indexNodeHead)
	{
		auto nodeHead = vecNodeHead.at(indexNodeHead);
		nodeHead->updateBarHp();
	}
}

void HandleHead::nodeHeadScalePostionGet(const bool &isMove, const int &index, NodeHead *nodeHead, NodeHead *nodeHeadLast, float &scale, Vec2 &postion)
{
	auto scaleMax = 1.0f;
	auto scaleMin = 0.6f;
	auto isMst = nodeHead->getIsMst();
	auto sizeParent = nodeHead->getParent()->getContentSize();

	if (index == 0)
	{
		scale = scaleMax;
		auto wSize = nodeHead->getLayoutBg()->getContentSize().width * scale;
		if (isMst)
		{
			postion = Vec2(wSize * 0.5f, sizeParent.height);
		}
		else
		{
			postion = Vec2(sizeParent.width - wSize * 0.5f, 0.0f);
		}
	}
	else
	{
		scale = scaleMin;
		auto xPositionLast = nodeHeadLast->getPositionX();
		auto wSizeLast = nodeHeadLast->getLayoutBg()->getContentSize().width * nodeHeadLast->getScaleX();
		if (isMove && index == 1)
		{
			scale = scaleMin + abs(xPositionLast - _xPostionBeganNodeHead) / wSizeLast * (scaleMax - scaleMin);
		}
		auto wSize = nodeHead->getLayoutBg()->getContentSize().width * scale;
		if (isMst)
		{
			postion = Vec2(xPositionLast + wSizeLast * 0.5f + wSize * 0.5f, sizeParent.height);
		}
		else
		{
			postion = Vec2(xPositionLast - wSizeLast * 0.5f - wSize * 0.5f, 0.0f);
		}
	}

	/*if (postion.x > vecPostionNodeHeadMst[0].x && postion.x < vecPostionNodeHeadMst[1].x)
	{
		auto k = (1.0f - 0.55f) / (vecPostionNodeHeadMst[0].x - vecPostionNodeHeadMst[1].x);
		auto b = (vecPostionNodeHeadMst[0].x * 0.55f - vecPostionNodeHeadMst[1].x * 1.0f) / (vecPostionNodeHeadMst[0].x - vecPostionNodeHeadMst[1].x);
		auto scale = k * postion.x + b;
		setScale(scale);
		/ *setPositionX(vecPostionNodeHeadMst[1].x + (postion.x - vecPostionNodeHeadMst[1].x) / getScaleX());* /
	}*/
}

void HandleHead::updateBarEnergy(const bool &isMst)
{
	auto name = isMst ? "layoutEnergyMst" : "layoutEnergyMaid";
	auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
	auto dataEntity = isMst ? handleDataEntity->getDataEntityMst() : handleDataEntity->getDataEntityMaid();

	auto energy = dataEntity->getAttribute(IdAttribute::ENTITY_ENERGY);
	auto energyMax = dataEntity->getAttribute(IdAttribute::ENTITY_ENERGY_MAX);

	auto layout = (Layout *)_skin->getChildByName(name);
	auto bar = (LoadingBar *)layout->getChildByName("barEnergy");
	bar->setPercent(((float)energy / (float)energyMax) * 100.0f);
}

void HandleHead::recordPostionBegan(const bool &isMst)
{
	auto vecNodeHead = isMst ? _vecNodeHeadMst : _vecNodeHeadMaid;
	_xPostionBeganNodeHead = vecNodeHead.at(0)->getPositionX();
}

void HandleHead::moveNodeHead(const bool &isMst, const Vec2 &offset)
{
	if (offset.x == 0.0f)
	{
		return;
	}

	auto vecNodeHead = isMst ? _vecNodeHeadMst : _vecNodeHeadMaid;
	auto length = (int)vecNodeHead.size();
	
	if ((offset.x < 0.0f && isMst) || (offset.x > 0.0f && !isMst))//向左怪物或向右女仆
	{
		auto nodeHead = vecNodeHead.at(0);
		bool isOut = false;
		auto sizeParent = nodeHead->getParent()->getContentSize();
		auto sizeNodeHead = nodeHead->getLayoutBg()->getContentSize();
		if (isMst)
		{
			auto xBorder = nodeHead->getPositionX() + sizeNodeHead.width * nodeHead->getScaleX() * 0.5f;
			isOut = xBorder < 0.0f;
		}
		else
		{
			auto xBorder = nodeHead->getPositionX() - sizeNodeHead.width * nodeHead->getScaleX() * 0.5f;
			isOut = xBorder > sizeParent.width;
		}
		if (isOut && _isInserted)
		{
			if (isMst)
			{
				_vecNodeHeadMst.swap(0, length - 1);
				_vecNodeHeadMst.erase(0);
				vecNodeHead = _vecNodeHeadMst;
			}
			else
			{
				_vecNodeHeadMaid.swap(0, length - 1);
				_vecNodeHeadMaid.erase(0);
				vecNodeHead = _vecNodeHeadMaid;
			}
			length = (int)vecNodeHead.size();
			_isInserted = false;
		}
		if (!_isInserted)
		{
			nodeHead = vecNodeHead.at(0);
			auto nodeHeadTemp = nodeHead->clone();
			nodeHead->getParent()->addChild(nodeHeadTemp);
			isMst ? _vecNodeHeadMst.pushBack(nodeHeadTemp) : _vecNodeHeadMaid.pushBack(nodeHeadTemp);
			vecNodeHead = isMst ? _vecNodeHeadMst : _vecNodeHeadMaid;
			length = (int)vecNodeHead.size();
			_isInserted = true;
		}
	}
	else if ((offset.x < 0.0f && !isMst) || (offset.x > 0.0f && isMst))//向左女仆或向右怪物
	{
		auto nodeHead = vecNodeHead.at(length - 1);
		bool isOut = false;
		auto sizeParent = nodeHead->getParent()->getContentSize();
		auto sizeNodeHead = nodeHead->getLayoutBg()->getContentSize();
		if (isMst)
		{
			auto xBorder = nodeHead->getPositionX() - sizeNodeHead.width * nodeHead->getScaleX() * 0.5f;
			isOut = xBorder > sizeParent.width;
		}
		else
		{
			auto xBorder = nodeHead->getPositionX() + sizeNodeHead.width * nodeHead->getScaleX() * 0.5f;
			isOut = xBorder < 0.0f;
		}
		if (isOut && _isInserted)
		{
			if (isMst)
			{
				_vecNodeHeadMst.swap(0, length - 1);
				_vecNodeHeadMst.erase(length - 1);
				vecNodeHead = _vecNodeHeadMst;
			}
			else
			{
				_vecNodeHeadMaid.swap(0, length - 1);
				_vecNodeHeadMaid.erase(length - 1);
				vecNodeHead = _vecNodeHeadMaid;
			}
			length = (int)vecNodeHead.size();
			_isInserted = false;
		}
		if (!_isInserted)
		{
			nodeHead = vecNodeHead.at(length - 1);
			auto nodeHeadTemp = nodeHead->clone();
			nodeHead->getParent()->addChild(nodeHeadTemp);
			isMst ? _vecNodeHeadMst.insert(0, nodeHeadTemp) : _vecNodeHeadMaid.insert(0, nodeHeadTemp);
			vecNodeHead = isMst ? _vecNodeHeadMst : _vecNodeHeadMaid;
			length = (int)vecNodeHead.size();
			_isInserted = true;
		}
	}
	
	for (auto i = 0; i < length; i++)
	{
		auto nodeHead = vecNodeHead.at(i);
		log("``````````HandleHead::moveNodeHead nodeHead.getScaleX:%s", Value(nodeHead->getScaleX()).asString().c_str());
		auto scale = 1.0f;
		auto postion = Vec2(_xPostionBeganNodeHead + offset.x, nodeHead->getPositionY());
		if (i != 0)
		{
			auto nodeHeadLast = isMst ? _vecNodeHeadMst.at(i - 1) : _vecNodeHeadMaid.at(i - 1);
			nodeHeadScalePostionGet(true, i, nodeHead, nodeHeadLast, scale, postion);
		}
		nodeHead->setScale(scale);
		nodeHead->setPosition(postion);
	}
}

void HandleHead::dealOverMoveNodeHead(const Vec2 &offsetOver)
{

	_xPostionBeganNodeHead = 0.0f;
}
