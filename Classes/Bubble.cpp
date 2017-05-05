#include"Bubble.h"
#include<math.h>

extern vector<vector<int>> gLogicMap;

bool Bubble::init()
{
	ArmatureDataManager::getInstance()->addArmatureFileInfo("BubbleAnimation.exportJson");
	armature = Armature::create("BubbleAnimation");
	this->setVisible(false);
	armature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(Bubble::animationEvent, this,
		std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	this->addChild(armature);
	mapPreState = 1;
	return true;
}

void Bubble::animationEvent(Armature * pArmature, MovementEventType movementType, const std::string& movementIDstr)
{
	const char* movementTag = movementIDstr.c_str();
	auto logicMapLayer = LogicMapLayer::create();

	if (strcmp(movementTag, "BubbleExplodeAnimation") == 0)
	{
		if (movementType == START)
		{
			for (auto hero : heroVec)
			{
				pair<int, int> heroLogicPoint = logicMapLayer->getLogicPosicion(hero->getPosition().x, hero->getPosition().y);
				pair<int, int> bubbleLogicPoint = logicMapLayer->getLogicPosicion(this->getPosition().x, this->getPosition().y);
				if (heroLogicPoint.first == bubbleLogicPoint.first)
				{
					if (abs(heroLogicPoint.second - bubbleLogicPoint.second) < 2)
						hero->getBaseFSM()->changeToDead();
				}
				else if (heroLogicPoint.second == bubbleLogicPoint.second)
				{
					if (abs(heroLogicPoint.first - bubbleLogicPoint.first) < 2)
						hero->getBaseFSM()->changeToDead();
				}
				
			}
			for (auto monster : monsterVec)
			{
				pair<int, int> monsterLogicPoint = logicMapLayer->getLogicPosicion(monster->getPosition().x, monster->getPosition().y);
				pair<int, int> bubbleLogicPoint = logicMapLayer->getLogicPosicion(this->getPosition().x, this->getPosition().y);
				if (monsterLogicPoint.first == bubbleLogicPoint.first)
				{
					if (abs(monsterLogicPoint.second - bubbleLogicPoint.second) < 2)
						monster->getBaseFSM()->changeToDead();
				}
				else if (monsterLogicPoint.second == bubbleLogicPoint.second)
				{
					if (abs(monsterLogicPoint.first - bubbleLogicPoint.first) < 2)
						monster->getBaseFSM()->changeToDead();
				}

			}
		}
		else if (movementType == COMPLETE)
		{
			if (mapPreState == 1)
				gLogicMap[changeLogicPoint.first][changeLogicPoint.second] = 1;
		}
	}	
}

void Bubble::startBubble()
{
	this->setVisible(true);
}