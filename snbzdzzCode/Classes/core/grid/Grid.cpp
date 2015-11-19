#pragma execution_character_set("utf-8")

#include "Grid.h"
#include "data/define/DefinesRes.h"
#include "ManagerGrid.h"
#include "data/config/ManagerCfg.h"

using namespace cocostudio::timeline;

Grid::Grid() : 
	_skin(nullptr), 
	_indexGrid(0), 
	_dataGrid(nullptr), 
	_isCanMoveOver(false), 
	_durationTurn(0.0f), 
	_isNeedTurn(false), 
	_isCanScaleBig(true), 
	_isCanScaleSmall(false)
{
}

Grid::~Grid()
{
	_skin = nullptr;
	CC_SAFE_RELEASE_NULL(_dataGrid);
}

bool Grid::init()
{
	auto isInit = false;
	do 
	{
		CC_BREAK_IF(!Node::init());

		createSkin();

		isInit = true;
	} while (0);
	return isInit;
}

void Grid::createDataGrid()
{
	CC_SAFE_RELEASE_NULL(_dataGrid);
	_dataGrid = ManagerData::getInstance()->getHandleDataGrid()->getDataGrid();
	_dataGrid->setIndexGrid(_indexGrid);
	CC_SAFE_RETAIN(_dataGrid);
}

void Grid::createDataGridSkill(const bool &isMst)
{
	auto managerData = ManagerData::getInstance();
	auto handleDataEntity = managerData->getHandleDataEntity();
	auto dataEntity = isMst ? handleDataEntity->getDataEntityMst() : handleDataEntity->getDataEntityMaid();
	auto vecSkillInfo = dataEntity->vecSkillActiveInfoGet();
	auto idSkill = vecSkillInfo[0];
	auto indexSkill = vecSkillInfo[1];
	_dataGrid->setIdSkill(idSkill);
	_dataGrid->setIndexSkill(indexSkill);
	_dataGrid->updateSkillEffect();
	updateSkinAttribute();
}

void Grid::setDataGrid(DataGrid *dataGrid)
{
	CC_SAFE_RELEASE_NULL(_dataGrid);
	_dataGrid = dataGrid;
	CC_SAFE_RETAIN(_dataGrid);
	updateSkinAttribute();
}

