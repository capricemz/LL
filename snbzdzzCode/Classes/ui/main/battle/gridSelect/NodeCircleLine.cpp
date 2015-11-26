#pragma execution_character_set("utf-8")

#include "NodeCircleLine.h"
#include "data/define/DefinesRes.h"
#include "core/grid/ManagerGrid.h"
#include "ui/ManagerUI.h"

NodeCircleLine::NodeCircleLine() : _indexCurrent(-1), _indexLast(-1), _imageLineWidth(0.0f)
{
}

NodeCircleLine::~NodeCircleLine()
{
}

bool NodeCircleLine::init()
{
	auto isInit = false;
	do 
	{
		CC_BREAK_IF(!Node::init());

		isInit = true;
	} while (0);
	return isInit;
}

void NodeCircleLine::onTouchBegan(const int &indexGrid, const Vec2 &postionLayoutWorld, const Vec2 &postionTouchBegan)
{
	_indexCurrent = indexGrid;

	auto postion = getParent()->convertToNodeSpace(postionLayoutWorld);

	drawCircleLinePoint(postion);

	auto spriteLine = getChildByName("spriteLine" + Value(_indexCurrent).asString());
	auto positionBegan = convertToWorldSpace(spriteLine->getPosition());
	auto postionDelta = postionTouchBegan - positionBegan;
	spriteLine->setRotation(postionDelta.getAngle() * -180.0f / acos(-1.0));
	spriteLine->setScaleX(postionDelta.getLength() / _imageLineWidth);

	/*ManagerUI::getInstance()->notify(ID_OBSERVER::LAYER_GRID_SELECT, TYPE_OBSERVER_LAYER_GRID_SELECT::RUN_MAID_GRID_SCALE_BIG, indexGrid, nullptr);*/
}

void NodeCircleLine::onTouchMoved(const Vec2 &postionTouchMove)
{
	auto spriteLine = getChildByName("spriteLine" + Value(_indexCurrent != -1 ? _indexCurrent : _indexLast).asString());
	auto positionBegan = convertToWorldSpace(spriteLine->getPosition());
	auto postionDelta = postionTouchMove - positionBegan;
	auto angleLast = postionDelta.getAngle();
	log("````````` angleLast:%s", Value(angleLast).asString().c_str());
	auto rotation = postionDelta.getAngle() * -180.0f / acos(-1.0);
	spriteLine->setRotation(rotation);
	spriteLine->setScaleX(postionDelta.getLength() / _imageLineWidth);

	Vec2 postionLayoutWorldMoveOver;
	if (_indexCurrent != -1)//当前格子内
	{
		ManagerUI::getInstance()->notify(ID_OBSERVER::LAYER_GRID_SELECT, TYPE_OBSERVER_LAYER_GRID_SELECT::RUN_MAID_GRID_SCALE_SMALL, _indexCurrent, nullptr);

		auto isGridMoveOut = ManagerGrid::getInstance()->getIsGridMoveOut(_indexCurrent, postionTouchMove, postionLayoutWorldMoveOver);
		if (isGridMoveOut)
		{
			int indexLast;
			auto isGridMoveToLast = ManagerGrid::getInstance()->getIsGridMoveToLast(indexLast, rotation, positionBegan);
			if (isGridMoveToLast)
			{
				clearCircleLinePoint();
				_indexLast = indexLast;
				_indexCurrent = -1;

				auto managerGrid = ManagerGrid::getInstance();
				managerGrid->setAroundGridCanMoveOver(_indexLast);
			}
			else
			{
				_indexLast = _indexCurrent;
				_indexCurrent = -1;

				auto managerGrid = ManagerGrid::getInstance();

				auto gridMaidSelect = (Grid *)managerGrid->getDicGridMaidSelect().at(_indexLast);
				gridMaidSelect->setVisible(false);
				auto dataGrid = gridMaidSelect->getDataGrid();
				managerGrid->pushDataGridMaidSelected(dataGrid);

				auto indexGridSelected = managerGrid->getVecDataGridMaidSelected().size() - 1;
				auto gridMaidSelected = (Grid *)managerGrid->getDicGridMaidSelected().at(indexGridSelected);
				gridMaidSelected->setDataGrid(dataGrid);

				managerGrid->setAroundGridCanMoveOver(_indexLast);

				ManagerUI::getInstance()->notify(ID_OBSERVER::HANDLE_GRID, TYPE_OBSERVER_HANDLE_GRID::RUN_ACTION_GRID_SELECTED_MOVE_FROM_SELECT, indexGridSelected, _indexLast);//调用格子飞行特效
			}
		}
	}
	else//不在当前格子内
	{
		int indexGridMoveOver;
		auto isGridMoveOver = ManagerGrid::getInstance()->getIsGridMoveOver(postionTouchMove, postionLayoutWorldMoveOver, indexGridMoveOver);
		if (isGridMoveOver)
		{
			if (_indexLast != indexGridMoveOver)//若划入其他个格子
			{
				//画上一点与目标点连线
				auto positionBegan = convertToWorldSpace(spriteLine->getPosition());
				auto postionDelta = postionLayoutWorldMoveOver - positionBegan;
				spriteLine->setRotation(postionDelta.getAngle() * -180.0f / acos(-1.0));
				spriteLine->setScaleX(postionDelta.getLength() / _imageLineWidth);
				//画目标点圈线等
				onTouchBegan(indexGridMoveOver, postionLayoutWorldMoveOver, postionTouchMove);
			}
			else//若划入当前选中格子
			{
				ManagerUI::getInstance()->notify(ID_OBSERVER::LAYER_GRID_SELECT, TYPE_OBSERVER_LAYER_GRID_SELECT::RUN_MAID_GRID_MOVE_FROM_ACTION_ONE_BACK, indexGridMoveOver);//调用格子飞行特效
				ManagerGrid::getInstance()->popDataGridMaidSelected();
				_indexLast = getIndexLast();
				_indexCurrent = indexGridMoveOver;
			}
		}
	}
}

