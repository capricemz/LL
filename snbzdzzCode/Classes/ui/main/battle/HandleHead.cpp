#pragma execution_character_set("utf-8")

#include "HandleHead.h"
#include "ui/UILoadingBar.h"
#include "data/data/ManagerData.h"
#include "ui/ManagerUI.h"
#include "NodeHead.h"
#include "core/entity/ManagerEntity.h"

HandleHead::HandleHead() :
	_skin(nullptr),
	_vecNodeHeadMst({}),
	_vecNodeHeadMaid({}),
	_xPostionMoveTouchLast(0.0f),
	_dictanceMoved(0.0f),
	_indexNodeHeadTempMst(-1),
	_indexNodeHeadTempMaid(-1)
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
	else if (type == TYPE_OBSERVER_HANDLE_HEAD::SWITCH_NODE_HEAD_TO)
	{
		auto isMst = va_arg(values, bool);
		auto indexTo = va_arg(values, int);
		switchNodeHeadTo(isMst, indexTo);
	}
	else if (type == TYPE_OBSERVER_HANDLE_HEAD::SWITCH_LAYOUT_HEAD_MAID_TOUCHABLE)
	{
		auto isTouchEnabled = va_arg(values, bool);
		switchLayoutHeadMaidTouchable(isTouchEnabled);
	}
}