void Grid::updateSkinAttribute()
{
	auto spriteBgp = (Sprite *)_skin->getChildByName("spriteBgp");
	spriteBgp->removeAllChildren();
	//
	auto count = 0;
	vector<int> countLineBefores = {};//到当前行为止的总数
	vector<float> lineWidths = {};
	vector<float> lineBottom = {};
	auto idAttributeLast = IdAttribute::GRID_DAMAGE_PHYSICAL;
	auto dic = _dataGrid->getDicAttribute();
	for (auto var : dic)
	{
		auto idAttribute = var.first;
		auto value = var.second;
		auto remainder = count % 3;
		if (remainder != 0 && value && idAttributeLast != idAttribute)//若余数不为0且有属性值且与之前属性不同
		{
			count += 3 - remainder;//换行显示
		}
		idAttributeLast = idAttribute;
		while (value--)
		{
			auto cfgAttribute = ManagerCfg::getInstance()->getDicCfgAttribute()[(int)idAttribute];
			if (cfgAttribute.urlPic != "")
			{
				auto node = Sprite::createWithSpriteFrameName(cfgAttribute.urlPic);
				spriteBgp->addChild(node);
				auto line = count / 3;
				auto nodeHeight = node->getContentSize().height;
				auto nodeWidth = node->getContentSize().width;
				auto countLineBeforeLast = line > 0 ? countLineBefores[line - 1] : 0;
				if ((int)countLineBefores.size() < line + 1)
				{
					countLineBefores.push_back(1 + countLineBeforeLast);
				}
				else
				{
					countLineBefores[line]++;
				}
				auto lineTopLast = line > 0 ? lineBottom[line - 1] : 0.0f;
				if ((int)lineBottom.size() < line + 1)
				{
					lineBottom.push_back(nodeHeight + lineTopLast);
				}
				else if(lineBottom[line] < nodeHeight + lineTopLast)
				{
					lineBottom[line] = nodeHeight;
				}
				if ((int)lineWidths.size() < line + 1)
				{
					lineWidths.push_back(nodeWidth);
				}
				else
				{
					lineWidths[line] += nodeWidth;
				}
				count++;
			}
		}
	}
	//
	auto dicCondition = _dataGrid->getDicAttributeCondition();
	if (dicCondition.size() != 0)
	{
		auto remainder = count % 3;
		if (remainder != 0)//若余数不为0且有属性值且与之前属性不同
		{
			count += 3 - remainder;//换行显示
		}
		auto node = Sprite::createWithSpriteFrameName("images/main/icon/zd.png");//for test
		spriteBgp->addChild(node);
		auto line = count / 3;
		auto nodeHeight = node->getContentSize().height;
		auto nodeWidth = node->getContentSize().width;
		auto countLineBeforeLast = line > 0 ? countLineBefores[line - 1] : 0;
		if ((int)countLineBefores.size() < line + 1)
		{
			countLineBefores.push_back(1 + countLineBeforeLast);
		}
		else
		{
			countLineBefores[line]++;
		}
		auto lineTopLast = line > 0 ? lineBottom[line - 1] : 0.0f;
		if ((int)lineBottom.size() < line + 1)
		{
			lineBottom.push_back(nodeHeight + lineTopLast);
		}
		else if (lineBottom[line] < nodeHeight + lineTopLast)
		{
			lineBottom[line] = nodeHeight;
		}
		if ((int)lineWidths.size() < line + 1)
		{
			lineWidths.push_back(nodeWidth);
		}
		else
		{
			lineWidths[line] += nodeWidth;
		}
		count++;
	}
	//
	auto xPostion = 0.0f;
	auto yPostion = 0.0f;
	count = 0;
	auto children = spriteBgp->getChildren();
	for (auto line = 0; line < (int)countLineBefores.size();)
	{
		auto countLineBefore = countLineBefores[line];
		if (count == 0 || count == countLineBefore)
		{
			if (count != 0)
			{
				line++;
			}
			xPostion = spriteBgp->getContentSize().width / 2.0f - lineWidths[line] / 2.0f;//行居中行起始x位置
			yPostion = spriteBgp->getContentSize().height / 2.0f + lineBottom[lineBottom.size() - 1] / 2.0f - (line > 0 ? lineBottom[line - 1] : 0.0f);//行居中对齐行y位置
		}
		auto node = (Node *)children.at(count);
		xPostion += node->getContentSize().width / 2.0f;
		node->setPositionX(xPostion);
		xPostion += node->getContentSize().width / 2.0f;
		node->setPositionY(yPostion - node->getContentSize().height / 2.0f);
		count++;
		if (count >= (int)children.size())
		{
			break;
		}
	}
}

Layout * Grid::getLayoutTouch()
{
	return (Layout *)_skin->getChildByName("layoutTouch");
}

void Grid::updateContent(const bool &isBack)
{
	auto actionTimeline = (ActionTimeline *)_skin->getActionByTag(_skin->getTag());
	if (_dataGrid->getAttribute(IdAttribute::GRID_GOLD) != 0)
	{
		actionTimeline->play("animationGold", false);
	}
	else if (_dataGrid->getAttribute(IdAttribute::GRID_STONE) != 0)
	{
		actionTimeline->play("animationStone", false);
	}
	else if (_dataGrid->getAttribute(IdAttribute::GRID_ICE) != 0)
	{
		actionTimeline->play("animationIce", false);
	}
	else if (_dataGrid->getAttribute(IdAttribute::GRID_TRAP) != 0)
	{
		actionTimeline->play("animationTrap", false);
	}
	else
	{
		actionTimeline->play(isBack ? "animationBack" : "animationFront", false);
	}
}