void NodeCircleLine::onTouchEndedCanceled()
{
	if (_indexCurrent != -1)
	{
		ManagerUI::getInstance()->notify(ID_OBSERVER::LAYER_GRID_SELECT, TYPE_OBSERVER_LAYER_GRID_SELECT::RUN_MAID_GRID_SCALE_SMALL, _indexCurrent, nullptr);
	}
	auto isVecDataGridMaidSelectedFull = ManagerGrid::getInstance()->getIsVecDataGridMaidSelectedFull();
	if (isVecDataGridMaidSelectedFull && _indexCurrent == -1)
	{
		auto managerGrid = ManagerGrid::getInstance();
		managerGrid->clearVecDataGridMaidSelected();
		managerGrid->linkDataGridSelected();
		auto managerUI = ManagerUI::getInstance();
		managerUI->notify(ID_OBSERVER::LAYER_BATTLE, TYPE_OBSERVER_LAYER_BATTLE::HIDE_LAYER_GRID_SELECT);
		managerUI->notify(ID_OBSERVER::HANDLE_HEAD, TYPE_OBSERVER_HANDLE_HEAD::SWITCH_LAYOUT_HEAD_MAID_TOUCHABLE, false);
	}
	else
	{
		ManagerUI::getInstance()->notify(ID_OBSERVER::LAYER_GRID_SELECT, TYPE_OBSERVER_LAYER_GRID_SELECT::RUN_MAID_GRID_MOVE_FROM_ACTION_ALL_BACK);//调用格子飞行特效
		ManagerGrid::getInstance()->clearVecDataGridMaidSelected();
	}
	removeFromParent();
}

void NodeCircleLine::drawCircleLinePoint(const Vec2 &postion)
{
	auto spriteCircle = Sprite::createWithSpriteFrameName(RES_IMAGES_MAIN_CIRCLE_LINE_CIRCLE_PNG);
	spriteCircle->setName("spriteCircle" + Value(_indexCurrent).asString());
	spriteCircle->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	spriteCircle->setPosition(postion);
	addChild(spriteCircle);
	
	/*_imageViewLine = ImageView::create(RES_IMAGES_MAIN_CIRCLE_LINE_LINE_PNG, Widget::TextureResType::PLIST);
	_imageViewLine->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	_imageViewLine->setPosition(postion);
	_imageViewLine->setScale9Enabled(true);
	_imageViewLine->setCapInsets(Rect(3.0f, 3.0f, _imageViewLine->getContentSize().width - 6.0f, _imageViewLine->getContentSize().height - 6.0f));
	addChild(_imageViewLine);
	_imageLineWidth = _imageViewLine->getContentSize().width - 3.0f;*/

	auto spriteLine = Scale9Sprite::createWithSpriteFrameName(RES_IMAGES_MAIN_CIRCLE_LINE_LINE_PNG);
	spriteLine->setName("spriteLine" + Value(_indexCurrent).asString());
	spriteLine->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	spriteLine->setPosition(postion);
	spriteLine->setPreferredSize(spriteLine->getContentSize());
	spriteLine->setCapInsets(Rect(3.0f, 3.0f, spriteLine->getContentSize().width - 6.0f, spriteLine->getContentSize().height - 6.0f));
	addChild(spriteLine);
	_imageLineWidth = spriteLine->getContentSize().width - 3.0f;

	auto spritePoint = Sprite::createWithSpriteFrameName(RES_IMAGES_MAIN_CIRCLE_LINE_POINT_PNG);
	spritePoint->setName("spritePoint" + Value(_indexCurrent).asString());
	spritePoint->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	spritePoint->setPosition(postion);
	addChild(spritePoint);
}

void NodeCircleLine::clearCircleLinePoint()
{
	auto spriteCircle = getChildByName("spriteCircle" + Value(_indexCurrent).asString());
	spriteCircle->removeFromParent();

	auto spriteLine = getChildByName("spriteLine" + Value(_indexCurrent).asString());
	spriteLine->removeFromParent();

	auto spritePoint = getChildByName("spritePoint" + Value(_indexCurrent).asString());
	spritePoint->removeFromParent();
}

int NodeCircleLine::getIndexLast()
{
	auto vecDataGridMaidSelected = ManagerGrid::getInstance()->getVecDataGridMaidSelected();
	if (vecDataGridMaidSelected.size() < 1)
	{
		return -1;
	}
	auto dataGridMaidSelected = vecDataGridMaidSelected.at(vecDataGridMaidSelected.size() - 1);
	auto indexGridMaidSelect = dataGridMaidSelected->getIndexGrid();
	return indexGridMaidSelect;
}