void HandleHead::setSkin(Layout *skin)
{
	_skin = skin;

	auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();

	Layout *layout = nullptr;
	int lengthVecDataEntity = 0;
	auto widthTotal = 0.0f;
	for (int i = 0; i < ENTITY_BATTLE_MAX * 2; i++)
	{
		auto index = i % ENTITY_BATTLE_MAX;
		auto isMst = i < ENTITY_BATTLE_MAX;

		if (index == 0)
		{
			widthTotal = 0.0f;
			layout = (Layout *)_skin->getChildByName(isMst ? "layoutHeadMst" : "layoutHeadMaid");
			layout->setTouchEnabled(false);
			lengthVecDataEntity = handleDataEntity->getLengthVecDataEntity(isMst);
			if (lengthVecDataEntity > 1)//非怪物且大于一个时添加点击事件
			{
				layout->addTouchEventListener(CC_CALLBACK_2(HandleHead::onTouchMoveHead, this, isMst));//添加头像拖动事件
			}
		}

		if (index < lengthVecDataEntity)
		{
			auto nodeHead = NodeHead::create();
			nodeHead->setInfo(isMst, index);
			nodeHead->updateAll();
			/*nodeHead->setName("nodeHead" + Value(i).asString());*/
			layout->addChild(nodeHead);

			auto &vecNodeHead = isMst ? _vecNodeHeadMst : _vecNodeHeadMaid;
			vecNodeHead.pushBack(nodeHead);

			auto scale = 0.0f;
			auto postion = Vec2::ZERO;
			nodeHeadScalePostionGet(index, isMst, scale, postion);
			nodeHead->setScale(scale);
			nodeHead->setPosition(postion);

			widthTotal += nodeHead->getLayoutBg()->getContentSize().width * nodeHead->getScaleX();
		}

		if (index == ENTITY_BATTLE_MAX - 1)
		{
			auto size = layout->getContentSize();
			auto deltaWidth = size.width - widthTotal;
			size.width = widthTotal;
			layout->setContentSize(size);
			if (!isMst && deltaWidth != 0.0f)
			{
				for (auto child : layout->getChildren())
				{
					child->setPositionX(child->getPositionX() - deltaWidth);
				}
			}
		}
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
	auto size = nodeHead->getLayoutBg()->getContentSize();
	auto postionFix = Vec2(0.0f, isMst ? -0.5f * size.height : 0.5f * size.height);
	auto postion = nodeHead->getParent()->convertToWorldSpace(nodeHead->getPosition() + postionFix);
	return postion;
}

void HandleHead::switchNodeHeadTo(const bool &isMst, const int &indexTo)
{
	_dictanceMoved = 0.0f;
	auto dictance = 0.0f;
	auto &vecNodeHead = isMst ? _vecNodeHeadMst : _vecNodeHeadMaid;
	auto length = (int)vecNodeHead.size();
	auto isSuccess = false;
	for (auto i = 0; i < length; i++)
	{
		auto nodeHead = vecNodeHead.at(i);
		if (i != 0)
		{
			auto nodeHeadLast = vecNodeHead.at(i - 1);
			dictance += nodeHeadLast->getLayoutBg()->getContentSize().width * nodeHeadLast->getScaleX() * 0.5f;//前一个的一半

			dictance += nodeHead->getLayoutBg()->getContentSize().width * nodeHead->getScaleX() * 0.5f;//当前的一半

			if ((indexTo == ENTITY_BATTLE_MAX && nodeHead->getDataEntity()->getIsAlive()) || nodeHead->getIndexDataEntity() == indexTo)
			{
				isSuccess = true;
				break;
			}
		}
	}
	if (!isSuccess)
	{
		ManagerUI::getInstance()->notify(ID_OBSERVER::HANDLE_ENTITY, TYPE_OBSERVER_HANDLE_ENTITY::DEAL_ROUND_OVER, true);//处理回合结束
		return;
	}
	auto speed = 244.0f;
	auto durationCallMove = Director::getInstance()->getAnimationInterval();
	
	auto duration = dictance / speed;
	auto xOffset = dictance / (duration / durationCallMove);
	xOffset = isMst ? -xOffset : xOffset;
	auto layout = (Layout *)_skin->getChildByName(isMst ? "layoutHeadMst" : "layoutHeadMaid");
	auto actionCallFunc = CallFunc::create([this, isMst, xOffset, layout, dictance]()
	{
		if (_dictanceMoved < dictance)
		{
			moveNodeHead(isMst, xOffset);
			_dictanceMoved += abs(xOffset);
		}
		else
		{
			layout->stopActionByTag(1);
			dealOverMoveNodeHead(isMst, false);
		}
	});
	auto actionMoveNodeHead = RepeatForever::create(Sequence::createWithTwoActions(DelayTime::create(durationCallMove), actionCallFunc));
	actionMoveNodeHead->setTag(1);
	layout->runAction(actionMoveNodeHead);
}



void HandleHead::onTouchMoveHead(Ref *ref, Widget::TouchEventType type, const bool &isMst)
{
	auto layout = (Layout *)ref;
	if (type == Widget::TouchEventType::BEGAN)
	{
		_xPostionMoveTouchLast = layout->getTouchBeganPosition().x;
	}
	else if (type == Widget::TouchEventType::MOVED)
	{
		auto touchMovePostion = layout->getTouchMovePosition();
		auto xOffset = touchMovePostion.x - _xPostionMoveTouchLast;
		moveNodeHead(isMst, xOffset);
		_xPostionMoveTouchLast = touchMovePostion.x;
	}
	else
	{
		/*auto touchBeganPostion = layout->getTouchBeganPosition();
		auto touchEndPostion = layout->getTouchEndPosition();
		auto offsetOver = touchEndPostion - touchBeganPostion;*/
		dealOverMoveNodeHead(isMst, true);
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

void HandleHead::updateBarEnergy(const bool &isMst)
{
	auto name = isMst ? "layoutEnergyMst" : "layoutEnergyMaid";
	auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
	auto dataEntity = isMst ? handleDataEntity->getDataEntityMst() : handleDataEntity->getDataEntityMaid();

	auto energy = dataEntity->getAttribute(IdAttribute::ENTITY_ENERGY);
	auto energyMax = dataEntity->getAttribute(IdAttribute::ENTITY_ENERGY_MAX);

	auto layout = (Layout *)_skin->getChildByName(name);
	layout->setTouchEnabled(false);
	auto bar = (LoadingBar *)layout->getChildByName("barEnergy");
	bar->setPercent(((float)energy / (float)energyMax) * 100.0f);
}

void HandleHead::switchLayoutHeadMaidTouchable(const bool &isTouchEnabled)
{
	auto layout = (Layout *)_skin->getChildByName("layoutHeadMaid");
	layout->setTouchEnabled(isTouchEnabled);
}

void HandleHead::nodeHeadScalePostionGet(const int &index, const bool &isMst, float &scale, Vec2 &postion, const float &xOffset /*= 0.0f*/)
{
	auto scaleMax = 1.0f;
	auto scaleMin = 0.6f;

	auto &vecNodeHead = isMst ? _vecNodeHeadMst : _vecNodeHeadMaid;
	auto nodeHead = vecNodeHead.at(index);
	auto sizeParent = nodeHead->getParent()->getContentSize();

	if (index == 0)
	{
		scale = scaleMax;
		if (xOffset != 0.0f)
		{
			postion = Vec2(nodeHead->getPositionX() + xOffset, nodeHead->getPositionY());
		}
		else
		{
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
	}
	else
	{
		scale = scaleMin;
		auto nodeHeadLast = vecNodeHead.at(index - 1);
		auto xPositionLast = nodeHeadLast->getPositionX();
		auto wSizeLast = nodeHeadLast->getLayoutBg()->getContentSize().width * nodeHeadLast->getScaleX();
		if (xOffset != 0.0f && index == 1)
		{
			auto isScaleBigger = (xOffset < 0.0f && isMst) || (xOffset > 0.0f && !isMst);//向左怪物或向右女仆时缩放变大
			auto scaleChange = abs(xOffset) / wSizeLast * (scaleMax - scaleMin);
			scale = nodeHead->getScale() + (isScaleBigger ? scaleChange : -scaleChange);
			if (scale < scaleMin)
			{
				scale = scaleMin;
			}
			else if (scale > scaleMax)
			{
				scale = scaleMax;
			}
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
}

void HandleHead::moveNodeHead(const bool &isMst, const float &xOffset)
{
	if (xOffset == 0.0f)
	{
		return;
	}

	dealNodeHeadTemp(isMst, xOffset < 0.0f);

	auto &vecNodeHead = isMst ? _vecNodeHeadMst : _vecNodeHeadMaid;
	auto length = (int)vecNodeHead.size();
	for (auto i = 0; i < length; i++)
	{
		auto nodeHead = vecNodeHead.at(i);
		auto scale = 0.0f;
		auto postion = Vec2::ZERO;
		nodeHeadScalePostionGet(i, isMst, scale, postion, xOffset);
		nodeHead->setScale(scale);
		nodeHead->setPosition(postion);
	}
}

void HandleHead::dealNodeHeadTemp(const bool &isMst, const bool &isLeft)
{
	auto &vecNodeHead = isMst ? _vecNodeHeadMst : _vecNodeHeadMaid;

	auto isPush = (isLeft && isMst) || (!isLeft && !isMst);//向左怪物或向右女仆
	auto isShift = (isLeft && !isMst) || (!isLeft && isMst);//向左女仆或向右怪物

	auto index = isPush && !isShift ? 0 : (int)vecNodeHead.size() - 1;
	
	auto nodeHead = vecNodeHead.at(index);
	bool isOut = false;
	auto sizeParent = nodeHead->getParent()->getContentSize();
	auto sizeNodeHead = nodeHead->getLayoutBg()->getContentSize();
	
	if (isLeft)
	{
		auto xBorder = nodeHead->getPositionX() + sizeNodeHead.width * nodeHead->getScaleX() * 0.5f;
		isOut = xBorder < 0.0f;
	}
	else
	{
		auto xBorder = nodeHead->getPositionX() - sizeNodeHead.width * nodeHead->getScaleX() * 0.5f;
		isOut = xBorder > sizeParent.width;
	}
	auto &indexNodeHeadTemp = isMst ? _indexNodeHeadTempMst : _indexNodeHeadTempMaid;
	if (isOut && indexNodeHeadTemp != -1)
	{
		vecNodeHead.erase(index);
		index = isPush && !isShift ? 0 : (int)vecNodeHead.size() - 1;
		indexNodeHeadTemp = -1;
	}

	if (indexNodeHeadTemp == -1)
	{
		nodeHead = vecNodeHead.at(index);
		auto nodeHeadTemp = nodeHead->clone();
		nodeHead->getParent()->addChild(nodeHeadTemp);
		isPush && !isShift ? vecNodeHead.pushBack(nodeHeadTemp) : vecNodeHead.insert(0, nodeHeadTemp);

		indexNodeHeadTemp = vecNodeHead.getIndex(nodeHeadTemp);

		auto indexBefore = isPush && !isShift ? indexNodeHeadTemp - 1 : indexNodeHeadTemp + 1;
		auto nodeHeadTempBefore = vecNodeHead.at(indexBefore);
		auto scale = nodeHeadTempBefore->getScale();
		auto postion = nodeHeadTempBefore->getPosition();
		auto wSize = nodeHeadTempBefore->getLayoutBg()->getContentSize().width * nodeHeadTempBefore->getScaleX();
		postion = isLeft ? Vec2(postion.x + wSize, postion.y) : Vec2(postion.x - wSize, postion.y);
		nodeHeadTemp->setScale(scale);
		nodeHeadTemp->setPosition(postion);
	}
}

void HandleHead::dealOverMoveNodeHead(const bool &isMst, const bool &isActive)
{
	auto &indexNodeHeadTemp = isMst ? _indexNodeHeadTempMst : _indexNodeHeadTempMaid;
	if (indexNodeHeadTemp != -1)
	{
		auto &vecNodeHead = isMst ? _vecNodeHeadMst : _vecNodeHeadMaid;
		auto nodeHeadTemp = vecNodeHead.at(indexNodeHeadTemp);
		auto xPostion = nodeHeadTemp->getPositionX();
		auto wSize = nodeHeadTemp->getParent()->getContentSize().width;
		if (xPostion >= 0.0f && xPostion <= wSize)//temp在内部
		{
			indexNodeHeadTemp = vecNodeHead.size() - 1 - indexNodeHeadTemp;
			nodeHeadTemp = vecNodeHead.at(indexNodeHeadTemp);
		}
		vecNodeHead.erase(indexNodeHeadTemp);
		indexNodeHeadTemp = -1;
		nodeHeadTemp->removeFromParent();

		auto length = (int)vecNodeHead.size();
		for (auto i = 0; i < length; i++)
		{
			auto nodeHead = vecNodeHead.at(i);
			auto scale = 0.0f;
			auto postion = Vec2::ZERO;
			nodeHeadScalePostionGet(i, isMst, scale, postion);
			nodeHead->setScale(scale);
			nodeHead->setPosition(postion);
		}

		auto nodeHead = vecNodeHead.at(0);
		auto indexDataEntityShow = nodeHead->getIndexDataEntity();
		auto handleDataEntity = ManagerData::getInstance()->getHandleDataEntity();
		auto indexDataEntityCurrent = isMst ? handleDataEntity->getIndexMst() : handleDataEntity->getIndexMaid();
		if (indexDataEntityShow != indexDataEntityCurrent)
		{
			auto func = []()
			{
				ManagerUI::getInstance()->notify(ID_OBSERVER::HANDLE_ENTITY, TYPE_OBSERVER_HANDLE_ENTITY::DEAL_ROUND_OVER, true);//处理回合结束
			};
			auto isSwitchSuccess = false;
			auto managerEntity = ManagerEntity::getInstance();
			auto entity = isMst ? (Entity *)managerEntity->getMonster() : (Entity *)managerEntity->getMaid();
			entity->switchEntity(indexDataEntityShow, isSwitchSuccess, func);//Entity内部调用switchEntity时需要手动调用DealRoundOver已切换下一轮
			if (isSwitchSuccess && isActive)
			{
				auto dataEntity = isMst ? handleDataEntity->getDataEntityMst() : handleDataEntity->getDataEntityMaid();
				dataEntity->setAttribute(IdAttribute::ENTITY_ENERGY, 0);//消耗能量
			}
			if (!isSwitchSuccess && !isActive)//未成功且非主动
			{
				func();
			}
		}
	}
}