void Grid::moveFrom(const Vec2 &postion, const bool &isBack, const float &scaleBegan, const float &scaleEnd, const Vec2 & offsetEnd, const function<void()> &func /*= nullptr*/)
{
	setLocalZOrder(1);

	setVisible(true);

	auto postionFrom = convertToNodeSpace(postion);
	_skin->setPosition(postionFrom);

	updateContent(isBack);

	_skin->setScale(scaleBegan);
	
	Vector<FiniteTimeAction *> vecActions;

	auto postionDelta = postionFrom - offsetEnd;
	auto postionDeltaNomalized = postionDelta.getNormalized();

	float xMid, xBezier1, yBezier1, xBezier2, yBezier2;
	if (postionDeltaNomalized.x == 0 && postionDeltaNomalized.y == 0)
	{
		xMid = 0.0f;
		xBezier1 = 0.0f;
		yBezier1 = 0.0f;
		xBezier2 = 0.0f;
		yBezier2 = 0.0f;
	}
	else if (postionDeltaNomalized.x == 0)
	{
		xMid = postionDeltaNomalized.x > 0 ? 50.0f : -50.0f;
		xBezier1 = postionDeltaNomalized.y > 0 ? 50.0f : -50.0f;
		yBezier1 = 0.0f;
		xBezier2 = postionDeltaNomalized.y > 0 ? -50.0f : 50.0f;
		yBezier2 = 0.0f;
	}
	else if (postionDeltaNomalized.y == 0)
	{
		xMid = postionDeltaNomalized.x > 0 ? 50.0f : -50.0f;
		xBezier1 = 0.0f;
		yBezier1 = postionDeltaNomalized.x > 0 ? 50.0f : -50.0f;
		xBezier2 = 0.0f;
		yBezier2 = postionDeltaNomalized.x > 0 ? -50.0f : 50.0f;
	}
	else
	{
		xMid = postionDeltaNomalized.x > 0 ? 50.0f : -50.0f;
		auto kNDelta = -postionDeltaNomalized.x / postionDeltaNomalized.y;
		kNDelta *= postionDeltaNomalized.y < 0 ? 1.0f : -1.0f;
		xBezier1 = postionDeltaNomalized.x > 0 ? 50.0f : -50.0f;
		yBezier1 = kNDelta * xBezier1;
		xBezier2 = postionDeltaNomalized.x > 0 ? -50.0f : 50.0f;
		yBezier2 = kNDelta * xBezier2;
	}

	auto postionMid = postionDelta + postionDeltaNomalized * xMid;
	ccBezierConfig cfg;
	cfg.controlPoint_1 = postionDelta + Vec2(xBezier1, yBezier1);
	cfg.controlPoint_2 = postionMid;
	cfg.endPosition = postionMid;
	auto actionToMid = Spawn::createWithTwoActions(BezierTo::create(0.2f, cfg), ScaleTo::create(0.2f, 1.0f));
	vecActions.pushBack(actionToMid);

	ccBezierConfig cfg1;
	cfg1.controlPoint_1 = postionMid + Vec2(xBezier2, yBezier2);
	cfg1.controlPoint_2 = offsetEnd;
	cfg1.endPosition = offsetEnd;
	auto actoinToEnd = Spawn::createWithTwoActions(BezierTo::create(0.3f, cfg1), ScaleTo::create(0.3f, scaleEnd));
	vecActions.pushBack(actoinToEnd);

	auto actionCallFunc = CallFunc::create([func, this]()
	{
		setLocalZOrder(0);
		_skin->getScale();
		if (func != nullptr)
		{
			func();
		}
	});
	vecActions.pushBack(actionCallFunc);

	auto actoinSequence = Sequence::create(vecActions);
	_skin->runAction(actoinSequence);
}

