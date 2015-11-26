#pragma execution_character_set("utf-8")

#include "HandleHead.h"
#include "ui/UILoadingBar.h"
#include "data/data/ManagerData.h"
#include "ui/ManagerUI.h"
#include "NodeHead.h"
#include "core/entity/ManagerEntity.h"

HandleHead::HandleHead() : _skin(nullptr), _vecNodeHeadMst({}), _vecNodeHeadMaid({}), _xPostionMoveTouchLast(0.0f), _indexNodeHeadTemp(-1)
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
	auto lengthVecDataEntityMst = handleDataEntity->getVecDataEntityMst().size();
	auto lengthVecDataEntityMaid = handleDataEntity->getVecDataEntityMaid().size();

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
			lengthVecDataEntity = isMst ? lengthVecDataEntityMst : lengthVecDataEntityMaid;
			if (lengthVecDataEntity > 1)//�ǹ����Ҵ���һ��ʱ��ӵ���¼�
			{
				layout->addTouchEventListener(CC_CALLBACK_2(HandleHead::onTouchMoveHead, this, isMst));//���ͷ���϶��¼�
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
	auto dictance = 0.0f;
	auto &vecNodeHead = isMst ? _vecNodeHeadMst : _vecNodeHeadMaid;
	auto length = (int)vecNodeHead.size();
	for (auto i = 0; i < length; i++)
	{
		auto nodeHead = vecNodeHead.at(i);
		if (nodeHead->getIndexDataEntity() == indexTo)
		{
			break;
		}
		if (i != 0)
		{
			auto nodeHeadLast = vecNodeHead.at(i - 1);
			dictance += nodeHeadLast->getLayoutBg()->getContentSize().width * nodeHeadLast->getScaleX() * 0.5f;
		}
		dictance += nodeHead->getLayoutBg()->getContentSize().width * nodeHead->getScaleX() * 0.5f;
	}
	if (dictance == 0.0f)
	{
		return;
	}
	auto duration = 0.4f;
	auto durationCallMove = 0.01f;
	auto xOffset = dictance / (duration / durationCallMove);
	xOffset = isMst ? -xOffset : xOffset;
	auto actionMoveNodeHead = RepeatForever::create(Sequence::createWithTwoActions(DelayTime::create(durationCallMove), CallFunc::create(CC_CALLBACK_0(HandleHead::moveNodeHead, this, isMst, xOffset))));
	actionMoveNodeHead->setTag(1);
	auto layout = (Layout *)_skin->getChildByName(isMst ? "layoutHeadMst" : "layoutHeadMaid");
	layout->runAction(actionMoveNodeHead);
	layout->runAction(Sequence::create(DelayTime::create(duration), CallFunc::create([layout]
	{
		layout->stopActionByTag(1);
	}), CallFunc::create(CC_CALLBACK_0(HandleHead::dealOverMoveNodeHead, this, isMst, false)), nullptr));
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
			auto isScaleBigger = (xOffset < 0.0f && isMst) || (xOffset > 0.0f && !isMst);//������������Ů��ʱ���ű��
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

	auto isPush = (isLeft && isMst) || (!isLeft && !isMst);//������������Ů��
	auto isShift = (isLeft && !isMst) || (!isLeft && isMst);//����Ů�ͻ����ҹ���

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

	if (isOut && _indexNodeHeadTemp != -1)
	{
		vecNodeHead.erase(index);
		index = isPush && !isShift ? 0 : (int)vecNodeHead.size() - 1;
		_indexNodeHeadTemp = -1;
	}

	if (_indexNodeHeadTemp == -1)
	{
		nodeHead = vecNodeHead.at(index);
		auto nodeHeadTemp = nodeHead->clone();
		nodeHead->getParent()->addChild(nodeHeadTemp);
		isPush && !isShift ? vecNodeHead.pushBack(nodeHeadTemp) : vecNodeHead.insert(0, nodeHeadTemp);

		_indexNodeHeadTemp = vecNodeHead.getIndex(nodeHeadTemp);

		auto indexBefore = isPush && !isShift ? _indexNodeHeadTemp - 1 : _indexNodeHeadTemp + 1;
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
	if (_indexNodeHeadTemp != -1)
	{
		auto &vecNodeHead = isMst ? _vecNodeHeadMst : _vecNodeHeadMaid;
		auto nodeHeadTemp = vecNodeHead.at(_indexNodeHeadTemp);
		auto xPostion = nodeHeadTemp->getPositionX();
		auto wSize = nodeHeadTemp->getParent()->getContentSize().width;
		if (xPostion >= 0.0f && xPostion <= wSize)//temp���ڲ�
		{
			_indexNodeHeadTemp = vecNodeHead.size() - 1 - _indexNodeHeadTemp;
			nodeHeadTemp = vecNodeHead.at(_indexNodeHeadTemp);
		}
		vecNodeHead.erase(_indexNodeHeadTemp);
		_indexNodeHeadTemp = -1;
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
		auto indexDataEntityMaid = ManagerData::getInstance()->getHandleDataEntity()->getIndexMaid();
		if (indexDataEntityShow != indexDataEntityMaid)
		{
			auto func = [isActive]()
			{
				ManagerUI::getInstance()->notify(ID_OBSERVER::HANDLE_ENTITY, TYPE_OBSERVER_HANDLE_ENTITY::DEAL_ROUND_OVER, true);//����غϽ���
			};
			auto isSwitchSuccess = false;
			ManagerEntity::getInstance()->getMaid()->switchEntity(indexDataEntityShow, isSwitchSuccess, func);//Entity�ڲ�����switchEntityʱ��Ҫ�ֶ�����DealRoundOver���л���һ��
			if (isSwitchSuccess && isActive)
			{
				ManagerData::getInstance()->getHandleDataEntity()->getDataEntityMaid()->setAttribute(IdAttribute::ENTITY_ENERGY, 0);//��������
			}
			if (!isSwitchSuccess && !isActive)//δ�ɹ��ҷ�����
			{
				func();
			}
		}
	}
}