void Grid::turn(const function<void()> &func /*= nullptr*/)
{
	auto actionDelay = DelayTime::create(0.1f);
	auto actionTurn = CallFunc::create([=]()
	{
		auto actionTimeline = (ActionTimeline *)_skin->getActionByTag(_skin->getTag());
		actionTimeline->play("animationTurn", false);
	});
	auto postionEnd = _skin->getPosition();
	auto actionToSmall = Spawn::createWithTwoActions(MoveTo::create(_durationTurn * 0.2f, postionEnd + Vec2(20.0f, 20.0f)), ScaleTo::create(_durationTurn * 0.2f, 0.4f));
	auto actionToBig = Spawn::createWithTwoActions(MoveTo::create(_durationTurn * 0.6f, Vec2(-20.0f, -20.0f)), ScaleTo::create(_durationTurn * 0.6f, 1.1f));
	auto actionToNormal = Spawn::createWithTwoActions(MoveTo::create(_durationTurn * 0.2f, Vec2::ZERO), ScaleTo::create(_durationTurn * 0.2f, 1.0f));
	auto actionCallFunc = CallFunc::create([func, this]()
	{
		/*auto actionTimeline = (ActionTimeline *)_skin->getActionByTag(_skin->getTag());
		actionTimeline->gotoFrameAndPause(actionTimeline->getEndFrame() - 1);*/
		if (func != nullptr)
		{
			func();
		}
	});
	auto actionSequenceTurn = Sequence::create(actionDelay, actionTurn, actionToSmall, actionToBig, actionToNormal, actionCallFunc, nullptr);
	_skin->runAction(actionSequenceTurn);
}

void Grid::throwTo(const Vec2 &postion, const float &angleEnd, const function<void ()> &func /*= nullptr*/)
{
	auto postionTo = convertToNodeSpace(postion);
	auto actionThrow = Spawn::createWithTwoActions(EaseBackIn::create(RotateTo::create(0.6f, angleEnd)), EaseBackIn::create(MoveTo::create(0.6f, postionTo)));
	auto actionCallFunc = CallFunc::create([=]()
	{
		if (func != nullptr)
		{
			func();
		}
	});
	_skin->runAction(Sequence::create(actionThrow, actionCallFunc, nullptr));
}

void Grid::playSpecialSthGenerate(const function<void()> &func /*= nullptr*/)
{
	setVisible(true);

	auto actionTimeline = (ActionTimeline *)_skin->getActionByTag(_skin->getTag());
	if (_dataGrid->getAttribute(IdAttribute::GRID_GOLD) != 0)
	{
		actionTimeline->play("animationGoldGenerate", false);
	}
	else if (_dataGrid->getAttribute(IdAttribute::GRID_STONE) != 0)
	{
		actionTimeline->play("animationStoneGenerate", false);
	}
	else if (_dataGrid->getAttribute(IdAttribute::GRID_ICE) != 0)
	{
		actionTimeline->play("animationIceGenerate", false);
	}
	else if (_dataGrid->getAttribute(IdAttribute::GRID_TRAP) != 0)
	{
		actionTimeline->play("animationTrapGenerate", false);
	}
	actionTimeline->setLastFrameCallFunc([func, actionTimeline]()
	{
		if (func != nullptr)
		{
			func();
		}
		actionTimeline->setLastFrameCallFunc(nullptr);
	});
}

void Grid::playSpecialSthBeUse(const function<void()> &func /*= nullptr*/)
{
	setVisible(true);

	auto actionTimeline = (ActionTimeline *)_skin->getActionByTag(_skin->getTag());
	if (_dataGrid->getAttribute(IdAttribute::GRID_GOLD) != 0)
	{
		actionTimeline->play("animationGoldGet", false);
	}
	else if (_dataGrid->getAttribute(IdAttribute::GRID_STONE) != 0)
	{
		actionTimeline->play("animationStoneCrushed", false);
	}
	else if (_dataGrid->getAttribute(IdAttribute::GRID_ICE) != 0)
	{
		actionTimeline->play("animationIceMelting", false);
	}
	else if (_dataGrid->getAttribute(IdAttribute::GRID_TRAP) != 0)
	{
		actionTimeline->play("animationTrapDisarm", false);
	}
	actionTimeline->setLastFrameCallFunc([func, actionTimeline]()
	{
		if (func != nullptr)
		{
			func();
		}
		actionTimeline->setLastFrameCallFunc(nullptr);
	});
}

bool Grid::isCanMoveOver() const
{
	return _isCanMoveOver;
}

void Grid::scaleBig(const bool &isAlignTop /*= true*/, CallFunc *funcOver /*= nullptr*/)
{
	_isCanScaleBig = false;
	setLocalZOrder(1);
	auto duration = 0.17f;
	auto s = 3.0f;
	Vector<FiniteTimeAction *> vectorActions;
	auto spriteBgp = (Sprite *)_skin->getChildByName("spriteBgp");
	auto yNew = spriteBgp->getContentSize().height * (s - 1.0f) / 2.0f;
	auto scaleTo = ScaleTo::create(duration, s);
	auto moveTo = MoveTo::create(duration, Vec2(0.0f, isAlignTop ? -yNew : yNew));
	vectorActions.pushBack(Spawn::createWithTwoActions(scaleTo, moveTo));
	if (funcOver != nullptr)
	{
		vectorActions.pushBack(funcOver);
	}
	auto actionCallFunc = CallFunc::create([this]()
	{
		_isCanScaleSmall = true;
	});
	vectorActions.pushBack(actionCallFunc);
	_skin->runAction(Sequence::create(vectorActions));
}

void Grid::scaleSmall(CallFunc *funcOver /*= nullptr*/)
{
	_isCanScaleSmall = false;
	auto duration = 0.17f;
	Vector<FiniteTimeAction *> vectorActions;
	auto scaleTo = ScaleTo::create(duration, 1.0f);
	auto moveTo = MoveTo::create(duration, Vec2::ZERO);
	vectorActions.pushBack(Spawn::createWithTwoActions(scaleTo, moveTo));
	if (funcOver != nullptr)
	{
		vectorActions.pushBack(funcOver);
	}
	auto actionCallFunc = CallFunc::create([this]()
	{
		_isCanScaleBig = true;
		setLocalZOrder(0);
	});
	vectorActions.pushBack(actionCallFunc);
	_skin->runAction(Sequence::create(vectorActions));
}

void Grid::resetSkin()
{
	if (_skin == nullptr)
	{
		return;
	}
	_skin->stopActionsByFlags(1);
	_skin->setPosition(Vec2::ZERO);
	_skin->setScale(1.0f);
	_skin->setRotation(0.0f);
	auto actionTimeline = (ActionTimeline *)_skin->getActionByTag(_skin->getTag());
	actionTimeline->play("animationBack", false);
}

void Grid::resetSpecialSth()
{
	if (_dataGrid == nullptr)
	{
		return;
	}
	_dataGrid->setAttribute(IdAttribute::GRID_GOLD, 0);
	_dataGrid->setAttribute(IdAttribute::GRID_STONE, 0);
	_dataGrid->setAttribute(IdAttribute::GRID_ICE, 0);
	_dataGrid->setAttribute(IdAttribute::GRID_TRAP, 0);
}

bool Grid::getIsCard()
{
	if (!_dataGrid)
	{
		return false;
	}
	auto isGold = _dataGrid->getAttribute(IdAttribute::GRID_GOLD) != 0;
	auto isStone = _dataGrid->getAttribute(IdAttribute::GRID_STONE) != 0;
	auto isIce = _dataGrid->getAttribute(IdAttribute::GRID_ICE) != 0;
	auto isTrap = _dataGrid->getAttribute(IdAttribute::GRID_TRAP) != 0;
	return !isGold && !isStone && !isIce && !isTrap;
}

bool Grid::getIsNotCard()
{
	if (!_dataGrid)
	{
		return false;
	}
	auto isGold = _dataGrid->getAttribute(IdAttribute::GRID_GOLD) != 0;
	auto isStone = _dataGrid->getAttribute(IdAttribute::GRID_STONE) != 0;
	auto isIce = _dataGrid->getAttribute(IdAttribute::GRID_ICE) != 0;
	auto isTrap = _dataGrid->getAttribute(IdAttribute::GRID_TRAP) != 0;
	return isGold || isStone || isIce || isTrap;
}

void Grid::createSkin()
{
	_skin = CSLoader::createNode(RES_MODULES_MAIN_NODE_GRID_CSB);
	addChild(_skin);

	auto actionTimeline = CSLoader::createTimeline(RES_MODULES_MAIN_NODE_GRID_CSB);
	actionTimeline->play("animationBack", false);
	_skin->runAction(actionTimeline);

	auto animationInfoTurn = actionTimeline->getAnimationInfo("animationTurn");
	auto interval = Director::getInstance()->getAnimationInterval();
	_durationTurn = (animationInfoTurn.endIndex - animationInfoTurn.startIndex) * interval;
}
